// FUNC_NAME: PacketStream::advanceWriteSlot
// Function at 0x00605c70: Advances the write pointer for the packet stream buffer.
class PacketStream {
    // +0x0c: Buffer state flag (non-null when additional validation is needed)
    void* m_bufferState;
    // +0x10: Element count per slot (each element is 4 bytes)
    int m_elementsPerSlot;
    // +0x14: Maximum valid slot index
    uint m_maxSlotIndex;
    // +0x18: Base address of the write buffer
    int* m_bufferBase;
    // +0x1c: Current write pointer (updated after advancement)
    int* m_writePointer;

    // Internal: checks if the write condition passes (returns 0 if okay)
    char checkWriteCondition();

    // Internal: resets the write pointer or handles overflow (takes slot index by reference)
    void handleWriteOverflow(uint* slotIndex);

public:
    // Advances the write pointer to the given slot index.
    // param_1: slotIndex - target slot number
    // param_2: flags - if non-zero and buffer state is valid, perform additional checks
    void advanceWriteSlot(uint slotIndex, int flags) {
        uint uVar2 = slotIndex;
        if ((flags != 0) && (m_bufferState != 0)) {
            char cVar1 = checkWriteCondition();
            if (cVar1 == '\0') {
                handleWriteOverflow(&slotIndex);
                uVar2 = slotIndex;
            }
        }
        if (uVar2 < m_maxSlotIndex) {
            m_writePointer = m_bufferBase + (uVar2 + 1) * m_elementsPerSlot * 4;
        }
    }
};