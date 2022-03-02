import matplotlib.pyplot as plt
plt.style.use('ggplot')
import glob
import os
paths = glob.glob("output/n_*")
values = []
names = []
for p in paths:
    f = open(p)
    values.append(int(f.read()))
    names.append(os.path.basename(p))
    f.close()
x_pos = [i for i, _ in enumerate(names)]
print(values)
print(names)
print(x_pos)
plt.bar(x_pos, values)
plt.ylabel("Frequency")
plt.title("Character sets used")
plt.xticks(x_pos, names)
plt.show()
