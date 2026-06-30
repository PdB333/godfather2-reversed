// FUNC_NAME: Container::findElementByType
void __thiscall Container::findElementByType(int this, undefined4 param_2)
{
    undefined4 **listIterator;
    undefined4 *elementPtr;
    undefined4 **tempIterator;
    uint currentIndex;
    bool isListMode;
    char isListModeFlag;
    int bitArray;
    undefined4 *bitArrayPtr;
    uint count;
    uint local_54;
    undefined4 *currentElement;
    undefined2 shortIndex;
    undefined4 elementData;
    undefined4 **local_8;

    beginIteration(param_2, 0x4f3368d0);  // Lock or begin iteration
    listIterator = local_8;
    currentIndex = local_58;
    while (true) {
        if (isListModeFlag == '\0') {
            isListMode = *listIterator == (undefined4 *)0x0;
        } else {
            isListMode = currentIndex == local_54;
        }
        if (isListMode) break;

        tempIterator = &currentElement;
        if (isListModeFlag == '\0') {
            tempIterator = listIterator;
        }
        // Check element type ID (0x25e3)
        if (*(short *)((int)tempIterator + 6) == 0x25e3) {
            elementPtr = (undefined4 *)(uint)*(ushort *)(tempIterator + 1);
        } else {
            elementPtr = tempIterator[1];
        }
        if (elementPtr == (undefined4 *)0x0) {
            tempIterator = &currentElement;
            if (isListModeFlag == '\0') {
                tempIterator = listIterator;
            }
            *(undefined4 **)(this + 0x180) = tempIterator[2];  // Store found element at +0x180
        }

        if (isListModeFlag == '\0') {
            // List mode iteration
            if ((int)currentIndex < 0) {
                local_8 = (undefined4 **)((int)listIterator + (int)*listIterator);
                advanceListIterator();
                listIterator = local_8;
                currentIndex = local_58;
            } else if ((int)currentIndex < (int)(count - 1)) {
                local_58 = currentIndex + 1;
                local_8 = (undefined4 **)((int)listIterator + (int)*listIterator);
                listIterator = (undefined4 **)((int)listIterator + (int)*listIterator);
                currentIndex = local_58;
            } else {
                local_8 = (undefined4 **)&DAT_01163cf8;  // Sentinel value
                listIterator = (undefined4 **)&DAT_01163cf8;
            }
        } else {
            // Bitmask mode iteration
            local_58 = currentIndex + 1;
            currentIndex = local_58;
            if (local_58 != count) {
                shortIndex = (short)local_58;
                if ((*(byte *)((local_58 >> 3) + bitArray) & (byte)(1 << ((byte)local_58 & 7))) == 0) {
                    currentElement = bitArrayPtr;
                    elementData = *bitArrayPtr;
                    bitArrayPtr = bitArrayPtr + 1;
                } else {
                    currentElement = (undefined4 *)0x0;
                    elementData = 0;
                }
            }
        }
    }
    endIteration(param_2);  // Unlock or end iteration
    (**(code **)(*(int *)(this + 400) + 4))(param_2);  // Call virtual function at vtable+4
    return;
}