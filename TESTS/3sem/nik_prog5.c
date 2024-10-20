#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 0;
    }
    
    FILE **files = (FILE **)calloc(argc - 1, sizeof(FILE *));
    int *streams = (int *)calloc(argc - 1, sizeof(int));

    for (int i = 1; i < argc; i++)
    {
        files[i - 1] = fopen(argv[i], "r");
    }

    for (int i = 0; i < (argc - 1); i++)
    {
        if (files[i] != NULL)
        {
            fscanf(files[i], "%d", &streams[i]);
        }
    }

    while (1)
    {
        int min_num = streams[0];
        int min_index = 0;
        int count = 0;

        for (int i = 0; i < (argc - 1); i++)
        {
            if (!feof(files[i]))
            {
                if (feof(files[min_index]))
                {
                    min_index = i;
                    min_num = streams[i];
                }
                if (streams[i] < min_num)
                {
                    min_num = streams[i];
                    min_index = i;
                }
            } else {
                count++;
            }
        }
        if(count == (argc - 1))
        {
            break;
        }
        printf("%d ", min_num);
        fscanf(files[min_index], "%d", &streams[min_index]);

    }
    printf("\n");

    return 0;
}