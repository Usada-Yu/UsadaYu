#include <stdio.h>
#include "containerOf.h"

typedef struct {
    int     member_1;
    int     member_2;
    char    resv[3];
    int     member_3;
} struct_object;

int main() {
    struct_object   object1         = {0};
    struct_object   *object_ptr     = NULL;
    int             *mem_ptr        = NULL;

    mem_ptr = &(object1.member_2);
    object_ptr = container_of(mem_ptr, struct_object, member_2);

    printf("Address: [object1: %p] [object_ptr: %p]\n", &object1, object_ptr);

    return 0;
}
