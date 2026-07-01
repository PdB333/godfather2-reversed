// FUNC_NAME: GodfatherGameManager::GodfatherGameManager

void __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager *this)
{
    // Set vtable pointers for base classes (initial)
    this->vtable0 = &PTR_FUN_00d74d10;   // +0x00: first vtable
    this->vtable1 = &PTR_LAB_00d74d00;   // +0x04: second vtable

    // Acquire global mutex (DAT_0112dcf4 is a critical section)
    enterCriticalSection(&DAT_0112dcf4);

    // Register this class instance with the system (hash 0x874f7077 = "GodfatherGameManager")
    registerClassInstance(0x874f7077);

    // If there is a subobject at offset +0x10, release it
    if (this->subObject != 0) {           // +0x10: pointer to subobject
        releaseSubObject(this->subObject);
    }

    // Update vtable pointers to final derived class vtables
    this->vtable1 = &PTR_LAB_00e30fe0;   // +0x04: override second vtable
    this->vtable0 = &PTR_LAB_00d74cfc;   // +0x00: override first vtable

    // Reset global flag
    DAT_0112a66c = 0;
}