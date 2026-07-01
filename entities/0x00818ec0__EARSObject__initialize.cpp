// FUNC_NAME: EARSObject::initialize
void __thiscall EARSObject::initialize(EARSObject* this, void* vtableOrBase, int childId)
{
    // Store the vtable/base pointer in the first field (offset +0x00)
    this->vtablePtr = vtableOrBase;

    // Call virtual function at vtable offset 8 (index 2) – likely a constructor/init
    ((void (*)())(*(int**)(vtableOrBase))[2])();

    // If a child ID is provided, create a child object via factory function
    if (childId != 0) {
        this->childObject = FUN_004265d0(childId, this->vtablePtr); // +0x04
    } else {
        this->childObject = 0;
    }
}