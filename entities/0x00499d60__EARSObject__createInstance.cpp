// FUNC_NAME: EARSObject::createInstance
int* EARSObject::createInstance()
{
    int* memory = (int*)EARSAllocator::allocate(0x170);
    if (memory != nullptr) {
        int* object = EARSObject::EARSObjectConstructor(); // FUN_00499da0
        // Call virtual function at vtable offset 0x2c (index 11)
        void (*initFunc)() = (void(*)())(*(int*)(*object + 0x2c));
        initFunc();
        return object;
    }
    // Error path: likely null pointer crash in original code
    (*(void(*)())(0x2c))(); // iRam00000000 + 0x2c
    return (int*)0x0;
}