// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(undefined4 *this)
{
  int iVar1;
  
  *this = &PTR_LAB_00d79828;
  this[1] = &PTR_LAB_00d79824;
  this[0xd8] = &PTR_LAB_00d79814;
  FUN_004086d0(&DAT_0112ee84);
  FUN_00408310(&DAT_0112ee84);
  FUN_004086d0(&DAT_0112ee7c);
  FUN_00408310(&DAT_0112ee7c);
  FUN_004086d0(&DAT_01206a20);
  if (DAT_0112b9b4 != (undefined4 *)0x0) {
    (**(code **)*DAT_0112b9b4)(1);
  }
  FUN_008a4dc0();
  FUN_009c8f10(this[0xf4]); // +0x3D0 - some resource/object
  iVar1 = this[0xef]; // +0x3BC - another object pointer
  if (iVar1 != 0) {
    FUN_009c8f10(*(undefined4 *)(iVar1 + 8)); // release child at +0x08
    FUN_009c8eb0(iVar1); // delete/release the object
  }
  if (this[0xe1] != 0) { // +0x384 - callback/function pointer
    (*(code *)this[0xe4])(this[0xe1]); // call with argument at +0x388
  }
  FUN_004bf030(); // final cleanup
  return;
}