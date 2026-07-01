// FUNC_NAME: ManagerUtility::processByType
void ManagerUtility::processByType(int typeHash, ManagerData* mgrData)
{
    // Begin processing – likely a scoped lock or enter function
    FUN_008c74d0(typeHash);

    // Retrieve a component or interface from the manager data (index 0)
    InterfaceHandle handle = FUN_008c4a60(mgrData, 0);

    // Check if this is a specific manager type (e.g., "CrimeManager" hash = 0x637b907)
    // and that the manager is active (byte at +0xC == 0 means not disabled)
    // and that it has entries to process (count at +0x14)
    if ((typeHash == 0x637b907) && (*(char*)(mgrData + 0xC) == 0) && (*(int*)(mgrData + 0x14) != 0))
    {
        uint count = 0;
        // Loop over all entries in the manager's list
        do {
            // Get next entry pointer – likely a global iterator or next-in-list function
            void* entry = FUN_00791300();

            if ((entry != nullptr) && 
                // Compare the entry's internal ID (offset +0x1EE8) with the manager's root/owner ID (at +0x8 → +0x38)
                (*(int*)(entry + 0x1EE8) != *(int*)(*(int*)(mgrData + 0x8) + 0x38)))
            {
                // Remove or finalize the entry (calls a cleanup on entry+0x3C)
                FUN_004088c0(entry + 0x3C);
            }
            count++;
        } while (count < *(uint*)(mgrData + 0x14));
    }

    // Finish processing – release the interface handle
    FUN_008c62e0(handle);
    return;
}