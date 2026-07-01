// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(undefined4 *this)
{
  undefined4 *puVar1;
  
  *this = &PTR_FUN_00d6fffc;
  this[1] = &PTR_LAB_00d6ffec;
  FUN_004086d0(&DAT_0112db7c);
  FUN_00408310(&DAT_0112db7c);
  FUN_00408310(&DAT_0112bb48);
  FUN_004086d0(&DAT_012067cc);
  FUN_007ed070(0,0,0);
  puVar1 = (undefined4 *)this[6]; // +0x18 - some manager object
  if (puVar1 != (undefined4 *)0x0) {
    FUN_007ecdd0();
    (**(code **)(*(int *)*puVar1 + 4))(puVar1[6],0x24); // delete with size 0x24
    puVar1[6] = 0;
    FUN_007ed520();
    FUN_009c8eb0(puVar1);
  }
  (**(code **)(*(int *)this[7] + 0xc))(); // +0x1C - another manager, call vtable+0xC
  this[7] = 0;
  FUN_009c8f10(this[4]); // +0x10 - free memory
  FUN_004083d0();
  *this = &PTR_LAB_00d6ffb0;
  DAT_0112a55c = 0;
  return;
}