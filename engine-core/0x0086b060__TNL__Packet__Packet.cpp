// FUNC_NAME: TNL::Packet::Packet
undefined4 * __thiscall TNL::Packet::Packet(undefined4 *this, int handle, int size) {
  int *piVar1;
  undefined4 uVar2;
  int field48;
  
  TNL::Packet::baseConstructor(handle, size);  // Calls base class constructor (FUN_004ac120)
  *this = &TNL_Packet_vtable;                  // Set vtable pointer (PTR_LAB_00d75d0c)
  this[0x14] = 0;                              // offset 0x50: stream object pointer
  this[0x16] = 0;                              // offset 0x58: unused?
  if (this[0x12] != 0) {                       // offset 0x48: previous data pointer
    field48 = this[0x12] - 0x48;                // offset adjustment (data - 0x48 => buffer start)
    this[0x17] = field48;                       // offset 0x5C: adjusted pointer
  }
  piVar1 = (int *)FUN_00542d70();              // Create internal stream object (e.g., new BitStream)
  this[0x14] = piVar1;                         // store at offset 0x50
  uVar2 = (**(code **)(*piVar1 + 0x30))(piVar1); // Call virtual function index 12 (e.g., getSize)
  this[0x15] = uVar2;                          // offset 0x54: store result (e.g., stream length)
  return this;
}