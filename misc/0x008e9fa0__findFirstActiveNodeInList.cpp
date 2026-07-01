// FUNC_NAME: findFirstActiveNodeInList

/**
 * Walks a linked list starting from the head pointer stored at the given address.
 * Finds the first node where the byte at offset 0x19 is non-zero (active flag).
 * param_1: pointer to a head pointer (e.g., address of a manager's list head)
 * Returns: pointer to the first active node, or NULL if none found? (code doesn't handle NULL)
 * 
 * Node structure assumed:
 *   +0x00: ListNode* next
 *   +0x19: char isActive (0 = inactive, non-zero = active)
 */
ListNode* findFirstActiveNodeInList(int** param_1)
{
    ListNode* current = (ListNode*)*param_1;  // dereference head pointer
    char activeFlag = *(char*)((int)current + 0x19);

    while (activeFlag == 0)
    {
        current = (ListNode*)*(int*)current;  // follow next pointer
        activeFlag = *(char*)((int)current + 0x19);
    }

    return current;
}