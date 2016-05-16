library(ggplot2)
data <- read.csv('bench.csv')
x <- data$NumberOfDataSets
y <- data$AverageTime
sd <- data$StandardDeviation
svg(filename = "bench.svg")
qplot(x,y) + 
  geom_errorbar(aes(x = x, ymin = y - sd, ymax = y + sd), width = 0.25) + 
  geom_smooth(method = 'lm',formula= y ~ x) + 
  labs(title = "Time to write HDF5 file with a number of datasets", 
       x = "Number of datasets in file", 
       y = "Time (s)")
dev.off()