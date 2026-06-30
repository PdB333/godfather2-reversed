// FUNC_NAME: SomeClass::destroyAllCallbacks
void SomeClass::destroyAllCallbacks()
{
    int count;
    int nextPtr;
    uint index;
    int currentPtr;
    undefined4 **callbackListHead;

    // First loop: invoke each callback function
    index = 0;
    callbackListHead = *(undefined4 ***)(this + 0x44); // +0x44: head of callback list (linked list of nodes)
    if (*(int *)(this + 0x48) != 0) { // +0x48: count of callbacks
        do {
            (*(code *)*callbackListHead)(); // Call the function pointer stored in the node
            callbackListHead = (undefined4 **)callbackListHead[1]; // Move to next node via offset 4
            index = index + 1;
        } while (index < *(uint *)(this + 0x48));
    }

    // Second loop: free each node
    currentPtr = *(int *)(this + 0x44);
    index = 0;
    if (*(int *)(this + 0x48) != 0) {
        do {
            nextPtr = *(int *)(currentPtr + 4); // Save next pointer before freeing
            FUN_009c8eb0(currentPtr); // Deallocate the node (likely operator delete or custom free)
            index = index + 1;
            currentPtr = nextPtr;
        } while (index < *(uint *)(this + 0x48));
    }

    // Reset head and count
    *(undefined4 *)(this + 0x44) = 0;
    *(undefined4 *)(this + 0x48) = 0;
    return;
}