import re
import csv
import sys

UPPER = ord("A")
LOWER = ord("a") - 1
SYMBOL = re.compile(r"^[A-Z][a-z]?$", re.ASCII)

def symbol_to_index(symbol):
    if not SYMBOL.match(symbol):
        raise ValueError("Invalid symbol: {!r}".format(symbol))

    if len(symbol) == 1:
        return ord(symbol) - UPPER

    return (ord(symbol[1]) - LOWER) * 26 + ord(symbol[0]) - UPPER

def create_header(rows):
    elements = ((symbol_to_index(symbol), mass) for symbol, mass in rows)
    last = 0

    for symbol, mass in sorted(elements, key=lambda t: t[0]):
        yield from ["0"] * (symbol - last - 1)
        yield mass
        last = symbol

if __name__ == "__main__":
    c = csv.reader(sys.stdin)
    l = list(create_header(c))

    print("const static float molar_masses[] = { " + ", ".join(l) + " };")
    print("const static int MM_COUNT = " + format(len(l)) + ";")
