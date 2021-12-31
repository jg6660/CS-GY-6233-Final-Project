#!/usr/bin/env python
# coding: utf-8

# In[2]:


import matplotlib.pyplot as plt
import csv
import numpy as np

x = []
y = []

with open('performance.csv','r') as csvfile:
    lines = csv.reader(csvfile, delimiter=',')
    next(lines, None) 
    for row in lines:
        x.append(row[0])
        y.append(float(row[1]))

f = plt.figure()
f.set_figwidth(10)
f.set_figheight(10)

plt.plot(x, y, color = 'g', linestyle = 'solid',
    marker = 'o',label = "Performance (in Mib/s)", linewidth=3)

plt.xticks(rotation = 25)
plt.xlabel('Block Size',fontsize=10)
plt.ylabel('Performance (MiB/s)',fontsize = 10)
plt.title('Performance vs Block Size', fontsize = 15)
parameters = {'axes.labelsize': 5}
plt.rcParams.update(parameters)
plt.grid()
plt.legend()
plt.show()
f.savefig('performance.png')


# In[ ]:





# In[ ]:




