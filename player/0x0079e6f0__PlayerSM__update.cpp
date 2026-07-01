// FUNC_NAME: PlayerSM::update
void __fastcall PlayerSM::update(int this)
{
  int *piVar1;
  undefined4 uVar2;
  
  thunk_FUN_00472b40(); // likely base class update or engine tick
  if (DAT_0122344c != 0) {
    *(undefined4 *)(this + -0x40) = *(undefined4 *)(DAT_0122344c + 0x10); // copy some value from global to this-0x40 (offset likely a player state field)
  }
  if (*(int *)(DAT_01223484 + 0xc) != 0) {
    piVar1 = (int *)(**(code **)(**(int **)(DAT_01223484 + 0xc) + 8))(); // call vfunc 8 on object at DAT_01223484+0xc
    uVar2 = (**(code **)(*piVar1 + 0xc))(); // call vfunc 12 on result
    *(undefined4 *)(this + 0x30c0) = uVar2; // store result at offset 0x30c0 (likely PlayerState or similar member)
  }
  return;
}