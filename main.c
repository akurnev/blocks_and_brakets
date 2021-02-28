#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum RESULT_TAG
{
    RESULT_OK    = 0,
    RESULT_NOK   = 1,
    RESULT_ERROR = 2

} RESULT_T;

typedef enum BOOLEAN_TAG
{
    FALSE = 0,
    TRUE  = 1

} BOOLEAN_T;

typedef struct BLOCK_TAG BLOCK_T;

struct BLOCK_TAG 
{
    BLOCK_T* parent_sp;
    BOOLEAN_T isComplete;
};
/*
 *
 */
RESULT_T processFile(FILE* fp)
{
    int c;
    int openBraketsCounter   = 0;
    int closeBraketsCounter  = 0;
    BLOCK_T* currentBlock_sp = NULL;
    BLOCK_T* block_sp        = NULL;
    BLOCK_T* startBlock_sp   = NULL;
    RESULT_T result          = RESULT_OK;
    BLOCK_T *blockArray_p[100]  = {NULL};
    int i = 0;

    while (EOF != (c = (fgetc(fp))))
    {
        /* printf("[DEBUG]: character is %d\n", c);*/
        if (c == '{')
        {
            /* Allocate memory for a new block */
            block_sp = (BLOCK_T *) malloc(sizeof(BLOCK_T));
            if (NULL == block_sp) 
            {
                printf("[ERROR]: malloc issue\n");
                return RESULT_ERROR;
            }
            memset(block_sp, 0, sizeof(BLOCK_T));

            blockArray_p[i++] = block_sp;

            if (currentBlock_sp != NULL)
            {             
                if (currentBlock_sp->isComplete == TRUE)
                {
                    block_sp->parent_sp = currentBlock_sp->parent_sp;
                }
                else
                {
                    block_sp->parent_sp = currentBlock_sp;
                }
            }

            currentBlock_sp = block_sp;
            openBraketsCounter++;
        }
        if (c == '}')
        {   
            if (currentBlock_sp->isComplete == TRUE)
            {
                if (currentBlock_sp->parent_sp == NULL)
                {
                    return RESULT_NOK;
                }
                else
                {
                    currentBlock_sp = currentBlock_sp->parent_sp;
                    currentBlock_sp->isComplete = TRUE;
                }
            }
            else 
            {
                currentBlock_sp->isComplete = TRUE;
            }

            closeBraketsCounter++;
        }
    }

    printf("Number of open brakets: %d, Number of close brakets: %d\n",
                openBraketsCounter, closeBraketsCounter);

   
    for (i = 0; blockArray_p[i] != NULL; ++i)
    {
        if (blockArray_p[i]->isComplete == FALSE)
        {
            result = RESULT_NOK;
            break;
        }
    }

    for (i = 0; blockArray_p[i] != NULL; ++i)
    {
        free(blockArray_p[i]);
    }
     memset(blockArray_p, 0, sizeof(blockArray_p));

    return result;
}

/*
 *
 */     
int main(int argc, char** argv)
{
    RESULT_T result = RESULT_OK;

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


        result = processFile (fp);

        switch (result)
        {
            case RESULT_OK: 
            {
                fprintf(stdout, "%s: Balance of brakets in the file %s is OK\n",
                        argv[0], argv[1]);
                break;
            }
            case RESULT_NOK:
            {
                fprintf(stdout, "%s: Balance of brakets in the file %s is NOK\n",
                        argv[0], argv[1]);
                break;
            }
            case RESULT_ERROR:
            {
                fprintf(stderr, "%s: Internal error during processing of the file %s\n",
                        argv[0], argv[1]);
                break;
            }
            default:
            {

            }
        }

        fclose(fp);
    }

    return 0;
}