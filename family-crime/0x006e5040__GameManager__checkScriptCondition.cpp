// FUNC_NAME: GameManager::checkScriptCondition

#include <cstdint>

// Forward declarations
extern uint32_t DAT_01205224;  // Global game time or timestamp
extern uint32_t DAT_00e514b0; // Some base time offset
extern int SomeFunc();        // Function at 0x0077dd80

// Assume g_pPlayer is a global pointer to the player object (stored in ESI)
extern class Player* g_pPlayer;

// Property getter function typedef: first param is property manager object (vtable),
// second is hash, third is output pointer. Returns success/availability.
typedef char (__thiscall* GetPropertyFunc)(void* propMgr, int hash, int* out);

// The property manager is at this+0x100, its vtable has the getter at offset 0x10.
bool GameManager::checkScriptCondition() {
    // First property lookup (hash 0x383225a1)
    int firstVal = 0;
    void* propMgr = *(void**)((uint8_t*)this + 0x100);
    void** vtable = *(void***)propMgr;
    GetPropertyFunc getProp = (GetPropertyFunc)vtable[4]; // offset 0x10 = index 4
    char success = getProp(propMgr, 0x383225a1, &firstVal);

    if (success && g_pPlayer != nullptr) {
        // Check player's internal timer at offset 0x26d0
        if (g_pPlayer->field_26d0 != 0 &&
            DAT_01205224 < (DAT_00e514b0 + g_pPlayer->field_26d0)) {
            return true;
        }
    }

    // Second property lookup (hash 0x369ac561)
    int secondVal = 0;
    char success2 = getProp(propMgr, 0x369ac561, &secondVal);

    if (success2 && secondVal != 0) {
        int counter = SomeFunc();
        if (counter > 2) {
            if (*(int*)(secondVal + 0x2238) != 0) {
                return true;
            }
            return false;
        }
        return false;
    }

    return false;
}