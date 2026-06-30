// FUNC_NAME: SortUtils::partitionMerge (address 0x005889d0)
// This function appears to be an internal partitioning/merging step for a sorting algorithm.
// It is called when the number of elements (computed from param_1 and in_EAX) exceeds 40.
// The algorithm splits the range into blocks of 8 elements and then calls FUN_00588c50
// to perform block swaps or merges. The logic is reminiscent of a multiway merge or
// in-place block swapping for stable partitioning.

// Note: The decompiler used "in_EAX" as a register variable; it likely holds the original
// 'this' pointer or an additional array end pointer. The actual C++ signature may be:
// static void partitionMerge(int* start, int* end, int* tempBuffer, int elementSize);
// but here elementSize is implicitly 4 (sizeof int). param_3 is passed through to the
// low-level block mover FUN_00588c50 and might be an element size or comparison context.

// FUN_00588c50 is a low-level block copy/move function (likely memmove or swap).
// It has multiple overloads or uses default parameters.

void __thiscall SortUtils::partitionMerge(int param_1, int param_2, undefined4 param_3)
{
  // in_EAX is assumed to hold a pointer to the end of the array or a pivot.
  // For reconstruction, we treat it as an implicit parameter passed in EAX.
  // This is likely the result of a previous calculation or a member variable.
  int arrayEnd; // in_EAX
  int elementCount;
  
  // Compute number of 4-byte elements between param_1 and arrayEnd
  elementCount = (arrayEnd - param_1) >> 2;
  
  if (elementCount > 40) {
    // Split into blocks of roughly (elementCount+1)/8 * 8 elements
    elementCount = elementCount + 1;                     // Round up
    elementCount = (elementCount + ((elementCount >> 31) & 7)) >> 3; // integer division by 8, rounding away from zero
    // elementCount is now the number of 8-element blocks (or block size in multiples of 8)
    
    // First block swap: copy from start to start + 8*elementCount
    FUN_00588c50(param_1, iVar1 * 8 + param_1, param_3);
    
    // Second block swap: copy from (param_2 - 4*elementCount) to (param_2 + 4*elementCount)
    FUN_00588c50(param_2 + iVar1 * -4, iVar1 * 4 + param_2, param_3);
    
    // Third block move: shift from end backwards by 8*elementCount
    FUN_00588c50(arrayEnd + iVar1 * -8); // single argument? Possibly memmove with implied size
    
    // Fourth block swap: copy from (param_1 + 4*elementCount) to (arrayEnd - 4*elementCount)
    FUN_00588c50(iVar1 * 4 + param_1, arrayEnd + iVar1 * -4, param_3);
    
    return;
  }
  
  // Base case: when the array is small (<= 40 elements), just call the low-level mover
  // for the whole input range.
  FUN_00588c50(param_1);
  return;
}