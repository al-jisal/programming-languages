"""
File: benford_par3.c -- implements a parallel version of the Benford's Law using a local
                        counter array with final update protected by single mutex
Author: Desmond Frimpong
Project: 08
Date: May 8, 2026
"""

import matplotlib.pyplot as plt

versions = [
    "Sequential",
    "Global Counter with Single Mutex",
    "Global Counter with Array of Mutexes",
    "Local Counter with Final Update Protected by Single Mutex",
    "Local Counter with Final Update Protected by Array of Mutexes",
    "Global Counter Array of Arrays Grouped by Thread (no mutex)",
    "Global Counter Array of Arrays Grouped by Digit (no mutex)"
]

# Mean execution times for each version (I populated this with each run)
execution_times = [
    0.001812,  # Sequential
    0.002618,  # Global Counter with Single Mutex
    0.001851,  # Global Counter with Array of Mutexes
    0.001986,  # Local Counter with Final Update Protected by Single Mutex
    0.002222,  # Local Counter with Final Update Protected by Array of Mutexes
    0.002163,  # Global Counter Array of Arrays Grouped by Thread (no mutex)
    0.001982   # Global Counter Array of Arrays Grouped by Digit (no mutex)
]

# Plotting the data
plt.figure(figsize=(10, 6))
plt.bar(versions, execution_times, color='skyblue')
plt.xlabel('Program Version')
plt.ylabel('Mean Execution Time (seconds)')
plt.title('Execution Time Comparison of Different Benford’s Law Implementations')
plt.xticks(rotation=45, ha='right')
plt.tight_layout()

# Show the plot
plt.show()
