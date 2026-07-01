// FUNC_NAME: Point3D::fromTransformAndDirection
void Point3D::fromTransformAndDirection(int transformPtr, undefined4 *param2, undefined8 *outStruct)
{
  *outStruct = *(undefined8 *)(transformPtr + 8);
  *(undefined4 *)(outStruct + 1) = *(undefined4 *)(transformPtr + 0x10);
  *(undefined8 *)((int)outStruct + 0xc) = *(undefined8 *)(transformPtr + 0x18);
  *(undefined4 *)((int)outStruct + 0x14) = *(undefined4 *)(transformPtr + 0x20);
  *(float *)(outStruct + 3) = SQRT(*(float *)(transformPtr + 0x14));
  *(undefined4 *)((int)outStruct + 0x1c) = *param2;
  *(undefined4 *)(outStruct + 4) = **(undefined4 **)(transformPtr + 0x24);
  *(undefined4 *)((int)outStruct + 0x24) = *(undefined4 *)(*(int *)(transformPtr + 0x24) + 4);
  return;
}