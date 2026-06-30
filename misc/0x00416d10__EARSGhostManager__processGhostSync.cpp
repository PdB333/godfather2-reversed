// FUNC_NAME: EARSGhostManager::processGhostSync

#include <cstring> // for memcpy

class EARSGhostManager
{
public:
    // Vtable at offset 0x0
    // +0x04: m_ghostId (int)
    // +0x08: m_pDataProvider (class with vtable, probably a DataProvider)
    // +0x0C: m_pSerializationSource (class with vtable, provides state buffer)
    // +0x54: m_pSlotList (class with vtable, has fields: +0x34 count, +0x50 array of slots (each 0xB0 bytes))
    // +0x60: m_frameIndex (int)
    // +0x62: m_flags (byte, bit2=needsFinalize, bit4=stateCaptured)

    void __fastcall processGhostSync()
    {
        ushort* packetPtr;
        int* slotArray;
        uint slotCount;
        uint matchIdx;
        int* slotBase;
        ushort packetEntryCount;
        uint entryIdx;
        int* entryDataPtr;
        short* statusArray;
        int* localList;
        uint listSize;
        int listIdx;
        void* stateSrc;
        void* stateDst;
        int frameIdx;
        uint* stackAllocPtr;
        int unknownRet;

        // Check if state already captured (bit 4)
        if (!(m_flags & 0x04))
        {
            // Get packet from data provider
            slotArray = (int*)(*(int*(__thiscall**)(int))(**(int**)(m_pDataProvider + 8) + 0x20))(0);
            packetPtr = (ushort*)(*(int*(__thiscall**)(int))(*slotArray + 0x14))(0);
            if (packetPtr != nullptr && (packetEntryCount = *packetPtr, packetEntryCount != 0) && ((char)packetPtr[1] == '\0'))
            {
                localList = (int*)&stack0xffffffb0; // Stack-allocated list (size unknown)
                listIdx = 0;
                if (*(int*)(m_pSlotList + 0x34) != 0)
                {
                    slotCount = 0;
                    do
                    {
                        entryIdx = 0;
                        if (packetEntryCount != 0)
                        {
                            entryDataPtr = (int*)(packetPtr + 2); // Points to packet entries (12 bytes each)
                            do
                            {
                                // Match current slot ID to packet entry ID
                                if (*(int*)(slotCount * 0xB0 + 0xC + *(int*)(m_pSlotList + 0x50)) == *entryDataPtr)
                                {
                                    // Store matched slot address and packet data
                                    localList[listIdx * 3] = slotCount * 0xB0 + *(int*)(m_pSlotList + 0x50);
                                    localList[listIdx * 3 + 1] = *(int*)(entryDataPtr + 4 + entryIdx * 0xC);
                                    listIdx++;
                                    break;
                                }
                                entryIdx++;
                                entryDataPtr += 3; // Advance to next packet entry
                            } while (entryIdx < packetEntryCount);
                        }
                        slotCount++;
                    } while (slotCount < *(uint*)(m_pSlotList + 0x34));
                }
            }

            // Get status array from data provider
            slotArray = (int*)(*(int*(__thiscall**)(int))(**(int**)(m_pDataProvider + 8) + 0x20))(0);
            statusArray = (short*)(*(int*(__thiscall**)(int))(*slotArray + 0x18))(0);
            if (statusArray == nullptr || *(int*)(statusArray + 2) == 0 || *statusArray == 0 || !checkStatusCondition())
            {
                // Not ready, set flag and finalize
                *(uint*)(m_pSlotList + 0x24) |= 0x20;
                (*(void(__thiscall**)(int))(**(int**)(m_pDataProvider + 8) + 0x20))(0);
                stackAllocPtr = (uint*)(DAT_01206880 + 0x14);
                **(undefined4**)(DAT_01206880 + 0x14) = &PTR_FUN_0112462c;   // Push allocator ID
                *stackAllocPtr += 4;
                finalizeState(); // FUN_004b9040
            }
            else
            {
                (*(void(__thiscall**)(int))(**(int**)(m_pDataProvider + 8) + 0x20))(0);
                processMatchedPackets(); // FUN_004b7970
            }

            // Capture state from serialization source
            stateSrc = (void*)(*(void*(__thiscall**)(int))(*(int*)m_pSerializationSource + 0x60))(0);
            stackAllocPtr = (uint*)(DAT_01206880 + 0x14);
            **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_0112467c;   // Push another allocator ID
            *stackAllocPtr += 4;
            *(int**)*stackAllocPtr = this;
            stateDst = (void*)(*stackAllocPtr + 0x13U & 0xFFFFFFF0);
            *stackAllocPtr = (int)stateDst;
            memcpy(stateDst, stateSrc, 0x40);
            *stackAllocPtr += 0x40;
            m_flags |= 0x04;
        }

        // Check if finalization needed (bit 2)
        if ((m_flags & 0x02) != 0 && m_ghostId != 0)
        {
            unknownRet = checkPendingAction(); // FUN_004a3790
            if (unknownRet != 0 && (*(int*)(unknownRet + 0x14) == 8 && *(int*)unknownRet != 0))
            {
                (*(void(__thiscall**)(int))(**(int**)(m_pDataProvider + 8) + 0x10))(0);
            }
        }

        // Call virtual update method
        (*(void(__thiscall**)(EARSGhostManager*))(*(int*)this + 0x84))(this);

        // Store frame index and this pointer on allocator stack
        frameIdx = m_frameIndex;
        stackAllocPtr = (uint*)(DAT_01206880 + 0x14);
        **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_011246f4;
        *stackAllocPtr += 4;
        *(int**)*stackAllocPtr = this;
        *stackAllocPtr += 4;
        *(char*)*stackAllocPtr = (char)frameIdx;
        *stackAllocPtr += 4 & 0xFFFFFFFC;
    }

private:
    int m_ghostId;           // +0x04
    int* m_pDataProvider;    // +0x08 (pointer to DataProvider)
    int* m_pSerializationSource; // +0x0C
    int* m_pSlotList;        // +0x54 (pointer to SlotList)
    int m_frameIndex;        // +0x60
    uint8_t m_flags;         // +0x62 (bits: 0x02=needsFinalize, 0x04=stateCaptured)

    // Helper functions (assumed external)
    bool checkStatusCondition(); // FUN_00416ce0
    void finalizeState();        // FUN_004b9040
    void processMatchedPackets(); // FUN_004b7970
    int checkPendingAction();     // FUN_004a3790
};

// External global for stack allocator
extern uint DAT_01206880;
extern uint PTR_FUN_0112462c;
extern uint PTR_LAB_0112467c;
extern uint PTR_LAB_011246f4;