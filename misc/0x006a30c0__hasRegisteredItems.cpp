// FUNC_NAME: hasRegisteredItems
// Address: 0x006a30c0
// Role: Checks whether the global list of registered items (circular singly linked list) is empty.
// Returns a global state flag (DAT_00e50c7c) and sets *outHasItems to true if the list is non-empty.

// The list uses a static head pointer that initially points to itself (sentinel).
// Nodes have a 'next' pointer at offset 0.
// If the global state flag is non-zero, the list is not checked and false is returned.

int hasRegisteredItems(bool* outHasItems)
{
    // Global flag: if non-zero, skip list check (e.g., error/initialization state)
    extern int gGlobalStateFlag;          // DAT_00e50c7c
    extern struct ListNode* gListHead;    // PTR_LOOP_00e50c80

    struct ListNode
    {
        ListNode* next; // offset +0x00
    };

    if (gGlobalStateFlag != 0)
    {
        *outHasItems = false;
        return gGlobalStateFlag;
    }

    int count = 0;
    ListNode* current = gListHead; // start at first node (or sentinel if empty)

    // If the head pointer does not point to itself, the list is non-empty
    if (current != (ListNode*)&gListHead)
    {
        do
        {
            count++;
            current = current->next; // move to next node
        } while (current != (ListNode*)&gListHead);
    }

    *outHasItems = (count != 0);
    return gGlobalStateFlag;
}