// FUNC_NAME: StreamWriter::writeTypedEvent
void __thiscall StreamWriter::writeTypedEvent(uint32_t param0, uint32_t param1, uint32_t param2, uint16_t param3, uint16_t param4)
{
    // Get pointer to internal buffer structure from "this" (offset 0 contains pointer to buffer)
    BufferState* buffer = reinterpret_cast<BufferState*>(this->bufferPtr);
    
    // Write a type marker (pointer to a static vtable/type info table)
    *reinterpret_cast<uint32_t*>(buffer->writeCursor) = &PTR_LAB_0110b668;  // +0x14 is writeCursor
    buffer->writeCursor += sizeof(uint32_t);
    
    // Write three 4-byte payload values
    *reinterpret_cast<uint32_t*>(buffer->writeCursor) = param0;
    buffer->writeCursor += sizeof(uint32_t);
    
    *reinterpret_cast<uint32_t*>(buffer->writeCursor) = param1;
    buffer->writeCursor += sizeof(uint32_t);
    
    *reinterpret_cast<uint32_t*>(buffer->writeCursor) = param2;
    buffer->writeCursor += sizeof(uint32_t);
    
    // Write first 16-bit value with alignment to next 4-byte boundary
    *reinterpret_cast<uint16_t*>(buffer->writeCursor) = static_cast<uint16_t>(param3);
    buffer->writeCursor = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(buffer->writeCursor) + 5) & ~3);
    
    // Write second 16-bit value also with alignment (ensures both are 4-byte aligned independently)
    *reinterpret_cast<uint16_t*>(buffer->writeCursor) = static_cast<uint16_t>(param4);
    buffer->writeCursor = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(buffer->writeCursor) + 5) & ~3);
}