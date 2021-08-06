#Colin Quinn
#Cloud Computing Assignment 2
#This takes in a file, reading it line by line and then splits
#each line into a key pair of word and score.
def fileRead(name):
    dictionary ={}
    with open(name, "r") as read:
        for line in read:
            (key, val) = line.split()
            dictionary[key] = int(val)
    return dictionary
