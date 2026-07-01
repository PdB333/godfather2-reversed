// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Function address: 0x0080a050
// Role: Constructor for the GodfatherGameManager class (object size = 0x1f30 bytes)
// Calls base EARSObject constructor and conditionally zeroes memory.

GodfatherGameManager* __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this, byte initFlags)
{
    EARSObject::EARSObject(this);
    if ((initFlags & 1) != 0) {
        // Zero-initialize the entire object (size 0x1f30 = 7984 bytes)
        // Typically used when the object is heap-allocated to clear memory.
        memset(this, 0, 0x1f30);
    }
    return this;
}