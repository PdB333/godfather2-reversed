// Xbox PDB: TNL::EventConnection::readPacket
// FUNC_NAME: NetConnection::processRawPacket
void __thiscall NetConnection::processRawPacket(NetBitStream *stream)
{
    // Packet node linked list: m_packetListHead is at offset 0x77
    // m_nextExpectedSeq is at offset 0x7a
    // m_connectionState is at offset 0x6d (7 = Connected)
    // m_maxPacketSeq is at offset 0x7c
    // m_seqBitCount is at offset 0x7d (number of bits for seq number)
    // m_flags at offset 0x66 (bit 0 = notify?)
    // Array at DAT_01223178 per master sequence index (index from this->getMasterSeqIndex() via vtable+0x50)
    // Packet object vtable: +0x04 = addRef? +0x08 = release? +0x0C = process? +0x10 = processPacket? +0x14 = processUnordered?
    
    uint localSeqNum = 0xfffffffe; // last sequence number written to waiting list
    bool firstPacket = true;
    PacketNode *curNode = reinterpret_cast<PacketNode*>(&this->m_packetListHead); // node with next pointer at offset 0
    uint readCount;
    
    while (true)
    {
        // Read the next bit from the stream (packet present flag)
        uint seqStreamPos = stream->m_readPos; // offset 0x18
        uint streamEndPos = stream->m_bitCount; // offset 0x2c
        
        bool bitValue;
        if (streamEndPos < seqStreamPos) {
            stream->m_overflow = 1;
            bitValue = false;
        } else {
            // Read bit from byte array (stream->m_data at offset 0xc)
            bitValue = (stream->m_data[seqStreamPos >> 3] & (1 << (seqStreamPos & 7))) != 0;
            stream->m_readPos = seqStreamPos + 1;
        }
        
        if (firstPacket) {
            if (bitValue) {
                firstPacket = false;
            } else {
                // No packet present? Try reading another bit?
                seqStreamPos = stream->m_readPos;
                if (streamEndPos < seqStreamPos) {
                    stream->m_overflow = 1;
                    goto end_of_stream;
                }
                bitValue = (stream->m_data[seqStreamPos >> 3] & (1 << (seqStreamPos & 7))) != 0;
                stream->m_readPos = seqStreamPos + 1;
                firstPacket = false;
            }
        }
        
        if (!bitValue) {
            // End of packet list in stream
            end_of_stream:
            if (this->m_packetListHead == 0) {
                return;
            }
            while (true) {
                curNode = (PacketNode*)this->m_packetListHead;
                if (curNode->seqNum != this->m_nextExpectedSeq) {
                    return;
                }
                this->m_nextExpectedSeq++;
                this->m_packetListHead = curNode->next;
                
                // Process the packet
                if (this->m_connectionState == 7) {
                    // Unordered packet processing (vtable+0x14)
                    curNode->packet->processUnordered(this);
                }
                
                // Ensure atexit registration happens once for memory pool cleanup
                if ((_atexitFlag & 1) == 0) {
                    _atexitFlag |= 1;
                    registerPoolCleanup();
                    _atexit(poolCleanup);
                }
                
                // Release packet reference
                Packet *pkt = curNode->packet;
                if (pkt != nullptr) {
                    int *refCount = &pkt->refCount; // at offset +8 from vtable?
                    (*refCount)--;
                    if (*refCount == 0) {
                        pkt->destroy(); // vtable+8
                    }
                }
                
                _allocatedNodeCount--;
                curNode->packet = (Packet*)_nodeFreeList; // push node to free list
                _nodeFreeList = curNode;
                
                if (_quitFlag != 0) {
                    return;
                }
                if (this->m_packetListHead == 0) {
                    return;
                }
            }
        }
        
        // Read packet sequence number
        uint packetSeq;
        if (!firstPacket) {
            seqStreamPos = stream->m_readPos;
            if (streamEndPos < seqStreamPos) {
                stream->m_overflow = 1;
                readCount = 0;
                // In original: call readBits(7, &readCount) to align?
                // Actually: FUN_0064b9e0(7,&param_2); but param_2 is local? 
            } else {
                byte byteVal = stream->m_data[seqStreamPos >> 3];
                stream->m_readPos = seqStreamPos + 1;
                if ((byteVal & (1 << (seqStreamPos & 7))) == 0) {
                    readCount = 0;
                    readBits(7, &readCount);
                }
                packetSeq = localSeqNum + 1;
            }
            packetSeq = packetSeq & 0x7f;
            localSeqNum = packetSeq;
        }
        
        // Optional: read notification flag
        if (this->m_flags & 0x1) {
            uint dummy;
            readBits(0x10, &dummy);
        }
        
        // Read packet index
        uint packetIndex;
        readBits(this->m_seqBitCount, &packetIndex);
        uint indexMask = (1 << this->m_seqBitCount) - 1;
        if (this->m_seqBitCount != 0x20) {
            packetIndex = packetIndex & indexMask;
        }
        
        if (this->m_maxPacketSeq <= packetIndex) {
            invalid_packet:
            logError("Invalid packet.");
            return;
        }
        
        // Get connection master sequence index from vtable
        int masterSeqIndex = this->getMasterSeqIndex(); // vtable+0x50
        int *packetArray = &packetMasterArray[masterSeqIndex * 0x24]; // DAT_01223178 + index*0x24
        
        if (packetArray[packetIndex] == 0) {
            goto invalid_packet;
        }
        
        // Get packet object from array
        int *packetPtr = (int*)(**(int**)(packetArray[packetIndex] + 4))(); // dereference somehow? Seems like a function call
        if (packetPtr == 0) {
            goto invalid_packet;
        }
        
        int packetState = packetPtr[3];
        if (packetState == 0 ||
            (packetState == 2 && ((this->m_connectionFlags >> 1) & 1)) ||
            (packetState == 3 && (this->m_connectionFlags & 1))) {
            logError("Invalid Packet.");
            return;
        }
        
        // Call packet process function (vtable+0x10)
        (*(void (**)(NetConnection*, NetBitStream*))(packetPtr[0] + 0x10))(this, stream);
        
        if (_quitFlag != 0) {
            return;
        }
        
        if (!firstPacket) {
            // Calculate actual sequence number with wrap-around
            uint actualSeq = packetSeq | (this->m_nextExpectedSeq & 0xffffff80);
            if ((int)actualSeq < this->m_nextExpectedSeq) {
                actualSeq += 0x80;
            }
            
            // Allocate a new node
            PacketNode *newNode;
            if (_atexitFlag & 1 == 0) {
                _atexitFlag |= 1;
                registerPoolCleanup();
                _atexit(poolCleanup);
            }
            
            if (_nodeFreeList == 0) {
                newNode = (PacketNode*)poolAlloc(poolSize);
                if (newNode == 0) {
                    newNode = 0;
                } else {
                    newNode->packet = 0;
                }
            } else {
                newNode = _nodeFreeList;
                _nodeFreeList = (PacketNode*)newNode->next; // next is list link
                newNode->packet = 0;
            }
            
            // Set node packet and ref count
            Packet *pktRef = newNode->packet;
            if (pktRef != nullptr) {
                int *refCount = &pktRef->refCount;
                (*refCount)--;
                if (*refCount == 0) {
                    pktRef->destroy();
                }
            }
            newNode->packet = (Packet*)packetPtr;
            packetPtr[2]++; // increment ref count on packet object
            newNode->seqNum = actualSeq;
            
            // Insert into list in sequence order
            int *nextNodePtr = (int*)this->m_packetListHead;
            while (nextNodePtr != 0 && *(int*)(*nextNodePtr + 4) < (int)actualSeq) {
                nextNodePtr = (int*)(*nextNodePtr + 8);
            }
            newNode->next = (PacketNode*)*nextNodePtr;
            *nextNodePtr = (int)newNode;
            curNode = &newNode->next; // point to next for future traversal
        } else {
            // First packet processing
            if (this->m_connectionState == 7) {
                packetPtr->processUnordered(this);
            }
            packetPtr->addRef(); // vtable+4(1) was called with arg 1
        }
        
        if (_quitFlag != 0) {
            return;
        }
    }
}