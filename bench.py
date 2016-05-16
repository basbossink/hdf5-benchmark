from subprocess import call
import timeit
import csv
import statistics
import math

with open('bench.csv', 'w') as csvfile:
    bench_writer = csv.writer(csvfile)
    bench_writer.writerow(['NumberOfDataSets', 'AverageTime', 'StandardDeviation'])
    for i in range(20, 61, 4):
        numSets = math.floor(math.pow(10, 0.1*i))
        t = timeit.Timer("call(['./a.out', str(%d)])" % numSets, setup="from subprocess import call") 
        data = t.repeat(repeat=5, number=1)
        bench_writer.writerow([numSets, statistics.mean(data), statistics.stdev(data)])
        
    
