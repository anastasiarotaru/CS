#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <string.h>

#define ROMANIAN_ALPHA_SIZE 31

// Romanian alphabet with diacritics in the correct order.
const wchar_t ROMANIAN_LETTERS[] = L"AĂÂBCDEFGHIÎJKLMNOPQRSȘTȚUVWXYZ";

int char_to_code(wchar_t c) {
    for (int i = 0; i < ROMANIAN_ALPHA_SIZE; i++) {
        if (ROMANIAN_LETTERS[i] == c) {
            return i;
        }
    }
    return -1;
}

wchar_t code_to_char(int code) {
    if (code >= 0 && code < ROMANIAN_ALPHA_SIZE) {
        return ROMANIAN_LETTERS[code];
    }
    return L'?';
}

wchar_t normalize_char(wchar_t c) {
    return towupper(c);
}

int validate_key(int key) {
    return key >= 1 && key <= ROMANIAN_ALPHA_SIZE - 1;
}

wchar_t encrypt_char(wchar_t c, int key) {
    int code = char_to_code(c);
    if (code == -1) {
        return L'\0';
    }

    int encrypted = (code + key) % ROMANIAN_ALPHA_SIZE;
    return code_to_char(encrypted);
}

wchar_t decrypt_char(wchar_t c, int key) {
    int code = char_to_code(c);
    if (code == -1) {
        return L'\0';
    }

    int decrypted = (code - key + ROMANIAN_ALPHA_SIZE) % ROMANIAN_ALPHA_SIZE;
    return code_to_char(decrypted);
}

int encrypt_text(const wchar_t* plaintext, wchar_t* ciphertext, int key) {
    int j = 0;

    for (int i = 0; plaintext[i] != L'\0'; i++) {
        wchar_t c = plaintext[i];

        if (c == L' ' || c == L'\n' || c == L'\r' || c == L'\t') {
            continue;
        }

        c = normalize_char(c);

        if (char_to_code(c) == -1) {
            wprintf(L"ERROR: Invalid character '%lc' in text. Only Romanian alphabet letters are allowed.\n", plaintext[i]);
            return 0;
        }

        wchar_t encrypted = encrypt_char(c, key);
        if (encrypted == L'\0') {
            wprintf(L"ERROR: Invalid character '%lc' in text.\n", plaintext[i]);
            return 0;
        }

        ciphertext[j++] = encrypted;
    }

    ciphertext[j] = L'\0';
    return 1;
}

int decrypt_text(const wchar_t* ciphertext, wchar_t* plaintext, int key) {
    int j = 0;

    for (int i = 0; ciphertext[i] != L'\0'; i++) {
        wchar_t c = ciphertext[i];

        if (c == L' ' || c == L'\n' || c == L'\r' || c == L'\t') {
            continue;
        }

        c = normalize_char(c);

        if (char_to_code(c) == -1) {
            wprintf(L"ERROR: Invalid character '%lc' in text.\n", ciphertext[i]);
            return 0;
        }

        wchar_t decrypted = decrypt_char(c, key);
        if (decrypted == L'\0') {
            wprintf(L"ERROR: Invalid character '%lc' in text.\n", ciphertext[i]);
            return 0;
        }

        plaintext[j++] = decrypted;
    }

    plaintext[j] = L'\0';
    return 1;
}

void display_alphabet() {
    wprintf(L"\n=== Romanian Alphabet (n = 31) ===\n");
    wprintf(L"Letter: ");
    for (int i = 0; i < ROMANIAN_ALPHA_SIZE; i++) {
        wprintf(L"%lc  ", ROMANIAN_LETTERS[i]);
    }
    wprintf(L"\nCode:   ");
    for (int i = 0; i < ROMANIAN_ALPHA_SIZE; i++) {
        wprintf(L"%-3d", i);
    }
    wprintf(L"\n\n");
}

int main() {
    if (setlocale(LC_ALL, "") == NULL) {
        setlocale(LC_ALL, "C.UTF-8");
    }

    display_alphabet();

    int key;
    int operation;
    wchar_t buffer[1000];

    while (1) {
        wprintf(L"Choose operation:\n");
        wprintf(L"  1 - Encrypt\n");
        wprintf(L"  2 - Decrypt\n");
        wprintf(L"Enter choice (1 or 2): ");

        if (wscanf(L"%d", &operation) != 1 || (operation != 1 && operation != 2)) {
            wprintf(L"ERROR: Please enter 1 or 2.\n");
            while (getwchar() != L'\n');
            continue;
        }

        while (getwchar() != L'\n');
        break;
    }

    while (1) {
        wprintf(L"Enter key (1-30): ");
        if (wscanf(L"%d", &key) != 1) {
            wprintf(L"ERROR: Key must be an integer between 1 and 30.\n");
            while (getwchar() != L'\n');
            continue;
        }

        while (getwchar() != L'\n');

        if (!validate_key(key)) {
            wprintf(L"ERROR: Key must be an integer between 1 and 30.\n");
            continue;
        }
        break;
    }

    if (operation == 1) {
        wprintf(L"Enter plaintext: ");
    } else {
        wprintf(L"Enter ciphertext: ");
    }

    fgetws(buffer, 1000, stdin);
    size_t len = wcslen(buffer);
    if (len > 0 && buffer[len - 1] == L'\n') {
        buffer[len - 1] = L'\0';
    }

    wchar_t result[1000];

    if (operation == 1) {
        if (encrypt_text(buffer, result, key)) {
            wprintf(L"\nPlaintext:  %ls\n", buffer);
            wprintf(L"Ciphertext: %ls\n\n", result);
        }
    } else {
        if (decrypt_text(buffer, result, key)) {
            wprintf(L"\nCiphertext: %ls\n", buffer);
            wprintf(L"Plaintext:  %ls\n\n", result);
        }
    }

    return 0;
}