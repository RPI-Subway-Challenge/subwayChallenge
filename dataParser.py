import pandas as pd

def dataParser(filename):
    file = open(filename, 'r')
    reader = csv.reader(file)
    data = []
    for row in reader:
        data.append(row)
    file.close()
