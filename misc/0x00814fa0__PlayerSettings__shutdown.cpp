// FUNC_NAME: PlayerSettings::shutdown
void __fastcall PlayerSettings::shutdown(undefined4 *this)
{
  int iVar1;
  
  iVar1 = this[7];  // +0x1C - some pointer member
  *this = &PTR_FUN_00d73134;  // reset vtable
  this[3] = &PTR_LAB_00d73130;  // +0x0C - secondary vtable or state pointer
  if (iVar1 != 0) {
    FUN_00816660();  // likely free/delete
    FUN_009c8eb0(iVar1);  // likely destructor
  }
  iVar1 = this[8];  // +0x20 - another pointer member
  if (iVar1 != 0) {
    FUN_00816660();  // free
    FUN_009c8eb0(iVar1);  // destructor
  }
  FUN_004086d0(&DAT_01206978);  // release some resource
  FUN_004086d0(&DAT_012069c4);  // release another resource
  this[3] = &PTR_LAB_00d7312c;  // update state pointer to shutdown state
  DAT_011298d4 = 0;  // clear global flag
  FUN_004083d0();  // final cleanup
  return;
}