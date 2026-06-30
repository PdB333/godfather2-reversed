// FUNC_NAME: BlendNode::evaluate

// Reconstructed from Ghidra decompiled output at 0x005ff280
// The function is part of the animation blend node evaluation.
// It appears to handle swapping of input pointers (likely for blending)
// and updates local transform and distance.

void __thiscall BlendNode::evaluate(BlendNode* thisPtr)
{
  int* piVar1;
  int* piVar2;
  uint uVar3;
  char cVar4;
  undefined4 uVar5;
  undefined4* puVar6;
  int iVar7;
  float* extraout_EDX; // likely some global or parent transform
  float fVar8;
  float fVar9;
  float fVar10;

  // Check if the owner/controller is valid (+0x118)
  if (*(int*)((int)thisPtr + 0x118) != 0)
  {
    // First condition: if either left or right child is null (?), try to get child from something
    if ((*(int*)((int)thisPtr + 0x94) == 0) || (*(int*)((int)thisPtr + 0x9c) == 0))
    {
      // Call a function to fetch child data (maybe from a parent or blend tree)
      cVar4 = FUN_005fe2e0((int)thisPtr, (int)thisPtr + 0x88, (int)thisPtr + 0x94, 0);
      if ((cVar4 == '\0') &&
          (((*(int*)((int)thisPtr + 0x7c) == 0 || (*(int*)((int)thisPtr + 0x84) == 0)) &&
           (*(int**)((int)thisPtr + 0x118) != (int*)0x0))))
      {
        // Call vtable function at offset +0xc of object at +0x118 (probably get blend weight)
        uVar5 = (**(code**)(**(int**)((int)thisPtr + 0x118) + 0xc))(*(undefined4*)((int)thisPtr + 0x120));
        // Convert or store the result
        FUN_005f7ba0(uVar5);
      }
    }

    // Double buffer pointer swapping: shift chain of input pointers
    // In this engine, blend nodes likely have multiple inputs, and this swaps them to update
    // Swaps: +0x70 <-> +0x7c, then +0x7c <-> +0x88, then +0x88 <-> +0x94
    // This is a typical "shift" or "blend" operation

    piVar1 = (int*)((int)thisPtr + 0x7c); // pointer to input B?
    piVar2 = (int*)((int)thisPtr + 0x70); // pointer to input A?
    // Swap A and B
    if (piVar2 != piVar1)
    {
      iVar7 = *piVar1;
      if (*piVar2 != iVar7)
      {
        if (*piVar2 != 0)
        {
          FUN_004daf90(piVar2); // release/reference decrement
        }
        *(int*)((int)thisPtr + 0x70) = iVar7;
        if (iVar7 != 0)
        {
          *(undefined4*)((int)thisPtr + 0x74) = *(undefined4*)(iVar7 + 4);
          *(int**)(iVar7 + 4) = (int*)((int)thisPtr + 0x70);
        }
      }
    }

    // Next swap: B <-> C (+0x88)
    piVar2 = (int*)((int)thisPtr + 0x88); // pointer to input C?
    *(undefined4*)((int)thisPtr + 0x78) = *(undefined4*)((int)thisPtr + 0x84);
    if (piVar1 != piVar2)
    {
      iVar7 = *piVar2;
      if (*piVar1 != iVar7)
      {
        if (*piVar1 != 0)
        {
          FUN_004daf90(piVar1);
        }
        *piVar1 = iVar7;
        if (iVar7 != 0)
        {
          *(undefined4*)((int)thisPtr + 0x80) = *(undefined4*)(iVar7 + 4);
          *(int**)(iVar7 + 4) = piVar1;
        }
      }
    }

    // Next swap: C <-> D (+0x94)
    *(undefined4*)((int)thisPtr + 0x84) = *(undefined4*)((int)thisPtr + 0x90);
    if (piVar2 != (int*)((int)thisPtr + 0x94))
    {
      iVar7 = *(int*)((int)thisPtr + 0x94);
      if (*piVar2 != iVar7)
      {
        if (*piVar2 != 0)
        {
          FUN_004daf90(piVar2);
        }
        *piVar2 = iVar7;
        if (iVar7 != 0)
        {
          *(undefined4*)((int)thisPtr + 0x8c) = *(undefined4*)(iVar7 + 4);
          *(int**)(iVar7 + 4) = piVar2;
        }
      }
    }
    *(undefined4*)((int)thisPtr + 0x90) = *(undefined4*)((int)thisPtr + 0x9c);

    // Update blend node (likely recalculate blended transforms)
    FUN_005f5ce0();

    // If either input pair is valid, copy the transform from the valid input
    // Note: piVar1 points to input B, and piVar2 now points to input D? Actually after swaps,
    // the code uses the original piVar1 and piVar2 which point to +0x7c and +0x88 respectively.
    // But after swaps, the actual values have shifted.
    if (((*piVar1 != 0) && (puVar6 = *(undefined4**)((int)thisPtr + 0x84), puVar6 != (undefined4*)0x0))
        || ((*(int*)((int)thisPtr + 0x70) != 0 &&
            (puVar6 = *(undefined4**)((int)thisPtr + 0x78), puVar6 != (undefined4*)0x0))))
    {
      // Copy the vector from the valid input to the node's local transform (+0x60)
      *(undefined4*)((int)thisPtr + 0x60) = *puVar6;
      *(undefined4*)((int)thisPtr + 0x64) = puVar6[1];
      *(undefined4*)((int)thisPtr + 0x68) = puVar6[2];
    }

    // Another update (probably matrix multiply or other)
    FUN_00414aa0();

    // If the "result" input is valid, update the node's final transform and compute distance
    if ((*piVar2 != 0) && (puVar6 = *(undefined4**)((int)thisPtr + 0x90), puVar6 != (undefined4*)0x0))
    {
      // Copy reference transform to +0x10 (maybe world position)
      *(undefined4*)((int)thisPtr + 0x10) = *puVar6;
      *(undefined4*)((int)thisPtr + 0x14) = puVar6[1];
      *(undefined4*)((int)thisPtr + 0x18) = puVar6[2];

      // Compute distance from extraout_EDX (likely parent or world space) to this node's position
      fVar10 = extraout_EDX[2] - *(float*)((int)thisPtr + 0x18);
      fVar9 = extraout_EDX[1] - *(float*)((int)thisPtr + 0x14);
      fVar8 = *extraout_EDX - *(float*)((int)thisPtr + 0x10);
      *(float*)((int)thisPtr + 0xc4) = sqrtf(fVar10 * fVar10 + fVar9 * fVar9 + fVar8 * fVar8);
      *(undefined4*)((int)thisPtr + 0xc0) = 0; // some flag

      // Advance the frame/state index if possible
      if (*(int**)((int)thisPtr + 0x118) != (int*)0x0)
      {
        uVar3 = *(uint*)((int)thisPtr + 0x120);
        iVar7 = (**(code**)(**(int**)((int)thisPtr + 0x118) + 8))();
        if (uVar3 < iVar7 - 1U)
        {
          *(uint*)((int)thisPtr + 0x120) = uVar3 + 1;
        }
      }

      // Call user callback if set
      if (*(code**)((int)thisPtr + 0xa4) != (code*)0x0)
      {
        (**(code**)((int)thisPtr + 0xa4))((int)thisPtr, (int)thisPtr + 0x70, piVar1, piVar1, piVar2);
      }
    }

    // Final cleanup call
    FUN_005fea70(0);
  }
  return;
}