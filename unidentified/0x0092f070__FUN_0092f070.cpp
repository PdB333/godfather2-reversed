// FUNC_NAME: UnknownClass::release
// Address: 0x0092f070
// Role: Destructor/release function for an object that owns a pointer to another object with a custom deleter.
// this[0] (offset 0x00): pointer to inner object
// this[3] (offset 0x0C): function pointer to release the inner object (called with inner object as argument)
// param_2 (deleteFlag): if bit 0 set, deallocate this object via operatorDelete

int* __thiscall UnknownClass::release(int* this, byte deleteFlag)
{
    if (this[0] != 0) {
        ((void (*)(int*))this[3])((int*)this[0]);
    }
    if ((deleteFlag & 1) != 0) {
        FUN_009c8eb0(this); // operatorDelete or custom deallocator
    }
    return this;
}