// FUNC_NAME: EARSObject::getWorldTransform
undefined8 * __thiscall EARSObject::getWorldTransform(int this, float *outTransform)
{
  char typeFlag;
  float fVar2;
  int iVar3;
  undefined8 *puVar4;
  
  typeFlag = *(char *)(this + 0x2b0); // +0x2b0: object type flag (1=static, 2=dynamic, 3=character)
  if (typeFlag == '\x01') {
    // Static object: get transform from shared data
    puVar4 = (undefined8 *)FUN_00471610(); // getStaticTransformData
    *(undefined8 *)outTransform = *puVar4;
    outTransform[2] = *(float *)(puVar4 + 1);
    return puVar4;
  }
  if (typeFlag != '\x02') {
    if (typeFlag != '\x03') {
      // Default/unknown type: get from object's own transform
      iVar3 = FUN_00471610(); // getObjectTransform
      *(undefined8 *)outTransform = *(undefined8 *)(iVar3 + 0x20);
      puVar4 = *(undefined8 **)(iVar3 + 0x28);
      outTransform[2] = (float)puVar4;
      return puVar4;
    }
    // Character type: get transform and mirror for character facing
    iVar3 = FUN_00471610(); // getCharacterTransform
    *(undefined8 *)outTransform = *(undefined8 *)(iVar3 + 0x20);
    fVar2 = DAT_00e44564; // world mirror axis value (likely -1.0 or 0.0)
    outTransform[2] = *(float *)(iVar3 + 0x28);
    *outTransform = fVar2 - *outTransform;
    outTransform[1] = fVar2 - outTransform[1];
    outTransform[2] = fVar2 - outTransform[2];
    return (undefined8 *)(iVar3 + 0x20);
  }
  // Dynamic object: get transform and mirror
  puVar4 = (undefined8 *)FUN_00471610(); // getDynamicTransform
  *(undefined8 *)outTransform = *puVar4;
  fVar2 = DAT_00e44564;
  puVar4 = *(undefined8 **)(puVar4 + 1);
  outTransform[2] = (float)puVar4;
  *outTransform = fVar2 - *outTransform;
  outTransform[1] = fVar2 - outTransform[1];
  outTransform[2] = fVar2 - outTransform[2];
  return puVar4;
}