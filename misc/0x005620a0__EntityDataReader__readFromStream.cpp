// FUNC_NAME: EntityDataReader::readFromStream
void __thiscall EntityDataReader::readFromStream(uint streamId)
{
  // streamId is passed to functions for reading data; also used to call a virtual method at end.
  dataMarker(streamId, 0xbaa03366); // Likely initializes stream: debug marker or CRC check

  bool hasData = false;
  uint8* curPos = &local_buffer;  // local_buffer is a pointer into the stream data
  uint index = 0;
  uint defaultVectorW = DAT_00e2b1a4; // Global constant, likely default alpha value (1.0f)

  while (true)
  {
    bool isEnd;
    if (useList) // local_78: false = list-based iteration, true = array-based
    {
      isEnd = (index == arraySize); // local_68: array size
    }
    else
    {
      isEnd = (*curPosPtr == nullptr); // curPosPtr = ppuVar6 initially
    }
    if (isEnd) break;

    hasData = true;

    // Determine current entry pointer
    uint8* entryPtr;
    if (useList)
    {
      entryPtr = curPosPtr;
    }
    else
    {
      entryPtr = &local_buffer; // Actually local_64 used as temp; but we compute from curPos
    }

    // Read field type: if offset 6 of entry is 0x25e3, it's an indirect reference; otherwise direct
    uint fieldType;
    if (*(short*)(entryPtr + 6) == 0x25e3)
    {
      fieldType = *(ushort*)(entryPtr + 4); // *(ppuVar5+1) as unsigned short
    }
    else
    {
      fieldType = (uint)entryPtr[4]; // Actually read as 4-byte value? In decompile it's ppuVar5[1] which is a pointer under some conditions. Reconstruct carefully.
    }

    // Based on field type, set member variables (this + offset)
    switch (fieldType)
    {
      case 0: // INTEGER_COUNTER_1
      {
        int value = *(int*)(entryPtr + 8); // ppuVar5[2]
        this->counter1 = value + 1; // +0x40
        break;
      }
      case 1: // BYTE_FLAG_1
      {
        uint8 byteVal = *(uint8*)(entryPtr + 8);
        this->flag1 = byteVal; // +0x24
        break;
      }
      case 2: // INTEGER_COUNTER_2
      {
        int value = *(int*)(entryPtr + 8);
        this->counter2 = value + 1; // +0x3c
        break;
      }
      case 3: // BYTE_FLAG_2 (also enables sub flags)
      {
        uint8 byteVal = *(uint8*)(entryPtr + 8);
        this->flag2 = byteVal; // +0x28
        if (byteVal != 0)
        {
          this->isActive = 1;    // +0x44
          this->isEnabled = 1;  // +0x60
        }
        break;
      }
      case 4: // VECTOR_3D_TYPE_A (position/color)
      {
        this->isActive = 1; // +0x44
        // Read three components and a fourth default value
        uint8* vecData = entryPtr;
        if (*(short*)(entryPtr + 6) == 0x25e3)
        {
          if (*(uint32*)entryPtr == 0)
            vecData = (uint8*)&DAT_00e2e5d0; // default vector
          else
            vecData = (uint8*)(*(uint32*)entryPtr + *(uint32*)(entryPtr + 8));
        }
        else
        {
          vecData = entryPtr + 8; // skip type and size? Actually moves two pointers ahead
        }
        this->vec1_x = *(float*)vecData;       // +0x50
        this->vec1_y = *(float*)(vecData + 4); // +0x54
        this->vec1_z = *(float*)(vecData + 8); // +0x58
        this->vec1_w = defaultVectorW;         // +0x5c
        break;
      }
      case 5: // VECTOR_3D_TYPE_B (secondary)
      {
        this->isEnabled = 1; // +0x60
        uint8* vecData = entryPtr;
        if (*(short*)(entryPtr + 6) == 0x25e3)
        {
          if (*(uint32*)entryPtr == 0)
            vecData = (uint8*)&DAT_00e2e5d0;
          else
            vecData = (uint8*)(*(uint32*)entryPtr + *(uint32*)(entryPtr + 8));
        }
        else
        {
          vecData = entryPtr + 8;
        }
        this->vec2_x = *(float*)vecData;       // +0x70
        this->vec2_y = *(float*)(vecData + 4); // +0x74
        this->vec2_z = *(float*)(vecData + 8); // +0x78
        this->vec2_w = defaultVectorW;         // +0x7c
        break;
      }
      case 6: // BYTE_FLAG_3
      {
        this->flag3 = *(uint8*)(entryPtr + 8); // +0x2c
        break;
      }
      case 7: // POINTER_1 (maybe string)
      {
        this->stringPtr1 = *(void**)(entryPtr + 8); // +0x14
        break;
      }
      case 8: // POINTER_2
      {
        this->stringPtr2 = *(void**)(entryPtr + 8); // +0x18
        break;
      }
      case 9: // BYTE_FLAG_4
      {
        this->flag4 = *(uint8*)(entryPtr + 8); // +0x30
        break;
      }
      case 10: // POINTER_3
      {
        this->ptr3 = *(void**)(entryPtr + 8); // +0x10
        break;
      }
      case 11: // BYTE_FLAG_5
      {
        this->flag5 = *(uint8*)(entryPtr + 8); // +0x34
        break;
      }
      case 12: // VECTOR_3D_TEMP (stored locally, later applied maybe)
      {
        uint8* vecData = entryPtr;
        if (*(short*)(entryPtr + 6) == 0x25e3)
        {
          if (*(uint32*)entryPtr == 0)
            vecData = (uint8*)&DAT_00e2e5d0;
          else
            vecData = (uint8*)(*(uint32*)entryPtr + *(uint32*)(entryPtr + 8));
        }
        else
        {
          vecData = entryPtr + 8;
        }
        // Store in local variables for later processing by another function (e.g., color?)
        local_vec3.x = *(float*)vecData;
        local_vec3.y = *(float*)(vecData + 4);
        local_vec3.z = *(float*)(vecData + 8);
        local_vec3.w = defaultVectorW;
        break;
      }
      case 13: // BYTE_FLAG_6
      {
        this->flag6 = *(uint8*)(entryPtr + 8); // +0x38
        break;
      }
      case 14: // POINTER_4
      {
        this->ptr4 = *(void**)(entryPtr + 8); // +0x1c
        break;
      }
      case 15: // POINTER_5
      {
        this->ptr5 = *(void**)(entryPtr + 8); // +0x20
        break;
      }
    }

    // Advance to next entry
    if (!useList)
    {
      int size = *(int*)curPosPtr; // size of current entry (includes size field)
      if (index == 0)
      {
        // First element? The code checks if index < 0, which never happens; then else if index < arraySize-1, advance by size.
        if (index < (arraySize - 1))
        {
          curPosPtr = (uint8*)((int)curPosPtr + size);
          index++;
        }
        else
        {
          curPosPtr = (uint8*)&endMarker; // DAT_01163cf8
        }
      }
      else
      {
        curPosPtr = (uint8*)((int)curPosPtr + size);
        // FUN_0043b140 called? Actually at that point in the code, it calls a function and then sets ppuVar6. Might be iterator reset.
        // We'll simplify: just advance.
      }
    }
    else // array-based iteration
    {
      index++;
      if (index != arraySize)
      {
        // Read next element from array
        int bitIndex = index >> 3;
        int bitMask = 1 << (index & 7);
        if ((arrayFlags[bitIndex] & bitMask) == 0)
        {
          // Entry exists: read from array
          tempEntry = arrayPtr; // arrayPtr = local_70
          curPos = arrayPtr; // local_64
          arrayPtr++; // advance array pointer (since each element is 4 bytes? Actually the code increments local_70 by 1 (sizeof pointer))
        }
        else
        {
          // Entry is null (skip)
          tempEntry = nullptr;
          tempSize = 0;
        }
      }
    }
  }

  this->dataLoaded = 1; // +0x80
  if (hasData)
  {
    processLocalVector(&local_vec3); // FUN_005624d0 - applies local_vec3 maybe as color/offset
  }
  // Call virtual finalizer on the stream
  (*(void (**)(int))(this->vtbl + 0x14))(streamId); // +0x8c is vtable pointer, call function at offset 0x14
  this->processingComplete = 1; // +0x84
}