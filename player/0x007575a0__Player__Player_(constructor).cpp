// FUNC_NAME: Player::Player (constructor)
// Address: 0x007575a0
// This appears to be a constructor for the Player class (or possibly a subclass of Sentient).
// It initializes multiple vtable pointers, zeros many fields, and performs a dynamic interface check
// to determine which function pointer to install at offset +0xa8 of another object.

undefined4* __thiscall Player::Player(Player* this, undefined4 param_2, undefined4 param_3)
{
    char cVar1;
    uint uVar2;
    int* piVar3;
    uint unaff_EDI;  // Possibly an additional parameter passed in EDI? (unused in formal def)
    int unaff_retaddr; // Stored return address? Unclear.

    // Call base class constructor (e.g., Sentient::Sentient)
    Sentient::Sentient(param_2, param_3);  // FUN_0075d1b0

    // Initialize vtable pointers and fields
    this[0x3e] = 0;                  // +0xF8
    this[0x3d] = &PTR_LAB_00d61acc;  // +0xF4 (vtable pointer 3)
    this[0x3f] = 0xffffffff;         // +0xFC
    *this = &PTR_LAB_00d64f34;       // +0x00 (vtable pointer 1)
    this[0x14] = &PTR_LAB_00d64f30;  // +0x50 (vtable pointer 2)
    this[0x3d] = &PTR_LAB_00d64f28;  // +0xF4 (overwrite vtable pointer 3)
    this[0x41] = 0;                  // +0x104
    this[0x42] = 0;                  // +0x108
    this[0x43] = 0;                  // +0x10C
    this[0x44] = 0;                  // +0x110
    this[0x45] = 0;                  // +0x114
    this[0x46] = 0;                  // +0x118
    this[0x47] = 0;                  // +0x11C
    this[0x48] = 0;                  // +0x120
    this[0x49] = 0;                  // +0x124
    this[0x4a] = 0;                  // +0x128
    this[0x4b] = 0;                  // +0x12C
    this[0x4c] = 0;                  // +0x130
    this[0x4d] = 0;                  // +0x134
    this[0x52] = 0;                  // +0x148
    this[0x53] = 0;                  // +0x14C
    this[0x54] = 0;                  // +0x150
    this[0x55] = 0;                  // +0x154
    this[0x1a] = 0;                  // +0x68
    this[0x19] = 0;                  // +0x64
    this[0x18] = 0;                  // +0x60
    this[0x58] = 0;                  // +0x160
    this[0x57] = 0;                  // +0x15C
    this[0x56] = 0;                  // +0x158
    this[0x2a] = this[0x2a] | 0x4010000; // +0xA8 flags

    // Determine the base object for the next vtable query
    if (this[0x12] == 0) { // +0x48
        piVar3 = (int*)0x0;
    }
    else {
        piVar3 = (int*)(this[0x12] - 0x48); // pointer to object at offset -0x48 from this[0x12]
    }

    // Virtual call #1: check if object implements interface with hash 0x383225a1
    param_3 = 0;
    cVar1 = (**(code**)(*piVar3 + 0x10))(0x383225a1, &param_3);
    if ((cVar1 != '\0') && (unaff_retaddr != 0)) {
        this[0x2a] = this[0x2a] | 0x100000; // set bit 20 in flags
    }

    // Second virtual query for interface hash 0x18645cd9
    if (this[0x12] == 0) {
        piVar3 = (int*)0x0;
    }
    else {
        piVar3 = (int*)(this[0x12] - 0x48);
    }
    cVar1 = (**(code**)(*piVar3 + 0x10))(0x18645cd9, &stack0x00000000);

    // Conditionally assign the result (unaff_EDI is likely a raw pointer passed in EDI)
    uVar2 = -(uint)(cVar1 != '\0') & unaff_EDI;
    this[0x40] = uVar2; // +0x100

    if (uVar2 != 0) {
        // Check if bit 20 is set in flags
        if ((this[0x2a] >> 0x14 & 1) != 0) {
            // Set the function pointer at offset +0xa8 of the object pointed to by uVar2
            *(code**)(uVar2 + 0xa8) = FUN_00757480;  // Handler A
            this[0x2a] = this[0x2a] & 0xffbfffff;   // Clear bit 22 (0x400000)
            return this;
        }
        // Otherwise use a different handler
        *(code**)(uVar2 + 0xa8) = FUN_00757520;  // Handler B
    }

    this[0x2a] = this[0x2a] & 0xffbfffff; // Clear bit 22
    return this;
}