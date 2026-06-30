// FUNC_NAME: ActionQueue::removeAction
void __thiscall ActionQueue::removeAction(int commandID)
{
    int index = 0;
    int* idField = (int*)(this + 0x48);
    do {
        if (idField[-10] == commandID) goto found;          // slot at index
        if (*idField == commandID) { index += 1; goto found; }
        if (idField[10] == commandID) { index += 2; goto found; }
        if (idField[0x14] == commandID) { index += 3; goto found; }
        index += 4;
        idField += 10; // advance 0x28 bytes (10 ints)
    } while (index < 32);

    // Check the currently active command
    if (*(int*)(this + 0x534) == commandID) {
        if (*(void**)(this + 0x530) != nullptr) {
            int tempData[2]; // local_c, local_8
            tempData[0] = **(int**)(this + 0x530);
            tempData[1] = 0;
            char extra = 0;
            clearData(tempData, 0); // FUN_00408a00 – resets some structure
        }
        *(void**)(this + 0x530) = nullptr;
        *(int*)(this + 0x52c) = 0;
        *(int*)(this + 0x534) = 0;
    }
    return;

found:
    {
        int slotAddr = (int)this + index * 0x28;
        if (*(int*)(slotAddr + 0x24) != 0) {
            releaseCommandData((int*)(slotAddr + 0x24)); // FUN_004daf90 – likely frees attached data
            *(int*)(slotAddr + 0x24) = 0;
        }
        *(int*)(slotAddr + 0x20) = 0;     // clear command ID
        *(int*)(slotAddr + 0x40) = 0;     // unknown field
        *(int*)(slotAddr + 0x44) = 0;     // unknown field
        (*(int*)(this + 0x520))--;        // decrement active command count
    }
}