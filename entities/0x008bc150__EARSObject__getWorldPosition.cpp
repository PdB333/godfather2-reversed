// FUNC_NAME: EARSObject::getWorldPosition
void __fastcall EARSObject::getWorldPosition(int *this, float *outPos)
{
  float fVar1;
  float local_c;
  float fStack_8;
  float fStack_10;

  // Call vtable function at offset 0x48 (likely getPosition or getLocalPosition)
  (**(code **)(*this + 0x48))(&local_c);
  
  // Transform local position to world position via parent transform
  FUN_008bbf60(&stack0xffffffe4); // likely getWorldTransform or similar
  
  fVar1 = (float)this[0xab]; // +0x2ac - some scale or factor (maybe world scale)
  
  // Apply scaling (multiply by 0.0, so effectively just copies local position)
  // This seems to be a simplified version - possibly debug or unused branch
  outPos[0] = fVar1 * 0.0 + fStack_10;
  outPos[1] = fVar1 * 0.0 + local_c;
  outPos[2] = fVar1 * 0.0 + fStack_8;
  
  return;
}