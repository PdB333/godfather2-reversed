// FUNC_NAME: GodfatherGameManager::updateGameState
void GodfatherGameManager::updateGameState(void)

{
  int *piVar1;
  
  if ((**(int **)(DAT_012233a0 + 4) != 0) && (**(int **)(DAT_012233a0 + 4) != 0x1f30)) {
    piVar1 = (int *)FUN_0043b870(DAT_01131018);
    if ((piVar1 != (int *)0x0) && (_DAT_00d577a0 <= DAT_00e53f64)) {
      (**(code **)(*piVar1 + 0x3c))(DAT_00e53f64);
      DAT_00e53f64 = DAT_00d5ccf8;
    }
  }
  DAT_0112dcc0 = 1;
  FUN_004464d0(&LAB_00842e60);
  return;
}