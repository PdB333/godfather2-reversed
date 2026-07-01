// FUNC_NAME: RefCountedObject::controlReference
void __thiscall RefCountedObject::controlReference(void* this, bool addRef)
{
  // Structure offsets:
  // +0x5c: flags (uint32)
  // +0x5e: autoDelete flag (byte)
  // +0x70: refCount (int32)

  int* refCount = (int*)((char*)this + 0x70);

  if (!addRef) {
    // Release/reference decrement
    *refCount = *refCount - 1;
    if (*refCount == 0) {
      // Release the static shared resource (e.g., sound bank or stream)
      staticResourceRelease(&DAT_012069c4); // FUN_004086d0
      if ((*(byte*)((char*)this + 0x5e) & 1) != 0) { // autoDelete flag check
        // Clear bit 17 of flags (0x10000) – possibly "pendingDelete" or "alive"
        *(uint32*)((char*)this + 0x5c) = *(uint32*)((char*)this + 0x5c) & 0xfffeffff;
        // Trigger cleanup/destruction
        onLastRelease(this); // FUN_00792200
      }
    }
  } else {
    // Add reference
    *refCount = *refCount + 1;
    if (*refCount == 1) {
      // Acquire the static shared resource for the first reference
      staticResourceAddRef(&DAT_012069c4); // FUN_00408680
      // Clear bit 17 of flags – object is now referenced, no pending delete
      *(uint32*)((char*)this + 0x5c) = *(uint32*)((char*)this + 0x5c) & 0xfffeffff;
      return;
    }
  }
}