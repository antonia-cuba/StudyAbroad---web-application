def main():
    height = int(input("Height: "))
    
    for i in range(height):
        for j in range(height):
            print("#", end="")
        print()
    
main()