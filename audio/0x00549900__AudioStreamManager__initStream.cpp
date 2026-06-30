// FUNC_NAME: AudioStreamManager::initStream
void AudioStreamManager::initStream()
{
  // Call base class constructor / initialization
  BaseClass::initialize();

  // Set vtable pointer for this object
  this->vtable = &g_vtable_AudioStreamManager;

  // Get thread-local storage (likely for current thread context)
  TlsGetValue(g_tlsIndexAudio);

  // Allocate a stream object (size 0x1C = 28 bytes, type 0xB)
  StreamObject* pStream = (StreamObject*)CustomAlloc(0x1C, 0xB);

  // Initialize stream object fields
  pStream->vtable = &g_vtable_StreamObject;           // +0x00
  pStream->field_0x04 = 0x1C;                          // +0x04: short (size value)
  pStream->field_0x06 = 1;                             // +0x06: short (type/value)
  pStream->field_0x14 = 0;                             // +0x14: int (offset 20)
  pStream->field_0x18 = 0;                             // +0x18: int (offset 24)

  // Store the stream object pointer at this+0x18 (offset 24 in this class)
  this->pStream = pStream;
}