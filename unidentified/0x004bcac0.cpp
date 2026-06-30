// FUN_NAME: EARSArray::reserve

void __thiscall EARSArray::reserve(EARSArray* thisPtr, uint newCapacity)
{
  // thisPtr->mData at +0x00
  // thisPtr->mCount at +0x04
  // thisPtr->mCapacity at +0x08
  // Element size: 32 bytes (0x20)
  // Each element starts with a vtable pointer (at element+0x00)

  int* oldData = thisPtr->mData;
  uint oldCount = thisPtr->mCount;

  if (thisPtr->mCapacity < newCapacity) {
    // Allocate new buffer: newCapacity * 32 bytes
    void* newData = FUN_009c8e80(newCapacity << 5); // malloc or custom alloc

    if (oldData != nullptr) {
      if (oldCount != 0) {
        // Copy each element from old buffer to new buffer
        uint idx = 0;
        // puVar4 points to the start of the first element in the new buffer (after 8 bytes preamble? Actually the code starts at newData+8, but that's an artifact; let's reinterpret.)
        // Reconstructing: the code starts copying from newData+8, but the old data is copied with an offset.
        // Actually the new buffer layout: first 8 bytes are not used? No, the copy starts at newData+8 and copies 24 bytes (6 * 4) from old element.
        // Wait, the copy copies 6 words: puVar4[-2], puVar4[-1], *puVar4, puVar4[1]..[5] correspond to 8 words total? Let's recalc: puVar4 is undefined4*, incremented by 8 each iteration (32 bytes). So each element is 8 undefined4 = 32 bytes.
        // The copy sets puVar4[-2] = &vtable, puVar4[-1] = old[1], puVar4[0] = old[2], ..., puVar4[5] = old[7].
        // So new element layout: offset -8: vtable, offset -4: old[1], offset 0: old[2], offset 4: old[3], offset 8: old[4], offset 12: old[5], offset 16: old[6], offset 20: old[7].
        // That's 8 words = 32 bytes. So the new element starts at (newData + 8) - 8 = newData. So the first 8 bytes of new buffer are part of the first element? The code sets puVar4[-2] which is at newData+0 when puVar4 = newData+8.
        // Therefore the entire new buffer is used for elements.
        // puVar2 points to the old element starting at oldData.
        // So the copy copies the whole 32-byte element but with the vtable replaced by a static one.
        // The loop increments puVar4 by 8 (32 bytes) per iteration.

        // We'll model it as:
        EARSArrayElement* newElem = (EARSArrayElement*)((char*)newData + 8); // start at offset 8 for the first element's base? Actually offset 8 is used for the last 24 bytes? Let's just do a clean copy loop.
        // Better to write it as: for each index, copy the element from old to new, setting new element's vtable.
        uint idx = 0;
        EARSArrayElement* oldElemBase = (EARSArrayElement*)oldData;
        EARSArrayElement* newElemBase = (EARSArrayElement*)newData;
        do {
          EARSArrayElement* newElem = &newElemBase[idx];
          EARSArrayElement* oldElem = &oldElemBase[idx];
          // Copy the vtable pointer and other data
          newElem->vtablePtr = &PTR_LAB_00e35c24; // static base vtable? (maybe initialize)
          // Copy 28 bytes from old element starting at oldElem->vtablePtr+4? Actually the copy does puVar4[-1] = old[1], etc. That skips old[0] (vtable) and copies old[1]..old[7] into new[-1]..new[5].
          // So we copy fields at offsets 4,8,12,16,20,24,28 (7 words) from old to new offsets 4..28? No new offset -4 is new vtable? Wait careful.
          // We'll just replicate the memcpy-like logic: copy the entire element except the vtable is overwritten.
          // Actually old element's vtable is at offset 0, we skip it and copy the next 28 bytes (7 DWORDs) into the new element starting at offset 4? But the new element's vtable at offset 0 is set to the static one.
          // In the code: puVar4[-1] = puVar2[1] -> new offset -4 = old offset 4
          // *puVar4 = puVar2[2] -> new offset 0 = old offset 8
          // puVar4[1] = puVar2[3] -> new offset 4 = old offset 12
          // ... puVar4[5] = puVar2[7] -> new offset 20 = old offset 28
          // So new element layout (relative to start of element, which is puVar4 - 2? Actually puVar4 is at newData+8 for first element, so element start is puVar4-8? No, let's recalc.
          // puVar4 starts at iVar1+8. puVar4[-2] is at iVar1+0, puVar4[-1] at iVar1+4, puVar4[0] at iVar1+8, puVar4[1] at iVar1+12, ... puVar4[5] at iVar1+28.
          // So each element occupies bytes 0..31 of the new buffer. The first element's vtable is set to &PTR_LAB_00e35c24.
          // The copy of old element: puVar2 = old element pointer. puVar2[0] (old vtable) is skipped; puVar2[1] goes to new offset 4, puVar2[2] to new offset 8, ..., puVar2[7] to new offset 28.
          // So the new element has:
          // +0x00: static vtable
          // +0x04: old field at old+4
          // +0x08: old field at old+8
          // +0x0C: old field at old+12
          // +0x10: old field at old+16
          // +0x14: old field at old+20
          // +0x18: old field at old+24
          // +0x1C: old field at old+28
          // So effectively it copies 7 DWORDs from old+4 to new+4.

          // Then it calls a virtual function on the old element: (**(code **)*puVar2)(0) -> call oldVtable[0](0) likely a notification or destructor.

          // Let's implement cleanly.
          newElem->field_04 = oldElem->field_04;
          newElem->field_08 = oldElem->field_08;
          newElem->field_0C = oldElem->field_0C;
          newElem->field_10 = oldElem->field_10;
          newElem->field_14 = oldElem->field_14;
          newElem->field_18 = oldElem->field_18;
          newElem->field_1C = oldElem->field_1C;

          // Set vtable
          newElem->vtable = (void*)&PTR_LAB_00e35c24;

          // Call virtual function at index 0 on old element (likely onMove, onDestroy, etc.)
          ((void (*)(EARSArrayElement*))(oldElem->vtable[0]))(oldElem);

          idx++;
        } while (idx < oldCount);
      }
      // Free old buffer
      FUN_009c8f10(oldData);
    }

    thisPtr->mData = newData;
    thisPtr->mCapacity = newCapacity;
  }
}