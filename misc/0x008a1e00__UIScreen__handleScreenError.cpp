// FUNC_NAME: UIScreen::handleScreenError
// Address: 0x008a1e00
// This function clears a 64-byte string buffer at offset +0x1bc and logs an error message based on the error code (param_2).
// Error codes: 0xa0 -> screen_taken, 0xa3 -> plasma_personas_error, otherwise -> name_error.
void __thiscall UIScreen::handleScreenError(void* this, int errorCode)
{
    // Clear the 64-byte error message buffer at this+0x1bc
    _strncpy((char*)((int)this + 0x1bc), "", 0x40);

    // Unimplemented system call (possibly a yield or wait)
    unknownSubroutine(0, 0, 0);  // FUN_00983120

    if (errorCode == 0xa0) {
        debugPrint("$ui_screen_taken");
        return;
    }
    if (errorCode == 0xa3) {
        debugPrint("$ui_plasma_personas_error");
        return;
    }
    debugPrint("$ui_pro_screen_name_error");
}