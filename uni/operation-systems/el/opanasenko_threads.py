import time
import sys
import numpy as np
from datetime import datetime, timedelta
from threading import Thread

def read_matrix(file):
	contents = open(file).read()
	return [item.split() for item in contents.split('\n')[:-1]]


def multiplying_matrixes(index):
	start = datetime.now()
	result = []
	MN = 'M' + str(index + 1)
	A = read_matrix('M0')
	B = read_matrix(MN)
	filename = 'M0x' + MN 
	for i in range(len(A)):
		row = []
		for j in range(len(B[0])):
			product = 0
			for v in range(len(A[i])):
				product += int(A[i][v]) * int(B[v][j])
			row.append(product)
		result.append(row)
	result = np.matrix(result)
	np.savetxt(filename, result, fmt='%d')
	finish = datetime.now()
	fopen = open(filename, "a+")
	fopen.write("Час роботи : %s\n" % str(finish - start))
	fopen.close()


threads = []
M0 = np.random.randint(1000, size=(20, 20))
np.savetxt('M0', M0, fmt='%d')
number = int(sys.argv[1])
print("Генеруемо %d файлів \n" % (number))
for i in range(number):
	name = 'M'+str(i + 1)
	M = np.random.randint(1000, size=(20, 20))
	np.savetxt(name, M, fmt='%d')
print("Запускаємо %d потоків \n" % (number))
for i in range(number):
	thread = Thread(target=multiplying_matrixes, args=(i,))
	threads.append(thread)
for thread in threads:
	thread.start()
for thread in threads:
	thread.join()