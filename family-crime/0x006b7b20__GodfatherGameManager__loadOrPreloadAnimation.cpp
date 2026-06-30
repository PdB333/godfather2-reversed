// FUNC_NAME: GodfatherGameManager::loadOrPreloadAnimation
void __thiscall GodfatherGameManager::loadOrPreloadAnimation(int this, undefined4 param_2)
{
  bool bVar1;
  char cVar2;
  int iVar3;
  float fVar4;
  float *pfVar5;
  float local_120;
  float local_11c;
  float local_118;
  undefined4 local_114;
  undefined4 local_104;
  undefined4 local_f4;
  undefined8 local_f0;
  undefined4 local_e8;
  undefined4 local_e4;
  
  FUN_0046c710(param_2);  // likely startAsyncOperation or beginLoad
  bVar1 = false;
  FUN_0043aff0(param_2,0xf3244a61);  // pushLoadRequest(?)
  cVar2 = FUN_0043b120();  // isLoadComplete?
  while (cVar2 == '\0') {
    FUN_0043b210();  // processNextLoadRequest
    iVar3 = FUN_0043ab70();  // getLoadRequestType(?) - returns 0 for model, 1 for animation
    if (iVar3 == 0) {
      iVar3 = FUN_0043b210();  // popLoadResult
      *(undefined4 *)(this + 0x60) = *(undefined4 *)(iVar3 + 8);  // store model pointer at +0x60
    }
    else if (iVar3 == 1) {
      iVar3 = FUN_0043b210();  // popLoadResult
      fVar4 = *(float *)(iVar3 + 8);  // animation duration
      if (fVar4 <= 0.0) {
        bVar1 = true;  // zero-length animation flag
      }
      *(float *)(this + 0x5c) = fVar4 * fVar4;  // squared duration at +0x5c
    }
    FUN_0043b1a0();  // advanceLoadProcess
    cVar2 = FUN_0043b120();  // isLoadComplete?
  }
  FUN_0043aff0(param_2,0xb390b11a);  // popLoadRequest or finalize
  FUN_0043af00(1);  // setLoadFocusWithPriority(1)
  cVar2 = FUN_0043b120();  // isLoadComplete?
  if (cVar2 == '\0') {
    pfVar5 = &local_120;  // vector3 accumulator
    local_114 = 0;
    local_104 = 0;
    local_f4 = 0;
    local_e4 = _DAT_00d5780c;  // global constant offset
    FUN_0043b210(pfVar5);  // getAnimationRootMotion
    FUN_0043ac60(pfVar5);  // transformVector
    if (bVar1) {
      fVar4 = SQRT(local_118 * local_118 + _DAT_00d577a0 + local_11c * local_11c +
                   local_120 * local_120) * _DAT_00d5c458;  // magnitude * scale
      *(float *)(this + 0x5c) = fVar4 * fVar4;  // recalculate squared duration
    }
    *(undefined8 *)(this + 0x50) = local_f0;  // store root motion XZ at +0x50
    *(undefined4 *)(this + 0x58) = local_e8;  // store root motion Y at +0x58
  }
  return;
}