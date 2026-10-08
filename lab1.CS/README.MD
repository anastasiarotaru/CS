# Caesar Cipher with Keyword Permutation

A comprehensive implementation of the classical Caesar cipher and its strengthened variant using keyword permutation, applied to the Romanian alphabet (31 letters).

## Project Overview

This laboratory work demonstrates fundamental cryptographic concepts through two implementations:

1. **Task 1.1 - Classical Caesar Cipher**: Simple substitution cipher with shift-based encryption
2. **Task 1.2 - Caesar Cipher with Keyword Permutation**: Enhanced version using alphabet permutation for increased key space

Both implementations support the complete Romanian alphabet including diacritical marks (Ă, Â, Ș, Ț, Î) using wide character support (wchar_t) and UTF-8 encoding.

## Features

✅ Full Romanian alphabet support (31 letters with diacritics)  
✅ UTF-8 character encoding with wide character (wchar_t) support  
✅ Modular, well-commented C code  
✅ Comprehensive input validation and error handling  
✅ Both encryption and decryption operations  
✅ Easy-to-use interactive CLI interface  

## Project Structure

```
.
├── caesar_task1.c          # Task 1.1: Classical Caesar cipher
├── caesar_task2.c          # Task 1.2: Caesar cipher with keyword permutation
├── Makefile                # Build configuration
├── README.md               # This file
└── report.pdf              # Detailed laboratory report (LaTeX compiled)
```

## Compilation

### Prerequisites

- C99-compliant compiler (GCC or Clang)
- POSIX-standard C library with wide character support
- Make (optional, for using Makefile)

### Using Makefile (Recommended)

```bash
make all                    # Compile both programs
make caesar_task1           # Compile Task 1.1 only
make caesar_task2           # Compile Task 1.2 only
make clean                  # Remove compiled binaries
```

### Manual Compilation

**macOS with Clang:**
```bash
clang -fcolor-diagnostics -fansi-escape-codes -g -o caesar_task1 caesar_task1.c
clang -fcolor-diagnostics -fansi-escape-codes -g -o caesar_task2 caesar_task2.c
```

**Linux/macOS with GCC:**
```bash
gcc -Wall -Wextra -std=c99 -o caesar_task1 caesar_task1.c
gcc -Wall -Wextra -std=c99 -o caesar_task2 caesar_task2.c
```

## Usage

### Task 1.1 - Classical Caesar Cipher

```bash
./caesar_task1
```

Follow the interactive prompts:
1. Choose operation: **1** for encrypt, **2** for decrypt
2. Enter numeric key: value between **1-30**
3. Enter text: plaintext for encryption, ciphertext for decryption

**Example:**
```
Choose operation: 1
Enter key (1-30): 3
Enter plaintext: HELLO

Plaintext:  HELLO
Ciphertext: KHOOR
```

### Task 1.2 - Caesar Cipher with Keyword Permutation

```bash
./caesar_task2
```

Follow the interactive prompts:
1. Choose operation: **1** for encrypt, **2** for decrypt
2. Enter numeric key: value between **1-30**
3. Enter keyword: **at least 7 Romanian letters** (no numbers/special chars)
4. Enter text: plaintext for encryption, ciphertext for decryption

**Example:**
```
Choose operation: 1
Enter numeric key (1-30): 5
Enter keyword (at least 7 Romanian letters): CRYPTOGRAPHY
Keyword: CRYPTOGRAPHY

Permuted Alphabet
Position: C R Y P T O G A H B D E F I Î J K L M N Q S Ș U V W X Z Ă Â Ț
Code:     0 1 2 3 4 5 6 7 8 9 ...

Enter plaintext: HELLO

Plaintext:  HELLO
Ciphertext: TOOIV
```

## Mathematical Background

### Caesar Cipher Formula

**Encryption:** `C = (P + k) mod 31`  
**Decryption:** `P = (C - k + 31) mod 31`

Where:
- `P` = plaintext letter position (0-30)
- `C` = ciphertext letter position (0-30)
- `k` = shift key (1-30)
- `31` = size of Romanian alphabet

### Key Space

| Cipher | Key Space | Security (bits) |
|--------|-----------|-----------------|
| Classical Caesar | 30 | ~4.9 |
| With Permutation | 31! × 30 ≈ 8.2×10³³ | ~110 |
| AES-128 | 2^128 | 128 |

