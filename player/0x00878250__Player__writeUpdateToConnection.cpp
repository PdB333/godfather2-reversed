// FUNC_NAME: Player::writeUpdateToConnection
void __thiscall Player::writeUpdateToConnection(int* this, int* target, int arg) {
    int retVal;
    char buffer[12]; // 12-byte buffer for serialization
    int messageField0; // offset unused
    int messageField1;
    int messageField2;
    int messageField3; // initialized from global constant

    if (target != (int*)0x0) {
        // Check if debug flag (bit 11) is set in the player's flags at +0xC88
        if (((uint)this[0x322] >> 11) & 1) {
            retVal = FUN_008f9d10(); // get some value (e.g., current time or ID)
            if (retVal != 0) {
                FUN_0043b870(DAT_01131070); // print debug message (global string)
                FUN_0074ca40(retVal);      // handle debug output
            }
        }

        // Initialize message structure
        messageField0 = 0;
        messageField1 = 0;
        messageField2 = 0;
        messageField3 = _DAT_00d5780c; // global constant

        // Virtual call on this: write data from offset arg+4 into buffer with count 1
        (**(code**)(*this + 0x90))(buffer, arg + 4, 1);

        // Virtual call on target: feed buffer to its update handler (offset +0x28)
        (**(code**)(*target + 0x28))(&stack0xffffffa4); // likely passes buffer address

        // Set flags on target: bits 0x802000 (0x800000 + 0x2000) and clear counter at +0x158
        target[0x7d6] = target[0x7d6] | 0x802000;
        target[0x56] = 0;
    }
    return;
}