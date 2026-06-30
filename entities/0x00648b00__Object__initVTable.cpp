// FUNC_NAME: Object::initVTable
void __thiscall Object::initVTable(Object *this, int arg1, int arg2)
{
    // +0x00: initialization flag (byte)
    if (this->flag == 0) {
        FUN_00648930();            // one-time init of some shared resource
        this->flag = 1;
    }
    // +0x18c (396): first vtable function pointer
    this->vtable1_func = (void (*)(void))0x00485380;
    // +0x190 (400): first vtable data/code pointer
    this->vtable1_data = (int)&LAB_004853b0;
    // +0x194 (404): first vtable context pointer (from caller)
    this->vtable1_context = vtableBasePtr;
    // +0x64 (100): self-pointer
    this->selfPtr = this;
    // +0x68 (104): second vtable function pointer (same as first)
    this->vtable2_func = (void (*)(void))0x00485380;
    // +0x6c (108): second vtable data/code pointer
    this->vtable2_data = (int)&LAB_004853b0;
    // +0x70 (112): second vtable context pointer (same value from caller)
    this->vtable2_context = vtableBasePtr;

    FUN_00648c60(arg1, arg2);      // further initialization
}