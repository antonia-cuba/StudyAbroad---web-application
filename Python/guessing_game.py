import random

def main():
    i = 0
    n = random.randint(0, 10)

    for i in range(3):
        ans = int(input("What's your guesss? "))
        if n == ans:
            print("Correct!")
            break # or return
        elif i == 2:
            print("Incorrect. Good luck next time!")
        else:
            print("Try again :(")
            i = i + 1

main()