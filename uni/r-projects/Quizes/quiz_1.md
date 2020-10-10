# QUIZ 1

## Question 1
----------
R was developed by statisticians working at
### Answer
The University of Auckland
#### Explanation
The R language was developed by Ross Ihaka and Robert Gentleman who were statisticians at the University of Auckland in New Zealand.


## Question 2
----------
The definition of free software consists of four freedoms (freedoms 0 through 3). Which of the following is NOT one of the freedoms that are part of the definition? Select all that apply.
### Answer
1. The freedom to prevent users from using the software for undesirable purposes.
2. The freedom to restrict access to the source code for the software.
3. The freedom to sell the software for any price.
#### Explanation
The four essential freedoms
A program is free software if the program's users have the four essential freedoms:
1. The freedom to run the program as you wish, for any purpose (freedom 0).
2. The freedom to study how the program works, and change it so it does your computing as you wish (freedom 1). Access to the source code is a precondition for this.
3. The freedom to redistribute copies so you can help others (freedom 2).
4. The freedom to distribute copies of your modified versions to others (freedom 3). By doing this you can give the whole community a chance to benefit from your changes. Access to the source code is a precondition for this.


## Question 3
----------
In R the following are all atomic data types EXCEPT: (Select all that apply)
### Answer
1. matrix
2. list
3. array
4. data frame
5. table
#### Explanation
R has six basic ('atomic') vector types: logical, integer, real, complex, string (or character) and raw.



## Question 4
----------
If I execute the expression `x <- 4L` in R, what is the class of the object `x` as determined by the `class()` function?
### Answer
integer


## Question 5
----------
What is the class of the object defined by `x <- c(4, TRUE)`?
### Answer
numeric
#### Explanation
The numeric class is the "lowest common denominator" here and so all elements will be coerced into that class.


## Question 6
----------
If I have two vectors `x <- c(1,3, 5)` and `y <- c(3, 2, 10)`, what is produced by the expression `cbind(x, y)`?
### Answer
a matrix with 2 columns and 3 rows


## Question 7
----------
A key property of vectors in R is that
### Answer
elements of a vector all must be of the same class


## Question 8
----------
Suppose I have a list defined as `x <- list(2, "a", "b", TRUE)`. What does `x[[2]]` give me? Select all that apply.l that apply.
### Answers
1. a character vector of length 1.
2. a character vector containing the letter "a"


## Question 9
----------
Suppose I have a vector `x <- 1:4` and a vector `y <- 2:3`. What is produced by the expression `x + y`?
### Answer
a numeric vector with elements 3,5,5,7


## Question 10
----------
Suppose I have a vector `x <- c(17, 14, 4, 5, 13, 12, 10)` and I want to set all elements of this vector that are greater than 10 to be equal to 4. What R code achieves this? Select all that apply.
### Answer
`[x >= 11] <- 4`
`x[x > 10] <- 4`


## Question 11
----------
In the dataset provided for this Quiz, what are the column names of the dataset? 
### Answer
```R
Ozone, Solar.R, Wind, Temp, Month, Day
```

## Question 12
----------
Extract the first 2 rows of the data frame and print them to the console. What does the output look like?
### Answer
```R
 Ozone Solar.R Wind Temp Month Day
1    41     190  7.4   67     5   1
2    36     118  8.0   72     5   2
```

## Question 13
----------
How many observations (i.e. rows) are in this data frame?
### Answer
`153`


## Question 14
----------
Extract the last 2 rows of the data frame and print them to the console. What does the output look like?
### Answer
```R
Ozone Solar.R Wind Temp Month Day
152    18     131  8.0   76     9  29
153    20     223 11.5   68     9  30
```


## Question 15
----------
What is the value of Ozone in the 47th row?
### Answer
`21`


## Question 16
----------
How many missing values are in the Ozone column of this data frame?
### Answer
`37`


## Question 17
----------
What is the mean of the Ozone column in this dataset? Exclude missing values (coded as `NA`) from this calculation.
### Answer
`42.1`



## Question 18
----------
Extract the subset of rows of the data frame where Ozone values are above 31 and Temp values are above 90. What is the mean of Solar.R in this subset?
### Answer
`212.8`



## Question 19
----------
What is the mean of "Temp" when "Month" is equal to 6? 
### Answer
`79.1`



## Question 20
----------
What was the maximum ozone value in the month of May (i.e. Month is equal to 5)?
### Answer
`115`
