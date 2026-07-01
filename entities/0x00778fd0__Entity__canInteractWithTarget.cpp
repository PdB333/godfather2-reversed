// FUNC_NAME: Entity::canInteractWithTarget
// Function at 0x00778fd0 - Checks if an entity can interact with its target based on flags, distance, and line of sight.

#include <cstdint>

// Forward declarations (assumed from other functions)
extern void* g_GlobalStateManager; // DAT_012233a0, pointer to global state manager
extern float g_MaxInteractionRange; // DAT_00d68360

// Assumed function signatures
extern bool __cdecl isGlobalStateBlocked(); // FUN_0087cb30 - returns non-zero if blocked
extern void* __cdecl getSomeObject(); // FUN_00471610 - returns pointer to an object (e.g., player or vehicle position)
extern bool __cdecl compareDistance(void* a, void* b); // FUN_0045c470 - compares distances, sets extraout_ST0
extern bool __cdecl checkLineOfSight(void* position, int param1, int param2); // FUN_006c0050 - line of sight check

// __thiscall reconstructed as member function
bool __fastcall Entity::canInteractWithTarget(void* thisPtr)
{
    // Offsets for this object
    // +0x90: uint32_t m_flags (bit4 = interactEnabled? bit5,6 = other blocking flags)
    // +0x88: void* m_pTargetEntity (pointer to target entity base)
    uint32_t flags = *(uint32_t*)((uint8_t*)thisPtr + 0x90);
    void* targetPtr = *(void**)((uint8_t*)thisPtr + 0x88);

    // Initial result false
    bool result = false;

    // Check if interaction allowed by flags and target exists valid
    if ((flags & (1 << 4)) != 0 && targetPtr != nullptr && targetPtr != (void*)0x48)
    {
        // Compute base of target entity (offset 0x48 subtracted)
        void* targetBase = (uint8_t*)targetPtr - 0x48;
        uint32_t targetStateFlags = *(uint32_t*)((uint8_t*)targetBase + 0xc88);
        uint32_t targetOtherFlags = *(uint32_t*)((uint8_t*)targetBase + 0xf28);

        // Check bit11 of state flags (0x800) and bit14 of other flags (0x4000)
        if ((targetStateFlags & (1 << 11)) == 0 &&
            (targetOtherFlags & (1 << 14)) == 0 &&
            !isGlobalStateBlocked() &&
            (flags & (1 << 6)) == 0 &&  // bit6
            (flags & (1 << 5)) == 0 &&  // bit5
            *(void**)((uint8_t*)g_GlobalStateManager + 4) != nullptr &&
            *(void**)((uint8_t*)g_GlobalStateManager + 4) != (void*)0x1f30)
        {
            // Get two objects (likely positions)
            void* obj1 = getSomeObject();
            void* obj2 = getSomeObject();

            // Compare distance between positions (+0x30 offset assumed for position)
            compareDistance((uint8_t*)obj2 + 0x30, (uint8_t*)obj1 + 0x30);

            // Check if distance is within range (extraout_ST0 < global max)
            // Note: compareDistance sets a floating point result; we model as function returning bool or using global flag
            if (/* extraout_ST0 < g_MaxInteractionRange */)
            {
                void* position = (uint8_t*)obj1 + 0x30;
                if (checkLineOfSight(position, 1, 1))
                {
                    result = true;
                }
            }
        }
    }

    return result;
}