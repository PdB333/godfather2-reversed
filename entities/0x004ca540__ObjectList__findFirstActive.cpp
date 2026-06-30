// FUNC_NAME: ObjectList::findFirstActive
void __thiscall ObjectList::findFirstActive(void)
{
    // this+0x8: pointer to head node of linked list
    Node* currentNode = *(Node**)((int)this + 8);
    // node+0x15: active flag (non-zero means active)
    char activeFlag = *(char*)((int)currentNode + 0x15);

    // Walk the list until we find a node with a non-zero flag
    while (activeFlag == '\0') {
        currentNode = *(Node**)((int)currentNode + 8); // node+0x8: next pointer
        activeFlag = *(char*)((int)currentNode + 0x15);
    }
}