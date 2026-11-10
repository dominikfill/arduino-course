# Turns one day of the Venice tide file into a list for the Arduino.
#
# In:  data/valori_orari_puntasalute_Venezia_2019.csv
#      one line per hour:  12/11/2019;23:00;1.81   (day ; hour ; level in metres)
# Out: tide_data.h in the sketches 18-tide-list and 20-tide-colour
#      the 24 hourly levels of one day, in cm, as Arduino code
#
# Run it with Python. It needs no extra packages.

import csv
from pathlib import Path

# ---------- change these ----------
FILE_NAME = "valori_orari_puntasalute_Venezia_2019.csv"
DAY = "12/11/2019"
# ----------------------------------

here = Path(__file__).parent
in_file = here.parent / "data" / FILE_NAME
# the sketches that use the list: each gets its own copy of tide_data.h
sketches = ["18-tide-list", "20-tide-colour"]

# 1. Read the file, line by line, and keep only the lines of DAY
tide = []

with open(in_file, newline="") as f:
    reader = csv.reader(f, delimiter=";")
    next(reader)                              # skip the first line: the column names
    for row in reader:
        if len(row) < 3 or row[2] == "":
            continue                          # empty or broken line: skip it
        day, hour, level = row
        if day == DAY:
            cm = round(float(level) * 100)    # "1.81" metres → 181 cm
            tide.append(cm)

if len(tide) == 0:
    print("No lines found for", DAY, "- check the date, written like 12/11/2019")
    raise SystemExit

# 2. Write the list as Arduino code, 12 numbers per line
numbers = [str(cm) for cm in tide]
lines = [", ".join(numbers[i:i + 12]) for i in range(0, len(numbers), 12)]

for sketch in sketches:
    out_file = here.parent / "sketches" / sketch / "tide_data.h"
    with open(out_file, "w") as f:
        f.write("// Made by tide_to_arduino.py from " + FILE_NAME + "\n")
        f.write("// Water level in Venice on " + DAY + ", hour by hour, in cm\n")
        f.write("const int HOURS = " + str(len(tide)) + ";\n")
        f.write("const int tide[HOURS] = {\n  " + ",\n  ".join(lines) + "\n};\n")

# 3. Show what happened
print("Read", len(tide), "hours of", DAY)
print("Lowest:", min(tide), "cm   Highest:", max(tide), "cm")
for sketch in sketches:
    print("Written to sketches/" + sketch + "/tide_data.h")
