// FUNC_NAME: FixedBlockAllocator::releaseBlock
void __thiscall FixedBlockAllocator::releaseBlock(void *thisPtr)
{
  int slotIndex = *(int *)((char *)thisPtr + 8); // +0x8: index of slot to release
  if (slotIndex >= 0)
  {
    // Get thread-local heap pointer (TLS index stored in global)
    void *tlsHeap = TlsGetValue(DAT_01139810);
    // Free block: base address + slotIndex * 16 (block size), with debug tag 0x17
    FUN_00aa26e0(*(void **)thisPtr, slotIndex << 4, 0x17);
  }
}