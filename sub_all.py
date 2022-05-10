import os
import sys
import time

import argparse
from multiprocessing import Process


parser=argparse.ArgumentParser(description='analysis all',formatter_class=argparse.ArgumentDefaultsHelpFormatter)
# parser.add_argument('--dcut','-d',action='store_true',help='Give dCut')
parser.add_argument('--read','-r',action='store_true', help='reading')
parser.add_argument('--draw','-d',action='store_true', help='drawing')

args=parser.parse_args()




start = time.time()

interval_i = [1, 2, 4, 6, 8, 12]
interval_f = [2, 4, 6, 8, 12, 24]
ptk = [0.5, 0.7, 0.7, 0.7, 0.7, 0.6]
ptp = [0.5, 0.7, 0.7, 0.7, 0.7, 0.6]
#dcut = [-0.2, -2, -0.5, -0.5, -0.5, 10]
dcut = [-0.00002, -0.0002, -0.00005, -0.00005, -0.00005, 10]

def ReadData(raw, i, cut):
    # for i in range(0,7):
    # for i in range(0,1):
        # for j in range(0,1):
        # j=1
    mycode = '''root 'NP_HW3.cpp("{}",{},{},{},{},{},{})' -l -q'''.format(raw.strip(),interval_i[i],interval_f[i],ptk[i],ptp[i],cut,dcut[i])
    # print(mycode)
    os.system(mycode)
    # print("---- is done----")


def DrawResult():
    for  i in ["DCut_", "NoD_"]:
    # for  i in ["NoD_"]:
        for j in range(0,6):
        # for j in range(0,1):
            
            if i == "NoD_" :
                dcut = "false"
            if i == "DCut_" :
                dcut = "true"

            if (dcut=="true") and (j==5):
                continue
            filename= '''Pair_{}{}_{}.root'''.format(i,interval_i[j],interval_f[j])
            print(filename)

            

            mycode = '''root 'Make_Plot.cpp("{}",{},{})' -l -q'''.format(filename,interval_i[j],interval_f[j])
            os.system(mycode)


if args.read :
    i=0
    flist = open("./testfile.lst", 'r')
    totalnum = len(flist.readlines())
    flist = open("./testfile.lst", 'r')
    for file in flist :
        
        pr0_noD = Process(target = ReadData, args=(file,0,"false"))
        pr1_noD = Process(target = ReadData, args=(file,1,"false"))
        pr2_noD = Process(target = ReadData, args=(file,2,"false"))
        pr3_noD = Process(target = ReadData, args=(file,3,"false"))
        pr4_noD = Process(target = ReadData, args=(file,4,"false"))
        pr5_noD = Process(target = ReadData, args=(file,5,"false"))

        pr0_noD.start()
        pr1_noD.start()
        pr2_noD.start()
        pr3_noD.start()
        pr4_noD.start()
        pr5_noD.start()

        pr0_noD.join()
        pr1_noD.join()
        pr2_noD.join()
        pr3_noD.join()
        pr4_noD.join()
        pr5_noD.join()


        i=i+1
        print("==========================================")
        print("file progress : %d/%d -> %.2f"%(i,totalnum,(float(i)/float(totalnum))))
        print("==========================================")
    flist.close()

    print("without Dcut is done")
    
    # i=0
    # flist = open("./file.lst", 'r')
    # for file in flist :
    #     pr0_cut = Process(target = ReadData, args=(file,0,"true"))
    #     pr1_cut = Process(target = ReadData, args=(file,1,"true"))
    #     pr2_cut = Process(target = ReadData, args=(file,2,"true"))
    #     pr3_cut = Process(target = ReadData, args=(file,3,"true"))
    #     pr4_cut = Process(target = ReadData, args=(file,4,"true"))
    #     # pr5_cut = Process(target = ReadData, args=(5,"false"))

    #     pr0_cut.start()
    #     pr1_cut.start()
    #     pr2_cut.start()
    #     pr3_cut.start()
    #     pr4_cut.start()
    #     # pr5_cut.start()

    #     pr0_cut.join()
    #     pr1_cut.join()
    #     pr2_cut.join()
    #     pr3_cut.join()
    #     pr4_cut.join()
    #     # pr5_cut.join()
        
    #     i=i+1
    #     print("==========================================")
    #     print("file progress : %d/%d -> %.2f"%(i,totalnum,(float(i)/float(totalnum))))
    #     print("==========================================")
    flist.close()

if args.draw:
    DrawResult()

end = time.time()
print("=========================")
print("{} sec(sub)".format(end-start))
print("=========================")