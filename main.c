#include <stdio.h>
#include <string.h>
#include <ctype.h>

static char wordList[99999];

//below is the comment I wrote in May... I hate myself - 2025 Dec 6 16:11
//do i need comments to my future me?
//i think i need but i won't write cuz i'm lazy
static void stringClean(char *input) {
    unsigned int counter = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != '\n' && input[i] != '|') {
            wordList[counter++] = input[i];
        }
    }
    wordList[counter] = '\0';
}

static int getShiftFromKey(const char *key, int *kIndex, int keyLen) {
    while (!islower(key[*kIndex])) {
        *kIndex = (*kIndex + 1) % keyLen;
    }
    int shift = key[*kIndex] - 'a';
    *kIndex = (*kIndex + 1) % keyLen;
    return shift;
}

static void stringDecode(char *key, char *context) {
    char decodedOut[99999];
    int i = 0, kIndex = 0;
    int keyLen = strlen(key);

    while (context[i] != '\0') {
        char charIn = context[i];
        if (islower(charIn)) {
            int shift = getShiftFromKey(key, &kIndex, keyLen);
            decodedOut[i] = ((charIn - 'a' - shift + 26) % 26) + 'a';
        } else if (isupper(charIn)) {
            int shift = getShiftFromKey(key, &kIndex, keyLen);
            decodedOut[i] = ((charIn - 'A' - shift + 26) % 26) + 'A';
        } else {
            decodedOut[i] = charIn;
        }
        i++;
    }
    decodedOut[i] = '\0';
    printf("%s\n", decodedOut);
}

static void stringEncode(char *key, char *context) {
    char encodedOut[99999];
    int i = 0, kIndex = 0;
    int keyLen = strlen(key);

    while (context[i] != '\0') {
        char charIn = context[i];
        if (islower(charIn)) {
            int shift = getShiftFromKey(key, &kIndex, keyLen);
            encodedOut[i] = ((charIn - 'a' + shift) % 26) + 'a';
        } else if (isupper(charIn)) {
            int shift = getShiftFromKey(key, &kIndex, keyLen);
            encodedOut[i] = ((charIn - 'A' + shift) % 26) + 'A';
        } else {
            encodedOut[i] = charIn;
        }
        i++;
    }
    encodedOut[i] = '\0';
    printf("%s\n", encodedOut);
}

// '|' illegal in context space/cap legal in key
int main() {
    char inputWord[99999];
    int instruction;
    char inputKey[999];

    printf("decode enter 1 encode enter 2\n");
    scanf("%d", &instruction);
    getchar();
    printf("instruction accepted. enter key (lowercase with space allowed):\n");
    fgets(inputKey, sizeof(inputKey), stdin);
    printf("key accepted. enter context:\n");
    fgets(inputWord, sizeof(inputWord), stdin);

    stringClean(inputWord);

    if (instruction == 1) {
        stringDecode(inputKey, wordList);
    } else if (instruction == 2) {
        stringEncode(inputKey, wordList);
    } else {
        printf("illegal input. rerun program");
    }
}

//code by Gnatear 2025 Mar 30 6:17