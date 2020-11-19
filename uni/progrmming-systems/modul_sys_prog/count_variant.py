day = int(input("Day : "))
month = int(input("Month : "))
group = int(input("Group : "))

sq_day = day ** 2
cube_month = month ** 3
f_group = group ** 4
res = sq_day + cube_month * f_group
res1 = res % 111
res2 = res1 % 6

print("Your variant :  %d" % (res2+1))
