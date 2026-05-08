# cpp-studies

```txt
learning c++ through low level projects
```

---

## structure

```txt
cpp-studies/
├── 01-basics/
│   ├── loops.cpp
│   └── functions.cpp
│
├── 02-pointers/
│   └── pointers.cpp
│
├── 03-structs/
│   └── structs.cpp
│
├── 04-files/
│   └── files.cpp
│
└── 05-mini-projects/
    ├── password-generator/
    ├── ascii-animation/
    ├── task-manager/
    ├── calculator/
    └── mini-shell/
```

---

## running any file

```bash
g++ -std=c++11 filename.cpp -o out && ./out
```

Windows:

```powershell
g++ -std=c++11 filename.cpp -o out.exe
.\out.exe
```

---

## mini projects

### password-generator

```txt
configurable password generator
entropy estimation
strength labels
```

```bash
cd 05-mini-projects/password-generator
g++ main.cpp -o passgen && ./passgen 24 5
```

---

### ascii-animation

```txt
spinner
progress bar
bouncing ball
matrix rain
ansi terminal rendering
```

```bash
cd 05-mini-projects/ascii-animation
g++ -std=c++11 main.cpp -o animation && ./animation
```

---

### task-manager

```txt
persistent terminal task manager
add / remove / complete tasks
file-based storage
timestamps
```

```bash
cd 05-mini-projects/task-manager
g++ -std=c++11 main.cpp -o tasks && ./tasks
```

---

### calculator

```txt
expression parser
operator precedence
history system
ans memory
```

```txt
> 2 + 3 * 4
= 14

> (2 + 3) * 4
= 20

> 2^10
= 1024
```

```bash
cd 05-mini-projects/calculator
g++ -std=c++11 main.cpp -o calc && ./calc
```

---

### mini-shell

```txt
minimal unix shell
fork / execvp / pipe
builtins + command history
```

```txt
.../cpp-studies $ ls
.../cpp-studies $ cd 01-basics
.../01-basics   $ history
```

```bash
cd 05-mini-projects/mini-shell
g++ -std=c++11 main.cpp -o shell && ./shell
```

> linux / mac only (POSIX APIs)

---

## concepts covered

```txt
loops           while / for / do-while / range-based
functions       recursion / overloading / pass-by-ref
pointers        arithmetic / double pointers
memory          stack vs heap / new-delete
structs         nested structs / defaults / pointers
file i/o        ifstream / ofstream / csv parsing
processes       fork / execvp / pipe / waitpid
terminal        ansi escape sequences / cursor control
parsing         recursive descent parser
randomness      mt19937 / distributions / shuffle
```

---

## currently learning

```txt
- systems programming
- terminal rendering
- parsers
- memory management
- process control
- low level concepts
```

---

## screenshots

### calculator

```txt
+-----------------------+
|      calculator       |
+-----------------------+
```

### task-manager

```txt
[ ] #1 study pointers
[x] #2 build parser
```

### ascii-animation

```txt
matrix rain / bouncing ball / progress bars
```

---

*built while learning. updated as i go.*