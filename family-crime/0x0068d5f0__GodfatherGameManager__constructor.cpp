// FUNC_NAME: GodfatherGameManager::constructor

// Reconstructed constructor for GodfatherGameManager (singleton manager)
// Sets up virtual function table entries, member fields, and copies initial data from global if available.

void* g_pGodfatherGameManager = nullptr;  // DAT_01129810

struct GodfatherGameManager {
    // Offset 0x00: Primary vtable pointer (set to &GodfatherGameManager_vtable)
    void* vtable;

    // Offset 0x04: Field, initialized to 1
    int field_04;

    // Offset 0x08: Field, initialized to 0
    int field_08;

    // Offset 0x0C: Pointer (initially base vtable/function pointer, then overridden with derived)
    void* somePtr_0C;

    // Offset 0x10: Field, initialized to 0
    int field_10;

    // Offset 0x14: Pointer (initially base vtable/function pointer, then overridden with derived)
    void* somePtr_14;

    // Offset 0x18: Field, initialized to 0
    int field_18;
};

// Static global data (symbolic names from Ghidra)
extern void* PTR_FUN_00d5c66c;   // Primary vtable pointer
extern void* PTR_FUN_00e32808;   // Base class vtable/function pointer
extern void* PTR_LAB_00d5c660;   // Another base pointer
extern void* PTR_LAB_00d5c668;   // Derived pointer for offset 0x0C
extern void* PTR_LAB_00d5c664;   // Derived pointer for offset 0x14

extern void* g_templateData;     // DAT_01206940 - pointer to template data block (0x8000 bytes)
extern void* g_configPtr;        // DAT_00d5779c - configuration pointer for FUN_009cb330

// Forward declarations of called functions
void FUN_0040eba0(int param);
void FUN_009cb330(void* param);
void FUN_00408900(void* dst, void* src, int size);  // Memory copy

GodfatherGameManager* __fastcall GodfatherGameManager_constructor(GodfatherGameManager* this) {
    // Initialize base class portion (first set base vtable pointers)
    this->field_04 = 1;
    this->field_08 = 0;
    this->somePtr_0C = &PTR_FUN_00e32808;  // Base vtable/function pointer
    this->field_10 = 0;
    this->somePtr_14 = &PTR_LAB_00d5c660;  // Base pointer

    // Store global singleton reference
    g_pGodfatherGameManager = this;

    // Override vtable with derived class pointers
    this->vtable = &PTR_FUN_00d5c66c;      // Derived primary vtable
    this->somePtr_0C = &PTR_LAB_00d5c668;  // Derived pointer for offset 0x0C
    this->somePtr_14 = &PTR_LAB_00d5c664;  // Derived pointer for offset 0x14
    this->field_18 = 0;

    // Call initialization routines
    FUN_0040eba0(0);                       // Engine or subsystem init
    FUN_009cb330(g_configPtr);             // Config initialization

    // Copy template data block into this object if available
    if (g_templateData != nullptr) {
        FUN_00408900(this, &g_templateData, 0x8000);
    }

    return this;
}