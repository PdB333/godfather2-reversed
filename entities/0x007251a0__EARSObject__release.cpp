// FUNC_NAME: EARSObject::release
void __thiscall EARSObject::release(int this, bool fullDestroy)
{
  void *pData;
  int *tempPtr;

  if (fullDestroy) {
    // Call virtual release on child object at offset +0x128 (param_1[0x4a])
    (**(code **)(*(int *)this[0x4a] + 0xc))();
    // Call virtual function at vtable+0x20 on this (likely base class cleanup)
    (**(code **)(*this + 0x20))();
    pData = (void *)this[0x35]; // +0xD4 - pointer to some allocated data
    tempPtr = (int *)pData;
  }
  else {
    pData = (void *)this[0x37]; // +0xDC - pointer to other data
    tempPtr = (int *)pData;
  }

  if (pData != (void *)0x0) {
    FUN_00408a00(&pData, 0); // Free memory (delete or release)
    tempPtr = (int *)pData;
  }

  if ((*(byte *)(this + 0x48) & 1) == 0) { // Check flag at +0x120 (bit 0)
    FUN_004088c0(this + 0xf); // Call destructor on member at +0x3C
    return;
  }

  this[0x3a] = this[0x3a] & 0xfffffffc; // Clear lower 2 bits of flags at +0xE8
}