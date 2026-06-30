// FUNC_NAME: HashState::updateChecksum
void __thiscall HashState::updateChecksum(void) {
    uint64_t uVar2;
    uint32_t uVar1;
    uint64_t uVar3;

    // Compute hash with complemented inputs
    uVar2 = hashUpdate(this, ~m_inputA, ~m_inputB);
    uVar1 = (uint32_t)uVar2;

    // Accumulate lower and upper 32 bits
    m_hashLow |= uVar1;
    m_hashHigh |= (uint32_t)(uVar2 >> 32);

    // Notify via virtual method with magic constants
    (this->vtable[0x44 / 4])(0xC9A8803, m_hashLow ^ uVar1);
    (this->vtable[0x44 / 4])(0x76F7F2FB, uVar1);

    uVar3 = 0;
    // If bit 4 of flags is clear, also compute hash with normal inputs
    if ((m_flags & 0x10) == 0) {
        uVar3 = hashUpdate(this, m_inputA, m_inputB);
    }

    // Finalize combined hash
    finalizeHash(uVar3 | uVar2);
}