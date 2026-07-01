// FUNC_NAME: Presentation::Initialize
void __fastcall Presentation::Initialize(undefined4 *this)

{
  *this = &PTR_FUN_00d87b98;        // Set vtable pointer (likely Presentation vtable +0x00)
  this[4] = &PTR_LAB_00d87b70;      // Set resource manager or similar pointer at +0x10
  this[0x13] = &PTR_LAB_00d87b6c;   // Set a state or method pointer at +0x4C
  FUN_009c8f10(this[0x1b]);         // Release or cleanup resource at +0x6C
  FUN_009c8f10(this[0x1a]);         // Release or cleanup resource at +0x68
  this[0x13] = &PTR_LAB_00d87b68;   // Update state/method pointer at +0x4C to a different value
  DAT_0112a87c = 0;                 // Reset global flag (likely system initialized flag)
  FUN_005c16e0();                   // Perform additional initialization routine
  return;
}