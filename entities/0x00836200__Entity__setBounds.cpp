// FUNC_NAME: Entity::setBounds
void __thiscall Entity::setBounds(int thisPtr, undefined4 *bounds)
{
  // Copy 4 words (16 bytes) of bounding data from param_2 to this+0x40
  // +0x40: Bounding box min/max or center+extents
  undefined4 x = bounds[0];
  undefined4 y = bounds[1];
  undefined4 z = bounds[2];
  undefined4 w = bounds[3];
  
  *(undefined4 *)(thisPtr + 0x40) = x;
  *(undefined4 *)(thisPtr + 0x44) = y;
  *(undefined4 *)(thisPtr + 0x48) = z;
  *(undefined4 *)(thisPtr + 0x4c) = w;
}