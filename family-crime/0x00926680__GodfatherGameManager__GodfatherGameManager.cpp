// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x00926680
// Role: Constructor for the GodfatherGameManager singleton. Sets up vtable, secondary pointers, and stores global instance.

// Forward declaration of base class constructor (called at 0x005bf9b0)
void __fastcall UnknownBaseConstructor(void); // Replace with actual base class name if known

// External global singleton pointer (DAT_0112fc8c)
extern GodfatherGameManager* g_pGodfatherGameManager;

// Vtable pointers (addresses are from data section)
extern void* PTR_FUN_00d85e48;  // Main vtable for GodfatherGameManager
extern void* PTR_LAB_00d85e24;  // Secondary vtable or interface pointer (offset +0x04)
extern void* PTR_LAB_00d85d78;  // Initially assigned to offset +0x4C
extern void* PTR_LAB_00d85e20;  // Final assignment to offset +0x4C

class GodfatherGameManager {
public:
    // Fields (offsets based on param_1[n] usage)
    void* vtable;                    // +0x00
    void* field_0x04;                // +0x04 (secondary vtable?)
    char pad_0x08[0x44];             // +0x08 to +0x4B (padding, not set in this function)
    void* field_0x4C;                // +0x4C (set twice, final value is PTR_LAB_00d85e20)
    int field_0x50;                  // +0x50 (initialized to 0)
    // Size likely >= 0x54

    GodfatherGameManager();
};

// Constructor implementation
void __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this) {
    // Call base class constructor (likely part of EARS::Framework::Manager)
    UnknownBaseConstructor();

    // Set main vtable pointer
    this->vtable = &PTR_FUN_00d85e48;

    // Set secondary pointer at offset +0x04 (possibly a derived interface)
    this->field_0x04 = &PTR_LAB_00d85e24;

    // Two assignments to field_0x4C: first then overwritten (decompiler artifact or intentional?)
    this->field_0x4C = &PTR_LAB_00d85d78;   // +0x4C initial
    this->field_0x4C = &PTR_LAB_00d85e20;   // +0x4C final

    // Initialize integer at +0x50 to 0
    this->field_0x50 = 0;

    // Store global singleton pointer
    g_pGodfatherGameManager = this;
}