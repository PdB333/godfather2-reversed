//FUNC_NAME: checkObjectTypeByGUID
int checkObjectTypeByGUID(int* guid1, int* guid2)
{
    // Known class GUID: {0xBABDBDBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911}
    // This GUID likely identifies a specific EARS class or interface.
    const int knownGUID[4] = {0xBABDBDBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911};

    // Check if guid1 matches the known GUID or is all zeros (null GUID)
    if ((guid1[0] == knownGUID[0] && guid1[1] == knownGUID[1] && guid1[2] == knownGUID[2] && guid1[3] == knownGUID[3]) ||
        (guid1[0] == 0 && guid1[1] == 0 && guid1[2] == 0 && guid1[3] == 0))
    {
        return 1; // Match or null -> success
    }

    // Check guid2 similarly
    if (!(guid2[0] == knownGUID[0] && guid2[1] == knownGUID[1] && guid2[2] == knownGUID[2] && guid2[3] == knownGUID[3]) &&
        !(guid2[0] == 0 && guid2[1] == 0 && guid2[2] == 0 && guid2[3] == 0))
    {
        // Look up an object by guid1 (hash table or registry)
        int* obj = (int*)FUN_00446100(guid1, 0); // likely a hash lookup
        if (obj != 0)
        {
            // Resolve a specific interface/component from the object
            int* component = (int*)FUN_00810750(obj, 0x420f378a); // constant likely a class ID
            if (component != 0)
            {
                // Call virtual method at vtable offset 0x14c (332 bytes) with guid2 as argument
                (*(code**)(*component + 0x14c))(guid2);
                return 1;
            }
        }
    }

    return 0; // No match
}