// FUNC_NAME: SimManager::applyEntityData
void __thiscall SimManager::applyEntityData(int thisPtr, int *entityData)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  int iVar6;
  
  if (*entityData == *(int *)(thisPtr + 0x14)) {
    iVar6 = FUN_006b8ed0(); // getSimEntity
    if (iVar6 != 0) {
      if (*(int *)(thisPtr + 0x1c) != 0) {
        FUN_006b8bd0(iVar6); // applyEntityTransform
      }
      if (-1 < *(int *)(thisPtr + 0x54)) {
        FUN_006b30c0(*(int *)(thisPtr + 0x54)); // setAnimation
      }
      if (-1 < *(int *)(thisPtr + 0x58)) {
        FUN_006b3160(*(int *)(thisPtr + 0x58)); // setAnimationBlend
      }
      iVar2 = *(int *)(iVar6 + 0xd4); // entityData +0xd4
      if (iVar2 != 0) {
        iVar3 = *(int *)(thisPtr + 0x38); // componentData[0]
        piVar1 = (int *)(iVar2 + 0x26c); // componentSlot0 +0x26c
        if (iVar3 != 0) {
          if (*piVar1 != 0) {
            FUN_00408310(piVar1); // releaseComponent
          }
          FUN_00408260(piVar1,iVar3); // setComponent
        }
        iVar3 = *(int *)(thisPtr + 0x3c); // componentData[1]
        piVar1 = (int *)(iVar2 + 0x274); // componentSlot1 +0x274
        if (iVar3 != 0) {
          if (*piVar1 != 0) {
            FUN_00408310(piVar1);
          }
          FUN_00408260(piVar1,iVar3);
        }
        iVar3 = *(int *)(thisPtr + 0x40); // componentData[2]
        piVar1 = (int *)(iVar2 + 0x1dc); // componentSlot2 +0x1dc
        if (iVar3 != 0) {
          if (*piVar1 != 0) {
            FUN_00408310(piVar1);
          }
          FUN_00408260(piVar1,iVar3);
        }
        iVar3 = *(int *)(thisPtr + 0x44); // componentData[3]
        piVar1 = (int *)(iVar2 + 0x29c); // componentSlot3 +0x29c
        if (iVar3 != 0) {
          if (*piVar1 != 0) {
            FUN_00408310(piVar1);
          }
          FUN_00408260(piVar1,iVar3);
        }
        if (*(int *)(thisPtr + 0x48) != 0) {
          *(int *)(iVar2 + 0x1d8) = *(int *)(thisPtr + 0x48); // setComponentData
        }
      }
      FUN_006b8f60(iVar6); // finalizeEntity
      return;
    }
  }
  else if ((*entityData == *(int *)(thisPtr + 0x1c)) && (*(int *)(thisPtr + 0x5c) != 0)) {
    iVar6 = FUN_006b8ed0(); // getSimEntity
    if (iVar6 != 0) {
      puVar4 = *(undefined4 **)(thisPtr + 0x5c); // entityDataPtr
      FUN_006b30c0(puVar4[7]); // setAnimation
      FUN_006b3160(puVar4[8]); // setAnimationBlend
      iVar2 = *(int *)(iVar6 + 0xd4); // entityData +0xd4
      if (iVar2 != 0) {
        uVar5 = *puVar4; // component0
        if (*(int *)(iVar2 + 0x26c) != 0) {
          FUN_00408310(iVar2 + 0x26c); // releaseComponent
        }
        FUN_00408260(iVar2 + 0x26c,uVar5); // setComponent
        uVar5 = puVar4[1]; // component1
        piVar1 = (int *)(iVar2 + 0x274);
        if (*piVar1 != 0) {
          FUN_00408310(piVar1);
        }
        FUN_00408260(piVar1,uVar5);
        uVar5 = puVar4[2]; // component2
        piVar1 = (int *)(iVar2 + 0x1dc);
        if (*piVar1 != 0) {
          FUN_00408310(piVar1);
        }
        FUN_00408260(piVar1,uVar5);
        uVar5 = puVar4[3]; // component3
        piVar1 = (int *)(iVar2 + 0x29c);
        if (*piVar1 != 0) {
          FUN_00408310(piVar1);
        }
        FUN_00408260(piVar1,uVar5);
        *(undefined4 *)(iVar2 + 0x1d8) = puVar4[4]; // setComponentData
      }
      FUN_006b9090(iVar6); // finalizeEntityWithData
    }
    if (*(int *)(thisPtr + 0x5c) != 0) {
      FUN_009c8eb0(*(int *)(thisPtr + 0x5c)); // freeEntityData
      *(undefined4 *)(thisPtr + 0x5c) = 0;
    }
  }
  return;
}