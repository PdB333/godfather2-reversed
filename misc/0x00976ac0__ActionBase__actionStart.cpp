// FUNC_NAME: ActionBase::actionStart
void __thiscall ActionBase::actionStart(int* this, int param_2, long long* param_3)
{
    // Set a flag byte at offset 0x1C1 to 0 (e.g., "active" or "pending" flag)
    *(char*)(this + 0x1C1) = 0;

    // Engine-internal function (possibly memory manager or subsystem init)
    FUN_00957780(2);

    if (param_3 != nullptr && param_2 != 0)
    {
        // Set flags at +0x60 (bit 0x20)
        this[0x18] |= 0x20; // +0x60

        // Copy the first 8 bytes of param_3 into a field at +0x94 (64-bit)
        *(long long*)(this + 0x94) = *param_3;

        // Copy an integer from offset 8 of param_3 into field at +0x9C
        this[0x27] = *(int*)((char*)param_3 + 8); // +0x9C

        // Store param_2 into field at +0x90
        this[0x24] = param_2; // +0x90
    }

    // Call virtual method at vtable offset 0x28 (likely "onStart" or "execute")
    (*(void (**)(void))(*this + 0x28))();
}