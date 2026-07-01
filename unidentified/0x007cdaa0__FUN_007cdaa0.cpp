//FUNC_NAME: SomeManager::clearAndProcessList
void __fastcall SomeManager::clearAndProcessList(void* thisPtr)
{
    // Stack-allocated structure for item iteration
    struct ItemInfo {
        int field_0;          // +0x00
        int field_4;          // +0x04
        int field_8;          // +0x08
        void (*callback)(void*); // +0x0C
        int field_10;         // +0x10
        char flagChar;        // +0x14
        int field_18;         // +0x18
    } itemInfo;

    int index = 0;
    bool foundFlag = false;
    memset(&itemInfo, 0, sizeof(itemInfo));

    // If there's a current item, call its destructor via callback
    if (*(int*)((char*)thisPtr + 0x1EC) != 0) {
        (*(void (**)(int))((char*)thisPtr + 0x1F8))(*(int*)((char*)thisPtr + 0x1EC));
    }

    // Clear the item pointer and related fields
    *(int*)((char*)thisPtr + 0x1EC) = 0;   // m_pCurrentItem
    *(int*)((char*)thisPtr + 0x1F4) = 0;   // m_nCount (offset 500 = 0x1F4)
    *(int*)((char*)thisPtr + 0x1F0) = 0;   // m_bFlag

    // First pass: iterate items until a null flagChar is found
    char result = FUN_005e2af0(0, &itemInfo);
    if (result != '\0') {
        do {
            if (foundFlag) goto cleanup;
            foundFlag = (itemInfo.flagChar == '\0');
            index++;
            result = FUN_005e2af0(index, &itemInfo);
        } while (result != '\0');
        if (foundFlag) goto cleanup;
    }

    // Second pass: look for an item with field_18 == -1
    index = 0;
    result = FUN_005e2af0(0, &itemInfo);
    while (result != '\0') {
        if (itemInfo.field_18 == -1) {
            FUN_004d3e20(&itemInfo);
            int value = FUN_005e3260();
            FUN_005e2ad0(itemInfo.field_10, value);
            break;
        }
        index++;
        result = FUN_005e2af0(index, &itemInfo);
    }

cleanup:
    if (itemInfo.field_0 != 0) {
        itemInfo.callback((void*)itemInfo.field_0);
    }
    return;
}