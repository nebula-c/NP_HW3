from multiprocessing import Process

import time
import sys, os

def func(num):
    for i in range(0,10):
        print("%i process : %i "%(num,i))
        time.sleep(num)

    


pr2_noD = Process(target = func, args=(2,))
pr3_noD = Process(target = func, args=(3,))
pr4_noD = Process(target = func, args=(4,))

pr2_noD.start()
pr3_noD.start()
pr4_noD.start()

pr2_noD.join()
pr3_noD.join()
pr4_noD.join()

print("hi im done")