// FUNC_NAME: releaseResources
void __fastcall releaseResources(uint *param_1)
{
  // param_1 is assumed to point to a struct with fields:
  // +0x00: first object/resource (uint)
  // +0x0C: second object/resource (uint)
  // +0x10: pointer to a releaser object that has a vtable
  // The releaser vtable has methods at offsets:
  //   +0x04: release(uint object, int flags)
  //   +0x0C: destroy()

  // Release the first object (ID 0)
  (**(void (__fastcall **)(uint, int))(**(int **)(param_1[4]) + 4))(param_1[0], 0);

  // Conditionally release the second object
  if (param_1[3] != 0) {
    (**(void (__fastcall **)(uint, int))(**(int **)(param_1[4]) + 4))(param_1[3], 0);
  }

  // Destroy the releaser itself (e.g. free memory)
  (**(void (__fastcall **)())(**(int **)(param_1[4]) + 0xC))();
}