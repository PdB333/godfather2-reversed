// FUNC_NAME: EARSAllocator::constructor
undefined4 * __fastcall EARSAllocator::constructor(undefined4 *this)

{
  undefined4 uVar1;
  
  *this = &PTR_FUN_00d73840;  // vtable pointer
  this[1] = 0;                // +0x04: allocated count
  uVar1 = FUN_009c8e80(0x40); // allocate 0x40 bytes (likely memory pool or buffer)
  this[2] = uVar1;            // +0x08: pointer to allocated memory
  this[3] = 0;                // +0x0C: some counter or flag
  this[4] = 0x10;             // +0x10: initial capacity (16 items)
  return this;
}