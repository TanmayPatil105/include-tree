# include-tree

This program performs a depth-first search to generate and print the file inclusion tree of a specified input file in a tree-like format

This program can be really helpful for debugging and refactoring.

# Usage

```
$ itree ipuz-acrostic.c
ipuz-acrostic.c
├── libipuz-config.h
├── ipuz-private.h
│   ├── ipuz-puzzle.h
│   ├── ipuz-crossword.h
│   ├── ipuz-cell.h
│   ├── ipuz-clue.h
│   └── ipuz-clue-sets.h
├── acrostic-board-dimensions.h
└── ipuz-magic.h
    └── ipuz-puzzle.h
```

## Build and Install

```
$ make
```
```
$ sudo make install
```
