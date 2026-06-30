// FUNC_NAME: ManagerClass::anyReadyObject
int __thiscall ManagerClass::anyReadyObject(void) {
    // this+0x14: head of a linked list of nodes
    Node* node = *(Node**)(this + 0x14); // +0x14: linked list pointer
    while (node) {
        // node+0x08: pointer to an object with a byte flag at +0xb2
        void* obj = (void*)node->field2; // actually node[2] (offset 0x08)
        if (obj && ((*(uint8_t*)((uintptr_t)obj + 0xb2) & 1) == 0)) {
            return 0; // found an object with bit0 clear (ready)
        }
        node = (Node*)node->next; // node[0] is next pointer
    }
    return 1; // no ready object found
}