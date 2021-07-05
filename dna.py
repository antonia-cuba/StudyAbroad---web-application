import csv
from sys import argv, exit


def consec(seq, DNA):
    i = 0
    while seq * (i + 1) in DNA:
        i += 1
    return i
    

def match(seq12, dna_seq, row):
    for seq in seq12:
        if dna_seq[seq] != int(row[seq]):
            return False
        else:
            return True
            
            
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(4)
    
cvsfile = open(argv[1], "r")    
cvsfile = csv.DictReader(cvsfile)

with open(argv[2], "r") as txtfile:
    DNA = txtfile.read()

dna_seq = {}
seqs = cvsfile.fieldnames[1:]



for seq in seqs:
    dna_seq[seq] = consec(seq, DNA)
for row in cvsfile:
    if match(seqs, dna_seq, row):
        print(f"{row['name']}")
        exit(1)
    
print("No match")
        
cvsfile.close()