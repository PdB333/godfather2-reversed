// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager

// Address: 0x0068db80
// Destructor for the GodfatherGameManager singleton. Performs teardown of child objects, 
// restores vtable to base destructor, releases resources, and clears the global singleton flag.

void __fastcall GodfatherGameManager::~GodfatherGameManager(undefined4 *this)
{
    // Switch vtable to base class vtable for destruction
    *this = &PTR_FUN_00d5c684;
    this[3] = &PTR_LAB_00d5c680;

    // Call base cleanup (likely mutex unlock or other manager-level teardown)
    FUN_004086d0(&DAT_012069c4);

    // Release child object if present (call its virtual destructor at vtable+0xC)
    if (this[4] != (int *)0x0) {
        (**(code **)(*(int *)this[4] + 0xc))();
    }

    // Set vtable to final destructor vtable
    this[3] = &PTR_LAB_00d5c67c;

    // Mark singleton as destroyed
    DAT_011298e0 = 0;

    // Final cleanup (e.g., free memory, close handles)
    FUN_004083d0();
}