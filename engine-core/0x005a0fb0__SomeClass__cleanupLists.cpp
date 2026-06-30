// FUNC_NAME: SomeClass::cleanupLists
// Function address: 0x005a0fb0
// Role: Destructor/cleanup for a class containing three embedded linked lists.
// Offsets:
//   +0x08: pointer to first list head (sentinel)
//   +0x0C: sentinel's self-pointer (end marker)
//   +0x14: second list sentinel
//   +0x18: second list end marker
//   +0x34: third list sentinel
//   +0x38: third list end marker
//   +0x54: base offset for iterating over the second and third lists

void SomeClass::cleanupLists()
{
    int *listHead;
    int *node;
    int i;

    // Clean up first list (at +0x08)
    listHead = *(int **)(this + 8);
    if (listHead != (int *)(this + 0x0C)) {
        // Remove and delete all nodes in the first list
        FUN_005a16d0(listHead);
    }

    // Clean up second and third lists (at +0x14 and +0x34)
    // Loop twice: first iteration handles list at +0x34, second at +0x14
    i = 1;
    int *listBase = (int *)(this + 0x54);
    do {
        // For each list, get the head pointer (offset -0x20 from listBase)
        node = *(int **)(listBase - 0x20);
        // Check if list is not empty (head != end marker) and head is not null
        if (node != (int *)(listBase - 0x1C) && node != 0) {
            // Call global delete function on the head node
            (*DAT_0119caf4)(node);
        }
        i--;
        listBase = (int *)((char *)listBase - 0x20);
    } while (i >= 0);
}