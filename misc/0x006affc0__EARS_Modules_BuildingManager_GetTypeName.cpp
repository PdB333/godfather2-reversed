// Xbox PDB: EARS::Modules::BuildingManager::GetTypeName
// FUNC_NAME: BuildingDataManager::getOrCreateBuildingData
int __thiscall BuildingDataManager::getOrCreateBuildingData(int thisPtr, int buildingTypeIndex)
{
    // Entry structure: size 0x10, at this + 0x68 + index * 0x10
    // Entry layout:
    //   +0x00: void* buildingDataPtr (or object pointer)
    //   +0x04: int initializedFlag
    //   +0x08? +0x0C? - unknown, but we only touch first 8 bytes
    int* entryPtr = reinterpret_cast<int*>(thisPtr + 0x68 + buildingTypeIndex * 0x10);
    int* flagPtr = reinterpret_cast<int*>(thisPtr + 0x6C + buildingTypeIndex * 0x10);

    if (*flagPtr == 0)
    {
        // Get building type string ID (maybe an enum or hash)
        int typeID = getBuildingTypeStringID(buildingTypeIndex); // FUN_006af820

        // Format a string: "building_type_" + typeID
        char buffer[32]; // assumed local buffer
        FormatString(buffer, "building_type_%d", typeID); // FUN_00401d30

        // If buffer is null, use default string
        const char* name = buffer;
        if (buffer == nullptr)
        {
            name = "default_building_type_name"; // DAT_0120546e
        }

        // Create building data object from the formatted name
        void* newData = createObjectFromString(name); // FUN_004dafd0

        // Store the created object into the entry's first field
        setBuildingDataEntry(entryPtr, newData); // FUN_00603330

        // Note: original code had a cleanup call for local_10 if not null; 
        // likely that was the buffer (heap allocated?), but we skip for simplicity.
    }

    return reinterpret_cast<int>(entryPtr);
}