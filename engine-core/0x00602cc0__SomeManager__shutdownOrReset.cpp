// FUNC_NAME: SomeManager::shutdownOrReset
void __fastcall SomeManager::shutdownOrReset(undefined4 *this)
{
  *this = &PTR_FUN_00e40874;
  this[2] = &PTR_LAB_00e40880;
  this[5] = &PTR_LAB_00e40890;
  *(undefined1 *)(this + 7) = 0;
  if (this[8] != 0) {
    FUN_00602db0(); // likely sub-object cleanup
  }
  FUN_004086d0(&DAT_01222230); // release resource
  FUN_004086d0(&DAT_01222248);
  FUN_004086d0(&DAT_01222238);
  FUN_004086d0(&DAT_01222258);
  FUN_00408310(&DAT_01222250); // free memory
  FUN_00408310(&DAT_01222240);
  FUN_00408310(&DAT_01222230);
  FUN_00408310(&DAT_01222248);
  FUN_00408310(&DAT_01222238);
  FUN_00408310(&DAT_01222258);
  (**(code **)(*(int *)this[6] + 0xc))(); // virtual call on member
  if (this[0xc] != 0) {
    FUN_009c8f10(this[0xc]); // delete object
  }
  if (this[9] != 0) {
    FUN_009c8f10(this[9]); // delete object
  }
  this[5] = &PTR_LAB_00e40894;
  DAT_012234a4 = 0; // global flag reset
  FUN_004083d0(); // final cleanup
  FUN_0049c640(); // shutdown sequence
  return;
}