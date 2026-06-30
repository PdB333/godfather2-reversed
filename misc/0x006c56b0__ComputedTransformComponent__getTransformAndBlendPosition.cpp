// FUNC_NAME: ComputedTransformComponent::getTransformAndBlendPosition
void FUN_006c56b0(undefined8 *param_1)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = FUN_00471610();
  *param_1 = *(undefined8 *)(iVar1 + 0x30);
  *(undefined4 *)(param_1 + 1) = *(undefined4 *)(iVar1 + 0x38);
  fVar2 = (float10)FUN_006c55d0();
  *(float *)((int)param_1 + 4) = (float)(fVar2 + (float10)*(float *)((int)param_1 + 4));
  return;
}