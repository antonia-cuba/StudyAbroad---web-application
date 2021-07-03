# mario less
from cs50 import get_int


def main():
    n = get_right_nr()
    s = n - 1
    p = 1
    for i in range(n):
        print(" " * s, end="")
        s -= 1
        print("#" * p, end="")
        p += 1
        print()
        

def get_right_nr():
    while True:
        n = get_int("Height of pyramid: ")
        if n > 0 and n < 9:
            break
    return n
    
    
main()