// FUNC_NAME: DestructionState::deactivateOrFinalize
void __fastcall DestructionState::deactivateOrFinalize(int this)
{
    // Clear completion flag (0x10 + bitfields, clearing bit 4 and bit 5)
    *(uint *)(this + 0x10) = *(uint *)(this + 0x10) & 0xffffffaf;
    
    // Call base/system deactivation (0x0068c590) with a parameter 0
    FUN_0068c590(0);
    
    // Cleanup or finalize the associated data (at +0x18)
    FUN_008f2cf0(*(undefined4 *)(this + 0x18));
}