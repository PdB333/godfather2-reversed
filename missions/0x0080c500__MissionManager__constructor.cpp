// FUNC_NAME: MissionManager::constructor
void __fastcall MissionManager::constructor(undefined4 *this)

{
  undefined4 *pVar1;
  char cVar2;
  
  pVar1 = this + 0x19;  // +0x64 - some member field
  *this = &PTR_FUN_00d725b0;  // vtable pointer
  this[0xf] = &PTR_LAB_00d725a0;  // +0x3C - secondary vtable or function pointer
  this[0x12] = &PTR_LAB_00d7259c;  // +0x48 - another function pointer
  cVar2 = FUN_00402080(pVar1);  // initialize member at +0x64
  if (cVar2 != '\0') {
    FUN_004086d0(pVar1);  // cleanup or additional init if needed
  }
  FUN_00408310(pVar1);  // initialize member at +0x64
  FUN_00408310(this + 0x1b);  // initialize member at +0x6C
  FUN_00408310(this + 0x1d);  // initialize member at +0x74
  FUN_0046c640();  // global initialization or singleton access
  return;
}