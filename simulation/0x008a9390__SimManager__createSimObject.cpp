// FUNC_NAME: SimManager::createSimObject
void __thiscall SimManager::createSimObject(SimManager* this, int objectId)
{
    // Check if the simulation is active (FUN_00481660)
    bool isActive = (bool)FUN_00481660();
    if (!isActive) {
        return;
    }

    // Allocate a new SimObject (size 0x40 = 64 bytes)
    SimObject* newObj = (SimObject*)FUN_009c8e50(sizeof(SimObject));
    if (newObj) {
        // Initialize the new object using the manager (FUN_008a9240 returns this)
        newObj = newObj->init(this);
        // Store the object ID at offset +0x38
        newObj->field_0x38 = objectId;
        // Register the object (FUN_00481690)
        FUN_00481690(newObj);
        return;
    }

    // Allocation failure fallback: save the ID in a global and register null
    g_lastObjectId = objectId; // _DAT_00000038
    FUN_00481690(0);
}