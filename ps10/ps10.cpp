#include <stdio.h>
#include <string.h>

void ConvertToScores(const char* input, int scores[21]) {
    int pos = 0, prevScore = 0;
    for (int i = 0; input[i] && pos < 21; i++) {
        char c = input[i];
        if (c == 'X' || c == 'x') scores[pos++] = 10;
        else if (c == '/') scores[pos++] = 10 - prevScore;
        else if (c == '-' || c == ' ') scores[pos++] = 0;
        else if (c >= '0' && c <= '9') scores[pos++] = c - '0';
        prevScore = (c >= '0' && c <= '9') ? (c - '0') : ((c == 'X' || c == 'x') ? 10 : 0);
    }
}

int ScoreFromFrame(const int pins[21], int frame) {
    int pos = frame * 2;
    if (frame == 9) return pins[18] + pins[19] + pins[20];
    
    if (pins[pos] == 10) {
        if (pins[pos+2] == 10)
            return 20 + (frame < 8 ? pins[pos+4] : pins[pos+3]);
        return 10 + pins[pos+2] + pins[pos+3];
    }
    
    if (pins[pos] + pins[pos+1] == 10)
        return 10 + pins[pos+2];
    return pins[pos] + pins[pos+1];
}

int main(void) {
    char str[256];
    fgets(str, 255, stdin);
    
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') str[--len] = '\0';
    if (len < 21) { printf("Too Short"); return 0; }
    
    for (int i = 0; str[i]; i++) {
        char c = str[i];
        if (c != 'X' && c != 'x' && c != '/' && c != '-' && c != ' ' && 
            (c < '0' || c > '9')) {
            printf("Wrong Character");
            return 0;
        }
    }
    
    int scores[21] = {0}, total = 0;
    ConvertToScores(str, scores);
    for (int i = 0; i < 10; i++) total += ScoreFromFrame(scores, i);
    printf("%d", total);
    return 0;
}