// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::destructor(undefined4 *this)
{
  *this = &PTR_FUN_00d74a20;
  this[3] = &PTR_LAB_00d74a14;
  this[5] = &PTR_LAB_00d74a10;
  FUN_00408310(&DAT_0112dcd8);
  FUN_00408310(&DAT_0112dcd0);
  FUN_004086d0(&DAT_012069c4);
  FUN_004086d0(&DAT_012069b4);
  FUN_004086d0(&DAT_01206980);
  (**(code **)(*(int *)(this[7] + 4) + 8))();
  if ((undefined4 *)this[0xd] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this[0xd])(1);
  }
  if ((undefined4 *)this[0xc] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this[0xc])(1);
  }
  if ((undefined4 *)this[0xb] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this[0xb])(1);
  }
  if ((undefined4 *)this[10] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this[10])(1);
  }
  if ((undefined4 *)this[9] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this[9])(1);
  }
  if ((undefined4 *)this[8] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this[8])(1);
  }
  if ((undefined4 *)this[7] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this[7])(1);
  }
  (**(code **)(*(int *)this[6] + 0xc))();
  this[6] = 0;
  FUN_00843190();
  this[5] = &PTR_LAB_00d74948;
  DAT_01129948 = 0;
  FUN_0049c640();
  FUN_004083d0();
  return;
}