// FUNC_NAME: FlagSet::processOperation
bool __thiscall FlagSet::processOperation(int param_2, int param_3, int operation, uint* flagMask) {
    // operation codes:
    // 5 - test flag(s)
    // 6 - test and clear flag(s)
    // other - delegate to generic handler
    if (operation == 5) {
        // flagMask[1] contains bit mask at offset +4
        return (flagMask[1] & this->flags) != 0;
    }
    if (operation == 6) {
        bool result = (flagMask[1] & this->flags) != 0;
        if (result) {
            // Clear the matched bits
            this->flags &= ~flagMask[1];   // +0x38
        }
        return result;
    }
    // Fallback to generic flag operation handler
    return FUN_00624b00(param_2, param_3, operation, flagMask);
}