// FUNC_NAME: Player::getReputation
int Player::getReputation() {
    int result = 0;
    if (this != nullptr) {
        // Virtual function at vtable+0x1e8 returns a component pointer (e.g., ReputationComponent*)
        void* component = this->getComponent(); // (*(code **)(*this + 0x1e8))()
        if (component != nullptr) {
            // Second call to same virtual function (likely a bug in decompiler or intentional re-check)
            component = this->getComponent(); // (*(code **)(*this + 0x1e8))()
            // Return value at offset +0x1ed4 from the component (e.g., reputation score)
            return *(int*)((char*)component + 0x1ed4);
        }
        // Fallback: read member at offset +0x2e4 (0xB90 bytes) from this (e.g., cached reputation)
        result = *(int*)((char*)this + 0xB90);
    }
    return result;
}