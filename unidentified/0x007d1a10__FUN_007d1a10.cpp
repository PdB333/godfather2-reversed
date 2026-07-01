// FUNC_NAME: SomeEARSObject::destructor
void __fastcall SomeEARSObject::destructor(undefined4 *this)
{
  int *piVar1;
  
  *this = &PTR_LAB_00d6edcc;
  piVar1 = (int *)FUN_007ab130();
  (**(code **)(*piVar1 + 4))(this[0x1d]); // vtable call on member at +0x74
  piVar1 = (int *)FUN_007ab140();
  (**(code **)(*piVar1 + 4))(this[0x1e]); // vtable call on member at +0x78
  *(uint *)(this[0x16] + 0x24a0) = *(uint *)(this[0x16] + 0x24a0) & 0xfbffffff; // clear bit 25 at +0x24a0
  *(uint *)(this[0x16] + 0x24a0) = *(uint *)(this[0x16] + 0x24a0) & 0xf7ffffff; // clear bit 27 at +0x24a0
  *this = &PTR_LAB_00d6b95c;
  FUN_0080ea60(); // likely some cleanup function
  return;
}