# CLocker - An XOR File Locker

CLocker is a lightweight educational file locker built in C. It encrypts and decrypts files within a given directory using XOR encryption and renames them based on their locked status.

> This project was built for learning purposes only — it is **not** intended for malicious use.

---

## Features

- Encrypts all regular files in a folder using XOR
- Renames encrypted files by appending `.locked`
- Automatically decrypts files and restores original names if run again
- Accepts full path and key from the user via terminal
- Works on Windows with minimal dependencies
- Modular C codebase (split into `.h` and `.c` files)

---

## How It Works

1. The program asks the user for:
   - Full path to a folder (e.g. `C:\Users\your_username\Desktop\important`)
   - A single-character key
2. It scans the folder for regular files.
3. If a file ends with `.locked`, it is decrypted and renamed to its original name.
4. If a file does **not** end with `.locked`, it is encrypted and renamed to `filename.locked`.

---

## Build Instructions

### Requirements

- GCC (MinGW for Windows)
- [`dirent.h`](https://github.com/tronkko/dirent) (portable version with `static` implementations)

### Compile

```bash
gcc main.c locker.c -o locker.exe
```

> No need for `dirent.c` if you're using the self-contained `dirent.h`.

---

## Usage

After compiling:

```bash
./locker.exe
```

Example input:

```
Please Enter the Full Path of the Folder: C:\Users\your_username\Desktop\top-secret
Please Enter the Key (char): A
```

Run again with the same key to unlock files.

---

## Disclaimer

This project was created solely for educational and demonstration purposes.  
**Do not use this tool on systems, files, or data you do not own or have permission to test.**

---

## License

Licensed under the [MIT License](./LICENSE.md). You’re free to use and modify responsibly.