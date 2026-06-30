// FUNC_NAME: EARSObject::getPosition
void __thiscall getPosition(int this, Vec3 *outPos)
{
  int offset; // eax
  
  offset = *(int *)(this + 0x14); // +0x14: pointer to position data
  outPos->x = *(float *)(offset + 0x10); // +0x10: x coordinate
  outPos->y = *(float *)(offset + 0x14); // +0x14: y coordinate
  outPos->z = *(float *)(offset + 0x18); // +0x18: z coordinate
  return;
}