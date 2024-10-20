#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    struct Node *prev, *next;
    char *elem;
};

struct List
{
    struct Node *first, *last;
};

void print(struct Node *buffer)
{
    while (buffer != NULL)
    {
        printf("%s ", buffer->elem);
        buffer = buffer->next;
    }
    printf("\n");
}

void process(struct List *pl, const char *str)
{

    struct Node *iter = pl->first;

    struct Node *suffix_node = NULL;

    struct Node *suffix_iter = NULL;

    struct Node *del = NULL;

    struct Node *copy = NULL;



    if (iter == NULL)
        return;

    while (iter != NULL)
    {
        int compare_str = strcmp(iter->elem, str);

        if (compare_str == 0) // DELETE
        {
            if (iter->prev == NULL)
            {
                if (iter->next == NULL)
                {
                    pl->first = NULL;
                    pl->last = NULL;
                }
                else
                {
                    pl->first = iter->next;
                    pl->first->prev = NULL;
                }
            }
            else
            {
                if (iter->next == NULL)
                {
                    pl->last = iter->prev;
                    pl->last->next = NULL;
                }
                else
                {
                    iter->prev->next = iter->next;
                    iter->next->prev = iter->prev;
                }
            }

            del = iter;
            iter = iter->next;

            free(del->elem);
            free(del);
        }

        else if (compare_str > 0)
        {
            copy = iter->next;

            if (iter->prev == NULL)
            {
                if (iter->next != NULL)
                {
                    pl->first = iter->next;
                    pl->first->prev = NULL;
                }
                iter->prev = NULL;
                iter->next = NULL;

                if (suffix_node == NULL)
                {
                    suffix_node = iter;
                    suffix_iter = suffix_node;
                }
                else
                {
                    suffix_iter->next = iter;
                    iter->prev = suffix_iter;
                    suffix_iter = iter;
                }

                if (copy == NULL)
                {
                    pl->first = NULL;
                    pl->last = NULL;
                }
            }
            else
            {
                if (iter->next != NULL)
                {
                    iter->prev->next = iter->next;
                    iter->next->prev = iter->prev;
                }
                else
                {
                    pl->last = iter->prev;
                    pl->last->next = NULL;
                }
                iter->prev = NULL;
                iter->next = NULL;

                if (suffix_node == NULL)
                {
                    suffix_node = iter;
                    suffix_iter = suffix_node;
                }
                else
                {
                    suffix_iter->next = iter;
                    iter->prev = suffix_iter;
                    suffix_iter = iter;
                }
            }
            iter = copy;
        }
        else
        {
            iter = iter->next;
        }
    }

    if (pl->first == NULL && pl->last == NULL)
    {
        pl->first = suffix_node;
        pl->last = suffix_iter;
    }
    else
    {
        if (suffix_node != NULL)
        {
            pl->last->next = suffix_node;
            suffix_iter->prev = pl->last;
            pl->last = suffix_iter;
        }
    }
}

int main(int argc, char **argv)
{
    struct List *list = (struct List *)calloc(1, sizeof(struct List *));

    list->first = NULL;
    list->last = NULL;
    char str[256];

    while (scanf("%s", &str) != EOF)
    {
        struct Node *bufNode = (struct Node *)calloc(1, sizeof(struct Node *));

        bufNode->elem = (char *)calloc(strlen(str) + 1, sizeof(char));
        strcpy(bufNode->elem, str);
        bufNode->next = NULL;

        if (list->first == NULL && list->last == NULL)
        {
            list->first = bufNode;
            list->last = bufNode;
            bufNode->prev = NULL;
        }
        else
        {
            list->last->next = bufNode;
            bufNode->prev = list->last;
            list->last = bufNode;
        }
    }

    print(list->first);

    process(list, "a");

    print(list->first);

    return 0;
}