__author__ = 'NM242826'

import matplotlib.pyplot as plt
import numpy as np
plt.ion()
n = 100
x = range(n)
y = [np.sin(i) for i in x]


fig, ax = plt.subplots()
ax.set_xlim((0,n))

for k in range(n):
    plt.plot(x[0:k], y[0:k], 'g-', linewidth=1.5, markersize=4)
    ax.set_xlim((0, k))
    plt.pause(0.01)

plt.show(block=True)
