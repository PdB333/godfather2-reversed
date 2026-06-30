// FUNC_NAME: GlobalSystem::initialize
// Address: 0x0041be10
// Initializes the global system singleton, sets vtable pointers and zeroes members.

struct GlobalSystem {
    void** vtable;               // +0x00
    void* field_0x04;            // +0x04 (points to data buffer at 0x120f840)
    int field_0x10;              // +0x10
    int field_0x18;              // +0x18
    void* field_0x1C;            // +0x1C (points to vtable at 0x00e30760)
    void* field_0x20;            // +0x20 (points to data buffer at 0x120fa60)
    int field_0x2C;              // +0x2C
    int field_0x34;              // +0x34
};

GlobalSystem g_GlobalSystem;    // at 0x01206a38

__declspec(naked) GlobalSystem* GlobalSystem::initialize() {
    _asm {
        mov dword ptr [g_GlobalSystem.field_0x10], 0
        mov dword ptr [g_GlobalSystem.field_0x18], 0
        mov dword ptr [g_GlobalSystem.field_0x34], 0
        mov dword ptr [g_GlobalSystem.field_0x2C], 0
        mov dword ptr [g_GlobalSystem.vtable], 0x00e30710
        mov dword ptr [g_GlobalSystem.field_0x1C], 0x00e30760
        mov dword ptr [g_GlobalSystem.field_0x04], 0x0120f840
        mov dword ptr [g_GlobalSystem.field_0x20], 0x0120fa60
        mov eax, offset g_GlobalSystem
        ret
    }
}