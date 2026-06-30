// FUNC_NAME: GodfatherGameManager::shutdown
// Address: 0x006e79c0
// This function performs the shutdown/deinitialization of the GodfatherGameManager,
// releasing two subsystem objects (likely network and audio managers) and resetting
// the vtable to a finalized state.
// The class layout has function pointer tables at offsets 0x00, 0x04, and 0x10.

// Assume these external functions exist elsewhere in the engine:
void __fastcall releaseObject(int field);  // FUN_009c8f10
void __fastcall freeObject(void* ptr);     // FUN_009c8eb0
void __fastcall shutdownSubsystem();       // FUN_006e6cf0
void __fastcall cleanupA();                // FUN_0049c640
void __fastcall cleanupB();                // FUN_004083d0

// External globals:
extern void* DAT_0112a99c;  // pointer to first subsystem (e.g., network manager)
extern void* DAT_0112a9a0;  // pointer to second subsystem (e.g., audio manager)
extern int DAT_011298a4;    // shutdown flag (0 = active, set to 0 after shutdown)

// External vtable-related labels (pointers to function tables in .rdata):
extern void* PTR_FUN_00d5fb3c;
extern void* PTR_LAB_00d5fb2c;
extern void* PTR_LAB_00d5fb20;
extern void* PTR_LAB_00d5fb00;

// The actual class structure (only the fields we modify are shown)
struct GodfatherGameManager {
    void* vtable;       // +0x00
    void* field_4;      // +0x04
    // ... (offset 0x08, 0x0C unused)
    void* field_16;     // +0x10
};

void __fastcall GodfatherGameManager::shutdown(GodfatherGameManager* this) {
    // Set vtable and additional function pointers to shutdown versions
    this->vtable = &PTR_FUN_00d5fb3c;   // +0x00
    this->field_4 = &PTR_LAB_00d5fb2c; // +0x04
    this->field_16 = &PTR_LAB_00d5fb20; // +0x10

    // Release first subsystem (e.g., network manager)
    if (DAT_0112a99c != nullptr) {
        // First field of the subsystem object is passed to releaseObject
        releaseObject(*(int*)DAT_0112a99c);
        freeObject(DAT_0112a99c);
    }

    // Release second subsystem (e.g., audio manager) with an extra shutdown step
    if (DAT_0112a9a0 != nullptr) {
        shutdownSubsystem();
        releaseObject(*(int*)DAT_0112a9a0);
        freeObject(DAT_0112a9a0);
    }

    // Perform general engine cleanup
    cleanupA();
    cleanupB();

    // Set vtable to final deleted state and mark shutdown complete
    this->vtable = &PTR_LAB_00d5fb00;
    DAT_011298a4 = 0;
}