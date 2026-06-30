// FUNC_NAME: EntityValidator::updateState
char EntityValidator::updateState(int contextParam) {
    char result = 1;

    // Check if the object is active (bit 0 of +0x24)
    if ((*(byte*)(this + 0x24) & 1) == 0) {
        return 0;
    }

    // Call initialization/validation helper
    FUN_005ddd30();  // Likely resets internal state

    int* childList = *(int**)(this + 0x2c); // Linked list head at +0x2c
    if (childList != 0) {
        uint childCount = *(uint*)(this + 0x28); // Number of children at +0x28
        result = 1;
        if (childCount != 0) {
            do {
                if (childList == 0) {
                    result = 0;
                } else {
                    char check = FUN_005dc6e0(contextParam); // Validate child node
                    if (check == 0) {
                        result = 0;
                    }
                    childList = *(int**)childList[0x28 / 4]; // Next node link at +0x28
                }
                childCount--;
            } while (childCount > 0);
        }

        // Second list: array of pointers at +0x34, count at +0x30
        uint** ptrArray = *(uint***)(this + 0x34);
        uint arrayCount = *(uint*)(this + 0x30);
        uint index = 0;
        if (arrayCount != 0) {
            do {
                if (ptrArray == 0) {
                    result = 0;
                } else {
                    int obj = FUN_005dc670(*ptrArray); // Dereference pointer, get object ID
                    if (obj == 0) {
                        result = 0;
                    } else {
                        char check2 = FUN_005de000(obj, ptrArray); // Validate object entry
                        if (check2 == 0) {
                            result = 0;
                        }
                    }
                    ptrArray = (uint**)ptrArray[7]; // Next entry at stride 28 bytes (7*4)
                }
                index++;
            } while (index < arrayCount);
        }
    }
    return result;
}