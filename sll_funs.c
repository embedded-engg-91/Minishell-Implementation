#include "msh.h"

pid_t backup_pid = 0;

int insert_at_last(Slist **head, pid_t pid, char *input_str)
{
    Slist *new_node = malloc(sizeof(Slist));
    if (new_node == NULL)
    {
        return FAILURE;
    }
    strcpy(new_node->p_name, input_str);
    new_node->pid = pid;
    new_node->link = NULL;
    if ((*head) == NULL)
    {
        *head = new_node;
        return SUCCESS;
    }
    Slist *temp = (*head);
    while (temp->link != NULL)
    {
        temp = temp->link;
    }
    temp->link = new_node;
    return SUCCESS;
}

void print_list(Slist *head)
{
    int ind = 1;
    if (head == NULL)
    {
        printf("INFO : No jobs remaining\n");
    }
    else
    {
        while (head)
        {
            printf("[%d] Stopped PID %d      %s\n", ind++, head->pid, head->p_name);
            head = head->link;
        }

        printf("\n");
    }
}

int sl_delete_last(Slist **head)
{

    if (*head == NULL)
    {
        printf("No jobs Remaining\n");
        return FAILURE;
    }
    if ((*head)->link == NULL)
    {
        backup_pid = (*head)->pid;

        free((*head));
        (*head) = NULL;
        return SUCCESS;
    }
    Slist *temp = (*head);
    Slist *backup = temp;
    while (temp->link != NULL)
    {
        backup = temp;
        temp = temp->link;
    }
    backup_pid = temp->pid;
    free(temp);
    backup->link = NULL;
    return SUCCESS;
}