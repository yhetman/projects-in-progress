import statistics as st
import math
import matplotlib.pyplot as plt

def dat(n):  
    b = 77
    M = 100000
    a0 = 8
    bvv = [0]*n
    a = [0]*(n+1)
    a[0] = a0
    for i in range(1,n+1):
        a[i] = (b * a[i - 1]) % M
        bvv[i - 1] = a[i - 1] / M
    return bvv

def ver():
    bvv = dat(2000000)
    xv = bvv[999999]
    t = []
    for i in range(1000000,len(bvv)):
        if bvv[i] == xv: t.append(i)
    T=t[1]-t[0]
    for i in range(T):
        if bvv[i]==bvv[T+i]: 
            L = i
            break
    print('T = ',T)
    print('L = ', L)
    return T,L

N = 10000
bvv = dat(N)
k = int(1+math.log2(N))
h = (max(bvv)-min(bvv))/14

print('MIN : ',min(bvv))
print('MAX :',max(bvv))
print("INTERVALS : ",k)

gr_c = dict.fromkeys([min(bvv)+ h * i for i in range(k)],0)
gr_s = dict.fromkeys([min(bvv)+ h * i for i in range(k)],0)

print(gr_c)
print(gr_s)

for i in bvv:
    for j in gr_c.keys():
        if (i > j and i < j + h):
            gr_c[j] += 1
            gr_s[j] += i - j + min(bvv)

for i in gr_c.keys():
    print(gr_s[i] / gr_c[i])


hi = 0    
for i in gr_c.keys():
    hi += (gr_c[i] - N/k)**2 / (N / k)
print('Hi = ', hi)




t = 10
Rp = [0]*t
avg = st.mean(bvv)
for j in range(t):
    s = 0
    for i in range(N-t):
        s += bvv[i] * bvv[i + j]
    Rp[j] = s / (N - j - 1) - (N / (N - 1)) * avg**2

delta = [abs(Rp[0] - 1/12)]+[abs(Rp[i]) for i in range(1,t)]

print("delta R =", delta)

print(1.65*(2)**0.5/(12*(N-1)**0.5), 1.65/(12*(N-1)**0.5))

MomPerev = abs(avg - 0.5) / (1 / 12 / N)**0.5

print("Moment Verification =" , MomPerev)  
var = 0
for i in range(N):
    var += (bvv[i] - avg)**2
var /= N - 1
print("Variance =" , var, avg)
TeoDis = (0.0056 / N + 0.0028/(N**2) - 0.0083/(N**3))
print("Teoretical Dispersion", TeoDis)
DisPerev = (N - 1) * abs(var - 1 / 12) / (0.0056 / N + 0.0028/(N**2) - 0.0083/(N**3))**0.5 / N
print("Dispersion Verification =" ,DisPerev)

y = [0]*k
j = 0
print(gr_c)
for i in gr_c.keys():
    y[j] = gr_c[i]
    j += 1
x = range(10000)
fig, ax = plt.subplots()
ax.plot(range(k),y)
