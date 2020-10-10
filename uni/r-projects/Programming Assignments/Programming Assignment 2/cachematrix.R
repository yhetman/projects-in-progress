## Put comments here that give an overall description of what your
## functions do

## Write a short comment describing this function


## This function creates a special "matrix" object hat can cache its inverse.
makeCacheMatrix <- function(x = matrix()) {
        cachematrix <- NULL
        
        ## set the value of the matrix
        set <- function( matrix )
        {
                x <<- matrix
                cachematrix <<- NULL
        }
        
        # get the value of the matrix
        get <- function() x
        
        ## set the value of the inverse matrix in cache
        setCacheMatrix <- function(inverse) cachematrix <<- inverse

        ## get the value of the inverse matrix
        getCacheMatrix <- function() cachematrix

    list(set = set, get = get, setCacheMatrix = setCacheMatrix, getCacheMatrix = getCacheMatrix)
}


## Write a short comment describing this function
## This function computes the inverse of the special
## "matrix" returned by `makeCacheMatrix` above. If the inverse has
##  already been calculated (and the matrix has not changed), then
##  `cacheSolve` should retrieve the inverse from the cache.
cacheSolve <- function(x, ...) {
        m <- x$getCacheMatrix()

        if( !is.null(m) )
        {
                message("getting cached data")
                return(m)
        }

        data <- x$get()
        m <- solve(data) %*% data
        x$setCacheMatrix(m)
        m
}
