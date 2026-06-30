// FUNC_NAME: NetConnection::processReceivePacket
void __thiscall NetConnection::processReceivePacket(void *thisPtr, uint incomingBitStreamPtr)
{
  int *nodePtr;
  byte bitValue;
  uint tempSeq;
  int *allocatedNode;
  bool isFirstRead;
  uint seqDelta;
  int genIndex;
  int *nodeIterPtr;
  int *freeNodePtr;
  int *currentNode;
  uint currentBit;
  bool bitSet;
  uint dummySeq;
  uint local_4;
  
  local_4 = 0xfffffffe;
  isFirstRead = true;
  nodePtr = (int *)((int)thisPtr + 0x77); // +0x77: mPendingPacketListHead

  do {
    // Read bits from the incoming stream to determine if a packet is missing/acknowledged
    currentBit = *(uint *)(incomingBitStreamPtr + 0x18);
    genIndex = *(uint *)(incomingBitStreamPtr + 0x2c);
    if (genIndex < currentBit) {
      *(undefined1 *)(incomingBitStreamPtr + 0x1c) = 1; // mark end of bitstream
      bitSet = false;
    } else {
      bitSet = (*(byte *)((currentBit >> 3) + *(int *)(incomingBitStreamPtr + 0xc)) & (byte)(1 << ((byte)currentBit & 7))) != 0;
      *(uint *)(incomingBitStreamPtr + 0x18) = currentBit + 1;
    }

    if (isFirstRead) {
      if (!bitSet) {
        // First bit not set: skip one bit (this is probably a start bit)
        currentBit = *(uint *)(incomingBitStreamPtr + 0x18);
        if (genIndex < currentBit) {
          *(undefined1 *)(incomingBitStreamPtr + 0x1c) = 1;
          goto LAB_0064ee68;
        }
        bitSet = (*(byte *)((currentBit >> 3) + *(int *)(incomingBitStreamPtr + 0xc)) & (byte)(1 << ((byte)currentBit & 7))) != 0;
        *(uint *)(incomingBitStreamPtr + 0x18) = currentBit + 1;
        isFirstRead = false;
        goto LAB_0064ebf7;
      }
    } else {
LAB_0064ebf7:
      if (!bitSet) {
LAB_0064ee68:
        // No more bits: check pending list for expired nodes
        if (*(int *)((int)thisPtr + 0x77) == 0) {
          return;
        }
        while (true) {
          nodePtr = (int *) *(int *)((int)thisPtr + 0x77);
          if (nodePtr[1] != *(int *)((int)thisPtr + 0x7a)) {
            return;
          }
          *(int *)((int)thisPtr + 0x7a) = *(int *)((int)thisPtr + 0x7a) + 1;
          *(int *)((int)thisPtr + 0x77) = nodePtr[2];

          if (*(int *)((int)thisPtr + 0x6d) == 7) {
            (**(code **)(*(int *)*nodePtr + 0x14))(thisPtr);
          }

          if ((gPacketAllocatorLock & 1) == 0) {
            gPacketAllocatorLock |= 1;
            initializePacketAllocator();
            _atexit((_func_4879 *)&shutdownPacketAllocator);
          }

          freeNodePtr = (int *)*nodePtr;
          if (freeNodePtr != (int *)0x0) {
            int *refCount = freeNodePtr + 2;
            *refCount = *refCount - 1;
            if (*refCount == 0) {
              (**(code **)(*freeNodePtr + 8))();
            }
          }

          gPacketAllocCount--;
          *nodePtr = (int)gPacketFreeList;
          gPacketFreeList = nodePtr;

          if (gShutdownRequested != '\0') break;
          if (*(int *)((int)thisPtr + 0x77) == 0) {
            return;
          }
        }
        return;
      }
    }

    // Process the actual packet data
    dummySeq = 0xffffffff;
    if (!isFirstRead) {
      currentBit = *(uint *)(incomingBitStreamPtr + 0x18);
      if (genIndex < currentBit) {
        *(undefined1 *)(incomingBitStreamPtr + 0x1c) = 1;
LAB_0064ec19:
        dummySeq = 0;
        readBitsFromStream(7, &dummySeq);
      } else {
        bitValue = *(byte *)((currentBit >> 3) + *(int *)(incomingBitStreamPtr + 0xc));
        *(uint *)(incomingBitStreamPtr + 0x18) = currentBit + 1;
        if ((bitValue & (byte)(1 << ((byte)currentBit & 7))) == 0) goto LAB_0064ec19;
        dummySeq = local_4 + 1;
      }
      dummySeq = dummySeq & 0x7f;
      local_4 = dummySeq;
    }

    if (*(char *)((int)thisPtr + 0x66) != '\0') {
      uint logValue = 0;
      readBitsFromStream(0x10, &logValue);
    }

    byte bitCount = *(byte *)((int)thisPtr + 0x7d);
    uint packetType = 0;
    readBitsFromStream(bitCount, &packetType);
    uint maskedType = packetType;
    if (bitCount != 0x20) {
      maskedType = (1 << (bitCount & 0x1f)) - 1U & packetType;
    }

    if (*(uint *)((int)thisPtr + 0x7c) <= maskedType) {
LAB_0064ef2f:
      debugPrint("Invalid packet.");
      return;
    }

    int connIndex = (**(code **)(*((int *)thisPtr) + 0x50))(); // virtual: getConnectionIndex?
    // gPacketHandlerTable is an array of structs indexed by connIndex*0x24 + packetType*4
    int handlerPtr = *(int *)(*(int *)(&gPacketHandlerTable + connIndex * 0x24) + maskedType * 4);
    if (handlerPtr == 0 ||
        (currentNode = (int *)(**(code **)(*(int *)handlerPtr + 4))(), currentNode == (int *)0x0))
      goto LAB_0064ef2f;

    int packetState = currentNode[3];
    if (((packetState == 0) ||
         ((packetState == 2 && ((*(uint *)((int)thisPtr + 0x2e) >> 1 & 1) != 0)))) ||
        ((packetState == 3 && ((*(byte *)((int)thisPtr + 0x2e) & 1) != 0)))) {
      debugPrint("Invalid Packet.");
      return;
    }

    (**(code **)(*currentNode + 0x10))(thisPtr, (void *)incomingBitStreamPtr);

    if (gShutdownRequested != '\0') {
      return;
    }

    if (!isFirstRead) {
      // Handle acknowledgment and insertion into pending list
      uint ackSeq = dummySeq | (*(int *)((int)thisPtr + 0x7a) & 0xffffff80U);
      if ((int)ackSeq < *(int *)((int)thisPtr + 0x7a)) {
        ackSeq = ackSeq + 0x80;
      }

      // Allocate a node from the free list or new
      if ((gPacketAllocatorLock & 1) == 0) {
        gPacketAllocatorLock |= 1;
        initializePacketAllocator();
        _atexit((_func_4879 *)&shutdownPacketAllocator);
      }

      int *freeList = gPacketFreeList;
      gPacketAllocCount++;
      if (gPacketFreeList == (int *)0x0) {
        freeList = (int *) allocatePacketNode(gPacketAllocator);
        if (freeList == (int *)0x0) {
LAB_0064ee1a:
          gPacketFreeList = (int *)0x0;
          freeList = (int *)0x0;
        } else {
          *freeList = 0;
        }
      } else {
        int *nextFree = (int *)*gPacketFreeList;
        if (gPacketFreeList == (int *)0x0) goto LAB_0064ee1a;
        *gPacketFreeList = 0;
        gPacketFreeList = nextFree;
      }

      // Reference count decrement on old data
      int *oldData = (int *)*freeList;
      if (oldData != (int *)0x0) {
        int *refCount = oldData + 2;
        *refCount = *refCount - 1;
        if (*refCount == 0) {
          (**(code **)(*oldData + 8))();
        }
      }

      *freeList = (int)currentNode;
      currentNode[2] = currentNode[2] + 1; // increase ref count
      freeList[1] = ackSeq;

      int *insertAfter = nodePtr;
      int insertAfterVal = *insertAfter;
      while ((insertAfterVal != 0 && (*(int *)(*nodePtr + 4) < (int)ackSeq))) {
        insertAfter = (int *)(*nodePtr + 8);
        insertAfterVal = *insertAfter;
      }

      freeList[2] = *insertAfter;
      *insertAfter = (int)freeList;
      nodePtr = freeList + 2;
      goto LAB_0064eb87; // Restart the main loop
    }

    if (*(int *)((int)thisPtr + 0x6d) == 7) {
      (**(code **)(*currentNode + 0x14))(thisPtr);
    }

    (**(code **)(*currentNode + 4))(1); // callback with 1
    if (gShutdownRequested != '\0') {
      return;
    }

  } while (true);
}