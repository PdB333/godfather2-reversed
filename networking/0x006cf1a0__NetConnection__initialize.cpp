// FUNC_NAME: NetConnection::initialize
void __fastcall NetConnection::initialize(NetConnection* this)
{
    // +0xa0: unknown field, set to 0
    *(int*)((char*)this + 0xa0) = 0;
    // +0xa8: unknown field, set to 0
    *(int*)((char*)this + 0xa8) = 0;
    // +0xac: unknown field, set to 0
    *(int*)((char*)this + 0xac) = 0;
    // +0xa4: set to global value (likely a default timeout or window size)
    *(int*)((char*)this + 0xa4) = g_defaultValue1;
    // +0xb0: set to another global value
    *(int*)((char*)this + 0xb0) = g_defaultValue2;
    // +0xc4: set to 2 (possibly mode or state)
    *(int*)((char*)this + 0xc4) = 2;

    // Allocate a sub-object (likely a packet window or reliable queue)
    PacketWindow* window = (PacketWindow*)FUN_004eb390(0x30, 0x10); // size 0x30, alignment 0x10
    int* globalVal = &g_defaultValue3;
    if (window != nullptr) {
        window->vtable = &PacketWindow_vtable; // PTR_FUN_00e372b4
        window->refCount = 0;
        window->field_4 = *globalVal;
        window->field_5 = *globalVal;
        window->field_6 = *globalVal;
        window->field_7 = *globalVal;
        window->field_8 = 0;
    }
    // Store pointer at +0xd8
    *(PacketWindow**)((char*)this + 0xd8) = window;
    if (window != nullptr) {
        window->refCount++; // increment reference count
    }

    // +0xe0: set to 0
    *(int*)((char*)this + 0xe0) = 0;
    // +0xe4: set to global value
    *(int*)((char*)this + 0xe4) = g_defaultValue4;
    // +0xe8: set to global value
    *(int*)((char*)this + 0xe8) = g_defaultValue5;
    // +0xec: set to global value (same as used in window init)
    *(int*)((char*)this + 0xec) = *globalVal;

    // Zero out a large buffer (0x98 bytes) starting at +0xf0
    memset((char*)this + 0xf0, 0, 0x98);

    // +0x188: set to 0 (likely a flag or byte)
    *(char*)((char*)this + 0x188) = 0;
}