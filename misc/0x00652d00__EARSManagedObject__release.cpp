// FUNC_NAME: EARSManagedObject::release
void EARSManagedObject::release(void)
{
  int *piVar1;
  int *piVar2;

  // Release refcounted object at +0x64
  piVar2 = *(int **)(this + 100); // +0x64
  if (piVar2 != (int *)0x0) {
    piVar1 = piVar2 + 2; // refcount field at offset 8 (after vtable)
    *piVar1 = *piVar1 - 1;
    if (*piVar1 == 0) {
      (**(code **)(*piVar2 + 8))(); // call vtable[2] (destructor/release)
    }
  }

  // Adjust global allocation counter using value at +0x54
  if (*(int *)(this + 0x54) != 0) {
    g_totalAllocatedSize -= *(int *)(this + 0x54);
  }

  // Free the raw buffer at +0x5c
  free(*(void **)(this + 0x5c));

  // Release refcounted objects at +0x2c
  piVar2 = *(int **)(this + 0x2c);
  if (piVar2 != (int *)0x0) {
    piVar1 = piVar2 + 2;
    *piVar1 = *piVar1 - 1;
    if (*piVar1 == 0) {
      (**(code **)(*piVar2 + 8))();
    }
  }

  // Release refcounted objects at +0x28
  piVar2 = *(int **)(this + 0x28);
  if (piVar2 != (int *)0x0) {
    piVar1 = piVar2 + 2;
    *piVar1 = *piVar1 - 1;
    if (*piVar1 == 0) {
      (**(code **)(*piVar2 + 8))();
    }
  }

  // Release refcounted objects at +0x24
  piVar2 = *(int **)(this + 0x24);
  if (piVar2 != (int *)0x0) {
    piVar1 = piVar2 + 2;
    *piVar1 = *piVar1 - 1;
    if (*piVar1 == 0) {
      (**(code **)(*piVar2 + 8))();
    }
  }

  // Release refcounted objects at +0x20
  piVar2 = *(int **)(this + 0x20);
  if (piVar2 != (int *)0x0) {
    piVar1 = piVar2 + 2;
    *piVar1 = *piVar1 - 1;
    if (*piVar1 == 0) {
      (**(code **)(*piVar2 + 8))();
    }
  }

  return;
}