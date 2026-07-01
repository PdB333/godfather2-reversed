// FUNC_NAME: GodfatherGameManager::addPendingAction
void GodfatherGameManager::addPendingAction(int param_1, int *param_2)
{
  int iVar1;
  int iVar2;
  char cVar3;
  int in_EAX;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  
  if ((in_EAX != 0) && (*(int *)(in_EAX + 0x130) != 0)) {
    puVar4 = (undefined4 *)FUN_004a45c0(); // likely getActionData or allocateAction
    puVar5 = (undefined4 *)(*param_2 * 0x10 + param_1); // param_1 is action array base, param_2 is count pointer
    *puVar5 = *puVar4;
    puVar5[1] = puVar4[1];
    puVar5[2] = puVar4[2];
    puVar5[3] = puVar4[3]; // copy 16 bytes (4 ints) of action data
    iVar2 = *param_2;
    iVar6 = iVar2 * 0x10;
    iVar1 = iVar6 + param_1;
    if (((*(int *)(iVar6 + param_1) != 0) ||
        (((*(int *)(iVar1 + 4) != 0 || (*(int *)(iVar1 + 8) != 0)) || (*(int *)(iVar1 + 0xc) != 0)))
        ) && (cVar3 = FUN_0083b570(), cVar3 == '\0')) { // likely validateAction or isActionValid
      *param_2 = iVar2 + 1; // increment action count
    }
  }
  return;
}