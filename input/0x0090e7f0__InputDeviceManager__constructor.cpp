// FUNC_NAME: InputDeviceManager::constructor
// Function address: 0x0090e7f0
// Constructor for InputDeviceManager, initializes controller slots and event callbacks
// Each controller slot has a structure with a 4-byte state and two 2-byte fields (e.g., flags/counters)
// The class holds 6 such slots? Actually pattern shows 6 blocks of 8 bytes each (0x50 to 0x7F)
// Then a block of 8 ints (0x84..0xA0) and other fields.
// Base class constructor called via FUN_0046c590

undefined4 * __thiscall InputDeviceManager::constructor(undefined4 *this, undefined4 param_2)
{
    undefined4 globalValue;

    // Base class constructor call (e.g., Framework::Object::Object)
    FUN_0046c590(param_2);

    // Set vtable pointer (pointing to InputDeviceManager vtable)
    *this = &PTR_FUN_00d83770;

    // Set event handler function pointers at offsets +0x3C and +0x48
    // These likely handle device connection/disconnection notifications
    this[0xf] = &PTR_LAB_00d83760;   // +0x3C: onDeviceAdded ?
    this[0x12] = &PTR_LAB_00d8375c;  // +0x48: onDeviceRemoved ?

    // Initialize the first controller slot (index 0) - 8 bytes at +0x50..0x57
    this[0x14] = 0;                          // +0x50: slotState (4 bytes)
    *(undefined2 *)(this + 0x15) = 0;        // +0x54: slotFlags (2 bytes)
    *(undefined2 *)((int)this + 0x56) = 0;   // +0x56: slotCounter (2 bytes)

    // Slot 1
    this[0x16] = 0;                          // +0x58
    *(undefined2 *)(this + 0x17) = 0;        // +0x5C
    *(undefined2 *)((int)this + 0x5e) = 0;   // +0x5E

    // Slot 2
    this[0x18] = 0;                          // +0x60
    *(undefined2 *)(this + 0x19) = 0;        // +0x64
    *(undefined2 *)((int)this + 0x66) = 0;   // +0x66

    // Slot 3
    this[0x1a] = 0;                          // +0x68
    *(undefined2 *)(this + 0x1b) = 0;        // +0x6C
    *(undefined2 *)((int)this + 0x6e) = 0;   // +0x6E

    // Slot 4
    this[0x1c] = 0;                          // +0x70
    *(undefined2 *)(this + 0x1d) = 0;        // +0x74
    *(undefined2 *)((int)this + 0x76) = 0;   // +0x76

    // Slot 5
    this[0x1e] = 0;                          // +0x78
    *(undefined2 *)(this + 0x1f) = 0;        // +0x7C
    *(undefined2 *)((int)this + 0x7e) = 0;   // +0x7E

    // Clear following integer fields (possibly additional slot state arrays)
    this[0x20] = 0;  // +0x80
    this[0x21] = 0;  // +0x84
    this[0x22] = 0;  // +0x88
    this[0x23] = 0;  // +0x8C
    this[0x24] = 0;  // +0x90
    this[0x25] = 0;  // +0x94
    this[0x26] = 0;  // +0x98
    this[0x27] = 0;  // +0x9C
    this[0x28] = 0;  // +0xA0

    // More initialization
    this[0x2a] = 0;         // +0xA8
    globalValue = DAT_00e445ac;  // Possibly this pointer to another manager or global state
    this[0x29] = 0;         // +0xA4
    this[0x2d] = 0;         // +0xB4
    this[0x2b] = globalValue; // +0xAC: store global pointer
    this[0x2e] = 0xffffffff;  // +0xB8: -1, invalid/not connected
    this[0x2c] = 0x10;        // +0xB0: maximum number of controller slots (16)

    return this;
}