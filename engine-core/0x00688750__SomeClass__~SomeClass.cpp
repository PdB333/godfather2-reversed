// FUNC_NAME: SomeClass::~SomeClass
int __thiscall SomeClass::~SomeClass(int this, byte flags)
{
    // +0x140: pointer to sub-object (e.g., a component or child object)
    if (*(int *)(this + 0x140) != 0) {
        destroySubObject(this + 0x140);
    }
    performGlobalCleanup(); // static cleanup (e.g., manager shutdown)
    if ((flags & 1) != 0) {
        operatorDelete(this, 0x160); // free memory for this object (size 0x160)
    }
    return this;
}