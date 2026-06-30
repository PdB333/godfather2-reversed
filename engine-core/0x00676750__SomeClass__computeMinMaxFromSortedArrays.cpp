// FUNC_NAME: SomeClass::computeMinMaxFromSortedArrays
// Address: 0x00676750
// Role: Computes min and max (assuming sorted arrays) from two arrays, stores results in object at offsets +0x38/+0x3c and +0x40/+0x44.
// First array pointer is passed via EAX register (__fastcall or custom ABI), second via ecx/stack.
void __thiscall SomeClass::computeMinMaxFromSortedArrays(int* array1, int* array2, int count)
{
  int minVal, maxVal;
  int prevVal, curVal;
  int iteration = 0;

  do {
    // Initialize with first element of current array
    minVal = *array1;          // iVar5
    maxVal = *array1;          // iVar3 (also acts as "last element")
    prevVal = *array1;         // iVar2
    int idx = 1;               // iVar4

    if (0 < count) {
      do {
        curVal = array1[idx];  // iVar1
        maxVal = curVal;       // iVar3 = iVar1
        if ((curVal <= prevVal) && (maxVal = prevVal, curVal < minVal)) {
          minVal = curVal;
        }
        idx++;
        prevVal = maxVal;      // iVar2 = iVar3
      } while (idx <= count);
    }

    if (iteration == 0) {
      // Store first min/max pair (assumed sorted: min = first, max = last)
      *(int*)((int)this + 0x38) = minVal;  // field1_min
      *(int*)((int)this + 0x3c) = maxVal;  // field1_max
      array1 = array2; // switch to second array for next iteration (in_EAX = param_2)
    }
    else {
      *(int*)((int)this + 0x40) = minVal;  // field2_min
      *(int*)((int)this + 0x44) = maxVal;  // field2_max
    }
    iteration++;
  } while (iteration < 2);
}