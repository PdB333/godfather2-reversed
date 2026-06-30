// FUNC_NAME: ThreadLocalPool::releaseEntry
void __thiscall ThreadLocalPool::releaseEntry(ThreadLocalPool *this)
{
  int entryIndex;
  
  entryIndex = this->entryIndex; // +0x08
  if (entryIndex >= 0) {
    // Get thread-local storage for the pool manager (global TLS index stored at 0x01139810)
    TlsGetValue(DAT_01139810);
    // Perform deallocation: baseAddress + (entryIndex * 16), size = 0x17 (23)
    poolDeallocate(this->baseAddress, entryIndex << 4, 0x17); // +0x00 is baseAddress
  }
}