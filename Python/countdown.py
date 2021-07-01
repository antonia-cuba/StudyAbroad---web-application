import random

def main():
    n = random.randint(5, 15)
    # countdown(int(input("nr: ")))
    countdown(n)
    print("happy new year")

def countdown(n):
    for i in range(n):
        print(n - i)

main()


"""
multiline
comment
"""
# oneline comment