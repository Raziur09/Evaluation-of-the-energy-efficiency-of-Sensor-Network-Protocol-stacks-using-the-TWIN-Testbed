import csv

def remove_words(s):
    return ''.join(c for c in s if c.isdigit())

temp = open("ContikiMac1temp.csv",'r')
fout = open("ContikiMac1out.csv",'w')
with temp as infile, fout as outfile:
    reader = csv.reader(infile)
    writer = csv.writer(outfile)

    for line in reader:
        line = [remove_words(elem) for elem in line]
        writer.writerow([remove_words(elem) for elem in line])


