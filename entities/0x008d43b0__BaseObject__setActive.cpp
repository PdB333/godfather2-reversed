// FUNC_NAME: BaseObject::setActive
void __thiscall BaseObject::setActive(void)
{
    // Check if there is a callback object at offset +0x64 (100)
    if (*(void**)(this + 0x64) != nullptr)
    {
        // Call virtual function at vtable index 5 (offset 0x14) on the callback object
        (*(void(__thiscall**)(void*))(**(void***)(this + 0x64) + 0x14))();
    }
    // Set the active flag at offset +0x60 (96) to true
    *(uint8_t*)(this + 0x60) = 1;
}