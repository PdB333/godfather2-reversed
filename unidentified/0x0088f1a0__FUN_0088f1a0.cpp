// FUNC_NAME: SomeClass::forEachNode
void __thiscall SomeClass::forEachNode(void* arg) {
    // Iterate over a linked list embedded in this object.
    // The list head is at offset 0x68 (pointer to first node).
    // The sentinel node is at offset 0x64 (embedded in this object).
    // FUN_00ab3c50 returns the next node pointer.
    for (int* currentNode = *(int**)(this + 0x68);
         currentNode != (int*)(this + 100);
         currentNode = (int*)FUN_00ab3c50(currentNode)) {
        FUN_0088bb70(arg);
    }
}