// FUNC_NAME: ScriptEngine::executeScript
void __thiscall ScriptEngine::executeScript(int this, undefined4 param_2, undefined4 param_3)
{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined **local_90 [18];
  undefined1 local_48 [72];
  
  iVar5 = -0x1e98fd1; // Default return value (error code)
  FUN_00405e80(local_90,param_2,1); // Initialize script context
  uVar2 = FUN_00405f20(local_48); // Get first token
  cVar1 = FUN_00405f90(uVar2); // Check if token is valid
  do {
    if (cVar1 == '\\0') {
LAB_00813210:
      local_90[0] = &PTR_DAT_00e2f0c4; // Set error handler
      if (iVar5 != -0x1e98fd1) {
        FUN_008130c0(this,param_2,param_3,iVar5); // Handle error
      }
      return;
    }
    puVar3 = (undefined4 *)FUN_00405f80(); // Get next token
    iVar4 = FUN_0088dbb0(*(undefined4 *)*puVar3); // Check if token is a command
    if (iVar4 != 0) {
      iVar5 = *(int *)*puVar3; // Store command result
      goto LAB_00813210;
    }
    (*(code *)local_90[0][1])(); // Execute command handler
    uVar2 = FUN_00405f20(local_48); // Get next token
    cVar1 = FUN_00405f90(uVar2); // Check validity
  } while( true );
}