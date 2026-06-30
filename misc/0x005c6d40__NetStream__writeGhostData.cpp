// FUNC_NAME: NetStream::writeGhostData
void __thiscall NetStream::writeGhostData(NetStream* thisStream, GhostDataHeader* dataHeader)
{
  int elementSize;
  int currentOffset;
  int basePtr;
  int totalSize;
  int* writePosPtr;
  int* streamWritePos;
  int* dataPtr;
  int flag;
  int value1;
  int value2;
  float vecX, vecY, vecZ, vecW;
  __m128 vec128;
  __m128 minVec, maxVec;
  char localBuf[8];
  float fStack_58;
  float fStack_54;
  char local_50[76];
  
  // Initialize stream (likely reset write position)
  FUN_005c5320(thisStream);
  // Write header (maybe packet type)
  FUN_005c4850();
  // Write footer or finalize
  FUN_00417560();
  
  // Compute base address from dataHeader index
  basePtr = dataHeader->index * 0xd4 + 4 + DAT_012234f4;
  dataHeader->currentOffset = 0;
  
  if (0 < dataHeader->totalSize) {
    do {
      streamWritePos = (int*)DAT_01206880;
      dataPtr = dataHeader->basePtr + dataHeader->currentOffset;
      value2 = *(int*)(dataPtr + 0x3c);
      
      if (*(int*)(dataPtr + 0x34) < 1) {
        // Read vector data (12 bytes) from offset +4
        __m128 vecData = *(__m128*)(dataPtr + 4);
        // Copy to local buffer
        memcpy(localBuf, &vecData, 12);
        
        if ((char)PTR_DAT_00f17650 == '\0') {
          // Transform vector using global matrices
          vecX = *(float*)&localBuf[0];
          vecY = *(float*)&localBuf[4];
          vecZ = *(float*)&localBuf[8];
          vec128.m128_f32[0] = vecX * _DAT_0119d0b0 + DAT_0119d0c0;
          vec128.m128_f32[1] = vecY * _DAT_0119d0b4 + _DAT_0119d0c4;
          vec128.m128_f32[2] = vecZ * _DAT_0119d0b8 + _DAT_0119d0c8;
          vec128.m128_f32[3] = *(float*)(dataPtr + 0x10) * DAT_0119d0bc + _DAT_0119d0cc;
          // Clamp to min/max
          vec128 = _mm_min_ps(vec128, _DAT_00e2b2e0);
          vec128 = _mm_max_ps(vec128, _DAT_00e2b2d0);
          // Store back
          *(float*)&localBuf[0] = vec128.m128_f32[0];
          *(float*)&localBuf[4] = vec128.m128_f32[1];
          *(float*)&localBuf[8] = vec128.m128_f32[2];
          fStack_54 = vec128.m128_f32[3];
        }
        
        // Check condition for visibility
        if ((fStack_54 < DAT_00e2b1a4) || (((byte)DAT_0119d0ac & 0x17) != 0)) {
          flag = 0; // false
        } else {
          flag = 1; // true
        }
        
        // Write visibility flag
        *(int**)(*streamWritePos + 0x14) = &PTR_LAB_01126b40; // vtable for bool?
        *(int*)(streamWritePos + 0x14) = *(int*)(streamWritePos + 0x14) + 4;
        *(bool*)*(int*)(streamWritePos + 0x14) = !flag;
        *(int*)(streamWritePos + 0x14) = *(int*)(streamWritePos + 0x14) + 4 & 0xfffffffc;
        
        // Write two integers (value1 and value2)
        value1 = *(int*)(dataPtr + 0x38);
        writePosPtr = (int*)(DAT_01206880 + 0x14);
        **(int**)(DAT_01206880 + 0x14) = &PTR_LAB_01126d20;
        *writePosPtr = *writePosPtr + 4;
        *(int*)*writePosPtr = value1;
        *writePosPtr = *writePosPtr + 4;
        *(int*)*writePosPtr = value2;
        
        // Write 64-byte block (local_50)
        void* dst = (void*)(*writePosPtr + 0x13 & 0xfffffff0);
        *writePosPtr = (int)dst;
        memcpy(dst, local_50, 0x40);
        
        // Write 4 floats (transformed vector + w)
        int* floatDst = (int*)(*writePosPtr + 0x4f & 0xfffffff0);
        *writePosPtr = (int)floatDst;
        floatDst[0] = *(int*)&localBuf[0];
        floatDst[1] = *(int*)&localBuf[4];
        floatDst[2] = *(int*)&localBuf[8];
        floatDst[3] = *(int*)&fStack_54;
        *writePosPtr = *writePosPtr + 0x10;
      } else {
        // Write a byte 1 (true) for visibility
        *(int**)(DAT_01206880 + 0x14) = &PTR_LAB_01126b40;
        *(int*)(streamWritePos + 0x14) = *(int*)(streamWritePos + 0x14) + 4;
        **(char**)(streamWritePos + 0x14) = 1;
        *(int*)(streamWritePos + 0x14) = *(int*)(streamWritePos + 0x14) + 4 & 0xfffffffc;
        
        // Call another function to write additional data
        FUN_005d64e0(*(int*)(dataPtr + 0x38), value2, *(int*)(basePtr + 0xbc), &DAT_0119d0b0, &DAT_0119d0c0,
                     *(int*)(*(int*)(basePtr + 0xc0) + -4 + *(int*)(dataPtr + 0x34) * 4));
      }
      
      // Write a byte 0 (end marker?)
      streamWritePos = (int*)DAT_01206880;
      **(int**)(DAT_01206880 + 0x14) = &PTR_LAB_01126b40;
      *(int*)(streamWritePos + 0x14) = *(int*)(streamWritePos + 0x14) + 4;
      **(char**)(streamWritePos + 0x14) = 0;
      *(int*)(streamWritePos + 0x14) = *(int*)(streamWritePos + 0x14) + 4 & 0xfffffffc;
      
      // Advance to next element
      currentOffset = *(int*)(dataHeader->basePtr + dataHeader->currentOffset) + dataHeader->currentOffset;
      dataHeader->currentOffset = currentOffset;
    } while (currentOffset < dataHeader->totalSize);
  }
  return;
}