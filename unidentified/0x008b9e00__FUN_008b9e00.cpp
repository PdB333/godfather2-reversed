// FUNC_NAME: someObject::decrementReferenceCount
bool __fastcall someObject::decrementReferenceCount(int this)
{
  int *refCount = (int *)(this + 0x20c);
  *refCount = *refCount - 1;
  if (*refCount == 0) {
    *(unsigned int *)(this + 0x18c) = *(unsigned int *)(this + 0x18c) | 0x10000; // mark for deletion or cleanup
  }
  return *refCount != 0;
}