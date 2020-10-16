import seaborn as sns
import numpy as np
import random
import matplotlib.pyplot as plt
import statsmodels.distributions.empirical_distribution import ECDF

sns.set()

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
    ecdf = ECDF(data)
    
    # data = move_shuffle(data)
    # data = resample(data)
    # sx, y = ecdf(data)
    # plt.plot(sx, y)
    plt.show()

if __name__ == "__main__":
    main()
