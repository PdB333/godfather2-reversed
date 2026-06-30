// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Function address: 0x005f5a40
// Constructor for GodfatherGameManager. Sets up vtable pointers and performs base initialization.
// Object layout (assumed based on vtable handling):
//   +0x00: first vtable pointer (primary base)
//   +0x04: second vtable pointer (secondary base)
// Called functions:
//   FUN_004086d0: GodfatherGameManager::initBase (takes a global parameter)
//   FUN_004083d0: GodfatherGameManager::initSubsystem (global function, no args)

#include <cstddef> // for offsetof if needed

// Forward declarations for called functions (actual implementations elsewhere)
void __fastcall initBase(GodfatherGameManager* this, void* param); // FUN_004086d0
void __fastcall initSubsystem();                                    // FUN_004083d0

// Global variables referenced
extern void* g_someGlobal;        // DAT_012069c4 - likely a base struct or manager
extern int g_initializationFlag;  // _DAT_0122351c - set to 0 after construction

// Vtable symbols (addresses from PTR_ constants)
extern void* g_vtable_00e40788; // first base vtable
extern void* g_label_00e4078c;  // second base vtable or sentinel
extern void* g_vtable_00e4079c; // derived class vtable

struct GodfatherGameManager {
    void** vtable; // +0x00
    void* field_4; // +0x04 - secondary vtable or base pointer
    // ... other members follow

    GodfatherGameManager(); // constructor
};

void __fastcall GodfatherGameManager::GodfatherGameManager()
{
    // Step 1: Set vtable pointers for base class ordering
    this->vtable = (void**)&g_vtable_00e40788;  // primary base vtable
    this->field_4 = (void*)&g_label_00e4078c;   // secondary base vtable (or sentinel)

    // Step 2: Call base initialization routines (constructors init, etc.)
    initBase(this, &g_someGlobal);              // FUN_004086d0 - passes global
    initSubsystem();                            // FUN_004083d0 - no params

    // Step 3: Overwrite vtable with derived class vtable
    this->vtable = (void**)&g_vtable_00e4079c;  // derived class vtable

    // Step 4: Mark initialization complete (global flag)
    g_initializationFlag = 0;
}