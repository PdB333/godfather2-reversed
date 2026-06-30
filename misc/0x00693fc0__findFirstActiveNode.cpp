// FUNC_NAME: findFirstActiveNode
void __thiscall findFirstActiveNode(int this) {
    // Traverse a linked list starting from the head at this+0x8
    // Each node has a "next" pointer at offset 0x8 and an "active" flag at offset 0x25
    int node = *(int*)(this + 0x8); // get head node
    char isActive = *(char*)(node + 0x25);
    
    while (isActive == '\0') {
        node = *(int*)(node + 0x8);
        isActive = *(char*)(node + 0x25);
    }
    // Found the first active node (or looped forever if none)
    // Result is left in node (caller likely uses it from eax)
}