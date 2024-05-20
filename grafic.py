import matplotlib.pyplot as plt

# solver_neopt
x1 = [400, 600, 800, 1000, 1200]
y1 = [0.769440, 4.300715, 7.227302, 20.44082, 32.224691]

# solver_blas
x3 = [400, 600, 800, 1000, 1200]
y3 = [0.032413, 0.176025, 0.220670, 0.588446, 0.710876]

# solver_opt
x2 = [400, 600, 800, 1000, 1200]
y2 = [0.339444, 1.196584, 3.047206, 6.220156, 8.850394]

# Plot the data
plt.plot(x1, y1, 'o-', label='solver_neopt')
plt.plot(x2, y2, 'o-', label='solver_opt')
plt.plot(x3, y3, 'o-', label='solver_blas')

for i, (x, y) in enumerate(zip(x1, y1)):
    plt.annotate(f'({x}, {y:.2f})', (x, y), textcoords="offset points", xytext=(0,10), ha='center')

for i, (x, y) in enumerate(zip(x2, y2)):
    plt.annotate(f'({x}, {y:.2f})', (x, y), textcoords="offset points", xytext=(0,10), ha='center')

for i, (x, y) in enumerate(zip(x3, y3)):
    plt.annotate(f'({x}, {y:.2f})', (x, y), textcoords="offset points", xytext=(0,10), ha='center')

plt.xlabel('Size of matrix')
plt.ylabel('Time (seconds)')
plt.title('Matrix multiplication')

plt.legend()
plt.grid(True)
plt.show()
