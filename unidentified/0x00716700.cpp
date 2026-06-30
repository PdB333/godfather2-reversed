// FUN_00716700: Player::init
void __fastcall Player::init(int thisPtr)
{
    // Call global initialization function (likely EARS engine singleton)
    FUN_00716340(DAT_01205224);
    
    // Reset player flag at offset 0x1b0
    *(int*)(thisPtr + 0x1b0) = 0; // +0x1b0: m_playerFlags or similar
}