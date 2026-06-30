// FUNC_NAME: SomeClass::allocateAndCopyTriple
void __thiscall allocateAndCopyTriple(undefined4 *this, undefined4 *param_2)
{
  undefined4 *buffer;
  undefined4 unaff_retaddr;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  buffer = (undefined4 *)this[1]; // +0x04: pointer to existing buffer or null
  if ((undefined1 *)this[1] == (undefined1 *)0x0) {
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    buffer = &local_c; // Use stack as fallback if no existing buffer
  }
  // Call virtual function at vtable[0] to allocate 0xC bytes
  buffer = (undefined4 *)(*(code *)**(undefined4 **)*this)(0xc, buffer);
  if (buffer != (undefined4 *)0x0) {
    *buffer = local_4; // Copy first value
  }
  if (buffer + 1 != (undefined4 *)0x0) {
    buffer[1] = unaff_retaddr; // Copy second value (return address)
  }
  if (buffer + 2 != (undefined4 *)0x0) {
    buffer[2] = *param_2; // Copy third value from parameter
  }
  return;
}