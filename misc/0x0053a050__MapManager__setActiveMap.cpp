// FUNC_NAME: MapManager::setActiveMap

void __fastcall MapManager::setActiveMap(int mapId)
{
    // Set the active map id global
    gActiveMap = mapId;

    // Check if we are in the default state and the initialization flag is set,
    // and that the corresponding map entry in the dynamic array is non-zero
    if ((gCurrentStatePtr == &gDefaultStateStruct) && 
        (gStateInitFlag != 0) && 
        (gMapEntryArray[gCurrentMapIndex] != 0))
    {
        // Call the map load function with the state pointer, map entry, and map id
        FUN_0060b2f0(gStatePointer, gMapEntryArray[gCurrentMapIndex], mapId);
    }
}