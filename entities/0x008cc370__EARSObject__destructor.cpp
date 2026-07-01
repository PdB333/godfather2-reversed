// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::destructor(EARSObject *this)
{
  // +0x00: vtable pointer (set to PTR_FUN_00d7c488)
  // +0x0C: flags field (bit 3 = 0x8, bit 1 = 0x2)
  // +0x0E: some pointer (likely a child object or resource)
  // +0x2C (this+0xB): another vtable pointer (PTR_FUN_00d7c460)
  
  this->vtable = &PTR_FUN_00d7c488;
  this[0x3] = &PTR_LAB_00d7c474;
  this[0xB] = &PTR_FUN_00d7c460;
  
  // Check if bit 3 (0x8) is set in flags at +0x30 (this+0xC)
  if (((uint)this[0xC] >> 3 & 1) != 0) {
    this[0xC] = this[0xC] & 0xfffffff7;  // Clear bit 3
    FUN_004086d0(&DAT_012069f4);  // Likely some global cleanup
  }
  
  // Check if bit 1 (0x2) is set in flags and pointer at +0x38 (this+0xE) is non-null
  if ((((uint)this[0xC] >> 1 & 1) != 0) && (this[0xE] != 0)) {
    FUN_009f1b20(&this[0xB]);  // Release/destroy child object
    this[0xC] = this[0xC] & 0xfffffffd;  // Clear bit 1
  }
  
  // Set the vtable at +0x2C to purecall (making it abstract)
  this[0xB] = &PTR___purecall_00e3924c;
  
  // Call base class destructor or final cleanup
  FUN_004b6250();
}