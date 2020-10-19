import seaborn as sns
import numpy as np
import random
import matplotlib.pyplot as plt
from statsmodels.distributions.empirical_distribution import ECDF
from scipy.interpolate import interp1d
import scipy.stats as stats
import pandas as pd


sns.set()


def one_more_plot(x):
    n = 100
    reps = 1000

    xb = np.random.choice(x[:,0], n, reps, replace=True)
    yb = 1/np.arange(1, n+1)[:, None] * np.cumsum(xb, axis=0)
    upper, lower = np.percentile(yb, [2.5, 97.5], axis=1)
    plt.plot(np.arange(1, n+1)[:, None], yb, c='grey', alpha=0.02)
    plt.plot(np.arange(1, n+1), yb[:, 0], c='red', linewidth=1)
    plt.plot(np.arange(1, n+1), upper, 'b', np.arange(1, n+1), lower, 'b');
    plt.show()


def extrap1d(interpolator):
    """From StackOverflow http://bit.ly/1BjyRfk"""
    xs = interpolator.x
    ys = interpolator.y

    def pointwise(x):
        if x < xs[0]:
            return ys[0]+(x-xs[0])*(ys[1]-ys[0])/(xs[1]-xs[0])
        elif x > xs[-1]:
            return ys[-1]+(x-xs[-1])*(ys[-1]-ys[-2])/(xs[-1]-xs[-2])
        else:
            return interpolator(x)

    def ufunclike(xs):
        return np.array(list(map(pointwise, np.array(xs))))

    return ufunclike



def example():
    for n in 10**np.array([1,2,3,4,5,6,7,8]):
        pts = np.random.uniform(0, 1, (n, 2))
        pts[:, 1] *= np.e
        count = np.sum(pts[:, 1] < np.exp(pts[:, 0]))
        volume = np.e * 1 # volume of region
        sol = (volume * count)/n
        print ('%10d %.6f' % (n, sol))



def ecdf(x):
    sx = np.sort(x)
    cdf = (1.0 + np.arange(len(sx))) / len(sx)
    return sx, cdf


def read_4bytes():
    numbers = []
    with open('example', 'br') as f:
        data = f.read(4)
        while data:
            number = int.from_bytes(data, "big", signed=True)
            numbers.append(number)
            data = f.read(4)
    return numbers


def resample():
    n = len(weights)
    indices = []
    C = [0.] + [sum(weights[:i+1]) for i in range(n)]
    u0, j = random(), 0
    for u in [(u0+i)/n for i in range(n)]:
        while u > C[j]:
            j+=1
        indices.append(j-1)
    return indices

def scale(x, out_range=(-1, 1), axis=None):
    domain = np.min(x, axis), np.max(x, axis)
    y = (x - (domain[1] + domain[0]) / 2) / (domain[1] - domain[0])
    return y * (out_range[1] - out_range[0]) + (out_range[1] + out_range[0]) / 2



def count_freq(x): 
    freq = {} 
    for item in x: 
        if (item in freq): 
            freq[item] += 1
        else: 
            freq[item] = 1
    for key, value in freq.items():
        print ("% d : % d"%(key, value))
    data = freq.items()

    df = pd.DataFrame(data, columns = ['Values', 'Frequency'])
    return df
    
#    plt.show()


def bootstrap(x):
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2)
    x1, y = ecdf(x)
    n = len(x)
    reps = 10000
    xb = np.random.choice(x, (n, reps))
    mb = xb.mean(axis=0)
    mb.sort()
    print(np.percentile(mb, [2.5, 97.5]))
    yb = 1/np.arange(1, n+1)[:, None] * np.cumsum(xb, axis=0)
    upper, lower = np.percentile(yb, [2.5, 97.5], axis=1)
    #plt.plot(np.arange(1, n+1)[:, None], yb, c='grey', alpha=0.02)
    #plt.plot(np.arange(1, n+1), yb[:, 0], c='red', linewidth=1)
    #plt.plot(np.arange(1, n+1), upper, 'b', np.arange(1, n+1), lower, 'b');
    bins = np.linspace(np.min(x), np.max(x), n + 1)
    weights = x1.astype(float) / x1.sum()
    probability = weights.astype(float) / weights.sum()
    histogram, bins = np.histogram(x, bins=bins, weights=weights, density=True)
    bin_centers = 0.5*(bins[1:] + bins[:-1])
    ax1.plot(probability, x1, c='green', label="Weights")
    #pdf = stats.norm.pdf()
   # print(pdf)
    ax2.plot(bin_centers, histogram, c='black',label="PDF")
    ax3.scatter(bin_centers, x1, c='r', label="Samples")
    ax4.plot(bin_centers, np.cumsum(x, axis=0), label="Cummmulative sums")
    fig.legend()
    plt.show()



def main():
    x = read_4bytes()
    
    seq = []
    n = 1000000
    while len(seq) < n:
        seq.append(random.choice(x))
    df = count_freq(seq)
    df['Probability'] = df['Frequency'] / n
    with pd.option_context('display.max_rows', None, 'display.max_columns', None):
        print(df[df['Probability'] > 0.0001]);
    #plt.hist(df['Values'], df['Probability'])
    hist = df.hist()
    #bootstrap(scale(x))
    #plt.hist(np.asarray(data), 25, histtype='step', color='red', linewidth=1)
    #plt.hist(ys, 25, histtype='step', color='blue', normed=True, linewidth=1)
    # data = move_shuffle(data)
    # data = resample(data)
    # sx, y = ecdf(data)
    #plt.plot(ys)
    #plt.plot(data, c='red')
    

if __name__ == "__main__":
    main()
