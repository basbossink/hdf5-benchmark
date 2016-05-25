library(ggplot2)
data <- read.csv('read_bench.csv')
x <- data$NumberOfDataSets
y <- data$AverageTime
sd <- data$StandardDeviation
svg(filename = "read_bench.svg")
qplot(x,y) + 
  geom_errorbar(aes(x = x, ymin = y - sd, ymax = y + sd), width = 0.25) + 
  geom_smooth(method = 'lm',formula= y ~ x) + 
  labs(title = "Time to read a random selection of dataset from a HDF5 file", 
       x = "Number of datasets read from file", 
       y = "Time (s)")
dev.off()