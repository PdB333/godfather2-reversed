// FUNC_NAME: Camera::collectVisibleObjectsInFrustum
void __thiscall Camera::collectVisibleObjectsInFrustum(int param_2)
{
  // +0x10: pointer to a frustum/camera data structure
  // +0x24: pointer to an array of collected object entries (grows dynamically)
  // +0x28: current count of collected entries
  // +0x2c: capacity of the array

  int *piVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  int local_dc;             // address of temporary allocation
  int local_d8;             // number of results from the virtual function call
  int local_d4;             // size of allocation in floats? (initially 0x80000000)
  int iStack_d0;            // saved alloc start
  int local_cc;             // loop counter
  int local_c8;             // copy of frustum pointer
  int *local_c4;            // pointer to object vtable/type
  float local_c0;           // center X
  float local_bc;           // center Y
  float local_b8;           // center Z
  float local_b4;           // center W? or half-size W? Actually used as sum for fourth component
  float local_b0;           // half-size X (difference)
  float local_ac;           // half-size Y
  float local_a8;           // half-size Z
  float local_a4;           // half-size W
  int *local_98;            // pointer to the list entry
  int local_94;             // this pointer saved
  unsigned char auStack_90[48]; // buffer for transform matrix (6x4? 12 floats)
  float fStack_60;          // used as array for center
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  unsigned char auStack_50[76]; // buffer for output data from virtual call

  local_94 = (int)this;
  // param_2 used as an argument to some initialization function (maybe flags)
  FUN_00bed560(param_2);

  // Global factor (likely 0.5f to compute half-size and center)
  local_b4 = DAT_00e2cd54; // +0x00? Actually used for both diff and sum

  iVar8 = *(int *)((int)this + 0x10); // frustum data structure
  *(undefined4 *)((int)this + 0x28) = 0; // reset count

  // Compute half-extents:
  local_b0 = (*(float *)(iVar8 + 0xb0) - *(float *)(iVar8 + 0xa0)) * local_b4;
  local_ac = (*(float *)(iVar8 + 0xb4) - *(float *)(iVar8 + 0xa4)) * local_b4;
  local_a8 = (*(float *)(iVar8 + 0xb8) - *(float *)(iVar8 + 0xa8)) * local_b4;
  local_a4 = (*(float *)(iVar8 + 0xbc) - *(float *)(iVar8 + 0xac)) * local_b4;

  // Compute center:
  local_c0 = (*(float *)(iVar8 + 0xb0) + *(float *)(iVar8 + 0xa0)) * local_b4;
  local_bc = (*(float *)(iVar8 + 0xb4) + *(float *)(iVar8 + 0xa4)) * local_b4;
  local_b8 = (*(float *)(iVar8 + 0xb8) + *(float *)(iVar8 + 0xa8)) * local_b4;
  local_b4 = (*(float *)(iVar8 + 0xbc) + *(float *)(iVar8 + 0xac)) * local_b4; // reusing local_b4 for center W

  local_cc = 0;
  local_c8 = iVar8; // keep frustum pointer

  // Iterate over all objects in the list at frustum+0xc0, count at +0xc4
  if (0 < *(int *)(iVar8 + 0xc4)) {
    do {
      // piVar7 points to the current list entry (pointer to object descriptor)
      piVar7 = *(int **)(*(int *)(iVar8 + 0xc0) + local_cc * 4);
      piVar1 = (int *)*piVar7; // dereference to get object's vtable/type ptr

      // Check object is valid and type ID == 0xb
      if ((piVar1 != (int *)0x0) && (piVar1[3] == 0xb)) {
        // Initialize allocation parameters
        local_dc = 0;
        local_d8 = 0;
        local_d4 = 0x80000000; // sentinel value meaning "not yet allocated"
        local_c4 = piVar1;
        local_98 = piVar7;

        // Custom memory allocation via TLS
        piVar2 = (int *)TlsGetValue(DAT_01139810);
        iVar3 = piVar2[8]; // current alloc offset
        if ((uint)piVar2[0xb] < iVar3 + 0x110U) {
          // Not enough space in current block, allocate new block
          iVar3 = (**(code **)(*piVar2 + 0x14))(0x110);
        } else {
          piVar2[8] = iVar3 + 0x110U;
        }

        // Store center into a temporary array for the virtual function call
        fStack_60 = local_c0;
        fStack_5c = local_bc;
        fStack_58 = local_b8;
        local_d4 = -0x7fffffc0; // change sentinel? Actually this is the count of floats? Odd.
        fStack_54 = local_b4;
        local_dc = iVar3; // allocation start address
        iStack_d0 = iVar3; // save alloc start for later deallocation

        // Lock critical section
        FUN_00aa5450(&DAT_00ef3f00);

        // Get the transform matrix associated with the object (piVar7[2] is some transform handle)
        FUN_00aa1e40(piVar7[2], auStack_90);

        // Virtual function call on the object (vtable offset 0x24)
        // Arguments: output buffer, pointer to frustum half-extents array, flags (0), &allocation descriptor
        (**(code **)(*piVar1 + 0x24))(auStack_50, &local_b0, 0, &local_dc);

        iVar3 = local_94;
        if (local_d8 != 0) {
          // Append results to the output array
          iVar6 = *(int *)(local_94 + 0x28);
          piVar7 = (int *)(local_94 + 0x24);
          iVar8 = local_d8 + iVar6;
          uVar4 = *(uint *)(local_94 + 0x2c) & 0x3fffffff;
          if ((int)uVar4 < iVar8) {
            iVar5 = uVar4 * 2;
            if (iVar5 <= iVar8) {
              iVar5 = iVar8;
            }
            // Resize the pointer array (element size 0xc = 3 ints)
            FUN_00aa4110(piVar7, iVar5, 0xc);
          }
          // Copy data: each entry = pointer to list entry, object property (offset 0x34), and value from result buffer
          piVar7 = (int *)(*piVar7 + iVar6 * 0xc);
          iVar6 = 0;
          *(int *)(iVar3 + 0x28) = iVar8; // update count
          iVar8 = local_c8;
          if (0 < local_d8) {
            do {
              *piVar7 = (int)local_98;
              piVar7[1] = local_c4[0xd]; // offset 0x34 from object (maybe a transform ID or index)
              piVar7[2] = *(int *)(local_dc + iVar6 * 4); // result element (e.g., vertex index)
              iVar6 = iVar6 + 1;
              piVar7 = piVar7 + 3;
            } while (iVar6 < local_d8);
          }
        }

        iVar3 = iStack_d0;
        // Restore allocation offset
        piVar7 = (int *)TlsGetValue(DAT_01139810);
        piVar7[8] = iVar3;
        if (iVar3 == piVar7[10]) {
          // If we reached the end of the block, free it
          (**(code **)(*piVar7 + 0x18))(iVar3);
        }

        iVar3 = local_d4;
        if (-1 < local_d4) {
          // Free any temporary memory used by the virtual function
          TlsGetValue(DAT_01139810);
          FUN_00aa26e0(local_dc, iVar3 * 4, 0x17);
        }
      }
      local_cc = local_cc + 1;
    } while (local_cc < *(int *)(iVar8 + 0xc4));
  }
  return;
}