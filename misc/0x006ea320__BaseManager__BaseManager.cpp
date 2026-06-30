// FUNC_NAME: BaseManager::BaseManager

void __fastcall BaseManager::BaseManager(BaseManager* this)
{
    // Set vtable pointers for this object (virtual inheritance support)
    this->vftable0 = &PTR_FUN_00d5fd1c;   // Primary vtable at +0x00
    this->vftable1 = &PTR_LAB_00d5fd0c;   // Secondary vtable at +0x3C
    this->vftable2 = &PTR_LAB_00d5fd08;   // Another vtable at +0x48

    // Initialize global singleton or shared data structure
    initGlobalTable(&DAT_0120e93c);

    // Initialize a sub‑object embedded at offset 0x70
    initSubObject((int)this + 0x70);

    // If an optional resource pointer at +0x60 exists, call its destructor via function pointer at +0x6C
    if (this->resourcePtr != 0) {
        ((void (__thiscall*)(void*))this->resourceDestructor)(this->resourcePtr);
    }

    // Perform final constructor steps (e.g., registering self, posting creation)
    finalizeConstruction();
}