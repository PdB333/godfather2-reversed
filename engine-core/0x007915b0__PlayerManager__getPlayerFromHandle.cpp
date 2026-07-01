// FUNC_NAME: PlayerManager::getPlayerFromHandle
int __thiscall PlayerManager::getPlayerFromHandle() {
    // +0x9C: m_playerHandle (index or offset)
    int handle = *(int *)(this + 0x9C);

    // Check for invalid handle (0 or 0x48 sentinel) or if the handle is not valid
    if (handle == 0 || handle == 0x48 || !this->isHandleValid()) {
        // Fallback: get player from alternative system
        int altHandle = this->getFallbackHandle();
        return this->resolveFallbackPlayer(altHandle); // returns handle offset by 0x48
    }

    // Convert handle to an index: 0 stays 0, otherwise subtract the sentinel value (0x48)
    int index = (handle == 0) ? 0 : handle - 0x48;

    // +0x1ED8: array of player pointers (each entry is handle + 0x48)
    int *playerArray = (int *)(this + 0x1ED8);
    if (playerArray[index] != 0) {
        // Stored value is the actual player pointer plus 0x48; subtract sentinel to get real pointer
        return playerArray[index] - 0x48;
    }

    return 0;
}