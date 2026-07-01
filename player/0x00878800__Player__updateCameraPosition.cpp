// FUNC_NAME: Player::updateCameraPosition
void Player::updateCameraPosition(float *cameraPos)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  undefined1 local_80;
  undefined4 local_7c;
  undefined1 local_70 [16];
  float local_60;
  undefined4 local_5c;
  undefined4 local_50;
  undefined4 local_30;
  int *local_20;
  
  fVar1 = *cameraPos;
  fVar2 = cameraPos[2];
  fVar3 = cameraPos[1] + _DAT_00d5780c; // +0x0C: some global offset
  fVar4 = fVar3 - DAT_00e44634; // subtract another global
  local_80 = 0;
  local_7c = 0;
  local_94 = _DAT_00d5780c;
  local_a0 = fVar1;
  local_9c = fVar3;
  local_98 = fVar2;
  local_7c = FUN_00540c60(7,0x1f,0); // some query function (7, 31, 0)
  local_5c = 0xffffffff;
  local_50 = 0xffffffff;
  local_84 = _DAT_00d5780c;
  local_60 = _DAT_00d5780c;
  local_30 = 0;
  local_20 = (int *)0x0;
  local_90 = fVar1;
  local_8c = fVar4;
  local_88 = fVar2;
  FUN_009e69d0(&local_a0,local_70); // some transform/query function
  if ((local_20 != (int *)0x0) && (*(int *)(*local_20 + 0xc) == 0xb)) {
    fVar3 = (fVar4 - fVar3) * local_60 + fVar3 + DAT_00d58cbc;
    *cameraPos = (fVar1 - fVar1) * local_60 + fVar1;
    cameraPos[2] = (fVar2 - fVar2) * local_60 + fVar2;
    cameraPos[1] = fVar3;
  }
  return;
}