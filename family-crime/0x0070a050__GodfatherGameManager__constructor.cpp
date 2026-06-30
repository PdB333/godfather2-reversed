// FUNC_NAME: GodfatherGameManager::constructor
// Function address: 0x0070a050
// Role: Constructor for GodfatherGameManager. Sets global singleton pointer, stores vtable, calls further init.

#include <cstdint>

// Forward declaration of vtable type
struct GodfatherGameManager_vtable;

// External global singleton pointer (address 0x01129910)
extern GodfatherGameManager* g_pGodfatherGameManager;

// Forward declaration of additional initialization function (FUN_0070a000)
void __fastcall GodfatherGameManager_init(GodfatherGameManager* this);

// Constructor for GodfatherGameManager
GodfatherGameManager* __fastcall GodfatherGameManager::constructor(GodfatherGameManager* this)
{
    // Save this pointer as global singleton
    g_pGodfatherGameManager = this;

    // Set vtable pointer to the known vtable at 0x00d613b8
    this->vtable = reinterpret_cast<GodfatherGameManager_vtable*>(0x00d613b8);

    // Call additional init (virtual base class setup or member initialization)
    GodfatherGameManager_init(this);

    return this;
}