#!/usr/bin/env python
import subprocess
import sys
#import matplotlib.pyplot as plt



# Running the codes
threadarr=[2,4,8,12]
time_serial=[]
time_serial_opt=[]
time_PARALLEL_NAIVE =[]
time_PARALLEL_OPTIMIZED =[]


#print "This is Serial Execution"


our_range=[[100,100,10],[100,100,100],[100,100,1000],[100,100,10000]]
our_range2=[[1000,1000,10],[1000,1000,100],[1000,1000,1000]]
our_range3=[[10000,10000,1],[10000,10000,10]]
strv="SERIAL_NAIVE.c"
count=0
for vap in our_range:
	count=count+1
	subprocess.call(["gcc","-fopenmp",strv,"-lm","-w"])
	cmd = ["./a.out",str(vap[0]),str(vap[1]),str(vap[2])]
	temp2=[]
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))	
	print (min(temp2))
	output=min(temp2)
	time_serial.append(min(temp2))
for vap in our_range2:
	count=count+1
	subprocess.call(["gcc","-fopenmp",strv,"-lm","-w"])
	cmd = ["./a.out",str(vap[0]),str(vap[1]),str(vap[2])]
	temp2=[]
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))	
	print (min(temp2))
	output=min(temp2)
	time_serial.append(min(temp2))
for vap in our_range3:
	count=count+1
	subprocess.call(["gcc","-fopenmp",strv,"-lm","-w"])
	cmd = ["./a.out",str(vap[0]),str(vap[1]),str(vap[2])]
	temp2=[]
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))	
	print (min(temp2))
	output=min(temp2)
	time_serial.append(min(temp2))











for vap in our_range:
	count=count+1
	subprocess.call(["gcc","-fopenmp","SERIAL_OPTIMIZED.c","-lm","-w"])
	cmd = ["./a.out",str(vap[0]),str(vap[1]),str(vap[2])]
	temp2=[]
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))	
	print (min(temp2))
	output=min(temp2)
	time_serial_opt.append(min(temp2))
for vap in our_range2:
	count=count+1
	subprocess.call(["gcc","-fopenmp","SERIAL_OPTIMIZED.c","-lm","-w"])
	cmd = ["./a.out",str(vap[0]),str(vap[1]),str(vap[2])]
	temp2=[]
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))	
	print (min(temp2))
	output=min(temp2)
	time_serial_opt.append(min(temp2))
for vap in our_range3:
	count=count+1
	subprocess.call(["gcc","-fopenmp","SERIAL_OPTIMIZED.c","-lm","-w"])
	cmd = ["./a.out",str(vap[0]),str(vap[1]),str(vap[2])]
	temp2=[]
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))
	output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
	temp2.append(float(output))	
	print (min(temp2))
	output=min(temp2)
	time_serial_opt.append(min(temp2))











for thr in threadarr:
	for vap in our_range:
		count=count+1
		subprocess.call(["gcc","-fopenmp","PARALLEL_NAIVE.c","-lm","-w"])
		cmd = ["./a.out",str(vap[0]),str(vap[1]),str(vap[2]),str(thr)]
		temp2=[]

		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		print(output)
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))	
		print (min(temp2))
		output=min(temp2)
		time_PARALLEL_NAIVE.append(min(temp2))

for thr in threadarr:
	for vap in our_range2:
		count=count+1
		subprocess.call(["gcc","-fopenmp","PARALLEL_NAIVE.c","-lm","-w"])
		cmd = ["./a.out",str(vap[0]),str(vap[1]),str(vap[2]),str(thr)]
		temp2=[]
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))	
		print (min(temp2))
		output=min(temp2)
		time_PARALLEL_NAIVE.append(min(temp2))
for thr in threadarr:
	for vap in our_range3:
		count=count+1
		subprocess.call(["gcc","-fopenmp","PARALLEL_NAIVE.c","-lm","-w"])
		cmd = ["./a.out",str(vap[0]),str(vap[1]),str(vap[2]),str(thr)]
		temp2=[]
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))	
		print (min(temp2))
		output=min(temp2)
		time_PARALLEL_NAIVE.append(min(temp2))















for thr in threadarr:
	for vap in our_range:
		count=count+1
		subprocess.call(["gcc","-fopenmp","PARALLEL_OPTIMIZED.c","-lm","-w"])
		cmd = ["./a.out",str(vap[0]),str(vap[1]),str(vap[2]),str(thr)]
		temp2=[]
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))	
		print (min(temp2))
		output=min(temp2)
		time_PARALLEL_OPTIMIZED.append(min(temp2))

for thr in threadarr:
	for vap in our_range2:
		count=count+1
		subprocess.call(["gcc","-fopenmp","PARALLEL_OPTIMIZED.c","-lm","-w"])
		cmd = ["./a.out",str(vap[0]),str(vap[1]),str(vap[2]),str(thr)]
		temp2=[]
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))	
		print (min(temp2))
		output=min(temp2)
		time_PARALLEL_OPTIMIZED.append(min(temp2))
for thr in threadarr:
	for vap in our_range3:
		count=count+1
		subprocess.call(["gcc","-fopenmp","PARALLEL_OPTIMIZED.c","-lm","-w"])
		cmd = ["./a.out",str(vap[0]),str(vap[1]),str(vap[2]),str(thr)]
		temp2=[]
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))
		output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
		temp2.append(float(output))	
		print (min(temp2))
		output=min(temp2)
		time_PARALLEL_OPTIMIZED.append(min(temp2))






	

print ("time_serial= ",time_serial)
print ("time_serial_opt= ",time_serial_opt)


print ("time_PARALLEL_NAIVE=" ,time_PARALLEL_NAIVE)
print ("time_PARALLEL_OPTIMIZED=" ,time_PARALLEL_OPTIMIZED)


speedup1 =[]
speedup2 =[]


for i in range(0,len(time_PARALLEL_NAIVE)):
	speedup1.append(time_serial[i%len(time_serial)]/time_PARALLEL_NAIVE[i])
	speedup2.append(time_serial_opt[i%len(time_serial_opt)]/time_PARALLEL_OPTIMIZED[i])


print ("speedup1=",speedup1)
print ("speedup2=",speedup2)
