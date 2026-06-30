// FUNC_NAME: SimGroup::importObjectFromStream
undefined4 * __thiscall SimGroup::importObjectFromStream(SimGroup *thisGroup, void *streamPtr)
{
  undefined4 *object;
  char bVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  LARGE_INTEGER perfCounter;
  
  // Get some global object (maybe the engine root or manager)
  // Global pointer at DAT_0122337c + 0x84
  if (*(int *)(GlobalData + 0x84) == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(*(int *)(GlobalData + 0x84) + 0x1c);
  }
  
  // Read object pointer from stream offset 0x14
  object = *(undefined4 **)((int)streamPtr + 0x14);
  // Store it back as current object pointer (stream context)
  *(undefined4 **)((int)streamPtr + 0x1c) = object;
  
  puVar5 = (undefined4 *)0x0;
  // Check if the object has the SimG signature and version 1
  if ((object[2] == 0x53696d47) && (object[3] == 1)) {
    // Calculate elapsed time since last performance counter snapshot
    QueryPerformanceCounter(&perfCounter);
    // __allmul: multiply (perfCounterDelta) by 1000
    uVar2 = __allmul(perfCounter.s.LowPart - thisGroup->lastCounterLow,
                     (perfCounter.s.HighPart - thisGroup->lastCounterHigh) - 
                     (uint)(perfCounter.s.LowPart < thisGroup->lastCounterLow), 
                     1000, 0);
    // __aulldiv: divide by frequency (global stored at DAT_01163ec0/4)
    uVar2 = __aulldiv(uVar2, DAT_01163ec0, DAT_01163ec4);
    object[3] = uVar2; // Store elapsed time in the object (timestamp)
    
    // If there is a pointer relocation table (object[10] != 0), adjust it
    if (object[10] != 0) {
      object[10] = object[10] + (int)object;
    }
    
    // Relocate an array of pointers at object[10] with object[6] elements
    uVar4 = 0;
    if (object[6] != 0) {
      do {
        iVar3 = *(int *)(object[10] + uVar4 * 4);
        if (iVar3 != 0) {
          *(int *)(object[10] + uVar4 * 4) = iVar3 + (int)object;
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < (uint)object[6]);
    }
    
    object[0xb] = uVar2; // Store global ID in object slot 0xb
    
    bVar1 = FUN_00447070(); // Some check (maybe isReadOnly?)
    if (bVar1 == '\0') {
      // Insert into list A (head at thisGroup+0xa0)
      object[0] = 0;      // prev = NULL
      object[1] = thisGroup->listAHead; // next = current head of list A
    }
    else {
      // bVar1 != 0: check another condition
      if (thisGroup->field0xB8 != '\0') {
        goto LAB_InsertIntoListB;
      }
      iVar3 = FUN_00447890(object[4]); // Get some index
      if ((-1 < iVar3) && ((*(byte *)(thisGroup->field0xA4 + 4 + iVar3 * 8) & 4) != 0))
        goto LAB_InsertIntoListB;
      // Otherwise, insert into list A with an extra flag
      object[5] = object[5] | 0x100;
      object[0] = 0;      // prev = NULL
      object[1] = thisGroup->listAHead;
    }
    
    // Insert at head of list A
    if (thisGroup->listAHead != (undefined4 *)0x0) {
      // Set previous head's prev pointer to new object
      *(undefined4 **)thisGroup->listAHead = object;
      thisGroup->listAHead = object;
      return object;
    }
    // If list A was empty, also set tail (thisGroup+0x9c)
    thisGroup->listATail = object;
    thisGroup->listAHead = object;
    puVar5 = object;
  }
  return puVar5;
  
LAB_InsertIntoListB:
  // Insert into list B (head at thisGroup+0x88, tail at thisGroup+0x84)
  object[0] = 0;      // prev = NULL
  object[1] = thisGroup->listBHead;
  if (thisGroup->listBHead == (undefined4 *)0x0) {
    thisGroup->listBTail = object;
  }
  else {
    *(undefined4 **)thisGroup->listBHead = object;
  }
  thisGroup->listBHead = object;
  // Increment global counter at DAT_0122337c + 0x9c
  *(int *)(GlobalData + 0x9c) = *(int *)(GlobalData + 0x9c) + 1;
  object[5] = object[5] | 0x20;
  return object;
}