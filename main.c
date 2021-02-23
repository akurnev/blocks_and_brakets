#include <stdio.h>

/*
 *
 */
void processFile(FILE* fp)
{
    int c;
    int openBraketsCounter = 0;
    int closeBraketsCounter = 0;

    while (EOF != (c = (fgetc(fp))))
    {
        printf("[DEBUG]: character is %d\n", c);
        if (c == '{')
        {
            openBraketsCounter++;
        }
        if (c == '}')
        {   
            closeBraketsCounter++;
        }
    }

    printf("Number of open brakets: %d, Number of close brakets: %d\n",
                openBraketsCounter, closeBraketsCounter);
}

/*
 *
 */     
int main(int argc, char** argv)
{
    printf("Hello Block!\n");
    if (argc != 2)
    {
        fprintf(stderr, "%s: Wrong number of arguments. "
            "Should be only one: name of sample file\n", argv[0]);
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == 0)
    {
        fprintf(stderr, "%s: failed to open sample " 
            "file %s for reading\n", argv[0], argv[1]);
        return 2;
    }
    else
    {
        fprintf(stdout, "%s: Sample file %s is ready for processing\n",
            argv[0], argv[1]);


        processFile (fp);

        /*
         * Some processing
         */   
        fclose(fp);
    }

    return 0;
}