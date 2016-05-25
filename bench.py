from subprocess import call
import timeit
import csv
import statistics
import math
import numpy as np
with open('bench.csv', 'w') as csvfile:
    bench_writer = csv.writer(csvfile)
    bench_writer.writerow(['NumberOfDataSets', 'AverageTime', 'StandardDeviation'])
    for i in np.round(np.linspace(100, 1e6, 10)):
        t = timeit.Timer("call(['./a.out', str(%d)])" % i, setup="from subprocess import call") 
        data = t.repeat(repeat=5, number=1)
        bench_writer.writerow([i, statistics.mean(data), statistics.stdev(data)])
        
    
