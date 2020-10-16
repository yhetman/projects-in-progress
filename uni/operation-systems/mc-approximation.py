import seaborn as sns
import numpy as np
import random
import matplotlib.pyplot as plt
from statsmodels.distributions.empirical_distribution import ECDF
from scipy.interpolate import interp1d
import scipy.stats as stats

sns.set()


def one_more_plot(x):

    df = 10
    dist = stats.cauchy()
    upper = dist.pdf(0)

    with plt.xkcd():
        plt.figure(figsize=(12,4))
        plt.subplot(121)
        plt.plot(x, dist.pdf(x), linewidth=1)
        plt.axhline(upper, color='grey')
        px = 1.0
        plt.arrow(px,0,0,dist.pdf(1.0)-0.01, linewidth=1,
            head_width=0.2, head_length=0.01, fc='g', ec='g')
        plt.arrow(px,upper,0,-(upper-dist.pdf(px)-0.01), linewidth=1,
              head_width=0.3, head_length=0.01, fc='r', ec='r')
        plt.text(px+.25, 0.2, 'Reject', fontsize=16)
        plt.text(px+.25, 0.01, 'Accept', fontsize=16)
        plt.axis([-4,4,0,0.4])
        plt.title('Rejection sampling concepts', fontsize=20)

        plt.subplot(122)
    n = 1000
    df = 10
    dist = stats.t(df=df)
    y = stats.chi2(df=df).rvs(n)
    r = stats.norm(0, df/y).rvs(n)
    u = np.random.uniform(-4, 4, n)
    v = u[r < dist.pdf(u)]

    with plt.xkcd():
        plt.plot(x, dist.pdf(x), linewidth=2)

    # Plot scaled histogram
        factor = dist.cdf(4) - dist.cdf(-4)
        hist, bin_edges = np.histogram(v, bins=100, normed=True)
        bin_centers = (bin_edges[:-1] + bin_edges[1:]) / 2.
        plt.step(bin_centers, factor*hist, linewidth=2)

        plt.axis([-4,4,0,0.4])
        plt.title('Histogram of accepted samples', fontsize=20);
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
            number = int.from_bytes(data, "big")
            numbers.append(number)
            data = f.read(4)
    return numbers

#def move_shuffle():

#def resampline():


def main():
    data = read_4bytes()
    sx, y = ecdf(data)
    ecdf_1 = ECDF(data)
    inv_cdf = extrap1d(interp1d(ecdf_1.y, ecdf_1.x,
                            bounds_error=False, assume_sorted=True))
    print(ecdf_1)
    r = np.random.uniform(0, 1, 100)
    ys = inv_cdf(r)
    sx, y = ecdf(data)
    # one_more_plot(data)
    plt.plot(sx, np.exp(sx))
    plt.show()
    #plt.hist(np.asarray(data), 25, histtype='step', color='red', linewidth=1)
    #plt.hist(ys, 25, histtype='step', color='blue', normed=True, linewidth=1)
    # data = move_shuffle(data)
    # data = resample(data)
    # sx, y = ecdf(data)
    #plt.plot(ys)
    #plt.plot(data, c='red')
    #plt.show()

if __name__ == "__main__":
    main()
