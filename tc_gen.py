import random

n = int(input())

print(str(n))
for i in range(n):
    x = random.random()
    y = random.random()
    x = 10*x
    y = 10*y
    # x = int(100000000*x)/100000000
    # y = int(100000000*y)/100000000
    print(str(x) + " " + str(y))
