// FUNC_NAME: PlayerSM::handleActionMessage
void __thiscall PlayerSM::handleActionMessage(int *thisPlayer, int *actionMsg)
{
  char cVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  undefined8 *puVar8;
  float10 fVar9;
  undefined1 *local_34;
  undefined1 *local_30;
  undefined ***local_2c;
  undefined1 local_28 [4];
  undefined **local_24;
  undefined1 *local_20;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 local_8;
  undefined4 local_4;
  
  // Extract entity ID/handle from message offset +4
  if (*(int *)(actionMsg + 4) == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = *(int *)(actionMsg + 4) + -0x48; // entity index after subtracting base
  }

  // Switch on message type at offset +0x18
  switch(*(undefined4 *)(actionMsg + 0x18)) {
  case 1:
    // Attack/Takedown message
    puVar8 = (undefined8 *)(actionMsg + 0xc); // 64-bit timestamp/value
    if (((iVar3 != 0) && (iVar3 = findEntityByHash(iVar3, 0x4ecfbe13), iVar3 != 0)) &&
       ((piVar4 = (int *)getActiveSimSet(), piVar4 != (int *)0x0 && (piVar4 != thisPlayer)))) {
      local_34 = (undefined1 *)0x1bb845c9; // action hash: attack
      piVar5 = (int *)findObjectInSet(piVar4, 0x55859efa); // find target player?
      if (piVar5 == (int *)0x0) goto LAB_0072e778;
      iVar3 = getLocalPlayer(); // or getCrewLeaderComponent
      if (((iVar3 != 0) && (piVar6 = (int *)findObjectInSet(iVar3, 0x55859efa), piVar6 != (int *)0x0))
         && ((piVar5[0x7b5] == thisPlayer[0x7b5] || (piVar6[0x7b5] == thisPlayer[0x7b5])))) {
        cVar1 = (**(code **)(*thisPlayer + 0x28c))(); // is player alive?
        iVar3 = getGameTime();
        fVar9 = (float10)getGameTimeFloat(iVar3 + 0x30);
        if (((float10)g_timeThreshold < fVar9) ||
           (cVar2 = (**(code **)(*piVar5 + 0x28c))(), cVar1 != cVar2)) {
          iVar3 = getGameTime();
          fVar9 = (float10)getGameTimeFloat(iVar3 + 0x30);
          if (((float10)g_timeThreshold < fVar9) ||
             (cVar2 = (**(code **)(*piVar6 + 0x28c))(), cVar1 != cVar2)) goto LAB_0072e76c;
        }
        local_34 = (undefined1 *)0x1892c242; // action hash: takedown
      }
LAB_0072e76c:
      iVar3 = getGameTime();
      puVar8 = (undefined8 *)(iVar3 + 0x30);
LAB_0072e778:
      // Send event to network
      sendEvent(0, 0xffffffff);
      local_20 = local_34;
      deleteObject(piVar4); // release simset? or just reference
      local_8 = 1;
      local_14 = (undefined4)*puVar8;
      uStack_10 = (undefined4)((ulonglong)*puVar8 >> 0x20);
      local_c = *(undefined4 *)(puVar8 + 1);
      local_2c = &local_24;
      local_30 = g_simSetPtr;
      local_28[0] = 0;
      if (thisPlayer == (int *)0x0) {
        piVar4 = (int *)0x0;
      }
      else {
        piVar4 = thisPlayer + 0xf; // pointer to sub-object at offset 0x3C?
      }
      addToSimSet(&local_30, piVar4, 0);
      if (thisPlayer[0x834] != 0) {
        deleteString(thisPlayer + 0x834);
      }
      flushNetwork();
      return;
    }
    break;
  case 2:
    // Movement message
    local_c = 0;
    uStack_10 = 0;
    local_14 = 0;
    local_24 = &PTR_FUN_00d5dbbc; // some vtable?
    local_1c = 0;
    local_18 = 0;
    local_8 = 0;
    local_4 = g_someGlobal;
    local_20 = (undefined1 *)0x1970c04; // action hash: movement
    if (((*(int *)(actionMsg + 4) == 0) || (*(int *)(actionMsg + 4) == 0x48)) ||
       (*(int *)(actionMsg + 4) == 0)) {
      iVar3 = 0;
    }
    else {
      iVar3 = *(int *)(actionMsg + 4) + -0x48;
    }
    deleteObject(iVar3);
LAB_0072e925:
    local_c = *(undefined4 *)(actionMsg + 0x14);
    local_8 = 1;
    local_14 = (undefined4)*(undefined8 *)(actionMsg + 0xc);
    uStack_10 = (undefined4)((ulonglong)*(undefined8 *)(actionMsg + 0xc) >> 0x20);
    goto LAB_0072e93c;
  case 3:
  case 4:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
    break;
  case 5:
    // Some other action (e.g., interaction)
    local_c = 0;
    uStack_10 = 0;
    local_14 = 0;
    local_4 = g_someGlobal;
    local_24 = &PTR_FUN_00d5dbbc;
    local_1c = 0;
    local_18 = 0;
    local_8 = 0;
    local_20 = (undefined1 *)0x9985755e; // action hash
    if ((*(int *)(actionMsg + 4) == 0) || (*(int *)(actionMsg + 4) == 0x48)) goto LAB_0072e925;
    if ((*(int *)(actionMsg + 4) == 0) ||
       ((*(int *)(actionMsg + 4) == 0x48 || (*(int *)(actionMsg + 4) == 0)))) {
      deleteObject(0);
    }
    else {
      deleteObject(*(int *)(actionMsg + 4) + -0x48);
    }
LAB_0072e93c:
    local_2c = &local_24;
    local_30 = g_simSetPtr;
    local_28[0] = 0;
    if (thisPlayer == (int *)0x0) {
      thisPlayer = (int *)0x0;
    }
    else {
      thisPlayer = thisPlayer + 0xf;
    }
    addToSimSet(&local_30, thisPlayer, 0);
    if (local_1c != 0) {
      deletePointer(&local_1c);
    }
    break;
  case 6:
    // Fallback attack (maybe direct)
    if ((((*(int *)(actionMsg + 4) != 0) && (*(int *)(actionMsg + 4) != 0x48)) &&
        (*(int *)(actionMsg + 4) != 0)) &&
       ((iVar3 = *(int *)(actionMsg + 4) + -0x48, iVar3 != 0 &&
        (fVar9 = (float10)(**(code **)(*thisPlayer + 0xbc))(iVar3), fVar9 != (float10)0)))) {
      sendEvent(0, 0xffffffff);
      deleteObject(iVar3);
      uStack_10 = *(undefined4 *)(actionMsg + 0x14);
      local_30 = local_28;
      local_24 = (undefined **)0xafcdd651; // action hash
      local_c = CONCAT31(local_c._1_3_,1);
      local_18 = (undefined4)*(undefined8 *)(actionMsg + 0xc);
      local_14 = (undefined4)((ulonglong)*(undefined8 *)(actionMsg + 0xc) >> 0x20);
      local_34 = g_simSetPtr;
      local_2c = (undefined ***)((uint)local_2c & 0xffffff00);
      addToSimSet(&local_34, thisPlayer + 0xf, 0);
      flushNetwork();
      return;
    }
    break;
  case 0xc:
    // Another action type (maybe special)
    if ((((*(int *)(actionMsg + 4) != 0) && (*(int *)(actionMsg + 4) != 0x48)) &&
        (*(int *)(actionMsg + 4) != 0)) &&
       ((iVar3 = *(int *)(actionMsg + 4) + -0x48, iVar3 != 0 &&
        (fVar9 = (float10)(**(code **)(*thisPlayer + 0xbc))(iVar3), fVar9 != (float10)0)))) {
      sendEvent(0, 0xffffffff);
      local_24 = (undefined **)0x279e1a14; // action hash
      if ((*(int *)(actionMsg + 4) == 0) ||
         ((*(int *)(actionMsg + 4) == 0x48 || (*(int *)(actionMsg + 4) == 0)))) {
        iVar7 = 0;
      }
      else {
        iVar7 = *(int *)(actionMsg + 4) + -0x48;
      }
      deleteObject(iVar7);
      uStack_10 = *(undefined4 *)(actionMsg + 0x14);
      local_c = CONCAT31(local_c._1_3_,1);
      local_18 = (undefined4)*(undefined8 *)(actionMsg + 0xc);
      local_14 = (undefined4)((ulonglong)*(undefined8 *)(actionMsg + 0xc) >> 0x20);
      deleteObject(iVar3);
      local_30 = local_28;
      local_34 = g_simSetPtr;
      local_2c = (undefined ***)((uint)local_2c & 0xffffff00);
      addToSimSet(&local_34, thisPlayer + 0xf, 0);
      flushNetwork();
      return;
    }
    break;
  default:
    goto switchD_0072e653_default;
  }
switchD_0072e653_default:
  return;
}