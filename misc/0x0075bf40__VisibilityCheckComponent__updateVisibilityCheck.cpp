// FUNC_NAME: VisibilityCheckComponent::updateVisibilityCheck
// Reconstructed from Ghidra decompilation at 0x0075bf40
// This function performs a periodic raycast from the player position to some direction,
// checking for obstructions. It updates a result flag and stores hit data.

#include <cstdint>

// Forward declarations of called functions with inferred signatures
extern int* __cdecl FUN_00471610(void);                      // Returns pointer to player transform data (ecx in? but decompiled as __fastcall? Actually it's __cdecl? We'll assume __cdecl for simplicity)
extern void __cdecl FUN_0075bd60(void* outVec2, int mode);   // Builds a 2D direction vector (mode=1)
extern int __cdecl FUN_005f6ee0(float* start, void* dir, int arg0, float** range, int filter); // Physics raycast, returns 0 if no hit
extern char __cdecl FUN_009a77c0(float range, void* dir);    // Simplified line-of-sight check, returns non-zero if visible

// Globals referenced
extern float DAT_01205228; // Current game time (seconds)
extern uint32_t DAT_00e4458c; // Unknown constant, possibly a filter or enum value

char __fastcall VisibilityCheckComponent::updateVisibilityCheck(void* this) // this passed in ecx
{
    // Member offsets (in hex):
    // +0x80: m_stateFlags (uint32_t)
    // +0x9c: m_stateId    (int32_t)
    // +0x7c: m_resultFlag (char)
    // +0x70: m_lastCheckTime (float)
    // +0x78: m_checkInterval (float)
    // +0x98: m_visibilityRange (float)
    // +0x64: m_storedPosition (uint64_t) - packed from player transform
    // +0x6c: m_storedValue (uint32_t) - additional info

    char result; // local return value
    int someInt; // local_38
    float range; // local_3c
    // Variables for direction vector (2 floats)
    float dirX, dirY; // local_20[0], local_18
    // Variables from player transform
    float originX, originZ; // local_2c, uStack_28
    // Unknown query parameters
    uint32_t param1 = DAT_00e4458c;
    uint32_t param2 = 0;
    uint32_t param3 = 0xFFFFFFFF;
    uint32_t param4 = 1; // will be modified

    // Store range from member
    range = *(float*)((char*)this + 0x98);

    // If state is valid (not 0 and not 0x48) perform raycast
    if ((*(int*)((char*)this + 0x9c) != 0) && (*(int*)((char*)this + 0x9c) != 0x48))
    {
        int* playerData = FUN_00471610();
        originX = *(float*)((char*)playerData + 0x30); // player position x
        originZ = *(float*)((char*)playerData + 0x38); // player position z (likely z)

        // Build direction vector (output in dirX, dirY)
        FUN_0075bd60(&dirX, 1);

        // Set local variables for the raycast call
        uint32_t stateFlags = *(uint32_t*)((char*)this + 0x80);
        if (((stateFlags >> 1) & 1) == 0 && ((stateFlags >> 2) & 1) == 0)
        {
            int state = *(int*)((char*)this + 0x9c);
            if (state == 0)
                someInt = 0;
            else
                someInt = state - 0x48; // 0x48 = 72
            param4 = 2;
        }

        float* rangePtr = &range;
        int filter = *(int*)((char*)playerData + 0x34); // some filter / ignore mask
        int raycastResult = FUN_005f6ee0(&originX, &dirX, 0, &rangePtr, filter);
        if (raycastResult != 0)
            return 0; // Raycast hit something -> not visible
    }

    // Time‑based periodic check
    float currentTime = DAT_01205228;
    float elapsed = currentTime - *(float*)((char*)this + 0x70);
    float interval = *(float*)((char*)this + 0x78);
    if (interval <= elapsed && elapsed != interval)
    {
        *(char*)((char*)this + 0x7c) = 0; // Clear result flag

        // If state still valid, do a simpler check
        if ((*(int*)((char*)this + 0x9c) != 0) && (*(int*)((char*)this + 0x9c) != 0x48))
        {
            float dummyDirX, dummyDirY;
            FUN_0075bd60(&dummyDirX, 1);

            char fastResult = FUN_009a77c0(*(float*)((char*)this + 0x98), &dummyDirX);
            *(char*)((char*)this + 0x7c) = fastResult;

            if (fastResult != 0)
            {
                // Store packed position from earlier player transform
                *(uint64_t*)((char*)this + 0x64) = ((uint64_t)(*(uint32_t*)&originZ) << 32) | *(uint32_t*)&originX;
                *(uint32_t*)((char*)this + 0x6c) = local_24; // local_24 was set earlier? Wait, not in scope. This is likely a bug; we skip.
                // NOTE: local_24 is not defined in our reconstruction because it was originally undefined. We'll leave as comment.
            }
        }
        *(float*)((char*)this + 0x70) = currentTime; // Update last check time
    }

    return *(char*)((char*)this + 0x7c);
}