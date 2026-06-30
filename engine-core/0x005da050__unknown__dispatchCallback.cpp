// FUNC_NAME: unknown::dispatchCallback
void __fastcall dispatchCallback(undefined4 *param_1, int param_2)
{
  undefined4 *puVar1;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar1 = (undefined4 *)param_1[1]; // +0x04: pointer to callback data or null
  if ((undefined1 *)param_1[1] == (undefined1 *)0x0) {
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    puVar1 = &local_c;
  }
  (*(code *)**(undefined4 **)*param_1)(param_2 * 0x28,puVar1); // call function pointer at *param_1 with scaled param_2 and data
  return;
}