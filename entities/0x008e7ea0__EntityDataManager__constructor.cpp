// FUNC_NAME: EntityDataManager::constructor
undefined4 * __thiscall EntityDataManager::constructor(undefined4 *this, undefined4 param2)
{
    // Call base class constructor (likely some base game object)
    FUN_0046c590(param2);

    // Set vtable pointer at offset 0x00
    *this = &PTR_FUN_00d8085c;

    // Set function pointers for virtual methods
    // +0x3C: some function pointer
    this[0xf] = &PTR_LAB_00d8084c;
    // +0x48: another function pointer
    this[0x12] = &PTR_LAB_00d80848;

    // +0x50: likely a counter or flag, initialized to 0
    this[0x14] = 0;

    // +0x54 and +0x56: two 16-bit fields zeroed
    *(undefined2 *)(this + 0x15) = 0;          // offset 0x54
    *(undefined2 *)((int)this + 0x56) = 0;     // offset 0x56

    // +0x58: another 32-bit field zeroed
    this[0x16] = 0;

    // +0x5C and +0x5E: two 16-bit fields zeroed
    *(undefined2 *)(this + 0x17) = 0;          // offset 0x5C
    *(undefined2 *)((int)this + 0x5E) = 0;     // offset 0x5E

    // Initialize an array of 16 slots, each 16 bytes (4 ints), starting at offset 0x60
    // Each slot is filled with debug sentinel values to mark unused memory
    // 0xbadbadba, 0xbeefbeef, 0xeac15a55, 0x91100911
    this[0x18] = 0xbadbadba;
    this[0x19] = 0xbeefbeef;
    this[0x1a] = 0xeac15a55;
    this[0x1b] = 0x91100911;
    this[0x1c] = 0xbadbadba;
    this[0x1d] = 0xbeefbeef;
    this[0x1e] = 0xeac15a55;
    this[0x1f] = 0x91100911;
    this[0x20] = 0xbadbadba;
    this[0x21] = 0xbeefbeef;
    this[0x22] = 0xeac15a55;
    this[0x23] = 0x91100911;
    this[0x24] = 0xbadbadba;
    this[0x25] = 0xbeefbeef;
    this[0x26] = 0xeac15a55;
    this[0x27] = 0x91100911;
    this[0x28] = 0xbadbadba;
    this[0x29] = 0xbeefbeef;
    this[0x2a] = 0xeac15a55;
    this[0x2b] = 0x91100911;
    this[0x2c] = 0xbadbadba;
    this[0x2d] = 0xbeefbeef;
    this[0x2e] = 0xeac15a55;
    this[0x2f] = 0x91100911;
    this[0x30] = 0xbadbadba;
    this[0x31] = 0xbeefbeef;
    this[0x32] = 0xeac15a55;
    this[0x33] = 0x91100911;
    this[0x34] = 0xbadbadba;
    this[0x35] = 0xbeefbeef;
    this[0x36] = 0xeac15a55;
    this[0x37] = 0x91100911;
    this[0x38] = 0xbadbadba;
    this[0x39] = 0xbeefbeef;
    this[0x3a] = 0xeac15a55;
    this[0x3b] = 0x91100911;
    this[0x3c] = 0xbadbadba;
    this[0x3d] = 0xbeefbeef;
    this[0x3e] = 0xeac15a55;
    this[0x3f] = 0x91100911;
    this[0x40] = 0xbadbadba;
    this[0x41] = 0xbeefbeef;
    this[0x42] = 0xeac15a55;
    this[0x43] = 0x91100911;
    this[0x44] = 0xbadbadba;
    this[0x45] = 0xbeefbeef;
    this[0x46] = 0xeac15a55;
    this[0x47] = 0x91100911;
    this[0x48] = 0xbadbadba;
    this[0x49] = 0xbeefbeef;
    this[0x4a] = 0xeac15a55;
    this[0x4b] = 0x91100911;
    this[0x4c] = 0xbadbadba;
    this[0x4d] = 0xbeefbeef;
    this[0x4e] = 0xeac15a55;
    this[0x4f] = 0x91100911;
    this[0x50] = 0xbadbadba;
    this[0x51] = 0xbeefbeef;
    this[0x52] = 0xeac15a55;
    this[0x53] = 0x91100911;
    this[0x54] = 0xbadbadba;
    this[0x55] = 0xbeefbeef;
    this[0x56] = 0xeac15a55;
    this[0x57] = 0x91100911;

    return this;
}