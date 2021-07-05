from cs50 import get_float

k = 0
while True:
    dollars = get_float("Change owed: ")
    if dollars >= 0:
        break
    
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
    
print (k)
    