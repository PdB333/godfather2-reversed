// FUNC_NAME: Player::disableCoverAndSetNextTime
void __thiscall Player::disableCoverAndSetNextTime() {
    // Clear cover flag (bit 0) at offset +0x308
    *(uint *)((int)this + 0x308) &= 0xfffffffe;
    // Set next cover check time (global game time + 250ms) at offset +0x32c
    *(int *)((int)this + 0x32c) = DAT_01205224 + 250;
}