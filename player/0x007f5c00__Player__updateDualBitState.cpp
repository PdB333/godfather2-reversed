// FUNC_NAME: Player::updateDualBitState
// Address: 0x007f5c00
// Checks bit 4 at offsets +0x970 and +0x974, then calls dependent updates.

void __thiscall Player::updateDualBitState(void* this, uint32 arg2, uint32 arg3)
{
    // Bit 4 of two separate flag fields must both be set
    uint32 flags1 = *(uint32*)((uint8*)this + 0x970); // +0x970: first flag set
    uint32 flags2 = *(uint32*)((uint8*)this + 0x974); // +0x974: second flag set
    bool bBothActive = ((flags1 >> 4) & 1) && ((flags2 >> 4) & 1); // local_4

    // Internal update on this object (likely state machine step)
    FUN_007f16b0(this);               // updateInternal

    // Process action with arg3 (e.g., delta time or identifier)
    FUN_007f17a0(arg3, bBothActive);  // handleAction

    // Apply resulting effect using combined flag
    FUN_007f0080(this, bBothActive);  // applyEffect
}