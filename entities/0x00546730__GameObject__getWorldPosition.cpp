// FUNC_NAME: GameObject::getWorldPosition
// Address: 0x00546730
// Returns the world-space position of the object by reading from its internal transform component.
// this+0x2e8 points to a transform structure; position floats at offsets 0x1a0, 0x1a4, 0x1a8 (x, y, z).
void __thiscall GameObject::getWorldPosition(float *outPosVec3)
{
  int *transformPtr = *(int **)(this + 0x2e8);
  outPosVec3[0] = *(float *)(transformPtr + 0x68);   // +0x1a0 / 4 = 0x68 as float pointer offset
  outPosVec3[1] = *(float *)(transformPtr + 0x69);   // +0x1a4
  outPosVec3[2] = *(float *)(transformPtr + 0x6a);   // +0x1a8
}