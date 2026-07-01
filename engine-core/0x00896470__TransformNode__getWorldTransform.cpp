// FUNC_NAME: TransformNode::getWorldTransform
void TransformNode::getWorldTransform(uint flags, float *outMatrix)
{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float local_20;
  float fStack_1c;
  float local_18;
  undefined4 local_14;
  
  iVar4 = FUN_00471610(); // getLocalTransform()
  pfVar5 = (float *)FUN_00471610(); // getParentWorldTransform()
  iVar6 = FUN_00471610(); // getInverseParentTransform()
  fVar3 = DAT_00e44564; // identity value (0.0f?)
  fVar1 = *(float *)(iVar4 + 0x20); // localTransform[0] (translation.x)
  fVar2 = *pfVar5; // parentWorldTransform[0] (translation.x)
  local_20 = DAT_00e44564 - fVar1; // -localTranslation.x
  fStack_1c = DAT_00e44564 - *(float *)(iVar4 + 0x24); // -localTranslation.y
  local_18 = DAT_00e44564 - *(float *)(iVar4 + 0x28); // -localTranslation.z
  fVar8 = DAT_00e44564 - pfVar5[1]; // -parentWorldTranslation.y
  fVar9 = DAT_00e44564 - pfVar5[2]; // -parentWorldTranslation.z
  fVar7 = DAT_00e44564 - fVar2; // -parentWorldTranslation.x
  if (flags < 0x11) {
    if (flags == 0x10) {
      // Inverse combine: parentWorldTransform + localTransform (negated)
      local_20 = fVar7 + local_20;
      fStack_1c = fVar8 + fStack_1c;
      local_18 = fVar9 + local_18;
      *outMatrix = local_20;
      outMatrix[1] = fStack_1c;
      outMatrix[2] = local_18;
      local_14 = 0;
      FUN_0056afa0(&local_20,&local_20); // normalizeVector
      *outMatrix = local_20;
      outMatrix[1] = fStack_1c;
      outMatrix[2] = local_18;
      return;
    }
    switch(flags) {
    case 1:
      // Add local and parent translations
      *outMatrix = fVar2 + fVar1;
      outMatrix[1] = *(float *)(iVar4 + 0x24) + pfVar5[1];
      fVar9 = *(float *)(iVar4 + 0x28) + pfVar5[2];
      break;
    case 2:
      // Copy local transform
      *(undefined8 *)outMatrix = *(undefined8 *)(iVar4 + 0x20);
      outMatrix[2] = *(float *)(iVar4 + 0x28);
      return;
    default:
      return;
    case 4:
      // Add local translation to negated parent translation
      *outMatrix = fVar1 + fVar7;
      outMatrix[1] = *(float *)(iVar4 + 0x24) + fVar8;
      fVar9 = *(float *)(iVar4 + 0x28) + fVar9;
      break;
    case 8:
      // Copy negated parent translation
      *(ulonglong *)outMatrix = CONCAT44(fVar8,fVar7);
      outMatrix[2] = fVar9;
      return;
    }
  }
  else {
    switch(flags) {
    case 0x20:
      // Copy negated local translation
      *(ulonglong *)outMatrix = CONCAT44(fStack_1c,local_20);
      outMatrix[2] = local_18;
      return;
    default:
      return;
    case 0x40:
      // Add parent translation to negated local translation
      *outMatrix = fVar2 + local_20;
      outMatrix[1] = pfVar5[1] + fStack_1c;
      fVar9 = pfVar5[2] + local_18;
      break;
    case 0x80:
      // Copy parent world transform
      *(undefined8 *)outMatrix = *(undefined8 *)pfVar5;
      outMatrix[2] = pfVar5[2];
      return;
    case 0x100:
      // Inverse parent transform
      *outMatrix = DAT_00e44564 - *(float *)(iVar6 + 0x10);
      outMatrix[1] = fVar3 - *(float *)(iVar6 + 0x14);
      outMatrix[2] = fVar3 - *(float *)(iVar6 + 0x18);
      return;
    }
  }
  outMatrix[2] = fVar9;
  FUN_0043a210(outMatrix,outMatrix); // transformVector
  return;
}