import seaborn as sns
import numpy as np
import random
import matplotlib.pyplot as plt
from statsmodels.distributions.empirical_distribution import ECDF
from scipy.interpolate import interp1d


sns.set()



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
    print(type(data))
    ecdf = ECDF(data)
    inv_cdf = extrap1d(interp1d(ecdf.y, ecdf.x,
                            bounds_error=False, assume_sorted=True))
    print(ecdf)
    r = np.random.uniform(0, 1, 100)
    ys = inv_cdf(r)
    #plt.hist(np.asarray(data), 25, histtype='step', color='red', linewidth=1)
    #plt.hist(ys, 25, histtype='step', color='blue', normed=True, linewidth=1)
    # data = move_shuffle(data)
    # data = resample(data)
    # sx, y = ecdf(data)
    plt.plot(ys)
    plt.plot(data, c='red')
    plt.show()

if __name__ == "__main__":
    main()
