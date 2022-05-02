# Get text from user
text = input("Text: ")

# Start count for words, sentences and letters
letters = 0
# Words = lenght of the list of the text split by spaces
words = len(text.split())
sentences = 0

# Iterate the text, if it's alpha, count letter, if it's a . or ! or ?, count a sentence
for letter in text:
    if letter.isalpha() == True:
        letters = letters + 1
    elif letter in '.!?':
        sentences = sentences + 1

# Index calculation rounded up
index = round(0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8)
# print(f"Index: {index}")

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}.")