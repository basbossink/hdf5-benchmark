#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <string.h>
#include "H5Cpp.h"

using namespace H5;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << "<input-path> <number of datasets to read>" << std::endl;
  }
  const H5std_string FILE_NAME(argv[1]);
  H5File file(FILE_NAME, H5F_ACC_RDONLY);
  int noDataSets = std::stoi(argv[2]);
  std::random_device randomDevice;
  std::mt19937 generator(randomDevice());
  std::uniform_int_distribution<> distribution(0, 99999);
  unsigned long totalSize{0};
  for(int i =0; i < noDataSets; i++) {
    const H5std_string DATASET_NAME(std::to_string(distribution(generator)));
    DataSet dataSet = file.openDataSet(DATASET_NAME);
    DataSpace dataspace = dataSet.getSpace();
    hsize_t dims[2];
    int ndims = dataspace.getSimpleExtentDims(dims, nullptr);
    size_t fieldSize = sizeof(char) * (dims[0] + 1);
    char* fieldValue = static_cast<char*>(malloc(fieldSize));
    memset(fieldValue, '\0', fieldSize);
    dataSet.read(fieldValue, PredType::C_S1, dataspace);
    totalSize += dims[0];
    free(fieldValue);
  }
  std::cout << "Read a total a " << totalSize << " characters." << std::endl;
  return 0;
}
