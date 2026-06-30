// FUNC_NAME: safeDeleteNode
void __fastcall safeDeleteNode(void* container) {
    // container is a pointer to an object with a linked list node pointer at +0x8
    // and a sentinel node at +0xC. If the node pointer is not the sentinel and not null,
    // call the global destructor function on it.
    void* node = *(void**)((char*)container + 8);
    void* sentinel = (char*)container + 0xC;
    if (node != sentinel && node != nullptr) {
        // Global function pointer for node destruction (e.g., operator delete or custom deallocator)
        typedef void (*NodeDestructor)(void*);
        NodeDestructor destructor = (NodeDestructor)DAT_0119caf4;
        destructor(node);
    }
}