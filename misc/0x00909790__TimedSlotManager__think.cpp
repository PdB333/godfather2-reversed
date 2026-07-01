// FUNC_NAME: TimedSlotManager::think
// Function at 0x00909680, thunk at 0x00909790
// Manages 6 timed slots, checks for object removal based on threshold and active state

typedef unsigned int uint32_t;

struct SlotEntry {
    int m_id;               // +0x00: object identifier (0 or 0x48 = invalid/unused)
    int m_padding;          // +0x04: unused in this function
};

struct TimedSlotManager {
    // Offsets from this (hex)
    /* +0x00 */ // vtable pointer (inferred)
    /* +0x70 */ SlotEntry m_slots[6];          // 6 slot entries, each 8 bytes
    /* +0xA4 */ int m_timer;                   // Timer data used by getElapsedTime
    /* +0xB0 */ uint32_t m_activeCount;        // Number of active objects (compared to global limit)
    /* +0xB4 */ uint32_t m_flags;              // Bitfield: bit 0 = active, bit 2 = finished/pending removal
    /* +0xC8 */ float m_timeThreshold;          // Threshold for removal (scaled by global multiplier)
    /* +0x64 */ int m_pendingObject;            // Pointer/handle to an object to clean up
};

// External functions (signatures assumed from usage)
int __fastcall isSystemActive();                     // FUN_00909590
float __fastcall getElapsedTime(int timerAddr);       // FUN_006bff90
void __fastcall deleteObject(int objHandle);          // FUN_004daf90
void* __fastcall getObjectById(int id);              // FUN_00471610
char __fastcall extendObjectLife(void* objTimer, int, int); // FUN_006c0050
void __fastcall removeObject(int handleMinus12);      // FUN_004088c0

extern uint32_t g_maxActive;                         // DAT_01205224
extern float g_timeMultiplier;                       // DAT_00d5c454

// The method itself (this in ECX)
int __fastcall TimedSlotManager::think(TimedSlotManager* this) {
    int sysActive = isSystemActive();

    if (sysActive == 0) {
        // System inactive: check if we already handled finished state
        if (((this->m_flags >> 2) & 1) == 0) {
            // Not finished: deactivate and delete pending object if any
            this->m_flags &= 0xFFFFFFFE;          // Clear bit 0 (active)
            if (this->m_pendingObject != 0) {
                deleteObject(this->m_pendingObject);
                this->m_pendingObject = 0;
            }
            return 1;                             // Indicates cleanup done
        }
        // Already finished: clear finished flag and let fall through to return 0
        this->m_flags &= 0xFFFFFFFB;              // Clear bit 2
    }
    else if (this->m_activeCount < g_maxActive) {
        // System active and we can still add more objects
        float elapsed = getElapsedTime((int)&this->m_timer);
        if (this->m_timeThreshold <= elapsed) {
            float scaledThreshold = this->m_timeThreshold * g_timeMultiplier;

            // Iterate over all 6 slots
            for (int i = 0; i < 6; i++) {
                int id = this->m_slots[i].m_id;
                if (id != 0 && id != 0x48) {
                    // Object exists in this slot
                    void* obj = getObjectById(id);              // Get the full object
                    float objTime = getElapsedTime((int)((unsigned char*)obj + 0x30)); // Access obj's timer at +0x30
                    if (objTime < scaledThreshold) {
                        // Object not expired yet; try to extend its life
                        char result = extendObjectLife((unsigned char*)obj + 0x30, 0, 0);
                        if (result == 0)
                            goto continueLoop;                  // Extension failed, skip removal
                    }
                    // Remove the object (handle shifted by -0xC)
                    removeObject(id - 0xC);
                    this->m_flags |= 5;                          // Set bits 0 (active) and 2 (finished)
                }
            continueLoop:
                ; // Continue to next slot
            }
        }
    }
    // Default return: no special action taken
    return 0;
}