// FUNC_NAME: SomeClass::~SomeClass
int __thiscall SomeClass::~SomeClass(void* this, byte deleteFlag)
{
    // +0x10: pointer to a dynamically allocated child object
    if (*(int*)((int)this + 0x10) != 0) {
        destroyChild(*(int*)((int)this + 0x10)); // FUN_009c8f10
    }
    if ((deleteFlag & 1) != 0) {
        deallocateMemory(this); // FUN_009c8eb0 (operator delete or custom free)
    }
    return (int)this;
}