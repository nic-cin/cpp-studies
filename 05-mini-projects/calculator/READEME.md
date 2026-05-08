# calculator

```txt
terminal calculator with expression parsing, history and ans memory
```

---

## features

```txt
- basic operators: + - * / ^
- parentheses support
- operator precedence
- recursive descent parser
- command history
- ans variable
- division by zero handling
```

---

## usage

```bash
g++ -std=c++11 main.cpp -o calc
./calc
```

Windows:

```powershell
g++ -std=c++11 main.cpp -o calc.exe
.\calc.exe
```

Visual Studio:

```txt
Ctrl + F5
```

---

## commands

```txt
history   show previous calculations
clear     clear history
ans       show last result
quit      exit calculator
q         exit calculator
exit      exit calculator
```

---

## examples

```txt
> 2 + 3 * 4
= 14

> (2 + 3) * 4
= 20

> 2^10
= 1024

> ans / 2
= 512

> 355 / 113
= 3.14159292
```

---

## notes

```txt
multiplication must be explicit
```

Valid:

```txt
2 * (3 + 4)
```

Invalid:

```txt
2(3 + 4)
```

---

## concepts used

```txt
recursive descent parsing
operator precedence
vectors
structs
strings
exception handling
history storage
terminal input/output
```

---

*built while learning c++.*