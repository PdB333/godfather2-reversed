// FUNC_NAME: EntityManager::createObject
void __fastcall EntityManager::createObject(undefined4 param_1)
{
    char isActive;
    int newObject;
    undefined4 constructedObject;

    // Check if the system is active (e.g., game state valid)
    isActive = FUN_00481660();
    if (isActive != '\0') {
        // Allocate memory for a new object (size 0x38 = 56 bytes)
        newObject = FUN_009c8e50(0x38);
        if (newObject != 0) {
            // Construct the object with the given parameter (e.g., parent or ID)
            constructedObject = FUN_007a09b0(param_1);
            // Register the constructed object (e.g., add to manager list)
            FUN_00481690(constructedObject);
            return;
        }
        // Allocation failed, register null
        FUN_00481690(0);
    }
    return;
}