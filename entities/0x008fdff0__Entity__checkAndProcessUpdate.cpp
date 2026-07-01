// FUNC_NAME: Entity::checkAndProcessUpdate
// Address: 0x008fdff0
// Role: Validates object GUID and triggers update chain if conditions are met.

void __fastcall Entity::checkAndProcessUpdate(void) // param_1 is 'this'
{
    int* guidPtr = (int*)(this + 0x90); // +0x90: 128-bit GUID (4 ints)
    bool isSpecialGUID = (guidPtr[0] != 0xBABDBDB9) || // -0x45245246
                         (guidPtr[1] != 0xBEEFBEEF) || // -0x41104111
                         (guidPtr[2] != 0xEAC15A55) || // -0x153ea5ab
                         (guidPtr[3] != 0x91100911);   // -0x6eeff6ef

    bool isNonZeroGUID = (guidPtr[0] != 0) ||
                         (guidPtr[1] != 0) ||
                         (guidPtr[2] != 0) ||
                         (guidPtr[3] != 0);

    if (!isSpecialGUID)
        return; // If special GUID, skip everything

    if (!isNonZeroGUID)
        return; // If all zeros, skip

    int result = FUN_00446100(guidPtr, 0); // Check if GUID matches a known asset
    if (result == 0)
        return;

    FUN_006ba790(result); // Process the matched asset

    int namePtr = (this != 0) ? (int)(this + 0x50) : 0; // +0x50: name string pointer
    FUN_00791e70(namePtr); // Handle name

    FUN_00790110(1); // Set some flag (e.g., bNeedsUpdate)

    int someManager = FUN_007915b0(); // Get a manager/singleton
    if (someManager != 0)
    {
        int parentPtr = *(int*)(this + 0xC8); // +0xC8: parent/container pointer
        if (parentPtr != 0)
        {
            someManager = FUN_008c12a0(parentPtr - 0x48); // Derive manager from parent
            if (someManager != 0)
            {
                FUN_008c8160(this); // First update method
                FUN_008ff4f0(this); // Second update method
            }
        }
    }
}