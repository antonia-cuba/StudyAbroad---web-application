# cash in python

from cs50 import get_float

# nr of coins
k = 0

while True:
    dollars = get_float("Change owed: ")
    if dollars >= 0:
        break

# transforms $ in cents
cents = round(dollars * 100)

while cents >= 25:
    cents -= 25
    k += 1
    
while cents >= 10:
    cents -= 10
    k += 1
    
while cents >= 5:
    cents -= 5
    k += 1
    
while cents >= 1:
    cents -= 1
    k += 1
    
print(k)
    