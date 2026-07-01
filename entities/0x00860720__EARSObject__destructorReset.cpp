// FUNC_NAME: EARSObject::destructorReset
void __fastcall EARSObject::destructorReset(int *this) // 0x00860720
{
  if (*this != 0) { // Check if object pointer is non-null (+0x00)
    FUN_004daf90(this); // Likely calls virtual destructor or cleanup
    *this = 0; // Null out the object pointer (+0x00)
  }
  this[2] = 0; // Reset another field at offset +0x08
}