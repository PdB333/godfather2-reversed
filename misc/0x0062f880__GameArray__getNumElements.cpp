// FUNC_NAME: GameArray::getNumElements
void GameArray::getNumElements(void) {
    // Offsets relative to this pointer:
    // +8: m_pEnd (pointer to one past the last element)
    // +0xC: m_pStart (pointer to first element)
    // Each element is 8 bytes
    int numElements = (*(int *)((int)this + 8) - *(int *)((int)this + 0xC)) >> 3;
    debugOutputCount(numElements);
}