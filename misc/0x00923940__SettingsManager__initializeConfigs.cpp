// FUNC_NAME: SettingsManager::initializeConfigs
void __fastcall SettingsManager::initializeConfigs(int thisPtr) {
    char* stringPtr;
    int idResult;
    uint* groupTable;
    int* itemArray;
    int loopCount;
    int itemIndex;
    uint itemCount;
    int groupIndex;

    // Base configuration initialization
    baseInit();
    
    // Register main config variables with global string keys
    registerConfigEntry(&g_configString1, thisPtr + 0x54, 1, 0, 0, 0);
    registerConfigEntry(&g_configString2, thisPtr + 0x58, 1, 0, 0, 1);
    registerConfigEntry(&g_configString3, thisPtr + 0x5c, 1, 0, 0, 0);
    registerConfigEntry(&g_configString4, thisPtr + 0x6c, 1, &s_configCallback, 0, 0);
    
    // Process 5 config groups from global table
    groupTable = &g_configGroupTable; // DAT_00e564f4
    groupIndex = 5;
    do {
        itemCount = groupTable[0]; // Number of items in this group
        if (itemCount != 0) {
            itemIndex = 0;
            do {
                // Each item is 100 bytes
                itemArray = (int*)(groupTable[1] + itemIndex + 4); // Points to start of item data +4 offset
                loopCount = 2; // Two sub-entries per item
                do {
                    stringPtr = (char*)*itemArray;
                    if (stringPtr != 0 && *stringPtr != '\0') {
                        // Register sub-config: name, target at itemArray+9 (offset 36 bytes from item start)
                        registerConfigEntry(stringPtr, itemArray + 9, 3, 0, 0, 1);
                    }
                    itemArray += 12 / sizeof(int); // Move to next sub-entry (12 bytes per sub-entry)
                    loopCount--;
                } while (loopCount != 0);
                itemIndex += 100; // Move to next item
                itemCount--;
            } while (itemCount != 0);
        }
        groupTable += 2; // Next group (each group has count and pointer)
        groupIndex--;
    } while (groupIndex != 0);
    
    // Allocate a binding storage object (size 0x50)
    idResult = allocateMemory(0x50); // FUN_009c8e50
    if (idResult == 0) {
        idResult = 0;
    } else {
        // Create a binding object from some factory
        int factoryResult = createBindingFactory(); // FUN_006906b0
        idResult = createBindingFromFactory(factoryResult); // FUN_004c3880
    }
    *(int*)(thisPtr + 0x80) = idResult;
    // Set vtable pointer at offset 0x2C of the new object
    *(void**)(idResult + 0x2C) = &s_bindingVtable; // LAB_00923420
}