// FUNC_NAME: OwnerClass::~OwnerClass
void __fastcall OwnerClass::~OwnerClass(void *thisPtr)
{
    // Call base class or intermediate cleanup
    FUN_0084ace0(thisPtr);

    // Release owned object at offset 0x2c via its virtual destructor at 0x38
    if (*(int *)((char *)thisPtr + 0x2c) != 0) {
        (**(code **)((char *)thisPtr + 0x38))(*(int *)((char *)thisPtr + 0x2c));
    }

    // Release owned object at offset 0x1c via its virtual destructor at 0x28
    if (*(int *)((char *)thisPtr + 0x1c) != 0) {
        (**(code **)((char *)thisPtr + 0x28))(*(int *)((char *)thisPtr + 0x1c));
    }

    // Deallocate raw pointer at offset 0x10
    if (*(int *)((char *)thisPtr + 0x10) != 0) {
        FUN_009c8f10(*(int *)((char *)thisPtr + 0x10));
    }

    // Deallocate raw pointer at offset 0x04
    if (*(int *)((char *)thisPtr + 4) != 0) {
        FUN_009c8f10(*(int *)((char *)thisPtr + 4));
    }

    return;
}