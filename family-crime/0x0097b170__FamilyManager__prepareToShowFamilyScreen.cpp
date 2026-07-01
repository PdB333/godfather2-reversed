// FUNC_NAME: FamilyManager::prepareToShowFamilyScreen
/* Function address: 0x0097b170
   Role: Prepares the family screen for display, optionally updating family info.
   Reconstructed from decompiled Ghidra output. */

#include <cstdint>

// Global variables from the binary (addresses assumed)
extern uint32_t g_timeBase;          // DAT_011302b8
extern uint32_t g_someData;          // DAT_00d8f99c (context for events)
extern uint32_t g_defaultLastField;  // _DAT_00d5780c

// Helper function forward declarations (callconv __fastcall, but simplified)
void resetTimeStruct(void* timeStruct, int param);       // FUN_00408a00
void someFunctionWithOffset(void* pointer);              // FUN_0097e300
void anotherFunction(int param);                         // FUN_0097a310
void logEvent(const char* eventName, int flag, void* data, int flag2); // FUN_005a04a0

class FamilyManager {
public:
    void prepareToShowFamilyScreen();  // Method at 0x0097b170

    // Member variables (offsets from 'this')
    // +0x48: flag indicating family info needs update (byte)
    char m_needsFamilyUpdate;         
    // +0x5c: pointer or handle used in update
    void* m_updateFamilyInfoPtr;      
    // +0x60: bitfield (bit 0x200 = screen preparing flag)
    uint32_t m_flags;                 
    // +0x1b0..0x1bc: state variables
    int32_t m_field1;                 // +0x1b0
    int32_t m_field2;                 // +0x1b4
    int32_t m_field3;                 // +0x1b8
    int32_t m_lastField;              // +0x1bc
};

void FamilyManager::prepareToShowFamilyScreen() {
    // Temporary time/structure for reset
    struct TimeStruct {
        uint32_t base;   // +0x00
        uint32_t zero;   // +0x04
        uint8_t  pad;    // +0x08
    } timeStruct;

    timeStruct.base = g_timeBase;
    timeStruct.zero = 0;
    timeStruct.pad  = 0;

    // Reset the time structure (likely sets up a timer or timestamp)
    resetTimeStruct(&timeStruct, 0);

    // Set the flag indicating we are preparing the screen
    m_flags |= 0x200;

    // If not called on null instance, use the pointer at +0x5c
    void* ptr = (this) ? reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 0x5c) : nullptr;
    someFunctionWithOffset(ptr);

    // Another call with parameter 0 (maybe finalizing previous state)
    anotherFunction(0);

    // Optionally log family info update event
    if (m_needsFamilyUpdate != 0) {
        logEvent("UpdateFamilyInfo", 0, &g_someData, 0);
    }

    // Always log "PrepareToShowScreen" event
    logEvent("PrepareToShowScreen", 0, &g_someData, 0);

    // Clear three fields and set the last one from a global
    m_field1    = 0;
    m_field2    = 0;
    m_field3    = 0;
    m_lastField = g_defaultLastField;
}