import csv
from sys import argv, exit


def consec(str, DNA):
    i = 0
    while str * (i + 1) in DNA:
        i += 1
    return i
    

def match(seq12, dna_rep, row):
    for str in seq12:
        if dna_rep[str] != int(row[str]):
            return False
        else:
            return True
            
def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(4)
    
    cvsfile = open(argv[1], "r")    
    cvsfile = csv.DictReader(cvsfile)

    with open(argv[2], "r") as txtfile:
        DNA = txtfile.read()

    seq12 = cvsfile.fieldnames[1:]


    dna_rep = {}
    for str in seq12:
        dna_rep[str] = consec(str, DNA)
    
    for row in cvsfile:
        if match(seq12, dna_rep, row):
            print(f"{row['name']}")
            exit(2)
    
    print("No match")
        
#cvsfile.close()

main()