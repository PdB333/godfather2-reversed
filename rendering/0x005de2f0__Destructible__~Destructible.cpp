// FUNC_NAME: Destructible::~Destructible

void __thiscall Destructible::~Destructible(void)
{
    // Call virtual destructor (vtable+4) for current object
    (*(void (__thiscall**)(Destructible*))(*(int*)this + 4))(this);

    // Call virtual destructor for subobject at offset 0x38
    (*(void (__thiscall**)(void*))(*(int*)((char*)this + 0x38) + 4))((char*)this + 0x38);

    // Call virtual destructor for subobject at offset 0x70
    (*(void (__thiscall**)(void*))(*(int*)((char*)this + 0x70) + 4))((char*)this + 0x70);

    // Free pointer at offset 0xA8 if allocated (likely a resource)
    if (*(int*)((char*)this + 0xA8) != 0)
    {
        FUN_009c8f10(*(int*)((char*)this + 0xA8));  // Possibly delete or Release()
    }

    // Reset vtable of subobject at +0x70 to base vtable and invoke base destructor
    *(int*)((char*)this + 0x70) = (int)&PTR_FUN_00e3f2d8;
    FUN_004de130();  // base class destructor chain

    // Reset vtable of subobject at +0x38 to base vtable and invoke base destructor
    *(int*)((char*)this + 0x38) = (int)&PTR_FUN_00e3f2d0;
    FUN_004de130();

    // Reset own vtable to base vtable and invoke base destructor
    *(int*)this = (int)&PTR_FUN_00e3f2c8;
    FUN_004de130();
}