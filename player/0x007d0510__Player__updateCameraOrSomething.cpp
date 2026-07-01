// FUNC_NAME: Player::updateCameraOrSomething
void __fastcall Player::updateCameraOrSomething(int *thisPtr)
{
  float clampedValue;
  float fVar1;
  float local_4;
  
  local_4 = (float)thisPtr[0xc]; // +0x30 - some float field
  fVar1 = 0.0;
  if ((local_4 <= 0.0) || (fVar1 = DAT_00d5e288, DAT_00d5e288 <= local_4)) {
    local_4 = fVar1;
  }
  FUN_007ac750(local_4); // likely setCameraFOV or similar
  uVar2 = 0;
  // vtable call at +0x2c - likely some rendering/effect function
  (**(code **)(*thisPtr + 0x2c))
            ((-(uint)((*(uint *)(thisPtr[0x16] + 0x8e0) >> 1 & 1) != 0) & 0x6e24e6c2) + 0x46f5c7b4,1
             ,0,0,0x3f800000,0x3f800000);
  FUN_00799590(uVar2); // likely some cleanup or state update
  // vtable call at +0x164 on thisPtr[0x16] (some sub-object)
  (**(code **)(*(int *)thisPtr[0x16] + 0x164))();
  return;
}