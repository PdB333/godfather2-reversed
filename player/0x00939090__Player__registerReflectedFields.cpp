// FUNC_NAME: Player::registerReflectedFields

extern void registerBaseReflectFields();
extern void registerReflectField(uint* globalKey, void* fieldPtr, int size, int flags, int unk1, int unk2);
extern void registerReflectArray(uint* globalKey, void* arrayPtr, int flags, int unk1, int unk2);

void __thiscall Player::registerReflectedFields(int thisPtr)
{
    registerBaseReflectFields();

    // +0x64: m_playerId? (size 4)
    registerReflectField(&DAT_00d8a638, (void*)(thisPtr + 100), 4, 0, 0, 1);
    // +0x68: position x/y? (size 4, then 6)
    registerReflectField(&DAT_00d8a634, (void*)(thisPtr + 0x68), 4, 0, 0, 1);
    registerReflectField(&DAT_00d8a630, (void*)(thisPtr + 0x6c), 6, 0, 0, 1);
    // +0x70: string? (size 0)
    registerReflectField(&DAT_00d8a628, (void*)(thisPtr + 0x70), 0, 0, 0, 1);
    // +0x74, +0x78: ints (size 4 each)
    registerReflectField(&DAT_00d8a620, (void*)(thisPtr + 0x74), 4, 0, 0, 1);
    registerReflectField(&DAT_00d8a61c, (void*)(thisPtr + 0x78), 4, 0, 0, 1);
    // +0x7c: string? (size 0)
    registerReflectField(&DAT_00d8a618, (void*)(thisPtr + 0x7c), 0, 0, 0, 1);
    // +0x80: bool (size 1)
    registerReflectField(&DAT_00d8a610, (void*)(thisPtr + 0x80), 1, 0, 0, 1);
    // +0xb8, +0xbc: 6 bytes each (possibly half-float vectors)
    registerReflectField(&DAT_00d8a608, (void*)(thisPtr + 0xb8), 6, 0, 0, 1);
    registerReflectField(&DAT_00d8a600, (void*)(thisPtr + 0xbc), 6, 0, 0, 1);
    // +0xc0, +0xc4: strings
    registerReflectField(&DAT_00d8a5f8, (void*)(thisPtr + 0xc0), 0, 0, 0, 1);
    registerReflectField(&DAT_00d8a5f0, (void*)(thisPtr + 0xc4), 0, 0, 0, 1);
    // +0xc8: bool (m_isAlive?)
    registerReflectField(&DAT_00d8a5e8, (void*)(thisPtr + 200), 1, 0, 0, 1);
    // +0xd4: string, +0xd8, +0xdc: ints, +0xe0,+0xe4: 6 bytes
    registerReflectField(&DAT_00d87b18, (void*)(thisPtr + 0xd8), 4, 0, 0, 1);
    registerReflectField(&DAT_00d87b10, (void*)(thisPtr + 0xdc), 4, 0, 0, 1);
    registerReflectField(&DAT_00d87b08, (void*)(thisPtr + 0xd4), 0, 0, 0, 1);
    registerReflectField(&DAT_00d87b00, (void*)(thisPtr + 0xe0), 6, 0, 0, 1);
    registerReflectField(&DAT_00d87af8, (void*)(thisPtr + 0xe4), 6, 0, 0, 1);
    // +0xf8, +0xfc: 6 bytes, +0x100: string
    registerReflectField(&DAT_00d8a5e0, (void*)(thisPtr + 0xf8), 6, 0, 0, 1);
    registerReflectField(&DAT_00d8a5d8, (void*)(thisPtr + 0xfc), 6, 0, 0, 1);
    registerReflectField(&DAT_00d8a5d0, (void*)(thisPtr + 0x100), 0, 0, 0, 1);
    // +0x108,+0x10c: 6 bytes, +0x110: int
    registerReflectField(&DAT_00d8a5c8, (void*)(thisPtr + 0x108), 6, 0, 0, 1);
    registerReflectField(&DAT_00d8a5c0, (void*)(thisPtr + 0x10c), 6, 0, 0, 1);
    registerReflectField(&DAT_00d8a5b8, (void*)(thisPtr + 0x110), 4, 0, 0, 1);
    // +0x124,+0x128,+0x12c: ints, +0x130: 6 bytes
    registerReflectField(&DAT_00d8a5b0, (void*)(thisPtr + 0x124), 4, 0, 0, 1);
    registerReflectField(&DAT_00d8a5a8, (void*)(thisPtr + 0x128), 4, 0, 0, 1);
    registerReflectField(&DAT_00d8a5a0, (void*)(thisPtr + 300), 4, 0, 0, 1);
    registerReflectField(&DAT_00d8a598, (void*)(thisPtr + 0x130), 6, 0, 0, 1);
    // +0x140: array (registered via separate function)
    registerReflectArray(&DAT_00d8a590, (void*)(thisPtr + 0x140), 0, 0, 1);
}