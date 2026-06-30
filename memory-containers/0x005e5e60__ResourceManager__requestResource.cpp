// FUNC_NAME: ResourceManager::requestResource
// Address: 0x005e5e60
// This function checks/resets a resource slot identified by an ID.
// It supports two modes: mode==1 resets a static slot; mode!=1 checks a dynamic slot
// and falls back to static reset if dynamic slot is not ready.
bool __thiscall ResourceManager::requestResource(uint id, int mode)
{
    char isValid;
    void* staticSlot;
    bool result;

    if (mode == 1)
    {
        // Mode 1: reset static slot for this ID
        isValid = isValidId(id);  // FUN_005e63e0
        if (isValid != 0)
        {
            staticSlot = 0;
            if (id < 0x200) // Static array size 0x200 entries * 0x30 bytes
            {
                // Calculate pointer to static slot: this + 0x10 + id * 0x30
                staticSlot = (void*)((uint)this + 0x10 + id * 0x30);
            }
            // Zero out fields at offsets 0x10, 0x18, 0x20, 0x2c within the slot
            if (staticSlot != 0)
            {
                *(uint32_t*)((uint32_t)staticSlot + 0x10) = 0;
                *(uint32_t*)((uint32_t)staticSlot + 0x18) = 0;
                *(uint32_t*)((uint32_t)staticSlot + 0x20) = 0;
                *(uint32_t*)((uint32_t)staticSlot + 0x2c) = 0;
            }
            return true;
        }
        return false;
    }
    else
    {
        // Non-mode-1: check dynamic array
        uint32_t* dynamicArrayPtr = *(uint32_t**)((uint32_t)this + 0x603c); // pointer to dynamic array
        if (dynamicArrayPtr != 0)
        {
            if (id > 0x1ff)
                return false;
            uint32_t dynamicSlotAddr = (uint32_t)dynamicArrayPtr + id * 0x74; // each entry 0x74 bytes
            if (dynamicSlotAddr == 0)
                return false;
            uint32_t innerPtr = *(uint32_t*)(dynamicSlotAddr + 8); // offset +8 in dynamic entry
            if (innerPtr != 0)
            {
                // Check condition: innerPtr->+8 != 0 and global state is ready and innerPtr->+0x68 != 5
                if (*(uint32_t*)(innerPtr + 8) != 0 && isGlobalStateReady(0) && *(uint32_t*)(innerPtr + 0x68) != 5)
                {
                    return true;
                }
            }
            // Fallback: try static reset with mode 1
            result = requestResource(id, 1);
            return result;
        }
        return false;
    }
}