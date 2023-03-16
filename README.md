# roscript
mine own esoteric programming language written in C, executable through terminal. can run '.rse' files through provided .exe or be compiled directly into executable. 

---

## Syntax and Reasoning
This project was created as a test of my knowledge of C and its respective functions, as well as to see if I could make a language to execute code that can't easily be unobfuscated. 
Also because I find esoteric languages funny.

This project is built off of the concepts of the programming language [Brainfsck](https://en.wikipedia.org/wiki/Brainfuck), from which I pinched a good amount of operands. Unfortunately, my additions required a complete structural rewrite. 

Each program initializes a large Turing tape, and instruction pointer, a tape pointer, and a pocket, all initialized at zero. The turing tap holds a byte of data, usually in the form of a char. When the program begins, the first instruction at the location of the instruction pointer is read, and one of 14 different operands is executed.

Here they all are listed below.

| Syntax      | Description |
| ----------- | ----------- |
| <           | Move pointer left       |
| >   | Move pointer right        |
| + | Increment value at pointer |
| - | Decrement value at pointer 
| .| Print the value at the pointer|
| , | Store input at pointer|
| \[| If value at pointer = 0, skip to after corresponding ]|
| ]| Jump to corresponding \[|
| {| Copy value at pointer to value of pocket|
| }| Copy value in pocket to value at pointer|
| =| Save following cells up until \0 in file named after value in cell|
| \_| Load file into following cells|
| ^| Sleep a number of ms equivalent to value at pointer|
| #| Clear number of cells equivalent to value at pointer|

After the operand has finished executing, the instruction pointer is incremented and the program continues on.

Also due to cleaning up my laptop, I didn't have access to a Unix shell. I added the option to use a '.rse' file (RoScript Executable?) as input, though piping or redirecting should work as well. Because I didn't feel like hunting through errors for OSs I don't use, running this on Linux would require some slight syntax changes, for ex. replacing 'del' with 'rm' and so on, but the majority of it should still be fine.

## Project Structure
There are two main C files with two executables, one that runs roscript and another that compiles it.

### roscript.c
roscript.c has been compiled into the executable rtest.exe. This program will run your roscript code for you, whether inputted through text or custom file. The syntax for this program is

`.\rtest.exe .\roscriptFile.rse`
or
`.\rtest.exe ",+>,>,<<."`

You can also use '-p' to turn on debug mode, where used areas of tape are printed to the screen, like so. 

`.\rtest.exe .\roscriptFile2.rse -p`

### rscompiler.c
rscompiler.c has been compiled into the executable rcomp.exe. This program will take your roscript code and compile it into a runnable executable for you. The syntax for this program is similar, but stricter. As with rtest, you can

`.\rcomp.exe .\roscriptFile.rse` or `.\rcomp.exe ",+>,>,<<."`

These commands will compile your code into a file named 'a.exe'. If you want to add a custom name, you can do this. 

`.\rtest.exe ",+>,>,<<." example`

This will result in a new executable, 'example.exe'.

You can also decide whether or not you want a transcribed 'example.c' file by adding in a '-c' flag after specifying the roscript source.

`.\rtest.exe ",+>,>,<<." example -c` or `.\rtest.exe ",+>,>,<<." -c example`




