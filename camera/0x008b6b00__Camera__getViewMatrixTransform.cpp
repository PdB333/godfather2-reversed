// FUNC_NAME: Camera::getViewMatrixTransform
undefined8 * __thiscall Camera::getViewMatrixTransform(Camera *this, float *outTransform)
{
  char type;
  float halfSize;
  int viewport;
  undefined8 *puVar4;
  
  type = *(char *)(this + 0x2c8);
  if (type == '\x01') {
    puVar4 = FUN_00471610();
    *(undefined8 *)outTransform = *puVar4;
    outTransform[2] = *(float *)(puVar4 + 1);
    return puVar4;
  }
  if (type != '\x02') {
    if (type != '\x03') {
      viewport = FUN_00471610();
      *(undefined8 *)outTransform = *(undefined8 *)(viewport + 0x20);
      puVar4 = *(undefined8 **)(viewport + 0x28);
      outTransform[2] = (float)puVar4;
      return puVar4;
    }
    viewport = FUN_00471610();
    *(undefined8 *)outTransform = *(undefined8 *)(viewport + 0x20);
    halfSize = DAT_00e44564;
    outTransform[2] = *(float *)(viewport + 0x28);
    *outTransform = halfSize - *outTransform;
    outTransform[1] = halfSize - outTransform[1];
    outTransform[2] = halfSize - outTransform[2];
    return (undefined8 *)(viewport + 0x20);
  }
  puVar4 = FUN_00471610();
  *(undefined8 *)outTransform = *puVar4;
  halfSize = DAT_00e44564;
  puVar4 = *(undefined8 **)(puVar4 + 1);
  outTransform[2] = (float)puVar4;
  *outTransform = halfSize - *outTransform;
  outTransform[1] = halfSize - outTransform[1];
  outTransform[2] = halfSize - outTransform[2];
  return puVar4;
}