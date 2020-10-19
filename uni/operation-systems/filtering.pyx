
import numpy as np
import random
cimport numpy

def read_4bytes():
    cdef numpy.ndarray numbers
    with open('example', 'br') as f:
        data = f.read(4)
        while data:
            number = int.from_bytes(data, "big", signed=True)
            numbers.append(number)
            data = f.read(4)
    return numbers

def count_frequency(x): 
    freq = {} 
    for item in x: 
        if (item in freq): 
            freq[item] += 1
        else: 
            freq[item] = 1
    return freq



def random_choices(x, tries):
    sequence = []
    while len(sequence) < tries:
        sequence.append(random.choice(x))
    return sequence



def make_subsample(num_items, x):
    resulting_sequence = []
    weights = []
    while num_items:
        number_of_tries = 1000000
        sequence = random_choices(x, number_of_tries)
        freq = count_frequency(sequence)
        highest = max(freq.values())
        for key, value in freq.items():
            if value == highest:
                resulting_sequence.append(key)
                weights.append(value / n)
                x.remove(key)
                break ;
        random.shuffle(x)
        num_items -= 1
        print(resulting_sequence, "\n", weights)
    return resulting_sequence

    

def main():
	cdef unsigned int N = 100
    cdef numpy.ndarray x
	x  = read_4bytes()
	make_subsample(N, x)


if __name__ == "__main__":
    main()
