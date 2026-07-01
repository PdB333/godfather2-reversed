// FUNC_NAME: EventManager::processEventList
void __thiscall EventManager::processEventList(void* thisPtr, uint32_t* eventIdPtr)
{
    uint32_t* currentNode;
    int32_t someValue;
    int32_t otherValue;
    uint32_t* listHead;
    uint32_t* tempPtr;
    int32_t local_20;
    int32_t local_1c;
    uint32_t local_18;
    uint32_t local_14;
    uint8_t local_10;
    uint32_t local_c;
    uint32_t local_8;
    uint8_t local_4;

    // Get the first node from a global list keyed by eventId
    listHead = (uint32_t*)FUN_008ecc20(*eventIdPtr);
    if (listHead != nullptr) {
        local_20 = DAT_0122337c;  // Global state or list head
        // Iterate over linked list (first element is next pointer)
        for (currentNode = (uint32_t*)*listHead; currentNode != nullptr; currentNode = (uint32_t*)*currentNode) {
            // Check if node has a valid object pointer at offset 0x20
            if (currentNode[8] == 0) {
                someValue = 0;
            } else {
                someValue = currentNode[8] - 0x48;  // Adjust pointer
            }
            otherValue = currentNode[10];  // Offset 0x28
            // Condition: otherValue equals someValue, and either otherValue is 0 or bit 0 of byte at otherValue+0x40 is set
            if ((otherValue == someValue) && ((otherValue == 0) || ((*(uint8_t*)(otherValue + 0x40) & 1) != 0))) {
                // Check magic numbers (likely GUIDs for specific event types)
                if ((currentNode[2] == 0xBABDB9BA) &&
                   ((currentNode[3] == 0xBEEFBEEF && (currentNode[4] == 0xEAC15A55 && currentNode[5] == 0x91100911)))) {
                    // Specific event type: handle audio/visual event
                    if ((currentNode[8] != 0) && (currentNode[8] != 0x48)) {
                        int32_t result = FUN_008ecbc0(*eventIdPtr);
                        *(int32_t*)(result + 8) = 2;  // Set state to 2
                        local_18 = DAT_0112fddc;
                        int32_t objPtr = currentNode[8];
                        local_14 = 0;
                        local_10 = 0;
                        if ((objPtr == 0) || (objPtr == 0x48)) {
                            objPtr = 0;
                        } else {
                            objPtr = objPtr - 0xc;
                        }
                        FUN_00408bf0(&local_18, objPtr, 0);  // Copy or initialize data
                        objPtr = currentNode[8];
                        local_c = DAT_0112fdf8;
                        local_8 = 0;
                        local_4 = 0;
                        if ((objPtr == 0) || (objPtr == 0x48)) {
                            FUN_00408bf0(&local_c, 0, 0);
                        } else {
                            FUN_00408bf0(&local_c, objPtr - 0xc, 0);
                        }
                    }
                } else {
                    // Other event types
                    int32_t typeCheck = currentNode[6];  // Offset 0x18
                    if ((typeCheck == 0) ||
                       ((otherValue = FUN_004025a0(typeCheck), otherValue != 0 && (*(int32_t*)(otherValue + 0x24) == 3)))) {
                        if (currentNode[8] == 0) {
                            someValue = 0;
                        } else {
                            someValue = currentNode[8] - 0x48;
                        }
                        FUN_008ecf00(currentNode + 2, currentNode[7], someValue, typeCheck);
                    }
                }
            }
            // eventIdPtr may be updated? (puVar5 = param_2)
        }
    }

    // Second list processing
    tempPtr = (uint32_t*)FUN_008ecbc0(*eventIdPtr);
    for (currentNode = (uint32_t*)*tempPtr; currentNode != nullptr; currentNode = (uint32_t*)*currentNode) {
        // Empty loop - just iterates to the end
    }
    tempPtr[2] = 2;  // Set state to 2

    // Update local state and check consistency
    uint32_t* eventIdRef = eventIdPtr;
    FUN_008ec930(&local_20, &eventIdRef);
    int32_t savedLocal20 = local_20;
    int32_t memberAt24 = *(int32_t*)((uint8_t*)thisPtr + 0x24);
    // Assertion: local_20 must be null or equal to this+0x20
    if ((local_20 == 0) || (local_20 != (int32_t)((uint8_t*)thisPtr + 0x20))) {
        FUN_00b97aea();  // Assertion failure
    }
    if (local_1c != memberAt24) {
        FUN_008edd00(&local_20, savedLocal20, local_1c);
    }
    return;
}