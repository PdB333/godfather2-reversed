// FUNC_NAME: GhostPacketWriter::writeGhostEntry
void __thiscall GhostPacketWriter::writeGhostEntry(GhostPacketWriter* this, uint32 entryType, const void* ghostData, bool isImportant)
{
    // Dereference this to get pointer to the internal buffer manager structure
    // this + 0x0: BufferManager* m_bufferMgr
    BufferManager* bufferMgr = this->m_bufferMgr;

    // bufferMgr + 0x14: current write pointer (void* m_writePos)
    // First write: vtable pointer for ghost entry objects
    *reinterpret_cast<void**>(bufferMgr->m_writePos) = &PTR_LAB_0110b67c;
    bufferMgr->m_writePos = reinterpret_cast<uint8*>(bufferMgr->m_writePos) + 4;

    // Write the entry type ID (e.g., GhostUpdateType)
    *reinterpret_cast<uint32*>(bufferMgr->m_writePos) = entryType;
    // Align to next 16-byte boundary (standard for SIMD data)
    uint8* alignedDst = reinterpret_cast<uint8*>((reinterpret_cast<uint32>(bufferMgr->m_writePos) + 0x13) & 0xfffffff0);
    bufferMgr->m_writePos = alignedDst;

    // Copy the 64-byte ghost data (typically a ghost's state struct)
    memcpy(bufferMgr->m_writePos, ghostData, 0x40);
    bufferMgr->m_writePos += 0x40;

    // Write the importance flag as a bool after the data block
    *reinterpret_cast<bool*>(bufferMgr->m_writePos) = isImportant != false;
    // Align write pointer to next 4-byte boundary (dword alignment)
    bufferMgr->m_writePos = reinterpret_cast<uint8*>((reinterpret_cast<uint32>(bufferMgr->m_writePos) + 4) & 0xfffffffc);
}