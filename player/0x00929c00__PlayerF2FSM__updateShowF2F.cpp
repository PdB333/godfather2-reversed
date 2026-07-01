// FUNC_NAME: PlayerF2FSM::updateShowF2F
void __fastcall PlayerF2FSM::updateShowF2F(int this)
{
    // Call to update F2F state machine with byte at +0x51 (likely a state/flag)
    FUN_0093c920(*(undefined1 *)(this + 0x51));
    
    // If the flag at +0x50 is set, show the F2F (Face-to-Face) UI
    if (*(char *)(this + 0x50) != '\0') {
        // "ShowF2F" - likely a debug/UI command to display the F2F screen
        FUN_005a04a0("ShowF2F", 0, &DAT_00d88584, 0);
    }
}