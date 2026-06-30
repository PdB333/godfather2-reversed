// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::~EARSObject(EARSObject* this)
{
    // Set vtable to destructing state (vtable for partial destruction)
    this->vtable = &g_vtableDestructing; // PTR_FUN_00d5fb78

    // If the sub-object at offset +0xC exists, call its virtual destructor with delete flag (1)
    if (this->subObject != nullptr) {
        this->subObject->vtable->destructor(1); // (*(code *)**(undefined4 **)param_1[3])(1)
    }

    // Set vtable to deleted state (vtable for fully destroyed object)
    this->vtable = &g_vtableDeleted; // PTR_LAB_00e2f638
}