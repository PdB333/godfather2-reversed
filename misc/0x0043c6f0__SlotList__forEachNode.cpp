// FUNC_NAME: SlotList::forEachNode
void __thiscall SlotList::forEachNode(int this, uint slotIndex, int param3, int param4) {
    int *currentNode;

    if (slotIndex < 0x40) { // 64 slots
        // Base array pointer at this+0x4, each slot struct is 0x1c bytes, linked list head at +0x8 within slot
        int *slotBase = *(int **)(this + 4);
        int *listHead = (int *)(slotBase + 8 + slotIndex * 0x1c);
        for (currentNode = listHead; currentNode != nullptr; currentNode = (int *)currentNode[1]) {
            if (*currentNode != 0) {
                // Call callback on object at currentNode[0] + 0x3c (likely a virtual method)
                FUN_00408bf0(param3, *currentNode + 0x3c, param4);
            }
        }
    }
}