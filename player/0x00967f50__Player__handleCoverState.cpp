// FUNC_NAME: Player::handleCoverState
// Address: 0x00967f50
// Role: Handles cover state transitions based on flags at +0x6f4.
// If bit 19 (0x80000) is set, clears byte at +0x704 and calls exitCover.
// If bit 18 (0x40000) is set, sets bit 19 to transition into cover.

void __thiscall Player::handleCoverState(void)
{
    uint32_t flags = *(uint32_t *)((uint8_t *)this + 0x6f4); // +0x6f4: cover state flags

    // Check if already in cover (bit 19)
    if ((flags & 0x80000) != 0) {
        *(uint8_t *)((uint8_t *)this + 0x704) = 0; // +0x704: cover timer or substate
        FUN_00967ec0(*(uint32_t *)((uint8_t *)this + 0x1e0)); // +0x1e0: pointer to cover manager or component
        return;
    }

    // Check if entering cover (bit 18)
    if ((flags & 0x40000) != 0) {
        *(uint32_t *)((uint8_t *)this + 0x6f4) = flags | 0x80000; // Set bit 19 to mark as in cover
    }
}