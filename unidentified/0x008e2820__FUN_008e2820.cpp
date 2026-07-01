// FUNC_NAME: UnknownClass::releasePointers
// Function address: 0x008e2820
// Role: Release two child objects stored at offsets +0x44 and +0x3c.
void UnknownClass::releasePointers() {
    // offset +0x44: second pointer field
    if (this->m_pField2 != 0) {
        safeReleasePointer(&m_pField2); // FUN_004daf90
    }
    // offset +0x3c: first pointer field
    if (this->m_pField1 != 0) {
        safeReleasePointer(&m_pField1);
    }
}