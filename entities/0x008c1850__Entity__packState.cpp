// FUNC_NAME: Entity::packState
undefined4 __thiscall Entity::packState(int this, undefined4 *outBuffer)
{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  
  // Write m_classId (or m_ghostFlags) at offset 0x54
  outBuffer[0] = *(undefined4 *)(this + 0x54);
  // Default to global GUID constant if classId matches known hash
  uVar5 = DAT_00d7bca0;
  if (*(int *)(this + 0x54) != 0x637b907) {
    uVar5 = *(undefined4 *)(this + 0x100);
  }
  outBuffer[1] = uVar5;
  outBuffer[2] = 0;
  // Write rotation quaternion (X, Y, Z, W) at offsets 0x148, 0x14c, 0x150, 0x154
  outBuffer[4] = *(undefined4 *)(this + 0x148);
  outBuffer[5] = *(undefined4 *)(this + 0x14c);
  outBuffer[3] = *(undefined4 *)(this + 0x150);
  outBuffer[6] = *(undefined4 *)(this + 0x154);
  // Write translation or scale at 0x158
  outBuffer[7] = *(undefined4 *)(this + 0x158);
  // Write flags byte at 0x15c
  outBuffer[8] = (uint)*(byte *)(this + 0x15c);
  // Write unknown fields
  outBuffer[9] = *(undefined4 *)(this + 0x10c);
  outBuffer[10] = *(undefined4 *)(this + 0x118);
  outBuffer[0xb] = *(undefined4 *)(this + 400);
  // Write count of sub-objects (0x1a8) and sum their packed sizes
  outBuffer[0xc] = *(undefined4 *)(this + 0x1a8);
  uVar3 = 0;
  iVar4 = 0;
  if (*(int *)(this + 0x1a8) != 0) {
    do {
      iVar1 = Entity::getSubObjectPackedSize(); // FUN_008c8390
      uVar3 = uVar3 + 1;
      iVar4 = iVar4 + iVar1;
    } while (uVar3 < *(uint *)(this + 0x1a8));
  }
  outBuffer[0xd] = iVar4;
  // Write count of items in secondary array (0x134) and sum of values at offset 0x14 within each
  outBuffer[0xe] = *(undefined4 *)(this + 0x134);
  iVar4 = *(int *)(this + 0x134);
  iVar1 = 0;
  if (iVar4 != 0) {
    piVar2 = (int *)(*(int *)(this + 0x130) + 0x14);
    do {
      iVar1 = iVar1 + *piVar2;
      piVar2 = piVar2 + 7; // stride of 28 bytes (7 ints)
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  outBuffer[0xf] = iVar1;
  // Write position (0x84) and velocity (0x120)
  uVar5 = *(undefined4 *)(this + 0x84);
  outBuffer[0x11] = 0;
  outBuffer[0x12] = 0;
  outBuffer[0x10] = uVar5;
  outBuffer[0x13] = *(undefined4 *)(this + 0x120);
  // Zero out remaining slots (reserved)
  outBuffer[0x14] = 0;
  outBuffer[0x15] = 0;
  outBuffer[0x16] = 0;
  outBuffer[0x17] = 0;
  return 0x60; // total packed size: 96 bytes
}