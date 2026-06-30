// FUNC_NAME: NodeList::findNextActive
void __thiscall NodeList::findNextActive(void)
{
    // +0x8: next pointer in a singly linked list
    // +0x15: active flag (char, non-zero means active)
    int nextNode = *(int *)(this + 8);      // Start with node after current
    char active = *(char *)(nextNode + 0x15);

    // Traverse the list until an active node is found
    while (active == '\0') {
        nextNode = *(int *)(nextNode + 8);  // Move to next node
        active = *(char *)(nextNode + 0x15); // Check its active flag
    }

    // Note: Assumes the list is circular or guaranteed to have an active node
    // (no null check, will crash if end of list reached)
    // Result is implicitly returned via the node pointer? (Function returns void, caller likely uses side effect or register)
    // The pointer to the found node remains in eax (or in a register) for caller to use.
    return;
}