// FUNC_NAME: EARS::Framework::Object::setTransform
void EARS::Framework::Object::setTransform(int thisPtr)
{
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  local_c = *(undefined4 *)(thisPtr + 0xc); // +0x0C: position.z (or rotation component)
  local_8 = *(undefined4 *)(thisPtr + 8);   // +0x08: position.y (or rotation component)
  local_4 = 0;                               // +0x04: position.x (or rotation component) - initialized to zero
  
  if (*(int *)(thisPtr + 0x14) != 0) {       // +0x14: pointer to transform matrix or parent
    FUN_00408bf0(&local_c, *(int *)(thisPtr + 0x14)); // Apply relative transform
    return;
  }
  FUN_00408a00(&local_c, 0);                 // Apply absolute transform (identity parent)
  return;
}