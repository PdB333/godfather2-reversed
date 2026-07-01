// FUNC_NAME: SomeClass::operatorDeleteOrDestructor
undefined4 __thiscall SomeClass::disposeOrDestructor(SomeClass *this, byte flags)
{
    SomeClass::baseDestructor();
    if ((flags & 1) != 0) {
        SomeClass::operatorDelete((SomeClass *)this);
    }
    return (undefined4)this;
}