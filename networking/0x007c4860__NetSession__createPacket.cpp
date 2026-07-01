// FUNC_NAME: NetSession::createPacket
// Function address: 0x007c4860
// Role: Allocates and initializes a packet of a given type (0,1,2) from a memory pool,
//       then either sends it directly (type 0) or processes it further (types 1,2).
//       Checks conditions on a sub-object (offset +0xff0) before allocation.

bool __thiscall NetSession::createPacket(undefined4 param2, undefined4 param3, int actionType)
{
    // +0xff0: pointer to a sub-object (e.g., connection state)
    char* subObjPtr = *(char**)(this + 0xff0);
    bool result = false;

    if (subObjPtr != nullptr)
    {
        // +0x48: offset to some base of the sub-object
        char* subObjBase = subObjPtr - 0x48;
        if (subObjBase != nullptr &&
            // +0x1e8c and +0x1ed4: likely sequence numbers or version checks
            *(int*)(subObjPtr + 0x1e8c) != *(int*)(this + 0x1ed4) &&
            // +0x1b44 and +0xfb1: flags indicating state (e.g., not in use)
            *(char*)(subObjPtr + 0x1b44) == 0 &&
            *(char*)(subObjPtr + 0xfb1) == 0)
        {
            // +0x1fa4: some context value for allocation
            int allocContext = *(int*)(this + 0x1fa4);
            // +0x1fa8 and +0x1fb0: pointers to allocation parameters
            int* allocParam1 = (int*)(this + 0x1fa8);
            int* allocParam2 = (int*)(this + 0x1fb0);

            int allocatedObj = 0;

            if (actionType == 0)
            {
                // Type 0: allocate 0x208 bytes, pool ID 7, flags 0x208
                allocatedObj = FUN_00896b30(7, 0x208, allocContext, *allocParam1, 2, 0);
                if (allocatedObj != 0)
                {
                    char success = FUN_007c4600(allocatedObj, subObjBase, 0, this);
                    if (success != 0)
                    {
                        int localVar = 0;
                        FUN_007c4040(allocatedObj, &localVar, param3);
                        return true;
                    }
                }
            }
            else if (actionType == 1)
            {
                // Type 1: allocate 0x80 bytes, flags 0x10000400
                allocatedObj = FUN_00896b30(0x80, 0x10000400, allocContext, *allocParam2, 0x80, 0);
                if (allocatedObj == 0) return false;
                char success = FUN_007c4600(allocatedObj, subObjBase, 1, this);
                if (success == 0) return false;
                int localVar = 1;
                result = FUN_007c4500(allocatedObj, &localVar, this, param2, param3);
            }
            else if (actionType == 2)
            {
                // Type 2: allocate 8 bytes, flags 0x10000400
                allocatedObj = FUN_00896b30(8, 0x10000400, allocContext, *allocParam2, 8, 0);
                if (allocatedObj == 0) return false;
                char success = FUN_007c4600(allocatedObj, subObjBase, 2, this);
                if (success == 0) return false;
                int localVar = 2;
                result = FUN_007c4500(allocatedObj, &localVar, this, param2, param3);
            }
        }
    }
    return result;
}