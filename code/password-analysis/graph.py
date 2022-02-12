import matplotlib.pyplot as plt
import csv

with open('output/lengths', newline='') as f:
    reader = csv.reader(f)
    lengths = list(reader)
    lengths = [int(x) for x in lengths[0]]
with open('output/aboveMaxLen') as f:
    aboveMaxLen = int(f.read())
with open('output/ignored') as f:
    ignored = int(f.read())

fig, ax = plt.subplots()
ax.ticklabel_format(useOffset=False, style='plain')
ax.set_xlabel('Length')
ax.set_ylabel('Frequency')
ax.plot(lengths, label='password length')
ax.axhline(y=aboveMaxLen, color='orange', label='aboveMaxLen')
ax.axhline(y=ignored, color='red', label='ignored')
plt.legend()
plt.show()
