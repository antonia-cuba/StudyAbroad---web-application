from cs50 import get_string

text = get_string("Text: ")
L = 0
W = 1
S = 0
# iterates through each character
for letter in text:
    if letter.isalpha():
        L += 1
    elif letter.isspace():
        W += 1
    elif letter == "." or letter == "!" or letter == "?":
        S += 1
    
index = 0.0588 * (L / W * 100) - 0.296 * (S / W * 100) - 15.8
    
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")
