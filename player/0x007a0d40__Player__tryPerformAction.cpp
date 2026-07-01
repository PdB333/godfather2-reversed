// FUNC_NAME: Player::tryPerformAction
void Player::tryPerformAction(int this, int* pController, char bStart)
{
    char cVar1;
    undefined1 auStack_24 [4];
    undefined4 uStack_20;
    
    // Check state flags at offsets 0x8e0 and 0x8e8
    // Bit 24 of flag at 0x8e0 must be clear
    // Bit 28 of flag at 0x8e8 must be clear
    // Bit 23 of flag at 0x8e0 must be clear
    if ((((*(uint *)(this + 0x8e0) >> 0x18 & 1) == 0) &&
         ((*(uint *)(this + 0x8e8) >> 0x1c & 1) == 0)) &&
        ((*(uint *)(this + 0x8e0) >> 0x17 & 1) == 0) &&
        // Additional check via some global/system function
        (cVar1 = FUN_007f47a0(), cVar1 == '\0')) {
        // Virtual call on controller at VTable index 0x234 (141)
        // Arg1: opposite of bStart (bStart ? false : true)
        // Arg2: 1 (possibly enable or start)
        (**(code **)(*pController + 0x234))(bStart == '\0', 1);
        // Update controller subsystem at offset 0x58
        FUN_004a8ec0(pController + 0x16); // pController + 0x58 bytes
        // Prepare event data and send command 0x1a (26)
        auStack_24[0] = 1;
        uStack_20 = 5;
        FUN_007dd600(0x1a, auStack_24);
    }
    return;
}