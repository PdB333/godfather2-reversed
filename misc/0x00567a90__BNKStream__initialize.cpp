// FUNC_NAME: BNKStream::initialize
void __thiscall BNKStream::initialize(BNKStream *this)
{
  int size;
  void *buffer;

  // Reset buffer initialized flag
  this->flag_0x20 = 0;
  
  // Get size from source object (offset +0x24 points to a source/virtual object)
  size = this->m_pSource->vtable->getSize(this->m_pSource);
  
  if (size > 0) {
    // Allocate buffer from source (argument 0 indicates allocation mode)
    buffer = this->m_pSource->vtable->getBuffer(this->m_pSource, 0);
    this->m_pBuffer = buffer;
    
    // Mark buffer as initialized
    this->flag_0x20 = 1;
    
    // Decode/read into the buffer (vtable offset 0x30) - typical decode call
    buffer->vtable->decode(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFFFFFF, 0);
  }
}