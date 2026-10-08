#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <string.h>

#define ROMANIAN_ALPHA_SIZE 31

// Romanian alphabet with diacritics in the correct order.
const wchar_t ROMANIAN_LETTERS[] = L"AĂÂBCDEFGHIÎJKLMNOPQRSȘTȚUVWXYZ";

// gaseste inexul unei litere in alfabet
int char_to_code(wchar_t c) {
    for (int i = 0; i < ROMANIAN_ALPHA_SIZE; i++) {
        if (ROMANIAN_LETTERS[i] == c) {
            return i;
        }
    }
    return -1;
}

// converteste intexul in litera corespunzatoare
wchar_t code_to_char(int code) {
    if (code >= 0 && code < ROMANIAN_ALPHA_SIZE) {
        return ROMANIAN_LETTERS[code];
    }
    return L'?';
}

// normalizeaza majusculele
wchar_t normalize_char(wchar_t c) {
    return towupper(c);
}

// crpteaza o litere cu un shift in dependenta de key 1
wchar_t encrypt_char(wchar_t c, int key) {
    int code = char_to_code(c);
    if (code == -1) return L'\0';

    int encrypted = (code + key) % ROMANIAN_ALPHA_SIZE;
    return code_to_char(encrypted);
}

// decripteaza o litere cu un shift in dependenta de key 1
wchar_t decrypt_char(wchar_t c, int key) {
    int code = char_to_code(c);
    if (code == -1) return L'\0';

    int decrypted = (code - key + ROMANIAN_ALPHA_SIZE) % ROMANIAN_ALPHA_SIZE;
    return code_to_char(decrypted);
}

// construieste alfabetul permutat
void build_permuted_alphabet(const wchar_t *keyword, wchar_t *permuted) {
    int used[ROMANIAN_ALPHA_SIZE] = {0};
    int index = 0;

    for (int i = 0; keyword[i] != L'\0'; i++) {
        wchar_t c = keyword[i];
        if (c == L' ' || c == L'\n' || c == L'\r' || c == L'\t') {
            continue;
        }

        c = normalize_char(c);
        int code = char_to_code(c);

        if (code != -1 && !used[code]) {
            permuted[index++] = c;
            used[code] = 1;
        }
    }

    for (int i = 0; i < ROMANIAN_ALPHA_SIZE; i++) {
        if (!used[i]) {
            permuted[index++] = ROMANIAN_LETTERS[i];
        }
    }

    permuted[index] = L'\0';
}

// gaseste indexul literei in alfabetul permutat
int char_position_in_permuted(wchar_t c, const wchar_t *permuted) {
    for (int i = 0; i < ROMANIAN_ALPHA_SIZE; i++) {
        if (permuted[i] == c) {
            return i;
        }
    }
    return -1;
}

// criptarea in baza alfabetului permutat
int encrypt_text(const wchar_t *plaintext, wchar_t *ciphertext, int key, const wchar_t *permuted) {
    int j = 0;

    for (int i = 0; plaintext[i] != L'\0'; i++) {
        wchar_t c = plaintext[i];

        if (c == L' ' || c == L'\n' || c == L'\r' || c == L'\t') {
            continue;
        }

        c = normalize_char(c);

        if (char_to_code(c) == -1) {
            wprintf(L"ERROR: Invalid character '%lc'. Only Romanian alphabet letters are allowed.\n", plaintext[i]);
            return 0;
        }

        int perm_pos = char_position_in_permuted(c, permuted);
        if (perm_pos == -1) {
            wprintf(L"ERROR: Invalid character '%lc'.\n", c);
            return 0;
        }

        int encrypted_index = (perm_pos + key) % ROMANIAN_ALPHA_SIZE;
        ciphertext[j++] = permuted[encrypted_index];
    }

    ciphertext[j] = L'\0';
    return 1;
}

