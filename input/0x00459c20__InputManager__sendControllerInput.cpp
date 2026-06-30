// FUNC_NAME: InputManager::sendControllerInput

// Function address: 0x00459c20
// Role: Processes controller input states and sends network packets for each active controller.
// Uses alternate channels (left/right analog?) based on a toggle (m_useAlternateChannel).
// Builds packets of 16 DWORDs (64 bytes) from the input state and sends them via a network chain.

// Relevant structures:
// InputManager (size unknown):
//   +0x30: int m_inputStateId (compared against DAT_0110ab30 / DAT_0110ab2c)
//   +0x2d: bool m_useAlternateChannel (toggles between 0/1 each call)
//   +0x2e: char m_firstRun (guard flag)
//   +0x2f: bool m_lastWasAlternate
//   +0x34: int m_controllerCount
//   +0x50: Controller* m_pControllers (array of 0xB0-sized structs)

// Controller struct (0xB0 bytes):
//   +0x00: virtual table pointer
//   +0x04: byte m_inputType (1 = gamepad?)
//   +0x06: byte m_active
//   +0x08: uint16 m_flags (0x0010 = needsSend, 0x4000 = direct copy mode)
//   +0x34: int m_packetOffset
//   +0x38: ushort m_compressedCount
//   +0x3E: ushort m_uncompressedCount
//   +0x48: undefined4 m_compressedBuffer
//   +0x64: Buffer* m_alternateBuffers[2]  // one per channel toggle
//   +0x70: ChainNode* m_chainNodes[2]     // current chain node for each channel
//   +0x88: int m_bufferSize

// Global constants (addresses unknown, likely config values):
extern int DAT_0110ab30;   // "initialized" state id
extern int DAT_0110ab2c;   // alternate state id

// External functions (guessed names):
void lockMutex();                                   // FUN_0060be40
void unlockMutex();                                 // FUN_0060be40 (second call)
void FUN_00417560();                                // probably something like resetBuffer
void sendChainPacket(ChainNode*, void* packetData, uint32 compressedBuffer, int bufferSize, uint32 packetCount); // FUN_004cdd90

