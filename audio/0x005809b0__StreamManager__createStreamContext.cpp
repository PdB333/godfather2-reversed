// FUNC_NAME: StreamManager::createStreamContext
void StreamManager::createStreamContext(uint streamId)
{
  // Allocate stream context structure (0x14 = 20 bytes)
  StreamContext *context = (StreamContext *)operator new(0x14);
  if (context != (StreamContext *)0x0) {
    context->manager = this;              // +0x00
    context->streamId = streamId;         // +0x10
    // Stream descriptor: type=2 (e.g., kStreamTypeAudio), buffer size=0x10, flags=0
    StreamDescriptor desc;
    desc.type = 2;
    desc.bufferSize = 0x10;
    desc.flags = 0;
    // Virtual call: vtable[0] – opens or registers the stream
    uint handle = this->vtable->openStream(streamId, &desc);
    context->handle1 = handle;            // +0x08
    context->handle2 = handle;            // +0x0C
    context->counter = 0;                 // +0x04
    g_pStreamContext = context;
    return;
  }
  g_pStreamContext = (StreamContext *)0x0;
  return;
}