# include-tree

This program performs a depth-first search to generate and print the file inclusion tree of a specified input file in a tree-like format

This program can be really helpful for debugging and refactoring.

# Usage

```console
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
```console
$ itree app.h --cycle
app.h
├── app_utils.h
│   └── app_error.h
│       └── app_utils.h (in red)
├── app_safe.h
│   ├── app_input.h
│   └── app_utils.h
└── app_input.h
```

```console
$ itree app.h --depth 1
app.h
├── app_utils.h
│   └── app_error.h
├── app_safe.h
│   ├── app_input.h
│   └── app_utils.h
└── app_input.h
```
```console
$ itree app.h --grep app_safe.h -g app_none.h
app.h
├── app_utils.h
│   └── app_error.h
│       └── app_utils.h
├── app_safe.h (in green)
│   ├── app_input.h
│   └── app_utils.h
└── app_input.h
```
```console
$ itree *.h
app.h
├── app_utils.h
│   └── app_error.h
│       └── app_utils.h
├── app_safe.h
│   ├── app_input.h
│   └── app_utils.h
└── app_input.h
app_error.h
app_safe.h
app_utils.h

$ itree *.h --independent
app.h
├── app_utils.h
│   └── app_error.h
│       └── app_utils.h
├── app_safe.h
│   ├── app_input.h
│   └── app_utils.h
└── app_input.h
app_error.h
└── app_utils.h
    └── app_error.h
app_safe.h
├── app_input.h
└── app_utils.h
    └── app_error.h
        └── app_utils.h
app_utils.h
└── app_error.h
    └── app_utils.h
```

## Build and Install

```
$ make
```
```
$ sudo make install
```
