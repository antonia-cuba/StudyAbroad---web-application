from cs50 import get_int, get_string
import sys

nrc = 0
sum1 = 0
p = 1
nr2 = 0

nr = get_int("Number: ")
cnr = nr
cnr1 = nr

while nr >= 100:
    nr = nr / 10
    nrc += 1

nrc += 2
prim = nr

print(nrc)
if nrc != 15 and nrc != 16 and nrc != 13:
    print("INVALID")
    sys.exit()

while cnr:
    nr2 = nr2 + (cnr % 100 / 10 * 2) * p
    cnr /= 100
    p *= 10

while nr2:
    sum1 = sum1 + nr2 % 10
    nr2 /= 10

sum2 = sum1

while cnr1:
    sum2 += cnr1 % 10
    cnr1 /= 100

print(sum2)
if sum2 % 10 != 0:
    print("INVALID") # DOESN'T WORK HERE
elif nrc == 15 and (prim == 34 or prim == 37):
    print("AMEX")
elif (nrc == 16 and (prim == 51 or prim == 52 or prim == 53 or prim == 54 or prim == 55)):
    print("MASTERCARD")
elif (nrc == 13 or nrc == 16) and prim / 10 == 4:
    print("VISA")
else:
    print("INVALID")