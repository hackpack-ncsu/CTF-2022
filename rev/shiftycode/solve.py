# flag{my_sh1fti35_453_n1fty}                             

from z3 import *

s = Solver()

flag = [BitVec(f'flag[{i}]', 32) for i in range(0,27)]

for i in range(0, 27):
    s.add(flag[i] < 127)
    s.add(flag[i] > 0)

# f
s.add(flag[0] == 102)

# l
s.add(flag[1] < 109)
s.add(flag[1] > 107)

# ag
s.add(flag[2] + flag[3] == 200)
s.add((flag[2] + flag[3]) - (flag[3] - flag[2]) == 194)

# {}
s.add(flag[4] == 123) 
s.add(flag[26] == 125)

# my_
s.add(flag[5] + flag[6] + flag[7] - 100 == 225)
s.add(flag[6] + flag[7] == 216)
s.add(flag[5] + flag[7] == 204)

# sh1ft
# s 115 8
# h 104 9
# 1 49  10
# f 102 11
# t 116 12
s.add(flag[8] == flag[9] + 11)
s.add(flag[8] == flag[10] + 66)
s.add(flag[12] + flag[11] - flag[8] == 103)
s.add(flag[12] - flag[9] + flag[10] == flag[11] - 41)
s.add(flag[11] - flag[10] == 53)

# i35_453
# i 105 13
# 3 51  14
# 5 53  15
# _ 95  16
# 4 52  17
# 5 53  18
# 3 51  19
s.add(flag[14] == flag[19])
s.add(flag[15] == flag[18])
s.add(flag[16] == flag[7])
s.add(flag[13] - flag[18] == flag[17])
s.add(flag[17] < flag[18])
s.add(flag[17] > flag[19])
s.add(flag[18] - flag[19] == 2)
s.add(flag[13] - 54 == flag[14])

# _n1fty
# _ 95  20
# n 110 21
# 1 49  22
# f 102 23
# t 116 24
# y 121 25
s.add(flag[19] * 2 == flag[23])
s.add(flag[20] == flag[16])
s.add(flag[21] / 2 == flag[22] + 6)
s.add(flag[22] == flag[10])
s.add(flag[25] - flag[24] == 5)
s.add(flag[25] - flag[21] == 11)

s.check()

m = s.model()

s = ""
for i in range(0, 27):
    s += chr(int(str(m[flag[i]]) if str(m[flag[i]]) != '64' else "95"))

print(s)