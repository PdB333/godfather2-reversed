// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x0084b2f0
// Role: Constructor for the singleton GodfatherGameManager – initializes base class, sets vtables, zeroes fields, and registers with the engine.

extern void* g_vtable_GodfatherGameManager;        // PTR_FUN_00d74d54
extern void* g_vtable_GodfatherGameManager_Base2;  // PTR_LAB_00d74d4c (first secondary vtable)
extern void* g_vtable_GodfatherGameManager_Derived; // PTR_LAB_00d74d50 (overwrites secondary vtable)
extern GodfatherGameManager* g_pGodfatherGameManager; // DAT_0112a668

// Forward declarations for called functions
void __fastcall BaseObject_Constructor(void* this); // FUN_0049c610
void __fastcall RegisterManager(void* data, int flag); // FUN_0049c6e0

// 5 fields after offset 0x0C are initialized to zero
struct GodfatherGameManager {
    void* vtable;          // +0x00 primary vtable
    // +0x04 padding or base class data (not touched here)
    void* vtable2;         // +0x08 secondary vtable (multiple inheritance)
    int field_0C;          // +0x0C
    int field_10;          // +0x10
    int field_14;          // +0x14
    int field_18;          // +0x18
    int field_1C;          // +0x1C
};

void* __fastcall GodfatherGameManager::GodfatherGameManager(void* this) {
    BaseObject_Constructor(this);                // call base class ctor

    this->vtable = &g_vtable_GodfatherGameManager; // set primary vtable

    g_pGodfatherGameManager = this;              // store global singleton

    // Decompilation shows two assignments to the same offset – possibly 
    // indicating a second base class vtable that is later adjusted.
    this->vtable2 = &g_vtable_GodfatherGameManager_Base2;
    this->vtable2 = &g_vtable_GodfatherGameManager_Derived; // override

    // Zero-fill 5 fields starting at offset 0x0C
    this->field_0C = 0;
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    this->field_1C = 0;

    RegisterManager(&g_someGlobalData, 1);        // FUN_0049c6e0(&DAT_00d74d40,1)

    return this;
}