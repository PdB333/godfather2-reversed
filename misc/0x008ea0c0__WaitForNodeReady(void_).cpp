// FUNC_NAME: WaitForNodeReady(void*)
void WaitForNodeReady(void* node)
{
    // Traverse the linked list until a node with a ready flag (offset 0x15) is found.
    // +0x08: next node pointer
    // +0x15: readiness flag (char, 0 = not ready, non-zero = ready)
    char* currentNode = *(char**)((char*)node + 8); // Get the first node in the list
    char readyFlag = *(char*)(currentNode + 0x15);
    while (readyFlag == '\0') {
        // Follow the next pointer
        currentNode = *(char**)(currentNode + 8);
        readyFlag = *(char*)(currentNode + 0x15);
    }
}