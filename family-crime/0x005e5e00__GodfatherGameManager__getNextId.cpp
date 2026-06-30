// FUNC_NAME: GodfatherGameManager::getNextId
unsigned int __thiscall GodfatherGameManager::getNextId() {
    // Offset +0x6038: next unique identifier counter (ensures non-zero)
    int* idCounter = reinterpret_cast<int*>(this + 0x6038);
    *idCounter = *idCounter + 1;
    // Wrap-around: skip zero to avoid sentinel value conflicts
    if (*idCounter == 0) {
        *idCounter = 1;
    }
    return static_cast<unsigned int>(*idCounter);
}