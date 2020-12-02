#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Dec  1 17:14:17 2020

n >=16 : do access n times
k >=3: page index: 0 ~ 2^k-1
f: 4 ~ 2^k: size of page table

@author: y56
"""

# random.randint(a, b)
#  Return a random integer N such that a <= N <= b

import random

do=True
while do:
    def fun(n,k):
        trace =  [random.randint(0,2**k-1) for _ in range(n)]
        miss_record=[-1]*(2**k+1)
        for table_size in range(4,2**k+1): # size of page table
            table=[]
            miss=0
            for ask in trace:
                if ask in table:
                    None
                else:
                    miss+=1
                    if len(table) < table_size:
                        table.append(ask)
                    else:
                        del table[0]
                        table.append(ask)
            miss_record[table_size]=miss
        return miss_record
     
    k=4       
    miss_record=fun(64,k)
    
    import matplotlib.pyplot as plt
    plt.figure()
    plt.plot(range(4,2**k+1), miss_record[4:2**k+1])
    for left,right in zip(miss_record[4:2**k+1-1],miss_record[4+1:2**k+1]):
        if right>left:
            do=False
            
    