# password-generator

```txt
terminal password generator with configurable charset and entropy estimate
```

---

## features

```txt
- interactive mode
- command line arguments
- custom password length
- generate multiple passwords
- lowercase / uppercase / digits / symbols
- entropy estimation
- strength label
```

---

## usage

```bash
g++ main.cpp -o passgen
./passgen
```

Windows:

```powershell
g++ main.cpp -o passgen.exe
.\passgen.exe
```

Visual Studio:

```txt
Ctrl + F5
```

---

## examples

interactive mode:

```bash
./passgen
```

generate one password with length 24:

```bash
./passgen 24
```

generate 5 passwords with length 24:

```bash
./passgen 24 5
```

Windows:

```powershell
.\passgen.exe 24 5
```

---

## options

```txt
length       password size between 4 and 256
count        number of passwords to generate
uppercase    optional
digits       optional
symbols      optional
```

---

## example output

```txt
+-----------------------------+
|     password generator      |
+-----------------------------+

length [16]: 24
count  [1]:  3
include uppercase? [Y/n]: Y
include digits?    [Y/n]: Y
include symbols?   [Y/n]: Y

entropy : ~144 bits (very strong)
--------------------------------
Qp9@zL2#vT8!mX4$cR7%aB1&
K7!vRm2@Qa9#tL0%zXp4$Nw
xA8#Lm2!Qz7$vP9@Rt4%Kb
--------------------------------
```

---

## strength labels

```txt
< 40 bits    weak
< 60 bits    fair
< 80 bits    strong
>= 80 bits   very strong
```

---

## concepts used

```txt
random_device
mt19937
uniform_int_distribution
string manipulation
structs
command line arguments
lambda functions
shuffle
basic entropy estimation
interactive terminal input
```

---

## notes

```txt
the generator ensures at least one character from each enabled charset
```

```txt
entropy is an approximation based on selected charset size and password length
```

---

*built while learning c++ and terminal utilities.*