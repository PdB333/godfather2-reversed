// FUNC_NAME: TNLConnection::computePacketChecksum
int __thiscall TNLConnection::computePacketChecksum(TNLConnection *this, void *param_1, int param_2)
{
  // this+0x08: pointer to internal checksum context structure
  int *context = *(int **)(this + 8);
  int count = context[3]; // context+0x0C: number of elements to process
  int sum = 0;
  int i = 0;
  if (count > 0) {
    do {
      // Process each element – param_1/param_2 passed unchanged (likely a buffer and size)
      int partial = FUN_00558070(param_1, param_2);
      sum += partial & 0xFF;
      i++;
    } while (i < count);
  }
  return sum;
}