// FUNC_NAME: Entity::cleanup
void __thiscall Entity::cleanup(void)
{
  int iVar1;

  // Release sub-resources if pointer at +0x98 is non-zero
  if (*(int *)(this + 0x98) != 0) {
    sub_00d06250();
    sub_00d06400();
  }

  // Release object at +0xa0 (via virtual destructor with param 1)
  if (*(void **)(this + 0xa0) != (void *)0x0) {
    (*(code (__thiscall *)(int)) * (*(void **)(this + 0xa0)))(1);
    *(void **)(this + 0xa0) = 0;
  }

  // Release object at +0x9c
  if (*(void **)(this + 0x9c) != (void *)0x0) {
    (*(code (__thiscall *)(int)) * (*(void **)(this + 0x9c)))(1);
    *(void **)(this + 0x9c) = 0;
  }

  // Release object at +0xa8
  if (*(void **)(this + 0xa8) != (void *)0x0) {
    (*(code (__thiscall *)(int)) * (*(void **)(this + 0xa8)))(1);
    *(void **)(this + 0xa8) = 0;
  }

  // Release object at +0xa4
  if (*(void **)(this + 0xa4) != (void *)0x0) {
    (*(code (__thiscall *)(int)) * (*(void **)(this + 0xa4)))(1);
    *(void **)(this + 0xa4) = 0;
  }

  // Release and delete object at +0x98
  iVar1 = *(int *)(this + 0x98);
  if (iVar1 != 0) {
    sub_00d08d20();
    sub_009c8eb0(iVar1);
    *(int *)(this + 0x98) = 0;
  }

  // Release object at +0xac
  if (*(void **)(this + 0xac) != (void *)0x0) {
    (*(code (__thiscall *)(int)) * (*(void **)(this + 0xac)))(1);
    *(void **)(this + 0xac) = 0;
  }

  // If flag at +0x94 is false and pointer at +0x90 is non-null, call vfunc+0xc on it
  if ((*(char *)(this + 0x94) == '\0') && (*(int **)(this + 0x90) != (int *)0x0)) {
    (**(code (__thiscall *)(void)) * (*(int **)(this + 0x90) + 3))();
  }

  // Zero the pointer at +0x90
  *(int **)(this + 0x90) = 0;
  
  // Clear global flag
  DAT_01205887 = 0;
}