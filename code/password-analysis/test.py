import glob
paths = glob.glob("output/n_*")

x = 0

for p in paths:
    f = open(p)
    x += int(f.read())
    f.close()

print(x)
