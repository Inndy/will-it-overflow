#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

const char * const AAAAAAAA = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

void test(char *buffer, int length)
{
    if(buffer[16] == (char)0xff) {
        puts("Safe");
        if(buffer[15] != 0) {
            puts("But vulerable to information leakage (Not ensure that NULL terminated)");
        }
    } else {
        printf("Pwned: %.2x\n", (unsigned char)buffer[16]);
    }
}

int main()
{
    char buffer[17];

    puts("Round 0: scanf %s");
    memset(buffer, 0xff, 17);
    sscanf(AAAAAAAA, "%s", buffer);
    test(buffer, 16);

    puts("Round 1: scanf %16s");
    memset(buffer, 0xff, 17);
    sscanf(AAAAAAAA, "%16s", buffer);
    test(buffer, 16);

    puts("Round 2: fgets");
    memset(buffer, 0xff, 17);
    FILE *fp = fopen("AAAAAAAA", "r");
    fgets(buffer, 16, fp);
    fclose(fp);
    test(buffer, 16);

    puts("Round 3: fread");
    memset(buffer, 0xff, 17);
    FILE *fp2 = fopen("AAAAAAAA", "r");
    fread(buffer, 16, 1, fp2);
    fclose(fp2);
    test(buffer, 16);

    puts("Round 4: strcpy");
    memset(buffer, 0xff, 17);
    strcpy(buffer, AAAAAAAA);
    test(buffer, 16);

    puts("Round 5: strncpy");
    memset(buffer, 0xff, 17);
    strncpy(buffer, AAAAAAAA, 16);
    test(buffer, 16);

    puts("Round 6: read");
    memset(buffer, 0xff, 17);
    int fd = open("AAAAAAAA", O_RDONLY);
    read(fd, buffer, 16);
    close(fd);
    strncpy(buffer, AAAAAAAA, 16);
    test(buffer, 16);

    exit(0);
}
