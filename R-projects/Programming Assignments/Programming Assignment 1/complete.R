complete <- function(directory, id= 1:332){
     ids = c()
     nobses = c()
     files = list.files(directory)
     
     for(each in id)
     {
         path = paste(directory, "/", files[i], sep = "")
         data = read.csv(path, header = TRUE)
         completeCases = data[complete.cases(data), ]
         ids =  c(ids, each)                    
         nobss = c(nobses, nrow(completeCases) )
     }
     data.frame(id = ids, nobs = nobses)
}