import sys
from sage.all import *

def generateRandomSemistandardTableaux (size, max_entry_val, to_generate):
    v = []
    for i in range(to_generate):
        v.append(SemistandardTableaux(size, max_entry=max_entry_val).random_element())
    return v


def getAllSemistandardTableaux (size):
    return SemistandardTableaux(size).list ()


def writeTableauxToFile (t, fn):
    f = open(fn,"w")
    for row in reversed(t):
        for e in row:
            f.write("" + str(e) + "\n")
    f.close()


def writeTableauxToDirectory (tableaux, directory):
    i = 0
    for t in tableaux:
        fn = directory + "" + str(i) + ".sst"
        writeTableauxToFile(t,fn)
        i = i + 1


def showHelp (name):
     print "Usage: " + name + " <size> <output-directory> [all | random <max-entry-value> <number-to-generate>]"
     sys.exit(0)

if __name__ == "__main__":
    argv = sys.argv
    if len(sys.argv) <= 3:
        showHelp (argv[0])
    
    size = int(argv[1])
    output_directory = argv[2]
    tableaux = []
    if argv[3] == "all":
        tableaux = getAllSemistandardTableaux(size)
    elif argv[3] == "random":
        max_entry_val = int(argv[4])
        nr_to_generate = int(argv[5])
        tableaux = generateRandomSemistandardTableaux (size, max_entry_val, nr_to_generate)
    else:
        print "Invalid Option"

    writeTableauxToDirectory(tableaux, output_directory + "size_" + str(size) + "_")
    sys.exit(0)
