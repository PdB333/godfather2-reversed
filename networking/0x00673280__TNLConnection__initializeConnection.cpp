// FUNC_NAME: TNLConnection::initializeConnection
undefined4 * __thiscall TNLConnection::initializeConnection(int this, int param_2)

{
  undefined4 *in_EAX;
  undefined4 *puVar1;
  undefined4 extraout_ECX;
  int iVar2;
  undefined4 *puVar3;
  
  if (this == 0) {
    *in_EAX = 10000;
    return (undefined4 *)0x0;
  }
  *in_EAX = 0;
  puVar1 = (undefined4 *)FUN_00671190();  // Allocate memory for connection object
  puVar1[1] = extraout_ECX;  // +0x04: vtable pointer
  puVar1[0x60] = param_2;    // +0x180: store parameter (likely packet window or connection state)
  *puVar1 = 0x5a1234a5;      // +0x00: magic number for connection validation
  puVar1[0x16] = *(undefined4 *)(param_2 + 0xc0);  // +0x58: copy from param_2+0xC0
  puVar1[0x5b] = 0xffffffff; // +0x16C: initialize to -1
  puVar1[0x5a] = 0xffffffff; // +0x168: initialize to -1
  puVar1[0x142] = 0xa5fedc5a; // +0x508: another magic number
  puVar1[0x41] = 0;          // +0x104: clear
  *(undefined2 *)(puVar1 + 0x42) = 0;  // +0x108: clear 2 bytes
  puVar1[0x61] = 0;          // +0x184: clear
  puVar1[0x46] = 0;          // +0x118: clear
  puVar1[0x47] = 0;          // +0x11C: clear
  puVar1[0xc] = 0;           // +0x30: clear
  puVar1[0xd] = 0;           // +0x34: clear
  puVar1[0x14] = 0;          // +0x50: clear
  puVar1[0x15] = 0;          // +0x54: clear
  puVar1[8] = 0;             // +0x20: clear
  puVar1[9] = 0;             // +0x24: clear
  puVar1[0xe] = 0;           // +0x38: clear
  puVar1[0xf] = 0;           // +0x3C: clear
  puVar1[0x10] = 0;          // +0x40: clear
  puVar1[0x11] = 0;          // +0x44: clear
  puVar1[0x12] = 0;          // +0x48: clear
  puVar1[0x13] = 0;          // +0x4C: clear
  puVar1[0x17] = *(undefined4 *)(param_2 + 0x68);  // +0x5C: copy from param_2+0x68
  *(undefined2 *)(puVar1 + 0x18) = *(undefined2 *)(param_2 + 0x6c);  // +0x60: copy 2 bytes
  *(undefined2 *)((int)puVar1 + 0x62) = *(undefined2 *)(param_2 + 0x6e);  // +0x188: copy 2 bytes
  puVar3 = puVar1 + 0x62;    // Start at +0x188
  for (iVar2 = 0x95; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0xffffffff;    // Initialize 0x95 * 4 = 0x254 bytes to -1 (packet window slots?)
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)(puVar1[0x60] + 0x60) = 0xffff;  // Set param_2+0x60 to 0xFFFF
  *(undefined2 *)(puVar1[0x60] + 0x62) = 0xffff;  // Set param_2+0x62 to 0xFFFF
  if (*(int *)(puVar1[0x60] + 0x20) != 0) {
    *(int *)(*(int *)(puVar1[0x60] + 0x20) + 0xa8) = param_2;  // Link back to param_2
  }
  puVar1[6] = 0;             // +0x18: clear
  return puVar1;
}