void __thiscall InputManager::sendControllerInput(uint32* pInputData) {
    // pInputData is a 64-byte (16 DWORD) raw input state structure

    // Obtain the controller manager (this+0x50)
    ControllerMgr* pMgr = *(ControllerMgr**)(this + 0x50);

    // Check if the input state ID has changed
    if (pMgr->m_inputStateId != DAT_0110ab30) {
        bool bWasAlternate = (pMgr->m_inputStateId == DAT_0110ab2c);
        pMgr->m_inputStateId = DAT_0110ab30;
        pMgr->m_useAlternateChannel ^= 1;       // toggle alternate flag
        pMgr->m_lastWasAlternate = bWasAlternate;
        pMgr->m_firstRun = 0;
    }

    // First-run guard: skip processing if already done for this frame
    if (pMgr->m_firstRun == 0) {
        pMgr->m_firstRun = 1;

        ChainNode* pCurrentChain = nullptr;
        int chainOffset = 0;
        uint32 i = 0;

        if (pMgr->m_controllerCount != 0) {
            int controllerBase = 0;  // byte offset into pControllers array
            Controller* pControllers = pMgr->m_pControllers;

            do {
                // Pointer to current controller struct
                Controller* pCtrl = (Controller*)((uint8*)pControllers + controllerBase);

                // Check if this controller needs to send data (bit 0x10)
                if ((pCtrl->m_flags & 0x10) != 0) {
                    // Determine which alternate channel to use (based on m_useAlternateChannel)
                    uint32 channelIdx;
                    if ((pCtrl->m_inputType == 1) && (pCtrl->m_active != 0)) {
                        channelIdx = pMgr->m_useAlternateChannel;
                    } else {
                        channelIdx = 0;
                    }

                    int packetOffset = pCtrl->m_packetOffset;
                    Buffer* pBuffer = pCtrl->m_alternateBuffers[channelIdx];
                    uint16 compressedCount = pCtrl->m_compressedCount;
                    uint32 uncompressedCount = pCtrl->m_uncompressedCount;

                    uint32 compressedValue;
                    if (*(char*)((uint8*)pBuffer + 7) == 0) {
                        // Buffer is uncompressed, use raw storage
                        compressedValue = pBuffer->m_rawData;
                        *(uint8*)((uint8*)pBuffer + 0x1D) = 1;   // mark buffer as locked
                    } else {
                        // Buffer is compressed, decompress first
                        uint32 temp = 0;
                        // Call virtual function at vtable+0x2C (decompress)
                        (*(void (**)(void*, int, int, uint32*, int))(*pBuffer->vtable + 0x2C))(
                            pBuffer->vtable, 0, 0, &temp, 0x10);
                        compressedValue = temp;
                    }

                    int bufferSize = pCtrl->m_bufferSize;
                    // Select the chain node for the current alternate channel
                    ChainNode* pTargetChain = pCtrl->m_chainNodes[channelIdx];

                    // If we changed chain node, finish the previous chain and start a new one
                    if (pCurrentChain != pTargetChain) {
                        if (pCurrentChain != nullptr) {
                            if (*(char*)((uint8*)pCurrentChain + 0x28) == 0) {   // check if chain is compressed
                                *(uint8*)((uint8*)pCurrentChain + 0x29) = 0;    // mark chain as finalized
                            } else {
                                lockMutex();
                                // Call virtual function at vtable+0x30 (finalize and send)
                                (*(void (**)(void*))(*pCurrentChain->vtable + 0x30))(pCurrentChain->vtable);
                                pMgr = *(ControllerMgr**)(this + 0x50);  // reload (in case freed)
                            }
                        }
                        pCurrentChain = pTargetChain;
                        if (*(char*)((uint8*)pTargetChain + 0x28) == 0) {
                            chainOffset = pTargetChain->m_baseOffset;
                            *(uint8*)((uint8*)pTargetChain + 0x29) = 1;    // mark as building
                        } else {
                            uint32 flags = 0;
                            if (*(char*)((uint8*)pTargetChain + 8) != 0) {   // check if chain requires 0x3000 flag
                                flags = 0x3000;
                            }
                            // Call virtual function at vtable+0x2C (prepare chain buffer)
                            (*(void (**)(void*, int, int, uint32*, uint32))(*pTargetChain->vtable + 0x2C))(
                                pTargetChain->vtable, 0, 0, (uint32*)((uint8*)pTargetChain + 0x14), flags);
                            chainOffset = *(uint32*)((uint8*)pTargetChain + 0x14);
                        }
                    }

                    // Compute the destination write pointer in the chain buffer
                    ChainNode* pWriteDest = (ChainNode*)(chainOffset + packetOffset * 2);

                    // Decide how to copy data based on flags
                    if ((pCtrl->m_flags & 0x4000) == 0) {
                        // Normal mode: build packet from param_1 (pInputData)
                        uint32 packetData[16];
                        if (pCtrl->m_active == 0) {
                            FUN_00417560();   // likely a reset function
                        } else {
                            // Copy the 16 DWORDs from input data to local stack
                            packetData[0] = pInputData[0];
                            packetData[1] = pInputData[1];
                            packetData[2] = pInputData[2];
                            packetData[3] = pInputData[3];
                            packetData[4] = pInputData[4];
                            packetData[5] = pInputData[5];
                            packetData[6] = pInputData[6];
                            packetData[7] = pInputData[7];
                            packetData[8] = pInputData[8];
                            packetData[9] = pInputData[9];
                            packetData[10] = pInputData[10];
                            packetData[11] = pInputData[11];
                            packetData[12] = pInputData[12];
                            packetData[13] = pInputData[13];
                            packetData[14] = pInputData[14];
                            packetData[15] = pInputData[15];
                        }
                        // Send the packet via the chain
                        sendChainPacket(pWriteDest, packetData, pCtrl->m_compressedBuffer, bufferSize, uncompressedCount);
                    } else if (uncompressedCount != 0) {
                        // Direct copy mode: copy 6-byte elements from buffer to chain
                        int delta = bufferSize - (int)pWriteDest;
                        uint32 elements = uncompressedCount;
                        do {
                            // Copy 6 bytes (one DWORD + one WORD)
                            *(uint32*)pWriteDest = *(uint32*)(delta + (int)pWriteDest);
                            *(uint16*)((uint8*)pWriteDest + 4) = *(uint16*)(delta + 4 + (int)pWriteDest);
                            pWriteDest = (ChainNode*)((uint8*)pWriteDest + 6);
                            elements--;
                        } while (elements != 0);
                    }

                    // Finish buffer usage
                    if (*(char*)((uint8*)pBuffer + 7) == 0) {
                        *(uint8*)((uint8*)pBuffer + 0x1D) = 0;   // unlock buffer
                    } else {
                        // Release compressed buffer
                        (*(void (**)(void*))(*pBuffer->vtable + 0x30))(pBuffer->vtable);
                    }
                }

                controllerBase += 0xB0;   // move to next controller
                i++;
            } while (i < pMgr->m_controllerCount);

            // Finalize the last chain node if used
            if (pCurrentChain != nullptr) {
                if (*(char*)((uint8*)pCurrentChain + 0x28) != 0) {
                    lockMutex();
                    (*(void (**)(void*))(*pCurrentChain->vtable + 0x30))(pCurrentChain->vtable);
                    return;
                }
                *(uint8*)((uint8*)pCurrentChain + 0x29) = 0;   // mark chain as finalized
            }
        }
    }
}