// FUNC_NAME: TreeManager::processNodeAndCleanup
// Function at 0x005e1350 - Recursively traverses a sibling-linked tree structure,
// processing child nodes first, then calling a virtual cleanup method on each node.
// The node structure: offsets: +0x00 = next sibling pointer, +0x08 = child pointer,
// +0x15 = flag byte (0 = active, otherwise stop traversal).
// The cleanup call uses a vtable pointer stored at this+4, index 1, with size 0x18.
void __thiscall TreeManager::processNodeAndCleanup(int* node) {
    char flag = *(char*)((int)node + 0x15); // +0x15: active flag
    while (flag == 0) {
        // Recurse into child subtree
        processNodeAndCleanup((int*)node[2]); // +0x08: child pointer
        int* next = (int*)*node; // +0x00: next sibling

        // Call vtable function (virtual method 1) on the node with a size parameter
        // vtable at *(int*)(this + 4), second entry (+4)
        (**(void (__thiscall**)(int*, int))((*(int*)(this + 4)) + 4))(node, 0x18);

        node = next;
        flag = *(char*)((int)next + 0x15);
    }
}