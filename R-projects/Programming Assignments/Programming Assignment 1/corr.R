library("data.table")


corr <- function(directory, threshold = 0)
{
  data_list <- lapply(file.path(directory,
  	list.files(path = directory, pattern="*.csv")),
  	data.table::fread)
  dataTable <- rbindlist(data_list)
  dataTable <- dataTable[complete.cases(dataTable),]
  dataTable <- dataTable[, .(nobs = .N,
  	correlation = cor(x = sulfate, y = nitrate)),
  by = ID][nobs > threshold]
  return(dataTable[, correlation])
}