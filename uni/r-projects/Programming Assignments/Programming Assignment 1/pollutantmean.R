library("data.table")

pollutantmean <- function(directory, pollutant, id = 1:332) {
  files <- paste0(directory, '/', formatC(id, width=3, flag="0"), ".csv" )
  data_list <- lapply(files, data.table::fread)
  dataTable <- rbindlist(data_list)
  if (c(pollutant) %in% names(dataTable))
  {
    return(dataTable[,
    	lapply(.SD, mean, na.rm = TRUE),
    	.SDcols = pollutant][[1]])
  } 
}