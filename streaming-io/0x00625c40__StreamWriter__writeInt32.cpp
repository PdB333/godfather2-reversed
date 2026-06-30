// FUNC_NAME: StreamWriter::writeInt32
void StreamWriter::writeInt32(int param_1, undefined4 param_2)
{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 8);
  *puVar1 = 3;
  puVar1[1] = param_2;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
  return;
}