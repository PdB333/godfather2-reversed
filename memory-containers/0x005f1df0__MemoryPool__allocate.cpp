// FUNC_NAME: MemoryPool::allocate
undefined4 * MemoryPool::allocate(undefined4 param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int *unaff_EDI;
  bool bVar3;
  
  puVar2 = (undefined4 *)0x0;
  cVar1 = FUN_005f1790(); // check if pool is initialized
  if (cVar1 == '\0') {
    bVar3 = DAT_011a0f08 == 0; // free count
    if (bVar3) {
      FUN_005f1820(); // expand pool
      bVar3 = DAT_011a0f08 == 0;
    }
    if (!bVar3) {
      puVar2 = (undefined4 *)0x0;
      if ((DAT_011a0f00 != 0) && ((undefined4 **)DAT_011a0efc != &DAT_011a0efc)) {
        DAT_011a0f08 = DAT_011a0f08 + -1; // decrement free count
        puVar2 = DAT_011a0efc; // get free list head
        DAT_011a0efc = (undefined4 *)*DAT_011a0efc; // advance free list
      }
      FUN_005f5730(); // lock/unlock?
      cVar1 = FUN_005f2e40(param_1); // initialize allocation
      if (cVar1 != '\0') {
        puVar2[0x1d] = 0; // +0x74
        puVar2[0x21] = 0; // +0x84
        puVar2[0x22] = 0; // +0x88
        puVar2[0x23] = 0; // +0x8c
        *(undefined1 *)((int)puVar2 + 0x7b) = 0; // +0x7b
        puVar2[0x1f] = 0; // +0x7c
        puVar2[0x20] = 0; // +0x80
        puVar2[0xd] = *(undefined4 *)
                       (&DAT_011a0f14 + // pool type table
                       ((*(byte *)(puVar2[2] + 8) & 1) + (*(byte *)(*unaff_EDI + 7) & 1) * 2) * 4);
      }
      FUN_005dbc10(*(undefined1 *)(puVar2 + 0x19),puVar2[0x17],DAT_011a0efa); // set name?
    }
  }
  return puVar2;
}