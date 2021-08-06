#Colin Quinn
#Cloud Computing Assignment 2
#This takes in a string and creates a dashed version of same length
#with each dash separated by a space for readability.
import string

def createBlanks(word):
    blanks=""
    for letter in word:
        blanks+=" _"
    return blanks
