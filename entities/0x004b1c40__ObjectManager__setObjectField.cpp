// FUNC_NAME: ObjectManager::setObjectField
// Function address: 0x004b1c40
// Role: Sets a field (at +0x5c) on an object identified by a handle's ID.
// The handle's first DWORD is an ID. The lower 16 bits index into a global array of node structures (size 0x30 each),
// starting at g_objectNodeTableBase + 0x10.
// Each node holds a pointer to an object (+0x10) and the full ID (+0x2c).
// If the lookup succeeds, param_2 is written to the object's offset 0x5c.
// The validation function FUN_005e6580 is called (possibly acquire reference or validate).
// Returns 1 if the handle ID is zero (vacuous success) or if the operation succeeded, 0 otherwise.

extern uint g_objectNodeTableBase; // DAT_012234bc - base of the object node pool (first 0x10 bytes are header)

int __thiscall ObjectManager::setObjectField(int param_1, int param_2)
{
    uint handleID = *(uint*)this; // +0x00: the object's unique handle ID
    int result = 1;

    if (handleID != 0)
    {
        result = 0; // assume failure
        FUN_005e6580(handleID, param_1); // validation / reference acquisition

        uint index = handleID & 0xFFFF;
        int nodePtr = 0;
        if (index < 0x200)
        {
            // Node array starts at offset 0x10 from the global base; each node is 0x30 bytes
            nodePtr = index * 0x30 + 0x10 + (int)&g_objectNodeTableBase;
        }

        if (nodePtr != 0 && *(uint*)(nodePtr + 0x2C) == handleID)
        {
            int* objectPtr = *(int**)(nodePtr + 0x10); // +0x10: pointer to the actual game object
            if (objectPtr != 0)
            {
                *(int*)(objectPtr + 0x5C / 4) = param_2; // +0x5C: field to set (e.g. flag or value)
                result = 1;
            }
        }
    }
    // If handleID == 0, result remains 1 (vacuous success)
    return result;
}