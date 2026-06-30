// FUNC_NAME: MobfacePresetInstance::setPartOption(unsigned int)
// Function address: 0x004ec2b0
// Replaces a managed child object (smart pointer) in this preset instance.
// Updates parent's back pointer and handles ref counting.

void MobfacePresetInstance::setPartOption(undefined4 param_1)
{
  int *piVar1;      // ref count pointer
  int *piVar2;      // temp pointer
  int iVar3;        // parent pointer
  int iVar4;        // new child pointer
  undefined4 uVar5; // constant placeholder
  undefined4 *puVar6; // newly allocated child
  undefined4 local_20; // allocator parameters
  undefined4 local_1c;
  undefined4 local_18;

  // Only proceed if parent pointer (this+0x10) exists
  if (*(int *)(this + 0x10) != 0) {
    // Release old child (this+0x14) if any
    piVar2 = *(int **)(this + 0x14);
    if (piVar2 != (int *)0x0) {
      piVar1 = piVar2 + 1; // ref count at offset +4
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        // Call destructor via vtable+4
        (**(code **)(*piVar2 + 4))();
      }
      *(undefined4 *)(this + 0x14) = 0;
    }

    // Allocate new child (size 0x30 = 48 bytes)
    puVar6 = (undefined4 *)FUN_009c8f80();              // get allocator
    local_20 = 2;                                        // alignment flags?
    local_1c = 0x10;
    local_18 = 0;
    puVar6 = (undefined4 *)(**(code **)*puVar6)(0x30, &local_20); // allocate

    uVar5 = DAT_00e2b1a4; // constant (possibly 0.0f)
    if (puVar6 == (undefined4 *)0x0) {
      puVar6 = (undefined4 *)0x0;
    }
    else {
      puVar6[1] = 0;                                  // +0x04: ref count = 0
      *puVar6 = &PTR_FUN_00e372b4;                     // +0x00: vtable pointer
      puVar6[8] = 0;                                   // +0x20: uninitialized
      puVar6[4] = uVar5;                               // +0x10
      puVar6[5] = uVar5;                               // +0x14
      puVar6[6] = uVar5;                               // +0x18
      puVar6[7] = uVar5;                               // +0x1c
    }
    *(undefined4 **)(this + 0x14) = puVar6; // store new child

    FUN_004ec1c0(param_1); // additional initialization using param_1

    // Re-initialize child fields (overwrites what FUN_004ec1c0 may have set)
    uVar5 = DAT_00e2b1a4;
    iVar3 = *(int *)(this + 0x14);
    local_20 = DAT_00e2b1a4; // dead stores
    local_1c = DAT_00e2b1a4;
    *(undefined4 *)(iVar3 + 0x10) = DAT_00e2b1a4;
    *(undefined4 *)(iVar3 + 0x14) = uVar5;
    *(undefined4 *)(iVar3 + 0x18) = uVar5;
    *(undefined4 *)(iVar3 + 0x1c) = uVar5;

    // Now update parent's child pointer (parent at this+0x10)
    iVar3 = *(int *)(this + 0x10); // parent (this+0x10)
    iVar4 = *(int *)(this + 0x14); // new child (this+0x14)
    if (iVar3 != 0) {
      // Release parent's existing child at +0x20
      if (*(int *)(iVar3 + 0x20) != 0) {
        piVar2 = (int *)(*(int *)(iVar3 + 0x20) + 4);
        *piVar2 = *piVar2 + -1;
        if ((*(int **)(iVar3 + 0x20))[1] == 0) {
          (**(code **)(**(int **)(iVar3 + 0x20) + 4))();
        }
        *(undefined4 *)(iVar3 + 0x20) = 0;
      }
      // Point parent's child slot to new child
      *(int *)(iVar3 + 0x20) = iVar4;
      if (iVar4 != 0) {
        // Increment ref count of new child (for the parent's reference)
        *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 1;
      }
    }

    // Increment ref count of new child (for this object's reference)
    piVar2 = (int *)(*(int *)(this + 0x14) + 4);
    *piVar2 = *piVar2 + 1;
  }
  return;
}