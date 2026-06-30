// FUNC_NAME: SomeClass::processListenersOrCallbacks
void FUN_005693a0(int this, undefined4 *param_2)
{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 *local_8;
  uint local_4;
  
  iVar1 = param_2[0x41]; // param_2 + 0x104 - likely a count or flag
  param_2[0x42] = 6; // param_2 + 0x108 - set some state to 6
  local_4 = 0;
  if (*(int *)(this + 0x1c) != 0) { // this+0x1c is a count of something
    local_8 = (undefined4 *)(this + 8); // this+8 is an array of pointers
    do {
      if (iVar1 == 0) {
        // Call a virtual function on param_2 (likely a listener/callback interface)
        (**(code **)(*(int *)*local_8 + 8))(param_2);
      }
      uVar4 = 0;
      puVar3 = param_2;
      if (param_2[0x41] != 0) { // if count/flag is non-zero
        do {
          piVar2 = (int *)puVar3[1]; // get pointer from param_2+4
          *piVar2 = *piVar2 + 1; // increment reference count
          // Call virtual function on the object pointed to by local_8
          (*(code *)**(undefined4 **)*local_8)(piVar2);
          *piVar2 = *piVar2 + -1; // decrement reference count
          if (*piVar2 == 0) {
            // If ref count reached 0, call destructor (vtable+0x18)
            (**(code **)(*(int *)piVar2[0x43] + 0x18))(piVar2);
          }
          uVar4 = uVar4 + 1;
          puVar3 = puVar3 + 1;
        } while (uVar4 < (uint)param_2[0x41]);
      }
      local_8 = local_8 + 1;
      local_4 = local_4 + 1;
    } while (local_4 < *(uint *)(this + 0x1c));
  }
  return;
}