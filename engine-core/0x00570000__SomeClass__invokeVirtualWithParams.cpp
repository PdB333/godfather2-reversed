// FUNC_NAME: SomeClass::invokeVirtualWithParams
void __thiscall SomeClass::invokeVirtualWithParams(SomeClass *this) {
    // Structure for parameters passed to virtual function
    struct {
        int field0;   // +0x00: type/command, value 2
        int field4;   // +0x04: size/duration, value 0x10
        int field8;   // +0x08: flags/mode, value 0
    } params;

    params.field0 = 2;
    params.field4 = 0x10;
    params.field8 = 0;

    // Call virtual function via vtable (index 0)
    // DAT_0120556c is a pointer to the vtable
    (*(void (__thiscall **)(SomeClass*, struct Params*))(*DAT_0120556c))(this, &params);
}