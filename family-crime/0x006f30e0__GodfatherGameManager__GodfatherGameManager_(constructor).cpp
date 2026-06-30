// FUNC_NAME: GodfatherGameManager::GodfatherGameManager (constructor)
void __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager *this)
{
    // Set vtable pointer (offset +0x00)
    this->vfptr = &PTR_FUN_00d6063c;

    // Set function pointers for multiple inheritance / interfaces
    this->funcTable0xf = &PTR_LAB_00d6062c;  // +0x0f (offset 60)
    this->funcTable0x12 = &PTR_LAB_00d60628; // +0x12 (offset 72)
    this->funcTable0x24 = &PTR_LAB_00d60624; // +0x24 (offset 144)

    // Initialize a list-like sub-object at offset 0x31 (196 bytes)
    // Two initialization calls: first likely initializes internal list structure,
    // second may set up an iterator or container.
    initList(reinterpret_cast<ListHead *>(&this->subObject0x31));     // FUN_004086d0
    initContainer(reinterpret_cast<Container *>(&this->subObject0x31)); // FUN_00408310

    // Initialize another container at offset 0x3f (252 bytes)
    initContainer(reinterpret_cast<Container *>(&this->subObject0x3f)); // FUN_00408310

    // If a pointer exists at offset 0x41 (260), destroy it via function pointer at 0x44 (272)
    if (this->ptr0x41 != nullptr)
    {
        (*(void (__thiscall *)(void *))this->funcDestroy0x44)(this->ptr0x41);
    }

    // Global initialization routines
    initializeGameSubsystemA(); // FUN_006f7b80
    initializeGameSubsystemB(); // FUN_006f2ee0
}