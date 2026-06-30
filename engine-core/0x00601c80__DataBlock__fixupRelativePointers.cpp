// FUNC_NAME: DataBlock::fixupRelativePointers
void DataBlock::fixupRelativePointers() {
    // Convert stored relative offsets (from start of this object) to absolute pointers.
    // This is called after loading serialized data with embedded relative pointers.
    if (m_pRelativePtr0x20) {
        m_pRelativePtr0x20 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x20));
    }
    if (m_pRelativePtr0x24) {
        m_pRelativePtr0x24 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x24));
    }
    if (m_pRelativePtr0x28) {
        m_pRelativePtr0x28 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x28));
    }
    if (m_pRelativePtr0x30) {
        m_pRelativePtr0x30 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x30));
    }
    if (m_pRelativePtr0x40) {
        m_pRelativePtr0x40 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x40));
    }
    if (m_pRelativePtr0x44) {
        m_pRelativePtr0x44 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x44));
    }
    if (m_pRelativePtr0x48) {
        m_pRelativePtr0x48 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x48));
    }
    if (m_pRelativePtr0x34) {
        m_pRelativePtr0x34 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x34));
    }
    if (m_pRelativePtr0x38) {
        m_pRelativePtr0x38 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x38));
    }
    if (m_pRelativePtr0x50) {
        m_pRelativePtr0x50 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x50));
    }
    if (m_pRelativePtr0x58) {
        m_pRelativePtr0x58 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x58));
    }
    if (m_pRelativePtr0x60) {
        m_pRelativePtr0x60 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x60));
    }
    if (m_pRelativePtr0x68) {
        m_pRelativePtr0x68 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x68));
    }
    if (m_pRelativePtr0x70) {
        m_pRelativePtr0x70 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x70));
    }
    if (m_pRelativePtr0x7c) {
        m_pRelativePtr0x7c = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x7c));
    }
    if (m_pRelativePtr0x80) {
        m_pRelativePtr0x80 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x80));
    }
    if (m_pRelativePtr0x8c) {
        m_pRelativePtr0x8c = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + reinterpret_cast<uintptr_t>(m_pRelativePtr0x8c));
    }
}