// FUNC_NAME: Matrix4x4::setRowColumn
void __thiscall Matrix4x4::setRowColumn(int param_1, int param_2, int param_3, undefined4 *param_4)
{
  undefined4 *puVar1;
  
  // Calculate offset: param_2 = row index (0-3), param_3 = column index (0-3)
  // Matrix is stored row-major: each row is 0x50 bytes (20 floats = 4x5? likely 4x4 with padding)
  // Each element is 4 bytes (float), 0x10 = 4 elements per column stride
  // +0x7c is offset to matrix data within a larger structure
  puVar1 = (undefined4 *)(param_3 * 0x10 + param_2 * 0x50 + 0x7c + param_1);
  *puVar1 = *param_4;          // Copy 16 bytes (4 floats) for this row/column position
  puVar1[1] = param_4[1];
  puVar1[2] = param_4[2];
  puVar1[3] = param_4[3];
  return;
}