import matplotlib.pyplot as plt


times = {
    "Serial": 0.030116, 
    "Parallel 2 threads": 0.018073,  
    "Parallel 4 threads": 0.016161
}

labels = list(times.keys())
values = list(times.values())

plt.figure(figsize=(10, 6))
plt.bar(labels, values, color=['blue', 'orange', 'green'])
plt.xlabel('Execution Type')
plt.ylabel('Time (seconds)')
plt.title('Computation Time for Serial and Parallel Versions')
plt.show()
