# ascii-animation

```txt
terminal ascii animations and visual effects in c++
```

---

## features

```txt
- animated spinner
- progress bar
- bouncing ball physics
- matrix rain effect
- ansi terminal control
- cursor movement
- windows ansi support
```

---

## animations

### spinner

```txt
loading | / - \
```

### progress bar

```txt
[##########----------] 50%
```

### bouncing ball

```txt
+--------------------------------------------------+
|                                                  |
|                     O                            |
|                                                  |
+--------------------------------------------------+
```

### matrix rain

```txt
a83f0d#92jf@2
x9d2mff02m1zz
```

green animated falling characters inspired by matrix terminals.

---

## usage

```bash
g++ -std=c++11 main.cpp -o animation
./animation
```

Windows:

```powershell
g++ -std=c++11 main.cpp -o animation.exe
.\animation.exe
```

Visual Studio:

```txt
Ctrl + F5
```

---

## menu

```txt
1. spinner
2. progress bar
3. bouncing ball
4. matrix rain
```

---

## concepts used

```txt
ansi escape sequences
terminal cursor control
multithreading sleep timing
random number generation
2d buffers
vector containers
simple physics simulation
frame rendering
```

---

## platform support

```txt
windows   supported
linux     supported
macos     supported
```

windows automatically enables ansi escape processing. :contentReference[oaicite:0]{index=0}

---

## notes

```txt
matrix rain uses pseudo-random falling character streams
bouncing ball uses velocity inversion for wall collisions
```

---

*built while learning c++ and terminal rendering.* 