// FUNC_NAME: GUIDResource::shutdown
// Function at 0x008e1480 - Releases a pointer resource and a 128-bit GUID resource (if not empty or magic)
// Structure offsets:
//   +0x58: pointer to some resource (e.g., string, array)
//   +0x68-0x74: 16-byte GUID (four ints)
// Magic constants for "empty/cleared" GUID: 0xBBABDCBA, 0xBEEFBBEF, 0xEAC15A55, 0x91100911

void __thiscall GUIDResource::shutdown(void)
{
    // If there is a pointer resource, free it via some utility function
    if (*(int *)(this + 0x58) != 0) {
        // Stack variables used as a temporary structure (pointer + two zero fields)
        int temp[2];
        char extra = 0; // part of struct?
        temp[1] = 0;
        extra = 0;
        temp[0] = *(int *)(this + 0x58);
        // Call to free/deallocate (first arg is pointer to temp struct, second is 0)
        FUN_00408a00(temp, 0);
    }

    // Check if the GUID at +0x68 is either the magic "empty" value or all zeros
    if (!( (*(int *)(this + 0x68) == 0xBBABDCBA) &&
           (*(int *)(this + 0x6c) == 0xBEEFBBEF) &&
           (*(int *)(this + 0x70) == 0xEAC15A55) &&
           (*(int *)(this + 0x74) == 0x91100911) ) &&
        !( (*(int *)(this + 0x68) == 0) &&
           (*(int *)(this + 0x6c) == 0) &&
           (*(int *)(this + 0x70) == 0) &&
           (*(int *)(this + 0x74) == 0) ))
    {
        // Look up the resource manager for this GUID
        int *manager = (int *)FUN_00446100((int *)(this + 0x68), 0);
        if (manager != (int *)0x0) {
            // Call a virtual function on the manager (index 4: vtable+0x10) to release the GUID resource
            // First arg is a constant 0x96a9da2c (likely resource ID or type), second is a pointer to store result
            int result = 0;
            char releaseResult = (*(code **)(*manager + 0x10))(0x96a9da2c, &result);
            if (releaseResult != '\0') {
                // If release succeeded, call a finalization function (parameter 0)
                FUN_00891a50(0);
            }
        }
    }
}