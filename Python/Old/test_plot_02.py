__author__ = 'NM242826'

import matplotlib.pyplot as plt
import numpy as np
plt.ion()
x = np.arange(0, 4*np.pi, 0.1)
y = [np.sin(i) for i in x]



for k in range(10):
    plt.plot(x, [i**k for i in y], 'g-', linewidth=1.5, markersize=4)
    plt.pause(0.01)

plt.show(block=True)