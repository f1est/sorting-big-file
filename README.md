The program sorts the numbers of the double format (type double) stored in a text file 1 GB in size (one number in one line).

## Usage

```sh
$ make
```
will compile two executable files:
- 0_generator - this program generates random numbers of the double format and writes them to the file unsorted_double.txt (one number in one line) while the file is not achieved the size of 1 GB

*run:*
```sh
  $ ./0_generator
```

- 1_sorter - this program takes an input file for sorting (created by the program 0_generator or any other file with double numbers), sorts the numbers in ascending order, and saves them in a file sorted.txt, with the derivation of the timing of each stage

*run:*
```sh
  $ ./1_sorter unsorted_double.txt sorted.txt
```

**The sorter works very fast !!!**
