#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Defining a type of one bite size
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover.c image\n");
        return 1;
    }

    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");

    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // Buffer is an array tipe BYTE of size 512
    BYTE buffer[512];

    // Starting an image counter for found images
    int imagecount = 0;

    // Pointer to the file created at the end of the code
    FILE *imagepointer = NULL;

    // Allocation of memory for the extrated data
    char *output = malloc(8 * sizeof(char));

    // while fread returns 1, continue
    // fread => into buffer, insert the information for each 1 size of 512 bites from input
    while (fread(buffer, 512, 1, inptr))
    {
        // Checking the first 4 bites, the fourth: buffer[3] is being compared bit to bit to OxF0, if it's equal to 0xe0, returns true
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // In output, insert the JPG file name, using imagecount number
            sprintf(output, "%03i.jpg", imagecount);

            // In image pointer, write the data from output
            imagepointer = fopen(output, "w");

            // Increments image counter
            imagecount++;

        }

        // If there is data in imagepointer, write it in imagepointer the data from buffer
        if (imagepointer != NULL)
        {
            fwrite(&buffer, 512, 1, imagepointer);
        }
    }
    free(output);
    fclose(inptr);
    fclose(imagepointer);

    return 0;

}