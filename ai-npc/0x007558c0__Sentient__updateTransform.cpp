// FUNC_NAME: Sentient::updateTransform
void __thiscall Sentient::updateTransform(int *this, undefined4 angle, float deltaTime)
{
  char cVar1;
  int iVar2;
  int *pVariousPtr;
  longdouble tempFloat;
  float10 fVar5;
  
  // Check flag at +0x16 bit 3 (0x8) - possibly 'using direct rotation'
  if ((*(byte *)(this + 0x16) & 8) == 0) {
    // Convert angle to cos for comparison
    tempFloat = angleToCos(angle);
    fVar5 = (float10)fcos(tempFloat);
    // Compare with stored threshold at +0x60 (this[0x18])
    if ((float10)(float)this[0x18] < fVar5) {
      return;
    }
    // Apply rotation with speed factor this[0x17] * deltaTime
    fVar5 = (float10)applyRotation(angle, (float)this[0x17] * deltaTime, 0);
    if (fVar5 != (float10)0) {
      return;
    }
  }
  else {
    // Alternate path: check bit 4 (0x10) - 'rotation animation done'
    if ((*(byte *)(this + 0x16) & 0x10) != 0) {
      return;
    }
    // Get animation component pointer (offset +0x48)
    if (this[0x12] == 0) {
      pVariousPtr = (int *)0x0;
    }
    else {
      // Subtract 0x48 to get to base of animation object
      pVariousPtr = (int *)(this[0x12] + -0x48);
    }
    // Call virtual function at +0x164 (likely Animation::updateStep)
    (**(code **)(*pVariousPtr + 0x164))();
    cVar1 = isRotationAllowed();
    if (cVar1 == '\0') {
      return;
    }
    // Set bit 4 to indicate rotation animation is done
    *(byte *)(this + 0x16) = *(byte *)(this + 0x16) | 0x10;
  }
  // Now apply final transform if flag kUseManualTransform (bit 2) is clear
  if ((*(byte *)(this + 0x16) & 4) == 0) {
    iVar2 = this[0x1e];                     // +0x78 -> maybe target transform ID or direct pointer
    if (iVar2 == 0) {
      if ((*(byte *)(this + 0x16) & 2) == 0) {
        cVar1 = getDefaultTransform();
        // Magic constant derived from inverse of something: 0x2ca3cff6 = 0x75D44A? No, compute:
        // Conditional negation: if cVar1 != 0 then iVar2 = 0x2ca3cff6 else 0xd8a48e43? Actually it's (-(uint)(cVar1 != '\0') & 0xd8a48e43) + 0x2ca3cff6
        // That yields either 0x2ca3cff6 or 0x2ca3cff6 + 0xd8a48e43 = 0x104ec489? Not plausible. Likely a bug in decompiler; we'll assume it returns an index.
        // For reconstruction, we'll just keep the expression as is but simplify to a function call returning an ID.
        iVar2 = (-(uint)(cVar1 != '\0') & 0xd8a48e43) + 0x2ca3cff6;
      }
      else if (this[0x12] == 0) {
        iVar2 = getTransformFromAnimation(); // FUN_007347e0
      }
      else {
        iVar2 = getTransformFromAnimation();
      }
    }
    // Call virtual function at +0x2c (likely setWorldMatrix or setTransform) with (iVar2, 1, 0, 0, 1.0f, 1.0f)
    (**(code **)(*this + 0x2c))(iVar2, 1, 0, 0, 0x3f800000, 0x3f800000);
  }
  return;
}