// FUNC_NAME: SomeClass::cleanupResources
void __thiscall SomeClass::cleanupResources(SomeClass* this)
{
    // +0x00: pointer 0, +0x0C: function pointer 0
    if (this->ptr0 != 0) {
        (this->deleter0)(this->ptr0);
    }
    // +0x10: pointer 1, +0x1C: function pointer 1
    if (this->ptr1 != 0) {
        (this->deleter1)(this->ptr1);
    }
    // +0x20: pointer 2, +0x2C: function pointer 2
    if (this->ptr2 != 0) {
        (this->deleter2)(this->ptr2);
    }
    // +0x30: pointer 3, +0x3C: function pointer 3
    if (this->ptr3 != 0) {
        (this->deleter3)(this->ptr3);
    }
    // +0x40: pointer 4, +0x4C: function pointer 4
    if (this->ptr4 != 0) {
        (this->deleter4)(this->ptr4);
    }
}