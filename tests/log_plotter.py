import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import os

log_files = os.listdir("logs/")

for log in log_files:
    log_data = np.genfromtxt('logs/' + log, delimiter=';')

    plt.figure(log)
    plt.plot(log_data[:, 0], log_data[:, 1:])
    plt.suptitle(log.replace('log_', '').replace('.csv', ''))

plt.show()
