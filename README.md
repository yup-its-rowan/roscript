# roscript
mine own esoteric programming language written in C executable through terminal.

---

This project was created as a test of my knowledge of C and its respective functions, as well as to see if I could make a language to execute code that can't easily be unobfuscated. 
Also because I find esoteric languages funny.

This project shares a lot with the programming language [Brainfsck](https://en.wikipedia.org/wiki/Brainfuck), from which I pinched a good amount of operands. Unfortunately, my additions required a complete structural rewrite. 
Here they all are listed below.

| Syntax      | Description |
| ----------- | ----------- |
| <           | Move pointer left       |
| >   | Move pointer right        |
| + | Increment value at pointer |
| - | Decrement value at pointer 
| .| Print the value at the pointer|
| , | Store input at pointer|
| [| If value at pointer = 0, skip to after corresponding ]|
| ]| Jump to corresponding [|
| {| Copy value at pointer to value of pocket|
| }| Copy value in pocket to value at pointer|
| =| Save following cells up until \0 in file named after value in cell|
| _| Load file into following cells|
| ^| Sleep a number of ms equivalent to value at pointer|
| #| Clear number of cells equivalent to value at pointer|

Due to being on a new laptop I didn't have access to a Unix shell and instead added the option to use a '.rse' file (RoScript Executable?) as input.



