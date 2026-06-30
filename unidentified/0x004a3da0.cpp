// FUN_NAME: EATaskList::EATaskList
undefined4* __thiscall EATaskList::EATaskList(EATaskList* this, undefined4* inputData, int param3)
{
  short typeShort;
  undefined4 in_EAX; // returned value from caller? Not used meaningfully.
  undefined4 uVar2;
  int tempInt;
  uint count;
  int offset;
  int* tempPtr;
  char charData;
  int* arrayPtr;
  int local_20;
  int local_1c;
  uint countRemaining;
  int entryPtr;
  int value;

  this->field_0x08 = in_EAX;                  // +0x08: some saved value
  int iVar3 = DAT_0120547c;                    // global singleton check
  this->vtable = &PTR_FUN_00e35378;            // +0x00: vtable
  this->field_0x04 = 0;                        // +0x04: uninitialized
  if (iVar3 == 0) {
    uVar2 = 0;
  } else {
    uVar2 = *(undefined4*)(&DAT_01163ffc + iVar3 * 4);  // look up via global index
  }
  this->field_0x0C = uVar2;                    // +0x0C: some reference
  this->inputData = inputData;                 // +0x10: store input parameter
  // Zero-initialize a large block (offsets 0x30..0x7C)
  for (int i = 0x0C; i <= 0x1F; i++) {
    this->fieldArray[i] = 0;                   // +0x30..+0x7C
  }
  *(short*)(&this->fieldArray[0x16]) = 0;      // +0x58: short zero
  this->fieldArray[0x17] = 0;                  // +0x5C
  this->fieldArray[0x18] = 0;                  // +0x60
  this->fieldArray[0x19] = 0;                  // +0x64
  this->fieldArray[0x1A] = 0;                  // +0x68
  this->fieldArray[0x1B] = 0;                  // +0x6C
  this->fieldArray[0x1C] = 0;                  // +0x70
  this->fieldArray[0x1D] = 0;                  // +0x74
  this->fieldArray[0x1E] = 0;                  // +0x78
  this->fieldArray[0x1F] = 0;                  // +0x7C
  *(short*)(&this->fieldArray[0x20]) = 10;     // +0x80: short 10 (default?)
  // Clear bit 0 and set bits 1-10 at +0x82
  *(ushort*)((int)this + 0x82) = (*(ushort*)((int)this + 0x82) & 0xfffe) | 0x7fe;
  this->fieldArray[0x21] = 0;                  // +0x84
  this->fieldArray[0x22] = 0;                  // +0x88
  this->fieldArray[0x23] = 0;                  // +0x8C
  this->fieldArray[0x24] = 0;                  // +0x90
  this->fieldArray[0x25] = 0;                  // +0x94

  // Check bit 2 of flag in inputData+0x0C; if clear, call a setup function
  if ((*(uint*)(inputData + 0x0C) >> 2 & 1) == 0) {
    FUN_00442bd0(inputData);                    // likely inputData->init()
  }

  int managerPtr = DAT_0122342c;               // global manager reference
  // If param3 is zero, try to derive it from global data
  if ((param3 == 0) &&
     ((DAT_01205478 == 0 || (param3 = *(int*)(&DAT_01163fec + DAT_01205478 * 4), param3 == 0)))) {
    // Try to get a task from the global manager (offset 0x6C)
    int* piVar6 = (int*)(DAT_0122342c + 0x6C);
    tempInt = FUN_00443d40();                   // maybe getCount()
    if ((tempInt < 0) || (piVar6 = (int*)(*piVar6 + 0x10 + tempInt * 0x14), piVar6 == (int*)0x0)) {
      param3 = 0;
    } else {
      param3 = *(int*)(*piVar6 + 0x18);         // some field from that task
    }
  }

  // Initialize list metadata
  this->listCount = 0;                          // +0x34? Actually offsets: param1[0xb]=0 (offset 0x2C)
  this->listCapacity = 0;                       // +0x28? param1[10]=0
  this->listDataPtr = 0;                        // +0x24? param1[9]=0
  // I need to align: the code does param_1[8]=0, [9]=0, [10]=0, [0xb]=0.
  // Offsets: [8]=0x20, [9]=0x24, [10]=0x28, [0xb]=0x2C.
  // But earlier they set param1[0xc..0x1f] = 0, so 0x2C is within that range. Actually they set [0xc] to [0x1f], but [0xb] is separate.
  // I'll embed these in the object fields.
  this->field_0x2C = 0;                        // +0x2C
  this->field_0x28 = 0;                        // +0x28
  this->field_0x24 = 0;                        // +0x24
  this->field_0x20 = 0;                        // +0x20

  // Now iterate over entries from inputData+0x3C (array of 12-byte structs)
  countRemaining = (uint)*(ushort*)(inputData + 0x5C); // number of entries
  if ((countRemaining != 0) && (FUN_004a7a00(countRemaining), countRemaining != 0)) {
    offset = 0;
    do {
      // Each entry is 12 bytes: offset 8 = typeShort, offset 4 = id
      entryPtr = *(int*)(this->inputData + 0x3C) + offset;
      int* local_14 = (int*)entryPtr;          // unused? Actually they store entryPtr later.
      typeShort = *(short*)(entryPtr + 8);
      value = 0;
      if (typeShort == 1) {
        // Simple char value from some global? Call FUN_004430c0
        charData = 0;
        FUN_004430c0(&charData);
        value = charData;                       // treated as 3-byte? Actually local_c = CONCAT31(local_c._1_3_, charData) – but they truncated? We'll simplify.
      }
      else if (typeShort == 2) {
        // Look up in global manager's array at +0x18
        if (*(uint*)(managerPtr + 0x1C) != 0) {
          arrayPtr = *(int**)(managerPtr + 0x18);
          count = 0;
          tempPtr = arrayPtr;
          do {
            if (*tempPtr == *(int*)(entryPtr + 4)) {
              value = arrayPtr[count * 2 + 1];
              break;
            }
            count++;
            tempPtr += 2;
          } while (count < *(uint*)(managerPtr + 0x1C));
        }
      }
      else if (typeShort == 4) {
        // Same lookup as type 2
        if (*(uint*)(managerPtr + 0x1C) != 0) {
          arrayPtr = *(int**)(managerPtr + 0x18);
          count = 0;
          tempPtr = arrayPtr;
          do {
            if (*tempPtr == *(int*)(entryPtr + 4)) {
              value = arrayPtr[count * 2 + 1];
              break;
            }
            count++;
            tempPtr += 2;
          } while (count < *(uint*)(managerPtr + 0x1C));
        }
      }

      // Check if list buffer needs to grow
      int newCount = this->listCount + 1;
      if (this->listCount == this->listCapacity) {
        int newCapacity;
        if (this->listCapacity == 0) {
          newCapacity = 1;
        } else {
          newCapacity = this->listCapacity * 2;
        }
        FUN_004a7a00(newCapacity);              // reallocate? Actually allocates new buffer
        // After realloc, entryPtr might be invalid? But we don't store pointer.
      }
      // Store entry pointer and value into the list buffer
      int* bufferSlot = (int*)(this->listDataPtr + this->listCount * 8);
      this->listCount++;
      if (bufferSlot != (int*)0x0) {
        *bufferSlot = entryPtr;                 // store pointer to the entry (12-byte struct)
        bufferSlot[1] = value;                  // store resolved value
      }
      offset += 12;
      countRemaining--;
    } while (countRemaining != 0);
  }

  // Final initialization steps
  FUN_004a5ce0(this, param3);                  // post-process with param3
  FUN_004a6110();                               // probably register or notify
  return this;
}