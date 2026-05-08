# task-manager

```txt
terminal task manager with persistent storage
```

---

## features

```txt
- add tasks
- mark tasks as completed
- remove tasks
- clear completed tasks
- automatic file persistence
- timestamps
- colored terminal output
```

---

## usage

```bash
g++ -std=c++11 main.cpp -o tasks
./tasks
```

Windows:

```powershell
g++ -std=c++11 main.cpp -o tasks.exe
.\tasks.exe
```

Visual Studio:

```txt
Ctrl + F5
```

---

## commands

```txt
[a] add
[d] done
[r] remove
[c] clear completed
[q] quit
```

---

## example

```txt
tasks: 3  done: 1  pending: 2
--------------------------------------------------

[ ] #1  study c++ pointers      (2026-05-08 03:21)
[x] #2  read networking docs    (2026-05-08 03:40)
[ ] #3  build task manager      (2026-05-08 04:10)

[a] add  [d] done  [r] remove  [c] clear done  [q] quit
```

---

## persistence

```txt
tasks are automatically saved to:
```

```txt
tasks.dat
```

format:

```txt
id|done|timestamp|task text
```

example:

```txt
1|0|2026-05-08 03:21|study c++ pointers
2|1|2026-05-08 03:40|read networking docs
```

---

## concepts used

```txt
file i/o
vectors
structs
timestamps
lambda expressions
remove_if
terminal ui
ansi colors
persistent storage
```

---

## architecture

```txt
load tasks
    ↓
render ui
    ↓
handle command
    ↓
save tasks
```

---

## notes

```txt
completed tasks are rendered in dim gray color
```

```txt
task ids are persistent and auto-incremented
```

---

*built while learning c++ and terminal applications.*