## Romanian Alphabet Encoding

The Romanian alphabet (31 letters) is encoded as:

```
Position: 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
Letter:   A  Ă  Â  B  C  D  E  F  G  H  I  Î  J  K  L  M  N

Position: 17 18 19 20 21 22 23 24 25 26 27 28 29 30
Letter:   O  P  Q  R  S  Ș  T  Ț  U  V  W  X  Y  Z
```

## Character Encoding

Both implementations use **wide characters (wchar_t)** for proper UTF-8 support:

- Wide character literals: `L"AĂÂBCDEF..."`
- Wide I/O functions: `wprintf()`, `wscanf()`
- Locale initialization: `setlocale(LC_ALL, "")`
- String handling: `wcslen()`, `fgetws()`, `getwchar()`

This ensures Romanian diacritics display and encrypt correctly on all systems.

## Security Analysis

### Strengths
- Keyword permutation increases key space from 30 to 8.2×10³³
- Well-structured, readable code with validation
- Proper handling of edge cases

### Weaknesses
- **Frequency Analysis**: Both ciphers are monoalphabetic substitution ciphers; each plaintext letter consistently encrypts to the same ciphertext letter, preserving letter frequency patterns
- **Limited Modern Security**: Neither cipher is suitable for real-world cryptographic applications
- **Classical Nature**: Historical teaching tools, not practical encryption

### Recommendations
For actual cryptographic needs, use modern algorithms:
- **Symmetric**: AES (Advanced Encryption Standard)
- **Asymmetric**: RSA, ECDSA
- **Stream**: ChaCha20, Salsa20

## Testing Checklist

- [ ] Compile both programs without errors
- [ ] Task 1.1: Encrypt simple text (e.g., "ABCD" with key=3 → "DEFG")
- [ ] Task 1.1: Decrypt ciphertext to recover plaintext
- [ ] Task 1.1: Test wrap-around (e.g., "Z" with key=1 → "A")
- [ ] Task 1.1: Test with Romanian letters (Ă, Â, Ș, Ț, Î)
- [ ] Task 1.1: Invalid key error (e.g., key=50 should be rejected)
- [ ] Task 1.1: Invalid character error (e.g., numbers should be rejected)
- [ ] Task 1.2: Keyword validation (< 7 chars should be rejected)
- [ ] Task 1.2: Permuted alphabet displays correctly with diacritics
- [ ] Task 1.2: Encrypt and decrypt with keyword permutation
- [ ] Task 1.2: Different keywords produce different permutations

## Laboratory Work Information

**Course**: Cryptography and Data Security  
**Assignment**: Laboratory Work No. 1  
**Objectives**:
- Understand substitution ciphers applied to non-standard alphabets
- Implement Caesar cipher for Romanian alphabet
- Strengthen Caesar cipher using keyword permutation
- Analyze key space and security implications
- Handle UTF-8 characters with diacritical marks in C

## Files Included

- `caesar_task1.c` - Task 1.1 implementation (wchar_t version for UTF-8 support)
- `caesar_task2.c` - Task 1.2 implementation (wchar_t version for UTF-8 support)
- `Makefile` - Build configuration
- `README.md` - This documentation
- `report.tex` - Complete laboratory report (LaTeX source)

## Compilation Notes

### macOS

Clang on macOS handles UTF-8 well with the `-fcolor-diagnostics` and `-fansi-escape-codes` flags:

```bash
clang -fcolor-diagnostics -fansi-escape-codes -g -o caesar_task1 caesar_task1.c
```

### Linux

Standard GCC compilation works fine:

```bash
gcc -Wall -Wextra -std=c99 -o caesar_task1 caesar_task1.c
```

### Terminal Settings

Ensure your terminal is set to UTF-8 encoding:

```bash
export LC_ALL=en_US.UTF-8
export LANG=en_US.UTF-8
./caesar_task1
```

## Author

**Rotaru Anastasia**  
Faculty of Computers, Informatics and Microelectronics  
Technical University of Moldova

## License

This project is provided as educational material for the Cryptography and Data Security course.

## Acknowledgments

- Romanian alphabet definition and encoding
- POSIX wide character library documentation
- Cryptography course materials

---

**Note**: These implementations are for educational purposes only and should not be used for real cryptographic security. For production use, employ modern, peer-reviewed cryptographic libraries such as OpenSSL, libsodium, or GnuTLS.