import csv
import tempfile


def remove_words(s):
    return ''.join(c for c in s if c.isdigit())

fin = open("ContikiMac1.csv",'r')
temp = open("ContikiMac1temp.csv",'w')

with fin as infile, temp as outfile:
    reader = csv.reader(infile)
    writer = csv.writer(outfile, quoting=csv.QUOTE_NONE, escapechar=' ')

    for line in reader:
        line = [value.replace(';', ',') for value in line]

        if any('energest' in x for x in line):

            writer.writerow(line)

