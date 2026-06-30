// FUNC_NAME: MemoryPool::deallocate
undefined1 * __thiscall MemoryPool::deallocate(int this, int ptr, uint size)
{
  uint in_EAX;
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  puVar1 = (undefined1 *)FUN_00673070();
  if (ptr != 0) {
    if (in_EAX < size) {
      size = in_EAX;
    }
    if (0 < (int)size) {
      puVar2 = puVar1;
      do {
        *puVar2 = puVar2[ptr - (int)puVar1];
        puVar2 = puVar2 + 1;
        size = size - 1;
      } while (size != 0);
    }
    *(undefined4 *)(*(int *)(this + 0xc) + *(int *)(ptr + -8) * 4) = 0;
    *(int *)(this + 4) = *(int *)(this + 4) + -1;
    (*DAT_01206694)(ptr + -0x10);
  }
  return puVar1;
}