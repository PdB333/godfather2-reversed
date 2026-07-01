// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(GodfatherGameManager *this)
{
  int iVar1;
  
  iVar1 = this[0x16];
  this->vtable = &PTR_LAB_00d6e6c8;
  FUN_007f6420(0x21);
  *(uint *)(iVar1 + 0x249c) = *(uint *)(iVar1 + 0x249c) & 0xfffffbff;
  iVar1 = FUN_007ab710();
  if (iVar1 != 0) {
    FUN_007fb9b0(6,_DAT_00d6e6a4);
  }
  FUN_007ab120();
  FUN_00896db0(0x1ff);
  FUN_00896e10(this[0x27]);
  FUN_00897830(0x100);
  this->vtable = &PTR_LAB_00d6b95c;
  FUN_0080ea60();
  return;
}