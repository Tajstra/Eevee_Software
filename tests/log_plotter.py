import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import os

log_files = os.listdir("logs/")
print(log_files)

log_files_num = len(log_files)
fig, axs = plt.subplots(nrows=log_files_num, ncols=1)

ax_idx = 0
for log in log_files:
    log_data = np.genfromtxt('logs/' + log, delimiter=';')
    axs[ax_idx].plot(log_data)
    axs[ax_idx].grid()
    
    ax_idx = ax_idx + 1

plt.show()
