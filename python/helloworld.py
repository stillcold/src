#!usr/bin/python
#filename: helloworld.py
#run it in this way: python helloworld.py
#Lst edit by Li
import sys
print 'Hello World!'
for line in sys.stdin:
	a = line.split()
	print a[0]
