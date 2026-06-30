// FUNC_NAME: PlayerHud::drawMinimap
void PlayerHud::drawMinimap(void)
{
  undefined1 *puVar1;
  uint unaff_ESI; // ESI likely holds something like a player index or map ID
  float fVar2;
  float fVar3;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  // +0x1125d68: likely a flag indicating the minimap has been initialized
  if (DAT_01125d68 != 0) {
    FUN_006063b0(); // likely some render setup or clear
  }
  // unaff_ESI seems to be a map index or layer index, bounded by 0x1000 (4096)
  if (unaff_ESI < 0x1000) {
    puVar1 = &DAT_011a0f28 + unaff_ESI * 0x38; // +0x38 per entry: structure size for a minimap layer/region
  }
  else {
    puVar1 = (undefined1 *)0x0;
  }
  fVar2 = DAT_00e2b1a4 / (float)*(ushort *)(puVar1 + 2); // +0x2: width in the structure
  if (unaff_ESI < 0x1000) {
    puVar1 = &DAT_011a0f28 + unaff_ESI * 0x38;
  }
  else {
    puVar1 = (undefined1 *)0x0;
  }
  fVar3 = DAT_00e2b1a4 / (float)*(ushort *)(puVar1 + 4); // +0x4: height in the structure
  local_14 = DAT_00e44564 - fVar3;
  local_20 = fVar2;
  local_1c = fVar3;
  local_18 = fVar2;
  FUN_0060add0(DAT_01125ba4, DAT_01125d6c, &local_20); // likely a 2D draw call (texture, position/size)
  if (DAT_01125d70 != 0) {
    local_18 = fVar2 * DAT_00e2cd54; // +0xe2cd54: some scale factor (zoom?)
    local_14 = fVar3 * DAT_00e2cd54;
    local_20 = fVar2;
    local_1c = fVar3;
    FUN_0060add0(DAT_01125ba4, DAT_01125d70, &local_20);
  }
  return;
}