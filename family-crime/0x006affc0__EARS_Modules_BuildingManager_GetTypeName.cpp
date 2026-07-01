// Xbox PDB: EARS::Modules::BuildingManager::GetTypeName
// FUNC_NAME: BuildingManager::loadBuildingType
int BuildingManager::loadBuildingType(int buildingTypeIndex) {
    // Compute pointer to the building type data slot (each entry is 0x10 bytes)
    int* pDataSlot = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x68 + buildingTypeIndex * 0x10);
    // Check if this building type is already loaded (flag at offset +0x6c)
    int* pLoadFlag = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x6c + buildingTypeIndex * 0x10);
    if (*pLoadFlag == 0) {
        // Get the building type identifier (e.g., an integer ID or string suffix)
        int buildingTypeId = getBuildingTypeId(buildingTypeIndex); // FUN_006af820
        // Build a string like "building_type_<id>"
        TempString nameBuilder; // local_10 (likely a RAII string buffer)
        stringFormat(&nameBuilder, "building_type_%d", buildingTypeId); // FUN_00401d30

        // Use the created string to lookup/resolve the building type data
        const char* nameToLookup = nameBuilder.c_str();
        if (nameToLookup == nullptr) {
            nameToLookup = &DEFAULT_BUILDING_TYPE_NAME; // DAT_0120546e (global default string)
        }
        int resourceId = resolveBuildingTypeResource(nameToLookup); // FUN_004dafd0
        // Store the resolved resource ID into the data slot
        storeBuildingTypeResource(resourceId, pDataSlot); // FUN_00603330
        // nameBuilder destructor called automatically (local_4 destructor)
    }
    // Return pointer to the building type data slot
    return reinterpret_cast<int>(pDataSlot);
}