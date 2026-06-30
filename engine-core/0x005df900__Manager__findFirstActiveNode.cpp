// FUNC_NAME: Manager::findFirstActiveNode
void __thiscall Manager::findFirstActiveNode(void)
{
    // Manager struct: +0x8 = pointer to head of linked list (Node*)
    // Node struct: +0x8 = next pointer, +0x15 = active flag (char)
    Node* node = *(Node**)(this + 8); // dereference this+8 as Node*
    char activeFlag = *(char*)(node + 0x15);
    while (activeFlag == 0)
    {
        node = *(Node**)(node + 8); // follow next pointer
        activeFlag = *(char*)(node + 0x15);
    }
    // After loop, node points to first active element in the list.
    // The function returns void but likely leaves the node pointer in EAX for the caller.
    return;
}