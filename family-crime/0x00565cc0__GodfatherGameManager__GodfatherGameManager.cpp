// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x00565cc0
// Role: Constructor for the global GodfatherGameManager singleton. Stores instance pointer globally and initializes vtable.

void __fastcall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this)
{
    // Store the instance in the global singleton pointer (DAT_0122343c)
    g_GodfatherGameManager = this;

    // Set the vtable pointer to the class vtable (PTR_LAB_00e3a59c)
    this->vtable = (void*)0x00e3a59c;  // vtable for GodfatherGameManager
}