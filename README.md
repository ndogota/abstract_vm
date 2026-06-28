# AbstractVM

An experimental stack-machine bytecode interpreter written in C. It reads a
program written in a small stack-based assembly language (`.avm`), checks its
syntax, and executes it on a typed, linked-list stack.

The interpreter is split into focused modules:

- `src/core.c` parses the program and dispatches instructions.
- `src/lines.c` turns the raw file into normalised lines (tokenizer).
- `src/linked.c` implements the typed stack and the arithmetic operations.
- `src/tools.c` holds the low level helpers (printing, number parsing, file IO).
- `include/` holds one header per module.

## The .avm language

A program is a list of instructions, one per line. Blank lines are ignored, and
anything after a `;` on a line is treated as a comment. Every program must
contain an `exit` instruction.

Values are typed. The supported operand types are:

| Type     | Stored as | Range                              |
| -------- | --------- | ---------------------------------- |
| `int8`   | 8 bit     | -128 to 127                        |
| `int16`  | 16 bit    | -32768 to 32767                    |
| `int32`  | 32 bit    | -2147483648 to 2147483647          |
| `float`  | 32 bit    | floating point                     |
| `double` | 64 bit    | floating point                     |

A value that does not fit its type is rejected with an error message.

### Instructions

| Instruction       | Effect                                                              |
| ----------------- | ------------------------------------------------------------------ |
| `push <type>(<v>)` | Push value `<v>` of the given type onto the stack.                 |
| `pop`             | Remove the value on top of the stack.                              |
| `dump`            | Print every value on the stack, from top to bottom.                |
| `print`           | If the top value is an `int8`, print it as an ASCII character.     |
| `assert <type>(<v>)` | Check that the top value equals `<v>`; print a message if not.  |
| `add`             | Replace the top two values with their sum.                         |
| `sub`             | Replace the top two values with their difference.                  |
| `mul`             | Replace the top two values with their product.                     |
| `div`             | Replace the top two values with their quotient.                    |
| `mod`             | Replace the top two values with the remainder of their division.   |
| `exit`            | Stop execution. Required in every program.                         |

The arithmetic instructions consume the top two values and push the result back
using the wider of the two operand types. They report an error instead of
running when the stack does not hold enough values.

### Example

The bundled program `avm/example.avm`:

```
push int8(8)
push int16(16)
push int32(32)
push float(64)
push double(128)
pop
dump
exit
```

It pushes five typed values, pops the `double(128)` back off, then dumps the
remaining four values from top to bottom:

```
64.0
32
16
8
```

## Build

The project builds with `make` and is warning-free under strict flags
(`-Wall -Wextra -Werror -std=c11`, linked with `-lm`), which are enforced at the
compile step:

```
$ make
```

Other targets: `make clean` removes object files, `make fclean` also removes the
binary, and `make re` rebuilds from scratch.

## Usage

Pass the path of the `.avm` program to interpret:

```
$ ./abstractvm avm/example.avm
```

## Memory safety

The interpreter is built warning-free under `-Wall -Wextra -Werror -std=c11` and
has been checked under UndefinedBehaviorSanitizer on the bundled example, a
program exercising every supported instruction, the arithmetic instructions, and
a set of malformed and edge-case inputs (an empty file, an unknown instruction,
a missing `exit`, and stack underflow from `pop`, `dump`, and arithmetic on a
stack that is too small). All of these run cleanly and report errors instead of
crashing.

Buffer handling was checked with a guard-page harness that places the program
buffer against an unmapped page, so any read past the end faults immediately;
the line splitter and tokenizer stay within bounds on inputs with and without a
trailing newline. Allocations are freed on every path, including the early error
returns; this was confirmed with the macOS `leaks` tool reporting zero leaks
across the inputs above. The code also compiles cleanly with
`-fsanitize=address`; the AddressSanitizer runtime could not be executed in the
environment used here, so that check was done by compilation plus the guard-page
and `leaks` runs. Valgrind was not available in that environment.

## Limitations

This is a learning-grade interpreter, not a production virtual machine. Compared
to a fuller stack VM it does not support:

- Control flow: no labels, jumps, branches, or loops.
- Procedures: no function calls or return values.
- Storage beyond the single operand stack: no registers, named variables, or
  heap-addressable memory.
- `print` output for types other than `int8`.
- Rich numeric literals: the number parser handles decimal integers, decimal
  points, and scientific notation, but not hexadecimal or octal forms.
- Division and modulo by zero are not given special handling; they follow the
  underlying floating point behaviour.
- Diagnostics are basic: the first error stops execution, and messages report
  the line number rather than a full trace.
