// FUNC_NAME: StreamBuffer::release
void __thiscall StreamBuffer::release(void)
{
  char cleanupCtx[12];
  
  // Cleanup the currently held stream object (at +0x1c) using a helper
  StreamBuffer::prepareCleanup(cleanupCtx,this,*(uint32_t*)*(uint32_t*)(this + 0x1c),this,*(uint32_t*)(this + 0x1c));
  
  // Call virtual destructor on the object at +0x1c via its vtable (+4) with size 0x18
  (*(void (__thiscall **)(int,uint32_t))(**(uint32_t **)(this + 4) + 4))(*(int32_t *)(this + 0x1c),0x18);
  
  // Clear the stream pointers
  *(uint32_t *)(this + 0x1c) = 0;
  *(uint32_t *)(this + 0x20) = 0;
  
  // If there is an auxiliary buffer (at +0x18), release it as well
  if (*(int32_t *)(this + 0x18) != 0) {
    (*(void (__thiscall **)(int,uint32_t))(**(uint32_t **)(this + 0x14) + 4))(*(int32_t *)(this + 0x18),0);
    *(uint32_t *)(this + 0x18) = 0;
  }
  
  // Call virtual shutdown on the parent object (at +0x14)
  (*(void (__thiscall **)(void))(**(uint32_t **)(this + 0x14) + 0xc))();
  
  // Finalize cleanup
  StreamBuffer::postCleanup();
}