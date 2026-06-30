// FUNC_NAME: SomeClass::constructor
void SomeClass::constructor(void)
{
  undefined4 *this; // unaff_ESI
  undefined4 local_8;
  undefined4 local_4;
  
  // Call a helper function that likely initializes two 32-bit values (e.g., a GUID or pair of pointers)
  FUN_0064b9e0(0x40, &local_8);
  
  // Store the two values into the object's first two fields (offset +0x00 and +0x04)
  this[0] = local_8;
  this[1] = local_4;
  
  return;
}