// FUNC_NAME: PlayerSM::resetState
void __fastcall PlayerSM::resetState(int this)
{
    // +0x970: state flags (bitfield) - clear all but bits 0x9e0 (likely keep some persistent flags)
    *(uint32_t *)(this + 0x970) = *(uint32_t *)(this + 0x970) & 0x9e0;
    
    // +0xa21: some byte flag (e.g., bTransitioning or bAnimating)
    *(uint8_t *)(this + 0xa21) = 0;
    
    // Clear all state timer/accumulator slots (0x990-0x9ac, 0x9c0-0x9cc, 0x9b0-0x9bc)
    *(uint32_t *)(this + 0x990) = 0;
    *(uint32_t *)(this + 0x994) = 0;
    *(uint32_t *)(this + 0x998) = 0;
    *(uint32_t *)(this + 0x99c) = 0;
    *(uint32_t *)(this + 0x9a0) = 0;
    *(uint32_t *)(this + 0x9a4) = 0;
    *(uint32_t *)(this + 0x9a8) = 0;
    *(uint32_t *)(this + 0x9ac) = 0;
    *(uint32_t *)(this + 0x9c0) = 0;
    *(uint32_t *)(this + 0x9c4) = 0;
    *(uint32_t *)(this + 0x9c8) = 0;
    *(uint32_t *)(this + 0x9cc) = 0;
    *(uint32_t *)(this + 0x9b0) = 0;
    *(uint32_t *)(this + 0x9b4) = 0;
    *(uint32_t *)(this + 0x9b8) = 0;
    *(uint32_t *)(this + 0x9bc) = 0;
    
    // Clear input buffer slots (0x9f0-0x9fc, 0xa00-0xa0c, 0xa10-0xa1c)
    // These are 3 sets of 4-byte values, each set has a "current" and "previous" value
    // The _DAT_00d5780c is likely a global "invalid" or "neutral" input value
    uint32_t neutralInput = _DAT_00d5780c;
    
    *(uint32_t *)(this + 0x9f8) = 0;
    *(uint32_t *)(this + 0x9f4) = 0;
    *(uint32_t *)(this + 0x9f0) = 0;
    *(uint32_t *)(this + 0x9fc) = neutralInput;  // Set to neutral
    
    *(uint32_t *)(this + 0xa08) = 0;
    *(uint32_t *)(this + 0xa04) = 0;
    *(uint32_t *)(this + 0xa00) = 0;
    *(uint32_t *)(this + 0xa0c) = neutralInput;  // Set to neutral
    
    *(uint32_t *)(this + 0xa18) = 0;
    *(uint32_t *)(this + 0xa14) = 0;
    *(uint32_t *)(this + 0xa10) = 0;
    *(uint32_t *)(this + 0xa1c) = neutralInput;  // Set to neutral
    
    // Reset 28 state machine sub-state objects (each 0x30 bytes apart)
    // FUN_007ef3c0 is likely a "reset" or "clear" function for a state object
    // Offsets: 0xac0, 0xaf0, 0xb20, 0xb50, 0xb80, 0xbb0, 0xbe0, 0xc10,
    //          0xc40, 0xc70, 0xca0, 0xcd0, 0xd00, 0xd30, 0xd60, 0xd90,
    //          0xdc0, 0xdf0, 0xe20, 0xe50, 0xe80, 0xeb0, 0xee0, 0xf10,
    //          0xf40, 0xf70, 0xfa0 (0x4000 = 0xfa0)
    FUN_007ef3c0(this + 0xac0);
    FUN_007ef3c0(this + 0xaf0);
    FUN_007ef3c0(this + 0xb20);
    FUN_007ef3c0(this + 0xb50);
    FUN_007ef3c0(this + 0xb80);
    FUN_007ef3c0(this + 0xbb0);
    FUN_007ef3c0(this + 0xbe0);
    FUN_007ef3c0(this + 0xc10);
    FUN_007ef3c0(this + 0xc40);
    FUN_007ef3c0(this + 0xc70);
    FUN_007ef3c0(this + 0xca0);
    FUN_007ef3c0(this + 0xcd0);
    FUN_007ef3c0(this + 0xd00);
    FUN_007ef3c0(this + 0xd30);
    FUN_007ef3c0(this + 0xd60);
    FUN_007ef3c0(this + 0xd90);
    FUN_007ef3c0(this + 0xdc0);
    FUN_007ef3c0(this + 0xdf0);
    FUN_007ef3c0(this + 0xe20);
    FUN_007ef3c0(this + 0xe50);
    FUN_007ef3c0(this + 0xe80);
    FUN_007ef3c0(this + 0xeb0);
    FUN_007ef3c0(this + 0xee0);
    FUN_007ef3c0(this + 0xf10);
    FUN_007ef3c0(this + 0xf40);
    FUN_007ef3c0(this + 0xf70);
    FUN_007ef3c0(this + 0xfa0);  // 0x4000 = 0xfa0
}