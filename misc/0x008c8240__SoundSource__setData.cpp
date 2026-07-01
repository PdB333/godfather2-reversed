// FUNC_NAME: SoundSource::setData
void SoundSource::setData(SoundSource* source) {
    // Copy core fields from source
    m_id = source->m_id;           // +0x04 = source->+0x10
    m_field14 = source->m_field14; // +0x14 = source->+0x14
    m_refCountId = source->m_refCountId; // +0x18 = source->+0x18

    // Increment reference count on the shared data
    AddRef(m_refCountId); // FUN_00790d30

    // If the sound is attached to an owner, check if the owner's current ID matches the new reference ID
    if (m_owner != nullptr) { // +0x10
        if (m_owner->m_currentId == m_refCountId) { // owner+0x58
            OnOwnerMatch(); // FUN_008feb40
        } else {
            OnOwnerMismatch(); // FUN_008febb0
        }
    }

    // Update flags from source (masked after shifting)
    SetFlags((source->m_flags >> 1) & 0xffffff01); // FUN_00791a70

    // Final update if owner exists
    if (m_owner != nullptr) {
        UpdateOwnerState(); // FUN_008feab0
    }
}