// FUNC_NAME: BaseObject::~BaseObject

void __thiscall BaseObject::~BaseObject(BaseObject *this)
{
    // +0x10: pointer to child object (e.g., component or sub-object)
    // +0x1c: function pointer for child destructor
    if (this->childObject != 0) {
        (this->childDestructorFunc)(this->childObject);
    }
    // Set vtable to base class vtable (sentinel for after destruction)
    // +0x00: vtable pointer, assigned to &PTR_LAB_00e317cc (base vtable)
    this->vtable = (int *)&PTR_LAB_00e317cc;
    return;
}