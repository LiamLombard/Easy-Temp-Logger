library(ggplot2)
library(reshape2)


file <- readLines("data.txt")
file <-gsub("t=", ",", file)
file <-gsub("&h=", ",", file)

writeLines(file, "data.csv")
data <- read.csv("data.csv")
colnames(data) <- c("time", "temp", "humid")
data$time <- as.POSIXct(data$time,origin="1970-01-01",tz="GMT-1")
data <- melt(data, id.vars="time")


plot <- ggplot(data, aes(x=time, y=value, colour = variable)) +
geom_line() +
xlab("Date") +
ylab("Temperature(Celcius) / Humidty(%)") +
theme(legend.title=element_blank()) +
scale_colour_discrete(labels=c("Temperature", "Humidity"))
print(plot)
dev.off()