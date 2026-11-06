
#include  <stdio.h>
#include  <stdlib.h>

  int main(int argc, char *argv[])
{
    // 1. Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // 2. Open file in binary read mode
    FILE *file = fopen(argv[1], "rb");

    // 3. Check if file opened successfully
    if (file == NULL)
    {
        printf("Error: Cannot open file!\n");
        return 1;
    }

    // 4. Declare variables
    unsigned char buffer[16];
    size_t bytesRead;
    unsigned long offset = 0;

    printf("Offset   Hexadecimal Bytes                         ASCII\n");
    printf("---------------------------------------------------------------\n");

    // 5. Read file 16 bytes at a time
    while ((bytesRead = fread(buffer, 1, 16, file)) > 0)
    {
        // 6. Print memory offset
        printf("%08lX  ", offset);

        // 7. Print hexadecimal values
        for (size_t i = 0; i < 16; i++)
        {
            if (i < bytesRead)
            {
                printf("%02X ", buffer[i]);
            }
            else
            {
                printf("   ");
            }

            if (i == 7)
            {
                printf(" ");
            }
        }

        // 8. Print ASCII representation
        printf(" |");

        for (size_t i = 0; i < bytesRead; i++)
        {
            if (buffer[i] >= 32 && buffer[i] <= 126)
            {
                printf("%c", buffer[i]);
            }
            else
            {
                printf(".");
            }
        }

        printf("|\n");

        // 9. Update offset
        offset += bytesRead;
    }

    // 10. Close file
    fclose(file);

    return 0;
}
