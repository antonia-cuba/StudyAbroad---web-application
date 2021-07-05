import csv
from sys import argv, exit

def consec(seq, DNA):
    i = 0
    while seq * (i + 1) in DNA:
        i += 1
    return i


if len(argv) < 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)
    
    
with open(argv[1], "r") as cvsfile:
    person = csv.DictReader(cvsfile)
    for row in person:
        print(row)
        
print()
    
with open(argv[2], "r") as txtfile:
    DNA = txtfile.read()
    print(DNA)

seq1 = {
    'AGATC': 0, 'AATG': 0, 'TATC': 0
    
}
seq2 = {
    'AGATC': 0, 'TTTTTTCT': 0, 'AATG': 0, 'TCTAG': 0, 'GATA': 0, 'TATC': 0, 'GAAA': 0, 'TCTG': 0
    
}

maxi = 0
if argv[1] == "databases/small.csv":
    for seq in seq1:
            seq1[seq] = consec(seq, DNA)
else:
    for seq in seq2:
        seq2[seq] = consec(seq, DNA)

for mn in person:
        if seq1[seq] != int(row[seq]):
            row += 1
        else:
            continue