// FUNC_NAME: waitForActiveNode
void __thiscall waitForActiveNode(void) {
    // this+0x8 is the head pointer of a linked list (Node)
    // Each Node has a next pointer at +0x8 and a status byte at +0x15
    int* currentNode = *(int**)(this + 8);   // offset +0x8: head pointer
    char flag = *(char*)(currentNode + 0x15); // +0x15: active flag

    while (flag == '\0') {
        currentNode = *(int**)(currentNode + 8); // +0x8: next node pointer
        flag = *(char*)(currentNode + 0x15);
    }
    // Function blocks until a node with non-zero active flag is found
}