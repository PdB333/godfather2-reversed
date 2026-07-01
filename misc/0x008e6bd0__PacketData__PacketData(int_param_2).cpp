// FUNC_NAME: PacketData::PacketData(int param_2)
undefined4 * __thiscall PacketData::PacketData(PacketData *this, int param_2)
{
  // Call base constructor or initialization routine
  FUN_0046c590(param_2);

  // Set vtable pointer
  this->vtable = &PTR_FUN_00d80554;

  // Set function pointers / vtable extensions at known offsets
  this->somePointer1 = &PTR_LAB_00d80544;  // +0x3C
  this->somePointer2 = &PTR_LAB_00d80540;  // +0x48

  // Zero out counters / flags
  this->someCount = 0;                      // +0x50
  *(short *)((char *)this + 0x54) = 0;     // +0x54 (word)
  *(short *)((char *)this + 0x56) = 0;     // +0x56 (word)

  // Initialize debug sentinel array (12 ints) with alternating magic values
  // These are typical EA debug markers for uninitialized memory detection
  this->magicArray[0]  = 0xbadbadba;       // +0x58
  this->magicArray[1]  = 0xbeefbeef;       // +0x5C
  this->magicArray[2]  = 0xeac15a55;       // +0x60
  this->magicArray[3]  = 0x91100911;       // +0x64
  this->magicArray[4]  = 0xbadbadba;       // +0x68
  this->magicArray[5]  = 0xbeefbeef;       // +0x6C
  this->magicArray[6]  = 0xeac15a55;       // +0x70
  this->magicArray[7]  = 0x91100911;       // +0x74
  this->magicArray[8]  = 0xbadbadba;       // +0x78
  this->magicArray[9]  = 0xbeefbeef;       // +0x7C
  this->magicArray[10] = 0xeac15a55;       // +0x80
  this->magicArray[11] = 0x91100911;       // +0x84

  // Additional trailing field set to zero
  this->trailingZero = 0;                  // +0x88

  return this;
}