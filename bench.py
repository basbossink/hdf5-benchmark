from subprocess import call
import timeit
import csv
import statistics

if __name__ == '__main__':
    with open('bench.csv', 'w') as csvfile:
        bench_writer = csv.writer(csvfile)
        bench_writer.writerow(['NumberOfDataSets', 'AverageTime', 'StandardDeviation'])
        for i in range(1,8,2):
            numSets = 10**i
            t = timeit.Timer("call(['./a.out', str(%d)])" % numSets, setup="from subprocess import call") 
            data = t.repeat(repeat=5, number=1)
            bench_writer.writerow([numSets, statistics.mean(data), statistics.stdev(data)])
        
    
