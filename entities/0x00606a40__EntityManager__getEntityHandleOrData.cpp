// FUNC_NAME: EntityManager::getEntityHandleOrData
// Address: 0x00606a40
// Likely retrieves some handle/ID for an entity if its state is active (2 or 3).
// Uses global entity array gEntityList at 0x011a0f28 with 0x38-byte entries.
// Returns a handle (0x28 offset in return struct) or -1 on failure.

// Struct representing entity data (size 0x38)
struct EntityInfo {
    uint8_t state;           // +0x00: 0=?, 1=?, 2=active, 3=active_other, 4+ = ?
    uint8_t pad0[0x37 - 0x01];
};

// Global array of entity info
extern EntityInfo gEntityList[0x1000]; // size 0x38 each, at 0x011a0f28

// Forward declarations
int __cdecl FUN_00606fd0(void); // some initialization/check
void __cdecl FUN_00614ed0(uint param1, uint param2, uint param3, uint param4); // unknown
int __cdecl FUN_006071a0(void* buffer); // fills a 32-byte struct

int __thiscall FUN_00606a40(uint entityId)
{
    uint8_t state;
    int result;
    
    // Validate entity ID range
    if (entityId >= 0x1000)
        return -1;
    
    // Access entity info
    EntityInfo* pInfo = &gEntityList[entityId];
    if (pInfo == nullptr)
        return -1;
    
    state = pInfo->state;
    // Check if state is 2 or 3 (active states)
    if (state < 4 && state > 1 && state != 0) 
    {
        // Call initialization/validation function
        result = FUN_00606fd0();
        if (result != 0)
        {
            // If some global (unaff_ESI) is non-null, call another function
            // unaff_ESI is likely a register saving from caller, maybe 'this' or global pointer
            if (unaff_ESI != 0)
            {
                // Note: local_8, local_24, local_2c are uninitialized in decompilation
                // This may be a copy or constructor call with garbage parameters
                FUN_00614ed0(local_8, local_24, local_2c, local_2c);
            }
            // Fill a 32-byte buffer (probably returning data via this buffer)
            FUN_006071a0(local_4c);
            // Return the value at offset 0x28 in the stack buffer (a handle or ID)
            return local_28;
        }
    }
    return -1;
}