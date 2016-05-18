#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "H5Cpp.h"

using namespace H5;
using boost::property_tree::ptree;
using boost::property_tree::write_json;

std::string createJsonString(int dataSetIndex) {
  const int randomSizes[] = { 2, 58, 38, 30, 26, 35, 8, 13, 33, 98, 1, 81, 17, 55, 87, 11, 82, 49, 21, 79 };
  ptree flinstones;
  flinstones.put("flinstones.fred.name", "Fred");
  flinstones.put("flinstones.fred.married-with", "Wilma");
  flinstones.put("flinstones.fred.friends-with", "Barney");
  flinstones.put("flinstones.barney.name", "Barney");
  flinstones.put("flinstones.barney.married-with", "Betty");
  flinstones.put("flinstones.barney.friends-with", "Fred");
  flinstones.put("flinstones.barney.random-fill", std::string(randomSizes[dataSetIndex % 20], 'a'));
  std::ostringstream buf; 
  write_json (buf, flinstones, false);
  std::string json = buf.str();
  return json;
}

int main(int argc, char* argv[]) {
  const H5std_string FILE_NAME("test.h5");
  H5File file(FILE_NAME, H5F_ACC_TRUNC);
  if (argc < 1) {
    std::cerr << "Usage: " << argv[0] << "<number of datasets>" << std::endl;
  }
  int noDataSets = std::stoi(argv[1]);
  for(int i =0; i < noDataSets; i++) {
    std::string payload = createJsonString(i);
    hsize_t dims[1] = { payload.size()};
    DataSpace dataSpace(1, dims);
    const H5std_string DATASET_NAME(std::to_string(i));
    DataSet dataSet = file.createDataSet(DATASET_NAME, PredType::C_S1, dataSpace);
    dataSet.write(payload, PredType::C_S1);
  }
  return 0;
}
