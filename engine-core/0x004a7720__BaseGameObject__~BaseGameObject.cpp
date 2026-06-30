// FUNC_NAME: BaseGameObject::~BaseGameObject

BaseGameObject * __thiscall BaseGameObject::~BaseGameObject(BaseGameObject *this, byte flags)
{
    // Set vtable to first base class (base object)
    *this = &PTR_FUN_00e353e0; // +0x00 vtable pointer

    // Child object at offset 0x0C (param_1[3])
    if (this->child != 0) {
        // Cleanup child (likely destructor or release)
        FUN_004a6400();
    }

    // If child still exists, call its virtual function (index 0, e.g. release or destructor)
    if (this->child != (ChildObject *)0x0) {
        (*(code *)(**(code **)this->child))(1); // Calls child->vtable[0](1)
    }

    // Set vtable to second base class (final/destroyed state)
    *this = &PTR_LAB_00e2f638; // +0x00 vtable pointer

    // If flags bit 0 set, deallocate this object
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this); // custom operator delete
    }

    return this;
}