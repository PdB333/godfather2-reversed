// FUNC_NAME: HeapAllocator::allocateBlock
int* HeapAllocator::allocateBlock(uint alignment, uint minSize, uint maxSize, int offset, uint flags)
{
  LPCRITICAL_SECTION lpCriticalSection;
  LPCRITICAL_SECTION p_Var1;
  int iVar2;
  float fVar3;
  char cVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  uint uVar12;
  uint local_14;
  
  uVar12 = flags;
  iVar2 = this;
  local_14 = 0;
  
  // Align minimum size to 16 bytes
  if (minSize < 0x10) {
    minSize = 0x10;
  }
  else {
    minSize = minSize + 0xf & 0xfffffff0;
  }
  
  flags = uVar12;
  
  // Align maximum size to 16 bytes
  if (maxSize < 0x10) {
    maxSize = 0x10;
  }
  
  do {
    // Try to find a free block in the free list
    for (; (flags & 1) != 0; flags = flags & 0xfffffffe | 4) {
      uVar11 = minSize + maxSize + 0xf + offset & 0xfffffff0;
      
      // Walk through free lists by size class
      for (piVar5 = *(int **)(this + 0x18); piVar5 != (int *)(this + 4); piVar5 = (int *)piVar5[5]) {
        for (piVar10 = (int *)piVar5[3]; piVar10 != piVar5; piVar10 = (int *)piVar10[3]) {
          if (((piVar10[1] & 1U) == 0) && (uVar7 = piVar10[1] & 0xfffffffe, uVar11 <= uVar7)) {
            // Found a suitable free block - remove it from free list
            *(int *)(piVar10[5] + 0x18) = piVar10[6];
            *(int *)(piVar10[6] + 0x14) = piVar10[5];
            iVar8 = *piVar10;
            piVar10[1] = piVar10[1] | 1;  // Mark as allocated
            iVar9 = ((iVar8 - minSize) + uVar7 + maxSize + -1 + offset & -maxSize) - offset;
            piVar10[2] = iVar9;
            if (iVar8 + uVar7 < iVar9 + minSize) {
              piVar10[2] = ((iVar8 - uVar11) + uVar7 + maxSize + -1 + offset & -maxSize) - offset;
            }
            iVar8 = (iVar8 - minSize) - piVar10[2];
            goto LAB_00649905;
          }
        }
      }
    }
    
    uVar6 = flags & 4;
    uVar11 = minSize;
    
    if ((uVar6 != 0) || (uVar11 = minSize + maxSize + 0xf + offset & 0xfffffff0, minSize <= uVar11)) {
      // Calculate size class index
      fVar3 = (float)(int)uVar11;
      if ((int)uVar11 < 0) {
        fVar3 = fVar3 + DAT_00e44578;
      }
      this = ((uint)fVar3 >> 0x17) - 0x7f;
      if (this < 6) {
        this = 6;
      }
      this = this - 6;
      if (7 < this) {
        this = 7;
      }
      
      if (this < 8) {
        piVar5 = (int *)(this * 0x20 + 0x78 + iVar2);
        do {
          for (piVar10 = (int *)piVar5[6]; piVar10 != piVar5; piVar10 = (int *)piVar10[6]) {
            uVar7 = piVar10[1] & 0xfffffffe;
            if ((uVar11 <= uVar7) && ((uVar6 == 0 || ((maxSize - 1 & *piVar10 + offset) == 0)))) {
              // Remove block from free list and mark as allocated
              *(int *)(piVar10[5] + 0x18) = piVar10[6];
              *(int *)(piVar10[6] + 0x14) = piVar10[5];
              piVar10[1] = piVar10[1] | 1;
              offset = (*piVar10 + maxSize + -1 + offset & -maxSize) - offset;
              iVar8 = (*piVar10 - offset) - minSize;
              piVar10[2] = offset;
              
LAB_00649905:
              // Check if we need to split the block
              if ((*(uint *)(iVar2 + 0x178) <= iVar8 + uVar7) &&
                 (piVar5 = (int *)(**(code **)(iVar2 + 0x18c))(iVar2, 0x20, *(undefined4 *)(iVar2 + 0x194)),
                 piVar5 != (int *)0x0)) {
                // Split block into two
                piVar5[4] = piVar10[4];
                *(int **)(piVar10[4] + 0xc) = piVar5;
                piVar5[3] = (int)piVar10;
                uVar7 = uVar7 - (iVar8 + uVar7);
                piVar10[4] = (int)piVar5;
                *piVar5 = *piVar10 + uVar7;
                piVar5[1] = (-uVar7 ^ piVar5[1]) & 1 ^ (piVar10[1] & 0xfffffffeU) - uVar7;
                piVar10[1] = (piVar10[1] ^ uVar7) & 1 ^ uVar7;
                piVar5[1] = piVar5[1] & 0xfffffffe;
                FUN_00649490();  // Insert into free list
              }
              
              uVar12 = piVar10[2] - *piVar10;
              if ((*(uint *)(iVar2 + 0x178) <= uVar12) &&
                 (piVar5 = (int *)(**(code **)(iVar2 + 0x18c))(iVar2, 0x20, *(undefined4 *)(iVar2 + 0x194)),
                 piVar5 != (int *)0x0)) {
                // Split block at the end
                piVar5[3] = piVar10[3];
                *(int **)(piVar10[3] + 0x10) = piVar5;
                piVar5[4] = (int)piVar10;
                piVar10[3] = (int)piVar5;
                iVar2 = *piVar10;
                *piVar5 = iVar2;
                piVar5[1] = (piVar5[1] ^ uVar12) & 1 ^ uVar12;
                *piVar10 = iVar2 + uVar12;
                piVar10[1] = (-uVar12 ^ piVar10[1]) & 1 ^ (piVar10[1] & 0xfffffffeU) - uVar12;
                piVar5[1] = piVar5[1] & 0xfffffffe;
                FUN_00649490();  // Insert into free list
              }
              return piVar10;
            }
          }
          this = this + 1;
          piVar5 = piVar5 + 8;
        } while (this < 8);
      }
    }
    
    // If we couldn't find a block, try to grow the heap
    if (uVar6 == 0) {
      fVar3 = (float)(int)uVar11;
      if ((int)uVar11 < 0) {
        fVar3 = fVar3 + DAT_00e44578;
      }
      uVar7 = ((uint)fVar3 >> 0x17) - 0x7f;
      if (uVar7 < 6) {
        uVar7 = 6;
      }
      uVar7 = uVar7 - 6;
      if (7 < uVar7) {
        uVar7 = 7;
      }
      
      piVar5 = *(int **)(uVar7 * 0x20 + 0x90 + iVar2);
      if (((piVar5[1] & 0xfffffffeU) < minSize) || ((maxSize - 1 & *piVar5 + offset) != 0)) {
        if (*(int *)(iVar2 + 0x198) == 0) {
          return (int *)0x0;
        }
        local_14 = local_14 + 1;
        if (*(uint *)(iVar2 + 0x1a0) <= local_14) {
          return (int *)0x0;
        }
        if (uVar11 < minSize) {
          return (int *)0x0;
        }
        
        // Try to grow the heap via callback
        iVar8 = *(int *)(*(int *)(iVar2 + 0x1b8) + 0x18);
        iVar9 = iVar8;
        if (0 < iVar8) {
          do {
            lpCriticalSection = *(LPCRITICAL_SECTION *)(iVar2 + 0x1b8);
            p_Var1 = lpCriticalSection + 1;
            p_Var1->DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&p_Var1->DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(lpCriticalSection);
            iVar9 = iVar9 + -1;
          } while (iVar9 != 0);
        }
        
        cVar4 = (**(code **)(iVar2 + 0x198))(iVar2, minSize, uVar11, *(undefined4 *)(iVar2 + 0x19c));
        
        if (0 < iVar8) {
          do {
            p_Var1 = *(LPCRITICAL_SECTION *)(iVar2 + 0x1b8);
            EnterCriticalSection(p_Var1);
            p_Var1 = p_Var1 + 1;
            p_Var1->DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&p_Var1->DebugInfo->Type + 1);
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
        }
        
        flags = uVar12;
        if (cVar4 == '\0') {
          return (int *)0x0;
        }
      }
      else {
        flags = 4;
      }
    }
    else {
      flags = flags & 0xfffffffb;
    }
  } while( true );
}