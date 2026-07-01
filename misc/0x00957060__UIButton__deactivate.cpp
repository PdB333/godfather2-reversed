// FUNC_NAME: UIButton::deactivate
void __thiscall UIButton::deactivate(int this, int param_2)
{
  int *piVar1;
  int iVar2;
  
  iVar2 = param_2;
  if (param_2 == 0) {
    *(undefined1 *)(this + 0x7c) = 0; // +0x7c: some flag (e.g., active state)
    param_2 = 0x30; // 48, likely a sound ID or duration
    FUN_005a04a0("DeactivateButton",0,&DAT_00d8c174,1,&param_2); // UI sound/event call
  }
  else if (0 < *(int *)(this + 0x78)) { // +0x78: some counter (e.g., press count)
    *(int *)(this + 0x78) = *(int *)(this + 0x78) + -1;
  }
  FUN_005a04a0("DeactivateButton",0,&DAT_00d8c174,1,PTR_DAT_00e5743c); // Another UI event
  piVar1 = *(int **)(this + 0x54 + param_2 * 4); // +0x54: array of pointers (e.g., button states)
  if (*(char *)(this + 0x50) == '\0') { // +0x50: some flag
    FUN_00957e30(); // likely a helper function
  }
  (**(code **)(*piVar1 + 0x2c))(); // vtable call at offset 0x2c (e.g., onDeactivate)
  (**(code **)(*piVar1 + 0x90))(DAT_01130030); // vtable call at offset 0x90 (e.g., setState)
  FUN_0097de80(0); // likely a cleanup or update function
  FUN_0097b900(); // likely a UI refresh
  FUN_0097d690(); // likely a sound/event function
  return;
}