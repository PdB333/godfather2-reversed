// FUNC_NAME: InputDeviceManager::processRemapEntry
void __thiscall InputDeviceManager::processRemapEntry(int this, int entry) // this = param_1, entry = param_2
{
    byte *bytePtr;
    char *charPtr;
    int count;
    int *deviceListPtr;
    int index;
    bool hasKeyboard;
    bool hasController;
    undefined8 result;

    hasKeyboard = false;
    hasController = false;

    // Check if the target device (pointed by entry+8) has bit 0x11 set in offset+5 (likely device flags)
    if ((*(byte *)(*(int *)(entry + 8) + 5) & 0x11) == 0) {
        FUN_00626640(); // Some error or default handling
    }

    // Check another flag at entry+8+6 bit 8
    if ((*(byte *)(*(int *)(entry + 8) + 6) & 8) == 0) {
        result = FUN_00637f90(); // Allocate or retrieve a binding list
        deviceListPtr = (int *)result;
        if (*deviceListPtr == 0) {
            // Set bit 8 in offset+6 of the result's high part
            bytePtr = (byte *)((int)((ulonglong)result >> 0x20) + 6);
            *bytePtr = *bytePtr | 8;
            deviceListPtr = (int *)0x0;
        }
    }
    else {
        deviceListPtr = (int *)0x0;
    }

    // If we have a valid device list and its type == 4 (likely keyboard/virtual)
    if ((deviceListPtr != (int *)0x0) && (*deviceListPtr == 4)) {
        // Scan the device name (at deviceListPtr[1] + 0x10) for 'k' and 'v' characters
        charPtr = strchr((char *)(deviceListPtr[1] + 0x10), 0x6b); // 'k' -> keyboard
        hasKeyboard = charPtr != (char *)0x0;
        charPtr = strchr((char *)(deviceListPtr[1] + 0x10), 0x76); // 'v' -> controller (virtual?)
        hasController = charPtr != (char *)0x0;

        if ((hasKeyboard) || (hasController)) {
            // Update flags in entry+5: clear bits 1-3 and set according to hasController/hasKeyboard
            *(byte *)(entry + 5) = (hasController * '\\x02' | hasKeyboard) * '\\x02' | *(byte *)(entry + 5) & 0xf9;
            
            // Select which action list (this+4, this+8, this+0xc) to link into
            if (hasKeyboard) {
                if (hasController) {
                    deviceListPtr = (int *)(this + 0xc); // Both -> +0xc
                }
                else {
                    deviceListPtr = (int *)(this + 4);   // Only keyboard -> +4
                }
            }
            else {
                deviceListPtr = (int *)(this + 8);       // Only controller -> +8
            }
            // Insert entry into the appropriate doubly linked list
            *(int *)(entry + 0x18) = *deviceListPtr;   // entry->next = head
            *deviceListPtr = entry;                     // head = entry
            if (hasController) goto LAB_00626896;
        }
    }

    // Process another list: iterate over entries in entry+0xc with count from entry+0x1c
    count = *(int *)(entry + 0x1c);
    while (count != 0) {
        count = count + -1;
        // Each entry is a pair of ints: check first int > 3, then check flags in second int's offset+5
        if ((3 < *(int *)(*(int *)(entry + 0xc) + count * 8)) &&
            ((*(byte *)(*(int *)(*(int *)(entry + 0xc) + count * 8 + 4) + 5) & 0x11) == 0)) {
            FUN_00626640();
        }
    }

LAB_00626896:
    // Process another array: size = (1 << (entry[7] & 0x1f)) * 0x14 bytes
    count = 1 << (*(byte *)(entry + 7) & 0x1f);
    if (count != 0) {
        index = count * 0x14;
        do {
            index = index + -0x14;
            deviceListPtr = (int *)(*(int *)(entry + 0x10) + index);
            count = count + -1;
            // Each element has four ints: [0] type, [1] device1, [2] type2, [3] device2
            if (deviceListPtr[2] != 0) {
                // Check type > 3 and flags in corresponding device structs
                if (((3 < *deviceListPtr) && ((*(byte *)(deviceListPtr[1] + 5) & 0x11) == 0)) && (!hasKeyboard)) {
                    FUN_00626640();
                }
                if (((3 < deviceListPtr[2]) && ((*(byte *)(deviceListPtr[3] + 5) & 0x11) == 0)) && (!hasController)) {
                    FUN_00626640();
                }
            }
        } while (count != 0);
    }
    return;
}