// FUNC_NAME: GlobalSystems::areAllSubsystemsStopped
// Address: 0x0095b290
// Role: Checks if two subsystems (pointed by global pointers) are both disabled.
// If param_1 is non-zero, it calls a virtual method (offset 0x2c) on each subsystem if their flag at +0x12 is set.
// Returns 1 if both flags are zero (both disabled), otherwise 0.

// Global pointers to subsystem instances (likely singletons)
// DAT_0112fee4 -> g_systemA
// DAT_011305b4 -> g_systemB
struct Subsystem;
extern Subsystem* g_systemA;
extern Subsystem* g_systemB;

// Assume Subsystem has a vtable at +0x0, a byte flag at +0x12, and a disable method at vtable+0x2c
struct SubsystemVtable {
    void (*disable)(Subsystem* self);      // +0x2c
};

struct Subsystem {
    SubsystemVtable* vtable;               // +0x0
    // ... other fields
    char m_flag;                           // +0x12 (1 if active, 0 if disabled)
    // ... rest
};

int areAllSubsystemsStopped(char param_1)  // __cdecl
{
    Subsystem* systemA = g_systemA;
    Subsystem* systemB = g_systemB;

    if (param_1 != 0) {
        // If param_1 is set, attempt to disable each subsystem if it's currently active
        if (systemA->m_flag != 0) {
            systemA->vtable->disable(systemA);  // vtable+0x2c
        }
        if (systemB->m_flag != 0) {
            systemB->vtable->disable(systemB);
        }
    }

    // Return 1 only if both subsystems are fully disabled (flags == 0)
    if ((systemA->m_flag == 0) && (systemB->m_flag == 0)) {
        return 1;
    }
    return 0;
}