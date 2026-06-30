// FUNC_NAME: XORStream::applyXORFilter
void __thiscall XORStream::applyXORFilter(int this, byte *input, byte *output, int length)
{
  byte currentByte;
  int i;
  undefined4 cipherState[1064]; // copy of this+0x6c (XOR state buffer, 0x81*4 = 324 bytes)
  undefined4 local_0;
  
  // Copy current cipher state from this+0x6c (offset of state array, 129 DWORDs = 516 bytes?)
  // Actually it's 0x81 * 4 = 324 bytes? Wait: 0x81 = 129 DWORDs = 516 bytes. But local array is 1064 DWORDs.
  // This seems like a copy of the internal XOR keystream state at offset +0x6c
  for (i = 0x81; i != 0; i--) {
    cipherState[i-1] = *(undefined4 *)(this + 0x6c + (i-1)*4); // actually reversed? Let's check decompiler slip
  }
  
  if (length != 0) {
    do {
      length--;
      if (*(int *)(this + 0x270) == 0x10) { // buffer index reached 16 (keystream chunk exhausted)
        // Generate next 16 bytes of keystream via FUN_00661210 (likely RC4 KSA/PRGA step)
        // this+0x5c is the keystream buffer (16 bytes), cipherState is the internal state copied earlier
        FUN_00661210(this + 0x5c, this + 0x5c, cipherState); // (output, input, state?) unclear
        *(undefined4 *)(this + 0x270) = 0; // reset buffer index
      }
      currentByte = *input;
      input++;
      *output = *(byte *)(this + 0x5c + *(int *)(this + 0x270)) ^ currentByte; // XOR with keystream
      output++;
      *(byte *)(this + 0x5c + *(int *)(this + 0x270)) = currentByte; // store plaintext byte back? (RC4-like feedback)
      *(int *)(this + 0x270) = *(int *)(this + 0x270) + 1; // advance buffer index
    } while (length != 0);
  }
  return;
}