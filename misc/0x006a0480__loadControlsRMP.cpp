// FUNC_NAME: loadControlsRMP
void loadControlsRMP(void)

{
  undefined2 *puVar1;
  undefined2 *local_10 [3];
  code *local_4;
  
  FUN_00699080(local_10,PTR_u_controls_rmp_00e50c74,1);
  puVar1 = local_10[0];
  if (local_10[0] == (undefined2 *)0x0) {
    puVar1 = &DAT_00e2df14;
  }
  FUN_00497470(puVar1);
  if (local_10[0] != (undefined2 *)0x0) {
    (*local_4)(local_10[0]);
  }
  return;
}