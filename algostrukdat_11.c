#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct element *address;
struct element
{
    int info;
    address next;
    address prev;
};

typedef struct
{
    address first;
    address last;
} list_integer;

void CreateList(list_integer *a)
{
    a->first = NULL;
    a->last = NULL;
}

address CreateLm(int isi)
{
    address b = (address)malloc(sizeof(struct element));
    b->info = isi;
    b->next = NULL;
    b->prev = NULL;
    
    return b;
}

void InsertFirst(list_integer *a, address b)
{
    if ((a->first == NULL) && (a->last == NULL))
    {
        a->first = b;
        a->last = b;
        b->next = a->last;
        b->prev = a->first;
    }
    else
    {
        b->next = a->first;
        b->prev = a->last;
        a->first->prev = b;
        a->last->next = b;
        a->first = b;
    }
}

void InsertLast(list_integer *a, address b)
{
    if ((a->first == NULL) && (a->last == NULL))
    {
        a->first = b;
        a->last = b;
        b->next = a->last;
        b->prev = a->first;
    }
    else
    {
        b->prev = a->last;
        a->last->next = b;
        a->last = b;
        a->first->prev = a->last;
        a->last->next = a->first;
    }
}

void sortingAscending(list_integer *a, address new_node)
{
    if (a->first == NULL)
    {
        a->first = new_node;
        a->last = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
    }
    else if (a->first->info >= new_node->info)
    {
        address last = a->last;
        new_node->next = a->first;
        new_node->prev = last;
        last->next = new_node;
        a->first->prev = new_node;
        a->first = new_node;
    }
    else
    {
        address curr = a->first;
        while (curr->next != a->first && curr->next->info < new_node->info)
        {
            curr = curr->next;
        }
        new_node->next = curr->next;
        new_node->prev = curr;
        curr->next->prev = new_node;
        curr->next = new_node;
        if (curr == a->last)
        {
            a->last = new_node;
        }
    }
}

void Ascending(list_integer *a)
{
    if (a->first == NULL || a->first == a->last)
    {
        return;
    }

    list_integer new_list;
    CreateList(&new_list);

    address curr = a->first;
    address next;

    do
    {
        next = curr->next;
        curr->next = curr->prev = curr;
        sortingAscending(&new_list, curr);
        curr = next;
    }
    while (curr != a->first);

    a->first = new_list.first;
    a->last = new_list.last;
}

void TampilkanDaftar(list_integer a)
{
    if (a.first == NULL)
    {
        printf("\n[Daftar Kosong!]");
    }
    else
    {
        address current = a.first;
        do
        {
            printf("Di memori : %p, adalah Data ke %d\n", (void*)current, current->info);
            current = current->next;
        } while (current != a.first);
        printf("\n");
    }
}

int main()
{
    list_integer a;
    CreateList(&a);

    int N, isi;
    address b;

    printf("Masukkan jumlah data : ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        printf("Masukkan data ke-%d: ", i + 1);
        scanf("%d", &isi);
        b = CreateLm(isi);
        InsertLast(&a, b);
    }

    printf("List data sebelum pengurutan :\n");
    TampilkanDaftar(a);

    Ascending(&a);

    printf("List data setelah pengurutan :\n");
    TampilkanDaftar(a);

    return 0;
}