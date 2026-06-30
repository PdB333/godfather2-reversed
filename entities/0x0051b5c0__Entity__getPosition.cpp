// FUNC_NAME: Entity::getPosition
void __fastcall Entity::getPosition(int thisPtr, undefined4 *outPos)
{
  undefined4 posX, posY, posZ;
  
  if (*(int *)(thisPtr + 0xbc) != 0) {
    // If we have a physics body, get position from it
    FUN_0056b420(thisPtr + 0x30, *(int *)(thisPtr + 0xbc), outPos);
    return;
  }
  
  // Otherwise return the stored position from entity data
  // +0x60: posX
  // +0x64: posY (actually +100 = 0x64)
  // +0x68: posZ
  // +0x6C: posW or unused (fourth component)
  posX = *(undefined4 *)(thisPtr + 0x60);
  posY = *(undefined4 *)(thisPtr + 100); // 0x64
  posZ = *(undefined4 *)(thisPtr + 0x68);
  undefined4 posW = *(undefined4 *)(thisPtr + 0x6c);
  
  outPos[0] = posX;
  outPos[1] = posY;
  outPos[2] = posZ;
  // outPos[3] = posW; // not written, but likely unused
  return;
}