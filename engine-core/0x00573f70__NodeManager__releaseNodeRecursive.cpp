// FUNC_NAME: NodeManager::releaseNodeRecursive
// Function at 0x00573f70: Recursively releases a binary tree of nodes, decrementing a count.
void __thiscall NodeManager::releaseNodeRecursive(int* node) {
    // node +0x08: left child pointer
    if (*(int**)(node + 2) != nullptr) {
        releaseNodeRecursive(*(int**)(node + 2));
    }
    // node +0x0C: right child pointer
    if (*(int**)(node + 3) != nullptr) {
        releaseNodeRecursive(*(int**)(node + 3));
    }
    // Call virtual function at vtable index 1 (offset 4) on the nodeClass object at this+0x0C
    // The function signature is likely void (__thiscall)(int* node, int zero)
    (**(code**)(**(int**)(this + 0x0C) + 4))(node, 0);
    // Decrement node count at this+0x04
    *(int*)(this + 4) = *(int*)(this + 4) - 1;
}