// decriptarea in baza alfabetului permutat
int decrypt_text(const wchar_t *ciphertext, wchar_t *plaintext, int key, const wchar_t *permuted) {
    int j = 0;

    for (int i = 0; ciphertext[i] != L'\0'; i++) {
        wchar_t c = ciphertext[i];

        if (c == L' ' || c == L'\n' || c == L'\r' || c == L'\t') {
            continue;
        }

        c = normalize_char(c);

        if (char_to_code(c) == -1) {
            wprintf(L"ERROR: Invalid character '%lc'.\n", ciphertext[i]);
            return 0;
        }

        int perm_pos = char_position_in_permuted(c, permuted);
        if (perm_pos == -1) {
            wprintf(L"ERROR: Invalid character '%lc'.\n", c);
            return 0;
        }

        int decrypted_index = (perm_pos - key + ROMANIAN_ALPHA_SIZE) % ROMANIAN_ALPHA_SIZE;
        plaintext[j++] = permuted[decrypted_index];
    }

    plaintext[j] = L'\0';
    return 1;
}

void display_alphabet(void) {
    wprintf(L"\nRomanian Alphabet (n = 31)\n");
    wprintf(L"Letter: ");
    for (int i = 0; i < ROMANIAN_ALPHA_SIZE; i++) {
        wprintf(L"%lc  ", ROMANIAN_LETTERS[i]);
    }
    wprintf(L"\nCode:   ");
    for (int i = 0; i < ROMANIAN_ALPHA_SIZE; i++) {
        wprintf(L"%d  ", i);
    }
    wprintf(L"\n\n");
}

void display_permuted_alphabet(const wchar_t *permuted) {
    wprintf(L"\nPermuted Alphabet\n");
    wprintf(L"Position: ");
    for (int i = 0; i < ROMANIAN_ALPHA_SIZE; i++) {
        wprintf(L"%lc  ", permuted[i]);
    }
    wprintf(L"\nCode:     ");
    for (int i = 0; i < ROMANIAN_ALPHA_SIZE; i++) {
        wprintf(L"%d  ", i);
    }
    wprintf(L"\n\n");
}

int main(void) {
    if (setlocale(LC_ALL, "") == NULL) {
        setlocale(LC_ALL, "C.UTF-8");
    }

    display_alphabet();

    int key;
    int operation;
    wchar_t buffer[1000];
    wchar_t keyword[1000];
    wchar_t permuted[ROMANIAN_ALPHA_SIZE + 1];

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
        wprintf(L"Enter numeric key (1-30): ");
        if (wscanf(L"%d", &key) != 1) {
            wprintf(L"ERROR: Key must be an integer between 1 and 30.\n");
            while (getwchar() != L'\n');
            continue;
        }

        while (getwchar() != L'\n');

        if (key < 1 || key > 30) {
            wprintf(L"ERROR: Key must be an integer between 1 and 30.\n");
            continue;
        }
        break;
    }

    while (1) {
        wprintf(L"Enter keyword (at least 7 Romanian letters): ");
        fgetws(keyword, 1000, stdin);

        size_t len = wcslen(keyword);
        if (len > 0 && keyword[len - 1] == L'\n') {
            keyword[len - 1] = L'\0';
        }

        if (wcslen(keyword) < 7) {
            wprintf(L"ERROR: Keyword must have at least 7 characters.\n");
            continue;
        }

        int valid = 1;
        for (int i = 0; keyword[i] != L'\0'; i++) {
            wchar_t c = normalize_char(keyword[i]);
            if (c == L' ') continue;
            if (char_to_code(c) == -1) {
                wprintf(L"ERROR: Keyword contains invalid character '%lc'. Only Romanian alphabet letters are allowed.\n", keyword[i]);
                valid = 0;
                break;
            }
        }

        if (valid) break;
    }

    build_permuted_alphabet(keyword, permuted);

    wprintf(L"\nKeyword: %ls\n", keyword);
    display_permuted_alphabet(permuted);

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
        if (encrypt_text(buffer, result, key, permuted)) {
            wprintf(L"\nPlaintext:  %ls\n", buffer);
            wprintf(L"Ciphertext: %ls\n\n", result);
        }
    } else {
        if (decrypt_text(buffer, result, key, permuted)) {
            wprintf(L"\nCiphertext: %ls\n", buffer);
            wprintf(L"Plaintext:  %ls\n\n", result);
        }
    }

    return 0;
}