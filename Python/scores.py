def main():
    score1 = int(input("Score 1: "))
    score2 = int(input("Score 2: "))
    score3 = int(input("Score 3: "))
    
    print_scores(score1)
    print_scores(score2)
    print_scores(score3)
        
def print_scores(n):
    for i in range(n):
        # end="" means we don't go on the next line
        print("#", end="")
    # print a new line at the end
    print()

main()