# LL(1) Recursive Descent Parser

[![Language](https://img.shields.io/badge/Language-C99%20%2F%20C11-00599C.svg?logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Compiler](https://img.shields.io/badge/Compiler-GCC%20%2F%20Clang-green.svg)](https://gcc.gnu.org/)
[![Course](https://img.shields.io/badge/Course-BCSE306L%20Compiler%20Design-red.svg)](https://vit.ac.in)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Author Information
- **Author:** Shrri Dharshan D R
- **GitHub:** [@shrridharshan27](https://github.com/shrridharshan27)
- **Registration Number:** `23BPS1090`
- **Course:** Compiler Design Laboratory (`BCSE306L`)
- **Lab Slot:** `L23+L24`

---

## Overview
This repository contains a **Recursive Descent Parser (RDP)** implemented in C for LL(1) arithmetic expressions. Recursive descent is a top-down parsing technique where each non-terminal of the context-free grammar maps directly to a mutual recursive function.

### Grammar Transformations (Left Recursion Removal)
The original grammar with left recursion:
```
E -> E + T | E - T | T
T -> T * F | T / F | F
F -> ( E ) | id | num
```
Transformed LL(1) Grammar without left recursion:
```
E  -> T E'
E' -> '+' T E' | '-' T E' | e
T  -> F T'
T' -> '*' F T' | '/' F T' | e
F  -> '(' E ')' | id | num
```

---

## Compilation & Execution
```bash
# Compile with GCC
gcc -std=c99 -Wall -Wextra src/recursive_descent.c -o build/recursive_descent

# Run test suite
./build/recursive_descent
```

### Sample Output
```
Testing Input: "a + b * c"
  Result: [SUCCESS] Parsing Successful! Valid LL(1) Expression.

Testing Input: "a * + b"
  Result: [FAILED] Syntax Error in F: Unexpected symbol '+' at index 4

Testing Input: "(a + b * c"
  Result: [FAILED] Syntax Error in F: Missing closing parenthesis ')'
```

---

## License
MIT License - see [LICENSE](LICENSE) for details.
