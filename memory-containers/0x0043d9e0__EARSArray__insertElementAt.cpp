// FUNC_NAME: EARSArray::insertElementAt
int* EARSArray::insertElementAt(uint index)
{
  // this->buffer at +0x00, this->size at +0x04, this->capacity at +0x08
  // Element size is 0x1C (28 bytes = 7 int32s)
  if (this->size == this->capacity) {
    if (this->capacity == 0) {
      this->capacity = 1;
    } else {
      this->capacity *= 2;
    }
    this->grow(this->capacity);
  }

  char* base = (char*)this->buffer;
  if (index != this->size) {
    // Shift elements from index to size-1 one slot to the right
    int moveCount = this->size - index;
    char* dst = base + (index + 1) * 0x1C;
    char* src = base + index * 0x1C;
    for (int i = 0; i < moveCount; i++) {
      // Copy 7 int32s (28 bytes) from src to dst, moving backwards from the end?
      // Actually the loop goes from size-1 down to index? The decompiled loop works on swapped offsets.
      // The original loops from last element down to index, copying each element to the next slot.
      // We'll implement a standard memmove (but the decompiled is a manual loop).
      // For correctness, we replicate the backwards copy.
    }
    // But to simplify, we use memmove:
    // memmove(dst, src, moveCount * 0x1C);
    // However, the original code copies element by element from top down.
    // We'll replicate it.
    int* dstInt = (int*)(base + (this->size) * 0x1C);
    int* srcInt = (int*)(base + (this->size - 1) * 0x1C);
    for (int i = 0; i < moveCount; i++) {
      // Copy 7 ints from srcInt to dstInt (both pointing to start of element)
      dstInt[0] = srcInt[0];
      dstInt[1] = srcInt[1];
      dstInt[2] = srcInt[2];
      dstInt[3] = srcInt[3];
      dstInt[4] = srcInt[4];
      dstInt[5] = srcInt[5];
      dstInt[6] = srcInt[6];
      dstInt -= 7; // move to previous element? Wait, this is tricky.
    }
    // Actually the decompiled code uses param_1 and uVar1 and a loop that decrements iVar4 (offset).
    // Let's reinterpret step by step.
  }

  // At the end, zero out the element at index and increment size.
  int* elem = (int*)(base + index * 0x1C);
  elem[0] = 0;
  elem[1] = 0;
  elem[2] = 0;
  elem[3] = 0;
  elem[4] = 0;
  elem[5] = 0;
  elem[6] = 0;
  this->size++;
  return elem;
}

// However, the decompiled code shows a branch where if index != size, it performs a complex shift.
// The shift copies elements from index-1 to index? Actually it's inserting at a given index, shifting existing elements up.
// The code has two blocks: first it copies element at index-1 into the slot at index (which is the new element's slot)? No.

// Let's re-analyze from the decompiled:

// int FUN_0043d9e0(uint param_1)
// {
//   int *in_EAX;
//   uint uVar1;
//   int iVar2;
//   undefined4 *puVar3;
//   int iVar4;
//   
//   iVar4 = in_EAX[2];   // capacity
//   if (in_EAX[1] == iVar4) {  // size == capacity
//     if (iVar4 == 0) {
//       iVar4 = 1;
//     }
//     else {
//       iVar4 = iVar4 * 2;
//     }
//     FUN_0043dcf0(iVar4); // reallocate to new capacity
//   }
//   puVar3 = (undefined4 *)(*in_EAX + in_EAX[1] * 0x1c); // pointer to element after last (end)
//   if (param_1 != in_EAX[1]) {
//     // Inserting not at end
//     if (puVar3 != (undefined4 *)0x0) {
//       // Copy element at size-1 (last) to the end slot? Actually puVar3 points to end (size * 0x1c), which is beyond last element.
//       // So this copies what? puVar3[-7] is the last element? Let's compute: puVar3 = base + size*0x1c. puVar3[-7] is base + (size-1)*0x1c.
//       // So they copy the last element into the end slot (which is beyond current size). This is part of shifting.
//       *puVar3 = puVar3[-7];   // copy first 4 bytes
//       puVar3[1] = puVar3[-6]; // next 4
//       ...
//       puVar3[6] = puVar3[-1]; // last 4 bytes
//     }
//     uVar1 = in_EAX[1] - 1; // size-1
//     if (param_1 < uVar1) {
//       // More elements to shift
//       iVar4 = uVar1 * 0x1c; // offset of last element
//       iVar2 = uVar1 - param_1; // number of elements to shift
//       do {
//         puVar3 = (undefined4 *)(*in_EAX + iVar4); // pointer to current element
//         // Copy element from (puVar3 - 7) to puVar3 (i.e., copy element before to current)
//         if (puVar3 != puVar3 + -7) { // always true unless same
//           *puVar3 = puVar3[-7];
//           puVar3[1] = puVar3[-6];
//           ... up to puVar3[6] = puVar3[-1];
//         }
//         iVar4 = iVar4 + -0x1c; // move to previous element
//         iVar2 = iVar2 + -1;
//       } while (iVar2 != 0);
//     }
//     in_EAX[1] = in_EAX[1] + 1; // size++
//     puVar3 = (undefined4 *)(*in_EAX + param_1 * 0x1c); // pointer to insertion point
//     if (puVar3 != (undefined4 *)0x0) {
//       // Zero out all 7 fields
//       puVar3[3] = 0;
//       puVar3[2] = 0;
//       ...
//     }
//     return *in_EAX + param_1 * 0x1c; // return pointer to inserted element
//   }
//   // If inserting at end:
//   if (puVar3 != (undefined4 *)0x0) {
//     // Zero out the new element slot (which is after current end)
//     puVar3[3] = 0;
//     ...
//   }
//   iVar4 = in_EAX[1];
//   in_EAX[1] = iVar4 + 1; // size++
//   return *in_EAX + iVar4 * 0x1c; // return pointer to new element (old size)
// }

