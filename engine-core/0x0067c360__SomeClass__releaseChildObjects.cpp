// FUNC_NAME: SomeClass::releaseChildObjects
void __thiscall SomeClass::releaseChildObjects(int this, void* pObj1, void* pObj2)
{
    // Release references to two child objects (likely decrement reference counts)
    Release(pObj1);
    Release(pObj2);
    // Mark this object as destroyed/released (byte at offset 0x9 set to 1)
    *(byte*)(this + 9) = 1;
}