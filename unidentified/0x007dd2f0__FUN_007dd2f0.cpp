// FUNC_NAME: SomeManager::shutdown
void __fastcall SomeManager::shutdown(undefined4 *this)
{
  *this = &PTR_FUN_00d6f4f8;
  this[1] = &PTR_LAB_00d6f4e8;
  FUN_004086d0(&DAT_012069c4);
  FUN_004086d0(&DAT_012069b4);
  FUN_004086d0(&DAT_011302b8);
  FUN_004086d0(&DAT_01130248);
  FUN_00408310(&DAT_011302b8);
  FUN_00408310(&DAT_01130248);
  FUN_004083d0();
  *this = &PTR_LAB_00d6f4e4;
  DAT_0112991c = 0;
  return;
}