import csv
from sys import argv, exit

def consec(seq, DNA):
    i = 0
    while seq * (i + 1) in DNA:
        i += 1
    return i

def match1(seq1, row):
    for seq in seq1:
        if seq1[seq] != int(row[seq]):
            return False
        else:
            return True
            
def match2(seq2, row):
    for seq in seq2:
        if seq2[seq] != int(row[seq]):
            return False
        else:
            return True
            
if len(argv) < 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(4)
    
cvsfile = open(argv[1], "r")    
cvsfile = csv.DictReader(cvsfile)

with open(argv[2], "r") as txtfile:
    DNA = txtfile.read()

seq1 = {
    'AGATC': 0, 'AATG': 0, 'TATC': 0
    
}
seq2 = {
    'AGATC': 0, 'TTTTTTCT': 0, 'AATG': 0, 'TCTAG': 0, 'GATA': 0, 'TATC': 0, 'GAAA': 0, 'TCTG': 0
    
}

if argv[1] == "databases/small.csv":
    for seq in seq1:
            seq1[seq] = consec(seq, DNA)
    for row in cvsfile:
        if match1(seq1, row):
            print(f"{row['name']}")
            exit(1)
elif argv[1] == "databases/large.csv":
    for seq in seq2:
        seq2[seq] = consec(seq, DNA)
    for row in cvsfile:
        if match2(seq2, row):
            print(f"{row['name']}")
            exit(2)
    
print("No match")
        
cvsfile.close()