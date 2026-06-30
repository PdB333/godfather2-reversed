// FUNC_NAME: StringBuffer::init
void __thiscall StringBuffer::init(StringBuffer *this, char *buffer)
{
  char cVar1;
  char *pcVar2;
  
  // +0x00: start pointer
  // +0x04: current write position
  // +0x08: end pointer (one past last valid write)
  // +0x0C: capacity (calculated from strlen)
  // +0x10: current length
  // +0x14: max length (same as capacity initially)
  // +0x18: buffer pointer (same as input)
  // +0x1C: reserved
  // +0x20: read position
  // +0x24: remaining bytes to read
  
  this->start = buffer;
  this->writePos = buffer;
  this->end = buffer;
  this->capacity = 0;
  
  // Calculate string length
  pcVar2 = buffer;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  
  // Set capacity to string length (excluding null terminator)
  this->capacity = (int)pcVar2 - (int)(buffer + 1);
  this->length = (int)pcVar2 - (int)(buffer + 1);
  this->buffer = buffer;
  this->reserved = 0;
  
  // Calculate max length (including null terminator)
  pcVar2 = buffer + 1;
  do {
    cVar1 = *buffer;
    buffer = buffer + 1;
  } while (cVar1 != '\0');
  
  this->maxLength = (int)buffer - (int)pcVar2;
  this->remaining = (int)buffer - (int)pcVar2;
  
  return;
}