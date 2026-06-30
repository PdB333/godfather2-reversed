// FUNC_NAME: SomeClass::setAttachedObjectNode
void __thiscall SomeClass::setAttachedObjectNode(int thisPtr, int obj) {
    int* headNodePtr = (int*)(thisPtr + 0x70);          // pointer to head of intrusive list node (or embedded node)
    int newNode;

    if (obj == 0) {
        newNode = 0;
    } else {
        newNode = obj + 0x48;                           // embedded list node offset inside owning object
    }

    if (*headNodePtr != newNode) {
        if (*headNodePtr != 0) {
            FUN_004daf90(headNodePtr);                  // release/detach old node
        }
        *headNodePtr = newNode;                         // assign new head

        if (newNode != 0) {
            // Save the previous "next" pointer of the new node into this+0x74
            *(int*)(thisPtr + 0x74) = *(int*)(newNode + 4);
            // Set the new node's "next" to point to the head pointer variable (back‑pointer)
            *(int**)(newNode + 4) = headNodePtr;
        }
    }
}