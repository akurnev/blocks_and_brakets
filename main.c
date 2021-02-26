#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum BOOLEAN_TAG
{
    FALSE = 0,
    TRUE = 1

} BOOLEAN_T;

typedef struct BLOCK_TAG BLOCK_T;

struct BLOCK_TAG 
{
    BLOCK_T* next_sp;
    BLOCK_T* prev_sp;
    BLOCK_T** child_sp;
    BLOCK_T* parent_sp;
    BOOLEAN_T isComplete;
};
/*
 *
 */
void processFile(FILE* fp)
{
    int c;
    int openBraketsCounter = 0;
    int closeBraketsCounter = 0;
    BLOCK_T* currentBlock_sp = NULL;
    BLOCK_T* block_sp = NULL;

    while (EOF != (c = (fgetc(fp))))
    {
        printf("[DEBUG]: character is %d\n", c);
        if (c == '{')
        {
            block_sp = (BLOCK_T *) malloc(sizeof(BLOCK_T));
            if (NULL == block_sp) 
            {
                /*
                 * @TBD refactor
                 */
                printf("[ERROR]: malloc issue\n");
                return;
            }
            memset(block_sp, 0, sizeof(BLOCK_T));

            currentBlock_sp = block_sp;

            openBraketsCounter++;
        }
        if (c == '}')
        {   
            if (currentBlock_sp == block_sp)
            {
                block_sp->isComplete = TRUE;
            }

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