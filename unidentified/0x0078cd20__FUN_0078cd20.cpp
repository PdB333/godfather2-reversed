//FUNC_NAME: SomeClass::SomeClass
void __fastcall SomeClass::SomeClass(SomeClass *this)
{
  // Set vtable pointer for this class (offset 0x00)
  *(void **)this = &PTR_FUN_00d69b04;
  // Set vtable pointer for first base class/interface at offset 0x3C (0xF * 4)
  *(void **)((char *)this + 0x3C) = &PTR_LAB_00d69af4;
  // Set vtable pointer for second base class/interface at offset 0x48 (0x12 * 4)
  *(void **)((char *)this + 0x48) = &PTR_LAB_00d69af0;
  // Initialize subobject at offset 0x50 (0x14 * 4) – likely a base class constructor
  FUN_004086d0((int *)this + 0x14);
  // Call global initialization function (e.g., register class, allocate resources)
  FUN_0046c640();
}