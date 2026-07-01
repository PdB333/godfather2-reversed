// FUNC_NAME: Entity::getSomeIdOrHandle
int __fastcall Entity::getSomeIdOrHandle(int thisPtr)
{
  int *piVar1;
  int iVar2;
  
  if (*(char *)(thisPtr + 0x1a5) != '\0') {
    piVar1 = (int *)(thisPtr + 0x1cc);
    // Check if the 16-byte block at +0x1CC is either a known magic value or all zeros
    if ((((((*(int *)(thisPtr + 0x1cc) == -0x45245246) && (*(int *)(thisPtr + 0x1d0) == -0x41104111)
           ) && (*(int *)(thisPtr + 0x1d4) == -0x153ea5ab)) &&
         (*(int *)(thisPtr + 0x1d8) == -0x6eeff6ef)) ||
        (((*piVar1 == 0 && (*(int *)(thisPtr + 0x1d0) == 0)) &&
         ((*(int *)(thisPtr + 0x1d4) == 0 && (*(int *)(thisPtr + 0x1d8) == 0)))))) &&
       // Also check the 16-byte block at +0x64 (offset 100) for same magic or zeros
       ((((piVar1 = (int *)(thisPtr + 100), *(int *)(thisPtr + 100) == -0x45245246 &&
          (*(int *)(thisPtr + 0x68) == -0x41104111)) &&
         ((*(int *)(thisPtr + 0x6c) == -0x153ea5ab && (*(int *)(thisPtr + 0x70) == -0x6eeff6ef))))
        || ((((*piVar1 == 0 && (*(int *)(thisPtr + 0x68) == 0)) && (*(int *)(thisPtr + 0x6c) == 0))
            && (*(int *)(thisPtr + 0x70) == 0)))))) {
      // If both blocks are magic or zero, check the value at +0x1C4
      if (((*(int *)(thisPtr + 0x1c4) != 0) && (*(int *)(thisPtr + 0x1c4) != 0x48)) &&
         (*(int *)(thisPtr + 0x1c4) != 0)) {
        return *(int *)(thisPtr + 0x1c4) + -0x48;
      }
    }
    else {
      // Otherwise, call a helper function with the pointer to +0x1CC
      iVar2 = FUN_00446100(piVar1,0);
      if (iVar2 != 0) {
        return iVar2;
      }
    }
  }
  return 0;
}