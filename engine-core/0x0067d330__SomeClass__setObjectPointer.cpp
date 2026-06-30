// FUNC_NAME: SomeClass::setObjectPointer
void __thiscall SomeClass::setObjectPointer(SomeClass *this, SomeObject *newPtr)
{
    SomeObject **ptrMember = (SomeObject **)((char *)this + 0x18);
    if (*ptrMember != nullptr) {
        // Call Release (vtable offset 0x0C) on the old object
        (*(void (__thiscall **)(SomeObject *))(*ptrMember)->vtable[3])(*ptrMember);
    }
    *ptrMember = newPtr;
    if (newPtr != nullptr) {
        // Call AddRef (vtable offset 0x08) on the new object
        (*(void (__thiscall **)(SomeObject *))newPtr->vtable[2])(newPtr);
    }
}