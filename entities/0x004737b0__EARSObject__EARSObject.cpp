// FUNC_NAME: EARSObject::EARSObject
void __fastcall EARSObject::EARSObject(EARSObject *this)
{
  // call base initializer (likely zeros or sets up core fields)
  FUN_0046c490(0, 0);

  // set primary vtable pointer at offset 0x00
  this->vtable = (void *)*(&PTR_FUN_00e32af4);

  // set secondary vtable pointers at offsets 0x3c, 0x48, 0x50
  this->field_0x3c = (void *)*(&PTR_LAB_00e32b18);
  this->field_0x48 = (void *)*(&PTR_LAB_00e32b28);
  this->field_0x50 = (void *)*(&PTR_LAB_00e32b2c);

  // zero two byte-size members at offsets 0x54 and 0x55
  this->byte_0x54 = 0;
  this->byte_0x55 = 0;
}