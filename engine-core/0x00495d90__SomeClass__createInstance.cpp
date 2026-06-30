// FUNC_NAME: SomeClass::createInstance
int* SomeClass::createInstance()
{
    // Allocate memory for object of size 0x108 (264 bytes)
    int* memory = (int*)operator new(0x108);
    if (memory != nullptr)
    {
        // Call constructor at FUN_00495b20
        int* obj = FUN_00495b20(memory);
        // Call virtual method at vtable offset +0x2c (likely an init or post-constructor)
        (**(code**)(*obj + 0x2c))();
        return obj;
    }
    // Fallback: if allocation fails, still try to call virtual method (likely unreachable)
    (**(code**)(*((int*)nullptr) + 0x2c))();
    return nullptr;
}