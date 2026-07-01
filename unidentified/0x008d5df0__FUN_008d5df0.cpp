// FUNC_NAME: SomeClass::initializeDefaults
void __fastcall SomeClass::initializeDefaults(undefined4 *this)
{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar2 = _DAT_00d5c458; // +0x8: some global default value
  this[1] = 0;           // +0x4: field1 = 0
  this[3] = 0;           // +0xC: field3 = 0
  uVar1 = _DAT_00d5780c; // +0x10: another global default value
  *this = 0;             // +0x0: field0 = 0
  this[2] = uVar2;       // +0x8: field2 = global default
  this[4] = uVar1;       // +0x10: field4 = global default
  return;
}