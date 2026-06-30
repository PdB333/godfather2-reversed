// FUNC_NAME: SomeManager::destroy
void __thiscall SomeManager::destroy(void)
{
    // this vtable is set to the initial interface
    *this = &PTR_LAB_00e3f0ac;

    // call destructor for sub-object at offset 0x4 (e.g., a container or array)
    FUN_005d9a00(this + 1);

    // perform another cleanup step
    FUN_005d9e60();

    // if the resource handle at offset 0x8 is non-null, release it via vfunc[1] (offset 0x4)
    if (this->resourceHandle != 0) {
        // vtable[1] is a release function, called with argument 0
        (**(code **)(*(int *)*this + 4))(this->resourceHandle, 0);
        this->resourceHandle = 0;
    }

    // call vfunc[3] (offset 0xc) for final cleanup
    (**(code **)(*(int *)*this + 0xc))();

    // switch to a null vtable (indicates object is dead)
    *this = &PTR_LAB_00e3f0b0;

    // clear global singleton pointer (if applicable)
    _DAT_01223500 = 0;
}