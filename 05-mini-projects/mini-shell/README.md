# mini-shell

```txt
minimal unix shell built in c++
```

---

## features

```txt
- command execution via execvp
- process creation with fork
- pipe support using |
- builtin commands
- command history
- colored terminal prompt
- basic shell navigation
```

---

## builtins

```txt
cd
history
help
exit
quit
```

---

## usage

Linux / macOS:

```bash
g++ -std=c++11 main.cpp -o shell
./shell
```

WSL (Windows Subsystem for Linux):

```bash
cd /mnt/c/path/to/project
g++ -std=c++11 main.cpp -o shell
./shell
```

---

## examples

```txt
$ ls

$ pwd

$ cd ..

$ history

$ cat file.txt | wc -l

$ help

$ exit
```

---

## pipe support

```txt
command1 | command2
```

example:

```txt
cat main.cpp | wc -l
```

---

## concepts used

```txt
fork()
execvp()
pipe()
dup2()
waitpid()
process management
stdin/stdout redirection
token parsing
command history
terminal prompt rendering
```

---

## notes

```txt
this project uses POSIX APIs and does not compile on Windows/MSVC
```

required headers:

```txt
unistd.h
sys/wait.h
```

supported platforms:

```txt
linux
macos
wsl
```

---

## shell prompt

```txt
.../mini-shell $
```

prompt automatically displays the current working directory.

---

## architecture

```txt
input
  ↓
tokenize()
  ↓
builtin check
  ↓
fork()
  ↓
execvp()
  ↓
waitpid()
```

---

*built while learning low level process management in c++.*