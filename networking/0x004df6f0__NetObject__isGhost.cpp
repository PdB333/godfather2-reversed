// FUNC_NAME: NetObject::isGhost
void __thiscall NetObject::isGhost(int* thisPtr, uint8_t* outFlag) {
    *outFlag = 0;
    if (*thisPtr != 0) {
        // +0x10: pointer to ghost info or connection object
        int* ghostInfo = *(int**)(*thisPtr + 0x10);
        if (ghostInfo != 0) {
            // Calls subroutine at 0x004eaec0 to set the flag (likely based on ghost state)
            FUN_004eaec0(ghostInfo, outFlag);
        }
    }
}