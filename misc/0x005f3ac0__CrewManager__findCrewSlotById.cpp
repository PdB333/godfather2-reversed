// FUNC_NAME: CrewManager::findCrewSlotById
int __fastcall CrewManager::findCrewSlotById(void* thisPtr, int id) {
    // Offset +0x82ac: array of 10 CrewSlotEntry structures (each 0x5c bytes)
    // CrewSlotEntry: +0x00 = id, +0x04 = status (negative = invalid)
    int* pSlot = (int*)((char*)thisPtr + 0x82ac);
    for (int i = 0; i < 10; ++i) {
        if (pSlot[1] >= 0 && pSlot[0] == id) {
            return i;
        }
        pSlot += 0x5c / sizeof(int); // 0x17 ints per slot
    }
    return -1;
}