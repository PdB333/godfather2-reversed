// Xbox PDB: EARS_Apt_UIHud_RemoveCrew
// FUNC_NAME: CrewLeaderComponent::removeCrew
// Address: 0x00939550
// Role: Removes the crew associated with this component. Checks active flag, copies crew data from a manager, then logs the removal.

#include <cstdint>

class CrewLeaderComponent {
public:
    // +0x48: bool indicating if this component has an active crew
    bool m_bHasActiveCrew; // offset 0x48
    // +0x70: pointer to crew data (e.g., some structure containing crew info)
    void* m_pCrewData; // offset 0x70
};

// Forward declarations for called functions
class CrewManager; // assumed from callee FUN_007351c0
CrewManager* __cdecl getCrewManager(); // FUN_007351c0
void __cdecl eventLog(const char* format, int arg1, int arg2, int arg3); // FUN_005a04a0

void __thiscall CrewLeaderComponent::removeCrew(CrewLeaderComponent* this) {
    if (this->m_bHasActiveCrew) {
        CrewManager* pMgr = getCrewManager();
        if (pMgr != nullptr) {
            // Second call to get the same manager? Possibly a different instance or idempotent getter.
            CrewManager* pMgr2 = getCrewManager();
            // Offset +0xC4 in the manager contains the crew data pointer to copy into this component
            this->m_pCrewData = *(void**)((uint8_t*)pMgr2 + 0xC4);
        }
        eventLog("RemoveCrew", 0, 0x00d8a64c, 0); // 0x00d8a64c is some constant flag/ID
    }
}