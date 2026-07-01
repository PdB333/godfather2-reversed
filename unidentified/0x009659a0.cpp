// FUN_009659a0: NetSession::updateReadyState
void __thiscall NetSession::updateReadyState(void) {
    // +0x6F0: byte readyFlag
    // +0x220: bool m_isHost
    bool isReady = (*(this + 0x6F0) == 0); // ready when flag is zero? invert logic
    char canToggle = FUN_009647b0(isReady); // some condition check
    if (canToggle) {
        *(bool *)(this + 0x6F0) = isReady; // toggle the flag
        char* stateStr = "true";
        if (!isReady) stateStr = "false";

        if (*(char *)(this + 0x220) != 0) {
            // host ready state logging
            FUN_005a04a0("SetHostReadyState", 0, &DAT_00d8cdec, 1, stateStr);
        } else {
            // client ready state logging
            FUN_005a04a0("SetClientReadyState", 0, &DAT_00d8cdec, 1, stateStr);
        }
    }
}