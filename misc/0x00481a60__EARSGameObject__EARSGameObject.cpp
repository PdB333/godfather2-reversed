// FUNC_NAME: EARSGameObject::EARSGameObject
int __thiscall EARSGameObject::EARSGameObject(int this, byte isHeapAllocated)
{
  // Set vtable pointer at offset 0x28
  *(void***)(this + 0x28) = &PTR_LAB_00e317cc;

  // Call base class constructor (likely EARSObject or SimObject)
  EARSBaseObject::EARSBaseObject();

  // If this is a heap-allocated object (bit 0 set), perform additional post-construction
  // (e.g., register with manager or set up self-deletion)
  if ((isHeapAllocated & 1) != 0) {
    FUN_009c8eb0(this);
  }

  return this;
}