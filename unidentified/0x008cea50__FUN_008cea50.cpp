// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass::destructor(undefined4 *this, byte deleteFlag)
{
    int *allocator;

    // Set vtable to derived class vtable (destructor entry)
    *this = &PTR_FUN_00d7cb78;

    // If sub-object at offset 0x28 exists, release it
    if (this[10] != 0) {  // +0x28: pointer to sub-object
        releaseSubObject(this + 10);  // FUN_004daf90
    }

    // Switch vtable to base class vtable (after cleanup)
    *this = &PTR_LAB_00e2f638;

    // If delete flag is set, deallocate memory
    if ((deleteFlag & 1) != 0) {
        allocator = (int *)getMemoryManager();  // FUN_009c8f80
        // Call deallocate function through allocator vtable (offset 4)
        (**(code **)(*allocator + 4))(this, 0xc0);  // size = 192 bytes
    }

    return this;
}