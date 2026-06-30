// FUNC_NAME: ResourcePool::consume
void __thiscall ResourcePool::consume(uint requestedAmount) {
    uint available = *(uint *)(this + 0x6c); // m_currentCount at +0x6c

    if (available < requestedAmount) {
        requestedAmount = available; // Clamp to what's available
    }

    *(uint *)(this + 0x6c) = available - requestedAmount; // Decrement count

    FUN_006b2f70(); // may be onCountChanged callback or update
    return;
}