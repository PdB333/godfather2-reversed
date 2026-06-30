// FUNC_NAME: SomeClass::getSomeValueOrCallVirtual
undefined4 SomeClass::getSomeValueOrCallVirtual(void)
{
  // in_EAX points to this object
  // +0x00: vtable pointer
  // +0x14: some value (offset 0x14)
  // +0x1C: some byte flag (offset 0x1C, byte at this+0x1C)
  
  if (*(char *)(this + 0x1C) != '\0') {
    // If flag is set, call virtual function at vtable offset 0x34
    // This likely returns some value via the local buffer
    (**(code **)(*(int *)this + 0x34))((int *)this, local_1c);
    return uStack_14; // Return value from the virtual call
  }
  // Otherwise return the value at offset 0x14
  return *(this + 0x14);
}