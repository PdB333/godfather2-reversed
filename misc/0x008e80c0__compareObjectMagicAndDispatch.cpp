// FUNC_NAME: compareObjectMagicAndDispatch

int compareObjectMagicAndDispatch(int* objectA, int* objectB) {
    // Magic 128-bit identifier constants (FourCC-like)
    const int32 MAGIC_ID0 = -0x45245246; // 0xBADBDBBA
    const int32 MAGIC_ID1 = -0x41104111; // 0xBEEFBEEF
    const int32 MAGIC_ID2 = -0x153ea5ab; // 0xEAC15A55
    const int32 MAGIC_ID3 = -0x6eeff6ef; // 0x91100911

    // Check if objectA is either the magic pattern or all zero (null/sentinel)
    bool aIsMagic = (objectA[0] == MAGIC_ID0) && (objectA[1] == MAGIC_ID1) &&
                    (objectA[2] == MAGIC_ID2) && (objectA[3] == MAGIC_ID3);
    bool aIsNull = (objectA[0] == 0) && (objectA[1] == 0) &&
                   (objectA[2] == 0) && (objectA[3] == 0);

    if (!aIsMagic && !aIsNull) {
        // objectA is not valid; check objectB
        bool bIsMagic = (objectB[0] == MAGIC_ID0) && (objectB[1] == MAGIC_ID1) &&
                        (objectB[2] == MAGIC_ID2) && (objectB[3] == MAGIC_ID3);
        bool bIsNull = (objectB[0] == 0) && (objectB[1] == 0) &&
                       (objectB[2] == 0) && (objectB[3] == 0);

        if (!bIsMagic && !bIsNull) {
            // Both are invalid; attempt to resolve objectA via type factory
            // FUN_00446100: likely finds object instance from identifier
            // Second argument 0 may indicate search mode
            int* foundObject = (int*)FUN_00446100(objectA, 0);
            if (foundObject != 0) {
                // FUN_00810750: attempt to cast found object to a specific class
                // 0x420f378a is a class hash (e.g., for a specific component or entity type)
                int* classVtable = (int*)FUN_00810750(foundObject, 0x420f378a);
                if (classVtable != 0) {
                    // vtable offset 0x14c (332 bytes / 4 = 83rd vtable entry)
                    // This method likely performs some operation or assignment using objectB
                    (**(code**)(classVtable + 0x14c))(objectB);
                    return 1;
                }
            }
            return 0; // resolution failed
        }
    }
    // objectA (or objectB if objectA was invalid) is either magic or null – treat as valid
    return 1;
}