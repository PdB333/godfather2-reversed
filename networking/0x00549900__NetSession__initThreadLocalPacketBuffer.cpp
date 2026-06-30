// FUNC_NAME: NetSession::initThreadLocalPacketBuffer
void NetSession::initThreadLocalPacketBuffer()
{
  // Base class initialization (likely pure virtual or common setup)
  initBase();
  
  // Set this object's vtable to the derived class vtable
  this->vtable = &g_vtable_NetSession_00e39ba8; // +0x00
  
  // Retrieve the thread-local storage value (associated with a TLS index)
  // The return value is not used; may have side effects or be a debug assert
  TlsGetValue(g_tlsIndex_01139810);
  
  // Allocate a packet buffer header (28 bytes) with flags 0x0b
  PacketBufferHeader* header = (PacketBufferHeader*) allocateMemory(0x1c, 0x0b);
  
  // Initialize the allocated header structure
  header->vtable  = &g_vtable_PacketBufferHeader_00e39b98; // +0x00: vtable pointer
  header->size    = 0x1c;  // +0x04: size of this header (28 bytes) – stored as short
  header->version = 1;     // +0x06: version/type field – stored as short
  header->field20 = 0;     // +0x14 (puVar1[5]): unknown, zeroed
  header->field24 = 0;     // +0x18 (puVar1[6]): unknown, zeroed
  
  // Store the header pointer in this object at offset 24 (ESI[6])
  this->packetBufferHeader = header; // +0x18
}