CC=clang
CFLAGS=-std=c99 -Wall -Wextra -O4

all: molar-mass

molar-mass: molar-mass.c molar-masses.h
	$(CC) $(CFLAGS) molar-mass.c -o molar-mass

molar-masses.h: molar-masses.csv genmm.py
	python genmm.py < molar-masses.csv > molar-masses.h

clean:
	rm -f molar-masses.h molar-mass
