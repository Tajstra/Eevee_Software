import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import os
import csv

log_files = os.listdir("logs/")

for log in log_files:
    csv_file = open('logs/' + log)
    reader = csv.reader(csv_file, delimiter=';')
    header = next(reader)
    header.pop(0)
    header.pop()

    log_data = np.genfromtxt('logs/' + log, delimiter=';')
    [m,n] = log_data.shape
    log_data = np.delete(log_data, obj=n-1, axis=1)

    plt.figure(log)
    plt.plot(log_data[1:, 0], log_data[1:, 1:], label=header)

    plt.suptitle(log.replace('log_', '').replace('.csv', ''))
    plt.grid()
    plt.legend(header)

plt.show()
