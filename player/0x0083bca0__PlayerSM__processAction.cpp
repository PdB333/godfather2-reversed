// FUNC_NAME: PlayerSM::processAction

// Reconstructed from address 0x0083bca0
// This function checks action permissions via a hash lookup and delegates to the main action handler.
// The class is likely PlayerSM (Player State Machine) based on the use of flags at this+0xa8.

extern bool HashLookup(uint16_t key, uint32_t hash, int* outResult); // FUN_005fd340
extern int32_t DelegateAction(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, uint32_t flags); // FUN_0083b370

// Unknown internal structure at this+0xa8: flags bitfield
// Bit 1 (>>1 & 1) seems to indicate a blocked/restricted state

int32_t __thiscall PlayerSM::processAction(int32_t thisPtr, int32_t actionObj, int32_t actionData,
                                           int32_t arg4, int32_t arg5, int32_t arg6,
                                           int32_t arg7, int32_t arg8, int32_t arg9)
{
    uint32_t actionFlags = 0;
    int32_t permissionLevel = 2; // Default permission level (2 = blocked?)
    
    if (actionObj != 0)
    {
        int32_t result = 0;
        uint32_t* pLookupResult = 0;
        
        bool hashFound = HashLookup(*(uint16_t*)(actionData + 0x12), 0x48043505, &result);
        if (hashFound)
        {
            if ((pLookupResult != 0) && (result != 0) && (*(char*)(result + 0x06) == 0x02))
            {
                actionFlags = *pLookupResult;
            }
            if ((actionFlags & 2) != 0)
            {
                return 3; // Action explicitly blocked
            }
        }
        if ((actionFlags & 1) != 0)
        {
            permissionLevel = 1; // Permission granted
        }
        // Check the object's own restriction flag (bit 1 of flags at +0xa8)
        if (((*(uint32_t*)(thisPtr + 0xa8) >> 1 & 1) != 0) && (permissionLevel != 1))
        {
            return 3; // Blocked by own state
        }
    }
    
    // Delegate to the main action handler with modified flags
    return DelegateAction(arg4, arg5, arg6, arg7, arg8, arg9, (actionFlags >> 2) & 0xFFFFFF01);
}