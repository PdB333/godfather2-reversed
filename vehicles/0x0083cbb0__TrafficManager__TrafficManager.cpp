// FUNC_NAME: TrafficManager::TrafficManager

undefined4 * __thiscall TrafficManager::TrafficManager(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
    undefined4 uVar1;
    
    FUN_0046c490(0,0); // base class constructor
    *this = &PTR_FUN_00d743b8; // vtable pointer
    this[0xf] = &PTR_LAB_00d743a8; // +0x3C
    this[0x12] = &PTR_LAB_00d743a4; // +0x48
    this[0x14] = DAT_00d742d4; // +0x50
    this[0x17] = DAT_00d5ccf8; // +0x5C
    this[0x1d] = DAT_00d5779c; // +0x74
    this[0x15] = param_3; // +0x54
    this[0x1e] = 0; // +0x78
    this[0x1f] = 0; // +0x7C
    this[0x20] = 0; // +0x80
    this[0x22] = 0; // +0x88
    this[0x23] = 0; // +0x8C
    this[0x24] = 0; // +0x90
    uVar1 = FUN_009c8e80(0x100); // allocate 256 bytes
    this[0x25] = uVar1; // +0x94
    this[0x26] = 0; // +0x98
    this[0x27] = 0x20; // +0x9C - initial capacity 32
    this[0x28] = 0; // +0xA0
    this[0x29] = DAT_00e448a4; // +0xA4
    uVar1 = DAT_00d5eee4;
    this[0x2c] = 0xbadbadba; // +0xB0 - sentinel/magic
    this[0x2f] = 0x91100911; // +0xBC - another sentinel
    this[0x2d] = 0xbeefbeef; // +0xB4
    this[0x2e] = 0xeac15a55; // +0xB8
    this[0x30] = 0xbadbadba; // +0xC0
    this[0x35] = uVar1; // +0xD4
    this[0x36] = 0; // +0xD8
    this[0x34] = 0xffffffff; // +0xD0
    this[0x37] = 0; // +0xDC
    *(undefined2 *)(this + 0x38) = 0; // +0xE0
    *(undefined2 *)((int)this + 0xe2) = 0; // +0xE2
    this[0x39] = 0; // +0xE4
    *(undefined2 *)(this + 0x3a) = 0; // +0xE8
    *(undefined2 *)((int)this + 0xea) = 0; // +0xEA
    this[0x3b] = 0; // +0xEC
    *(undefined2 *)(this + 0x3c) = 0; // +0xF0
    *(undefined2 *)((int)this + 0xf2) = 0; // +0xF2
    this[0x3d] = 0xffffffff; // +0xF4
    this[0x3e] = param_2; // +0xF8
    this[0x3f] = 0x8000; // +0xFC - max vehicles 32768
    this[0x4a] = 0; // +0x128
    this[0x4e] = 0; // +0x138
    this[0x4f] = 0; // +0x13C
    this[0x50] = 0; // +0x140
    this[0x2a] = 0; // +0xA8
    this[0x2b] = 0; // +0xAC
    this[0x33] = 0; // +0xCC
    this[0x32] = 0; // +0xC8
    this[0x31] = 0; // +0xC4
    this[0x30] = 0; // +0xC0
    FUN_00446560(this); // initialize some internal state
    this[5] = this[5] & 0xdfffffff; // clear some flag
    FUN_00408240(&DAT_0112dc4c, "iMsgPauseAllTrafficManagers");
    FUN_00408240(&DAT_0112dc44, "iMsgUnPauseAllTrafficManagers");
    FUN_00408240(&DAT_0112dc58, "iMsgEntityDensitySpawned");
    FUN_00408240(&DAT_0112dc68, "iMsgEntityDensityPostSpawned");
    FUN_00408240(&DAT_0112dc60, "iMsgTrafficMgrDespawnEntities");
    FUN_00408680(&DAT_0112dc4c);
    FUN_00408680(&DAT_0112dc44);
    FUN_00408680(&DAT_0112dc60);
    return this;
}