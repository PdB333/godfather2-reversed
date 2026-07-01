// FUNC_NAME: Matrix4x4::lerpMatrixRows
int Matrix4x4::lerpMatrixRows(int param_1, float param_2, int param_3, int param_4)
{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  int local_20;
  
  fVar4 = _DAT_00d5780c - param_2; // deltaTime = currentTime - startTime
  FUN_00822f30(); // likely clamp or normalize interpolation factor
  iVar3 = param_3 + 0x90; // source matrix + row2 offset
  iVar2 = param_4 + 0x50; // target matrix + row1 offset
  iVar1 = param_1 + 0xd0; // output matrix + row3 offset
  local_20 = 4; // 4 rows to interpolate
  do {
    FUN_0056b5d0(fVar4,(param_3 - param_4) + iVar2,param_2,iVar2,(param_1 - param_4) + iVar2); // lerp row
    FUN_0056b5d0(fVar4,iVar3,param_2,iVar2 + 0x40,(param_1 - param_3) + iVar3); // lerp next row
    FUN_0056b5d0(fVar4,iVar3 + 0x40,param_2,iVar2 + 0x80,iVar1); // lerp third row
    iVar2 = iVar2 + 0x10; // advance 4 floats (16 bytes) per row
    iVar3 = iVar3 + 0x10;
    iVar1 = iVar1 + 0x10;
    local_20 = local_20 + -1;
  } while (local_20 != 0);
  return param_1; // return output matrix pointer
}