import threading, queue
from queue import Queue
from threading import Thread
import time
import sys


# Перевіряємо чи число парне
def f(x, q):
    print("Creating Thread #1 to evaluate f(x):")
    res_f = False;
    if(x % 2 == 0): res_f = True
    time.sleep(10)
    print("Thread 1 is done")
    q.put(res_f)


# Перевіряємо чи є число квадратом цілого числа
def g(x, q):
    print("Creating Thread #2 to evaluate g(x):")
    res_q = False
    if x > 1:
        for i in range(int(x / 2 ) + 1):
            if (i ** 2) == x:
                res_q = True
                break
    time.sleep(3)
    print("Thread 2 is done")
    q.put(res_q)


if __name__ == "__main__":
    print("--------------------------------------- ")
    print("Enter variable value for f(x) and g(x):")
    try:
        x = int(input())
        q = Queue()
        t1 = Thread(target=f, args=(x, q))
        t2 = Thread(target=g, args=(x, q))
        t1.start()
        t2.start()
        if (not t1.is_alive()):
            print("Thread 1 has finished")
        if (not t2.is_alive()):
            print("Thread 2 has finished")
        f = q.get()
        print("\tf(x) = ", f, file=sys.stdout)
        g = q.get()
        print("\tg(x) = ", g, file=sys.stdout)
        t1.join()
        t2.join()
        print('\n ************************************* \n')
        print("\tf(x) || g(x) =", f or g, file=sys.stdout)
        print("--------------------------------------- ")
    except:
        print("Invalid input")