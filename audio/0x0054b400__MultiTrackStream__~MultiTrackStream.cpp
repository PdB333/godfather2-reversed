// FUNC_NAME: MultiTrackStream::~MultiTrackStream
// Address: 0x0054b400
// Role: Destructor for a streaming audio/video object with thread-local memory management.
// Releases associated stream data if a valid index (held at +0x18) exists, then sets vtable to purecall.
// The class appears to use a 96-byte (0x60) slot system indexed by the stream handle.

#define TLS_STREAM_MANAGER_SLOT 0x01139810 // DAT_01139810 (TLS index)

MultiTrackStream * __thiscall MultiTrackStream::~MultiTrackStream(MultiTrackStream *this, byte deletingFlag)
{
  uint streamIndex;
  
  // Set vtable to base class (likely MultiTrackStream base)
  this->vtable = &PTR_FUN_00e39c48;
  
  streamIndex = this->m_streamIndex; // +0x18: stream handle/index
  if ((int)streamIndex >= 0) {
    // Thread-local storage: get the stream memory manager
    void *tlsValue = TlsGetValue(TLS_STREAM_MANAGER_SLOT);
    // Release the stream data block: pointer at +0x10, size = (streamIndex & 0x3FFFFFFF) * 0x60, flag 0x17
    deallocateStreamData(this->m_streamData, (streamIndex & 0x3FFFFFFF) * 0x60, 0x17);
  }
  
  // Finalize: set vtable to purecall marker to prevent further virtual calls
  this->vtable = &PTR___purecall_00dcfcf4;
  
  // If caller requested deletion (bit 0 set), free the object memory
  if ((deletingFlag & 1) != 0) {
    operatorDelete(this);
  }
  
  return this;
}