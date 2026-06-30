// FUNC_NAME: NetObject::~NetObject
void __thiscall NetObject::~NetObject()
{
    // +0x70: pointer to a packet buffer (m_pPacketBuffer)
    int* pPacketBuffer = *(int**)(this + 0x70);
    if (pPacketBuffer && pPacketBuffer != (int*)0x48) {
        // +0x5c: pointer to a packet manager object (m_pPacketManager)
        void* pPacketManager = *(void**)(this + 0x5c);
        // Check if this object belongs to the global packet manager
        if (pPacketManager == getPacketManager()) {
            // Check manager status: bit 25 of field at offset 0x1f58 (2006 ints) must be 0
            if (((*(int*)((int)pPacketManager + 0x1f58) >> 25) & 1) == 0) {
                // Determine the handle: if buffer is a valid pointer, subtract 0x48 header
                int handle = (pPacketBuffer == 0) ? 0 : ((int)pPacketBuffer - 0x48);
                // Call virtual function at index 150 on the manager to release the buffer
                (*(void (__thiscall**)(int))(*(int*)pPacketManager + 600))(handle);
            }
        }
    }
    // Free the packet buffer itself
    if (pPacketBuffer) {
        operator_delete(pPacketBuffer);
    }
    // Switch vtable to the base class's vtable
    *(int**)this = (int**)&VTABLE_BASE_CLASS;
    // +0x68: another heap-allocated buffer (m_pOtherBuffer)
    if (*(void**)(this + 0x68)) {
        operator_delete(*(void**)(this + 0x68));
    }
    // Finalize the object (e.g., remove from global lists)
    shutdown();
}