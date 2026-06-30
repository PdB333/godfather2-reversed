// FUNC_NAME: EARS::Buffer::detach
void Buffer::detach()
{
  // +0x0C: pointer to data buffer
  // +0x10: size of allocated data
  // +0x14: boolean flag indicating whether this object owns the data (1 = owned, 0 = shared)
  if (*(char *)(this + 0x14) == '\0') {
    void *newBuffer = malloc(*(size_t *)(this + 0x10));
    memcpy(newBuffer, *(void **)(this + 0x0C), *(size_t *)(this + 0x10));
    *(void **)(this + 0x0C) = newBuffer;
    *(char *)(this + 0x14) = 1;
  }
}