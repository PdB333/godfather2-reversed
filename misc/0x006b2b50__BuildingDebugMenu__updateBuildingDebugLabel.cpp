// FUNC_NAME: BuildingDebugMenu::updateBuildingDebugLabel
void __thiscall BuildingDebugMenu::updateBuildingDebugLabel(BuildingDebugMenu* this, bool selected)
{
    int buildingType;
    uint32_t* displayInfo; // pointer to two uint32s (e.g., building ID or coordinates)
    char* labelBuffer; // pointer to built debug label string
    uint32_t labelHash;
    int hashExists;
    int* debugListPtr;
    char* buffer;

    // Likely updates internal debug state or initializes something
    debugManagerUpdate();

    buildingType = *(int*)((uint8_t*)this + 0x194); // +0x194: building type/category
    if ((buildingType != 0) && (buildingType != 0x48)) // 0x48 = 72, might represent "no building" or invalid
    {
        // Get building display info (e.g., unique ID coordinates)
        displayInfo = (uint32_t*)getBuildingDisplayInfo(*(uint32_t*)((uint8_t*)this + 0x40)); // +0x40: building index/key

        // Build default debug label string "dv_building_<id1>_<id2>"
        // FUN_004d3ca0 likely returns a pointer to a local/static buffer
        buffer = buildDebugString("dv_building_", 0xc, *displayInfo, displayInfo[1]);

        if (selected)
        {
            appendString("_selected"); // appends suffix to current buffer
        }

        // Use the buffer, default to empty string if null
        labelBuffer = buffer;
        if (buffer == (char*)0x0)
        {
            labelBuffer = (char*)&DAT_0120546e; // default string (likely "")
        }

        // Hash the label string
        labelHash = hashString((const char*)labelBuffer);
        hashExists = hashTableLookup(labelHash); // check if this label already exists

        if (hashExists != 0)
        {
            // Register a new debug element in the global debug element list
            // DAT_01206880 + 0x14 likely points to a dynamic array or linked list
            debugListPtr = (int*)(*(uint8_t**)0x01206880 + 0x14); // offset 0x14 from global pointer
            **(uint32_t**)(debugListPtr) = &PTR_LAB_00e50d58; // set vtable for debug element
            *debugListPtr += 4;
            *(int*)*debugListPtr = buildingType + 0xc; // some type-dependent data
            *debugListPtr += 4;
            *(uint32_t*)*debugListPtr = labelHash; // store hash for later lookup
            *debugListPtr += 4;
        }

        // Free the allocated buffer if it was not the default
        if (buffer != (char*)0x0)
        {
            // NOTE: Decompiler shows call to address 0, likely a free function (e.g., operator delete[])
            // This is probably a vtable call or a function pointer. For reconstruction, we assume a free.
            freeStringBuffer(buffer);
        }
    }
}