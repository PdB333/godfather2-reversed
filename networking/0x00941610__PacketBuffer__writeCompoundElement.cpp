// FUNC_NAME: PacketBuffer::writeCompoundElement
void __thiscall PacketBuffer::writeCompoundElement(uint firstValue, uint value2, uint value3, uint value4, uint value5, uint lastValue)
{
    // Stack copy of four values (total 16 bytes) for bulk write
    uint stackData[4] = { value2, value3, value4, value5 };

    // Write the first value to the buffer and advance write pointer
    *(this->m_writePos) = firstValue;
    this->m_writePos++;

    // Copy the 4 dwords (16 bytes) from the stack into the buffer
    // FUN_0049c430 is a member function that writes source data to the buffer and advances m_writePos
    this->writeData(&stackData, 0x10, 4);

    // Write the last value and advance
    *(this->m_writePos) = lastValue;
    this->m_writePos++;
}