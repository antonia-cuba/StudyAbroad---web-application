import csv
from sys import argv, exit


def consec(seq, DNA):
    i = 0
    while seq * (i + 1) in DNA:
        i += 1
    return i
    

def match(seq12, dna_rep, row):
    for seq in seq12:
        if dna_rep[seq] != int(row[seq]):
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
    for seq in seq12:
        dna_rep[seq] = consec(seq, DNA)
    
    for row in cvsfile:
        if match(seq12, dna_rep, row):
            print(f"{row['name']}")
            exit(2)
    
    print("No match")
        
#cvsfile.close()

main()