// So the algorithm:
// 1. Ensure capacity (grow if needed)
// 2. If inserting not at end:
//    - Move the last element to the new end slot (size+1)
//    - Then shift elements from (size-2) down to index to the right by one
//    - Then zero out element at index
//    - Increment size
//    - Return pointer to index
// 3. If inserting at end:
//    - Zero out new element slot (after current end)
//    - Increment size
//    - Return pointer to old end (new element)

// This is a typical insertion by shifting. The initial copy of last element to end is done before shifting others.

// Given the complexity, we'll produce a clean version with memmove for clarity, but note the manual copying in comments.

// We'll also need to define the "grow" function (FUN_0043dcf0). We'll assume it reallocates the buffer.

// Let's produce the final code with meaningful names.// FUNC_NAME: EARSArray::insertElementAt
int* EARSArray::insertElementAt(uint index)
{
    // Class layout:
    // +0x00: void* buffer (data pointer)
    // +0x04: int size
    // +0x08: int capacity
    // Elements are 0x1C (28) bytes each, consisting of 7 int32 values.

    // Ensure capacity
    if (this->size == this->capacity)
    {
        int newCapacity = (this->capacity == 0) ? 1 : (this->capacity * 2);
        grow(newCapacity);  // FUN_0043dcf0 - reallocates buffer
    }

    char* base = (char*)this->buffer;
    int elementSize = 0x1C;

    if (index != this->size)
    {
        // Inserting at a position before end: shift elements to make room
        // First, move the last element to the new end (one slot after current last)
        int lastIndex = this->size - 1;
        char* srcLast = base + lastIndex * elementSize;
        char* dstNewEnd = base + this->size * elementSize; // after current end

        // Copy the last element to the new end (7 ints)
        int* srcInt = (int*)srcLast;
        int* dstInt = (int*)dstNewEnd;
        dstInt[0] = srcInt[0];
        dstInt[1] = srcInt[1];
        dstInt[2] = srcInt[2];
        dstInt[3] = srcInt[3];
        dstInt[4] = srcInt[4];
        dstInt[5] = srcInt[5];
        dstInt[6] = srcInt[6];

        // Now shift elements from (lastIndex-1) down to index one slot to the right
        for (int i = lastIndex - 1; i >= (int)index; i--)
        {
            char* src = base + i * elementSize;
            char* dst = base + (i + 1) * elementSize;
            int* srcI = (int*)src;
            int* dstI = (int*)dst;
            dstI[0] = srcI[0];
            dstI[1] = srcI[1];
            dstI[2] = srcI[2];
            dstI[3] = srcI[3];
            dstI[4] = srcI[4];
            dstI[5] = srcI[5];
            dstI[6] = srcI[6];
        }

        // Now zero out the insertion slot
        int* elem = (int*)(base + index * elementSize);
        elem[0] = 0;
        elem[1] = 0;
        elem[2] = 0;
        elem[3] = 0;
        elem[4] = 0;
        elem[5] = 0;
        elem[6] = 0;

        this->size++; // size increased after shift
        return elem;
    }
    else
    {
        // Inserting at end: zero out the new element slot (already after current last)
        int* elem = (int*)(base + this->size * elementSize);
        elem[0] = 0;
        elem[1] = 0;
        elem[2] = 0;
        elem[3] = 0;
        elem[4] = 0;
        elem[5] = 0;
        elem[6] = 0;

        int oldSize = this->size;
        this->size++; // size becomes oldSize+1
        return (int*)(base + oldSize * elementSize);
    }
}