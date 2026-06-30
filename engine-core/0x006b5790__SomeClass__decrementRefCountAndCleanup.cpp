// FUNC_NAME: SomeClass::decrementRefCountAndCleanup
// Function address: 0x006b5790
// Decrements reference count (offset +0x78). When it reaches zero, destroys all children indexed by count at +0xac.
void __thiscall SomeClass::decrementRefCountAndCleanup()
{
  int *refCount = reinterpret_cast<int *>(reinterpret_cast<uintptr_t>(this) + 0x78);
  *refCount -= 1;
  
  if (*refCount == 0) {
    int childCount = *reinterpret_cast<int *>(reinterpret_cast<uintptr_t>(this) + 0xac);
    // Destroy each child in reverse order (index from childCount-1 down to 0)
    for (int i = childCount - 1; i >= 0; --i) {
      // FUN_006b56a0 is likely a destructor for child objects
      FUN_006b56a0(i);
    }
  }
}