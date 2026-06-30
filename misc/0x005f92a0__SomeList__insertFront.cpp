// FUNC_NAME: SomeList::insertFront
void SomeList::insertFront(void* param1) // param1 is this pointer (ecx), but decompiler shows as first param
{
    // this points to an object with a list head pointer at offset 0x18
    int* listHead = *(int**)(this + 0x18); // +0x18: pointer to head sentinel node
    // FUN_005f9fc0 allocates a new node, sets its next to the head's current next, and returns it
    int* newNode = (int*)FUN_005f9fc0(listHead, *(int*)(listHead + 4), /* in_EAX? perhaps unused */ 0);
    // FUN_005fa010 is likely a constructor call on newNode (parameter missing in decompilation)
    FUN_005fa010(); // probably newNode->init() or similar
    // Insert at front: head->next = newNode
    *(int*)(listHead + 4) = (int)newNode; // +0x4: next pointer of sentinel
    // Update the previous first node's prev pointer (if it exists) to point to newNode
    // newNode+4 holds its next pointer (set by alloc to the old head->next)
    if (*(int*)(newNode + 4) != 0) {
        **(int**)(newNode + 4) = (int)newNode; // old first node's prev = newNode
    }
}