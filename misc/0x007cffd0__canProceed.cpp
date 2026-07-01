// FUNC_NAME: canProceed
bool canProceed() {
    // Check if first global flag is set
    uint8_t* first = reinterpret_cast<uint8_t*>(getGameManager());
    if ((first[4] & 1) != 0) {
        // If first flag set, then check second flag
        uint8_t* second = reinterpret_cast<uint8_t*>(getSimManager());
        if ((second[4] & 1) != 0) {
            // Both flags set – cannot proceed
            return false;
        }
    }
    return true;
}