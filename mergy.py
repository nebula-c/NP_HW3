import os,sys

start = [1, 2, 4, 6, 8, 12]
final = [2, 4, 6, 8, 12, 24]

for i in range(0,6):
    for iscut in ["DCut", "NoD"]:
        filename = "%s_%d_%d"%(iscut,start[i],final[i])
        os.system("hadd Total_"+filename + ".root ./Histo/Pair_" + filename + "*" )