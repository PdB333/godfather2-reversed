// FUNC_NAME: GameDataManager::initializeBuffer
undefined4 * __thiscall GameDataManager::initializeBuffer(undefined4 *this, undefined4 param_2)
{
  // Initialize memory buffer of 0x4000 bytes (16KB) for param_2?
  FUN_0046e6b0(param_2, 0x4000);

  // Set main vtable pointer (class vtable at 0x00d5e880)
  this[0] = &PTR_FUN_00d5e880;

  // Set additional function table pointers (likely virtual tables for multiple bases or subcomponents)
  // Offsets: +0x3C, +0x48, +0x50, +0x54, +0x58
  this[0xf] = &PTR_LAB_00d5e870;   // +0x3C
  this[0x12] = &PTR_LAB_00d5e86c;  // +0x48
  this[0x14] = &PTR_LAB_00d5e868;  // +0x50
  this[0x15] = &PTR_LAB_00d5e808;  // +0x54
  this[0x16] = &PTR_LAB_00d5e7a0;  // +0x58

  // Zero out integer fields at offsets +0x180, +0x184, +0x188
  this[0x60] = 0;
  this[0x61] = 0;
  this[0x62] = 0;

  // Zero out 16-bit fields at offsets +0x18C and +0x18E
  *(short *)(this + 99) = 0;          // +0x18C
  *(short *)((byte *)this + 0x18e) = 0; // +0x18E

  // If global data pointer is non-null, copy a large block (0x8000 bytes = 32KB) into subcomponent at +0x3C
  if (DAT_0120e93c != 0) {
    FUN_00408900(this + 0xf, &DAT_0120e93c, 0x8000); // copy from global to offset +0x3C
  }

  return this;
}