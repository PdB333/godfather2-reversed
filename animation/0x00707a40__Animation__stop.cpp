// FUNC_NAME: Animation::stop
// Address: 0x00707a40
// Stops an active animation by releasing its data and clearing the active flag.
// Offsets: 
//   +0x254 - m_pData (pointer to animation data/resource)
//   +0x1d0 - m_flags (bitfield; bit 9 (0x200) = active flag)
void Animation::stop() {
    if (m_pData != 0) {
        releaseData(); // FUN_004df600 - release the animation data resource
        m_flags &= ~0x200; // clear the active flag (bit 9)
    }
}