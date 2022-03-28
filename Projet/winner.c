#include <stdio.h>
#include <stdlib.h>
#include "listDeclaration.h"

void thwarted(CellProtected **LCP)  {
    if (!(*LCP))
        return;
    CellProtected *first = *LCP;
    CellProtected *prev = first;
    CellProtected *curr = first->next;

    while (curr)    {
        if (!verify(curr->data))  {
            prev->next = curr->next;
            delete_cell_protected(curr);
        } else {
            prev = curr;
        }
        curr = prev->next;
    }

    if (!verify(first->data)) {
        *LCP = first->next;
        delete_cell_protected(first);
    }
}