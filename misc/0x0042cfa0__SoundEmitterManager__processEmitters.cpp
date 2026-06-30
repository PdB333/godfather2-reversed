// FUNC_NAME: SoundEmitterManager::processEmitters
void SoundEmitterManager::processEmitters(void* param_2, SourceList* pList, void* param_4, uint8_t* param_5, uint32_t param_6, int32_t param_7) {
    // Global masks for audio system
    uint32_t uGlobalMask = _DAT_012053d8;   // Global enable/disable mask
    uint16_t uGlobalFlags = _DAT_012053dc;  // Additional per-slot flags
    param_6 |= uGlobalMask;                 // Merge global override

    // Iterate over array of source objects (each 0xB0 bytes)
    SourceObject* pElem = reinterpret_cast<SourceObject*>(pList->pArrayBase); // pList+0x50
    SourceObject* pEnd = reinterpret_cast<SourceObject*>(
        reinterpret_cast<uint8_t*>(pElem) + pList->numSources * 0xB0); // pList+0x34 (count) * stride
    bool bHadType6 = false;
    bool bHadNonType6 = false;

    if (pElem == pEnd) return; // Empty list

    // Get thread-local audio mixer structure (via FS segment)
    AudioMixer* pMixer = *reinterpret_cast<AudioMixer**>(__readfsdword(0x2C)); // FS:[0x2C] -> pointer to mixer

    do {
        uint16_t uParamMask = static_cast<uint16_t>(param_6);
        uint8_t* pOutput; // points to either param_5 or local buffer

        if (pElem->activeCount == 0) { // +0x28: active count (0 = inactive)
            if (pElem->type == 1) {    // +0x04: type (1 = something special)
                goto LAB_prepareTransform;
            }
            // Check flags and global condition
            if ((pElem->flags & 0x803C) == 0 && ((uGlobalFlags & uParamMask) != 0)) {
                pElem->flags |= 0x10000; // Set a "global override" flag
            }
            goto LAB_skipTransform;
        }
        else {
            // activeCount != 0
            if (pElem->type == 1) {
LAB_prepareTransform:
                pOutput = param_5;
                // Only if flags have bit 3 set, no child (byte at +0x06 == 0), and either master flag or no bit 4
                if ((pElem->flags & 8) != 0 && pElem->childHandle == 0) {
                    bool bMaster = *reinterpret_cast<char*>(reinterpret_cast<uint8_t*>(pList) + 0x2F) != 0;
                    if (bMaster || (pElem->flags & 0x10) == 0) {
                        FUN_00417560(); // Likely prepares audio processing
                        float* pSrc = reinterpret_cast<float*>(pElem->interpData); // +0x20: pointer to 7 floats
                        // Compute interpolation delta
                        float dx = (pSrc[4] - pSrc[0]) * DAT_00e2cd54; // scaling factor
                        float dy = (pSrc[5] - pSrc[1]) * DAT_00e2cd54;
                        float dz = (pSrc[6] - pSrc[2]) * DAT_00e2cd54;
                        float len = sqrt(dz*dz + dx*dx + dy*dy);
                        // New position = old + delta
                        float newPos[3];
                        newPos[0] = pSrc[0] + dx;
                        newPos[1] = pSrc[1] + dy;
                        newPos[2] = pSrc[2] + dz;
                        // Transform and store in local buffer
                        FUN_0042a1a0(newPos, local_50); // local_50 is defined earlier
                        pOutput = local_60; // local_60 is another buffer (maybe 16 bytes)
                    }
                }
            }
            else {
LAB_skipTransform:
                if (pElem->type == 1) goto LAB_prepareTransform;
                // Otherwise transform from source's position directly
                FUN_0042a1a0(pElem->position, param_4); // pElem+0x10
                pOutput = local_60;
            }
        }

        uint32_t uFlags = pElem->flags; // +0x08
        reinterpret_cast<uint32_t*>(&pElem->field_0x5C)[0] = param_2; // Store param_2

        // Determine state code (0-6)
        uint32_t uState;
        if ((uFlags & 0x20) != 0) {
            uState = 6;
        }
        else if ((uFlags & 0x0C) != 0) {
            uState = 3;
        }
        else {
            if (pElem->activeCount < 1) {
                if (pElem->type == 1 || (uFlags & 0x10) != 0) {
                    uState = 1;
                }
                else if ((uFlags & 0x8000) == 0) {
                    uState = (uFlags >> 14) & 4; // 0 or 4
                }
                else {
                    uState = 5;
                }
            }
            else {
                uState = 2;
            }
        }
        pElem->stateCode = static_cast<int8_t>(uState); // +0x29

        // Compute output mask, respecting mixer's channels
        uint32_t uOutMask = param_6 & 0xFFFF;
        if ((uFlags & 0x800) != 0) {
            uOutMask = static_cast<uint32_t>(~(pMixer->excludedMask)) & uParamMask; // pMixer+0x20
        }
        uint16_t mixerMask = pMixer->enableMask; // +0x0C
        uint16_t mixerDisableMask = pMixer->disableMask; // +0x0E
        if ((mixerMask & uOutMask) != 0 && (mixerDisableMask & uOutMask) != 0) {
            uOutMask &= ~mixerMask; // Remove channels that are enabled
        }

        // Execute action based on state
        switch (uState) {
            case 0:
            case 1:
            case 3:
            case 4:
                FUN_004c4ba0(pElem, param_4, pOutput, uOutMask, 0); // process with count=0
                bHadNonType6 = true;
                // fall through to default
            default:
                if (uState == 0 || (uState > 1 && uState < 4)) {
                    // Write param_7 to a slot in an array of channel structs
                    // Array base: this+0x1240, elements of size 0x6A0
                    ChannelSlot* pSlot = reinterpret_cast<ChannelSlot*>(
                        reinterpret_cast<uint8_t*>(this) + 0x1240 + uState * 0x6A0);
                    // pElem->field_0x2A is a short index
                    reinterpret_cast<int32_t*>(&pSlot->channels[pElem->channelIndex])[0x1C/4] = param_7;
                }
                break;
            case 2:
                {
                    int iCount = static_cast<int>(pElem->activeCount);
                    if (pElem->activeCount == 0) iCount = 1;
                    FUN_004c4ba0(pElem, param_4, pOutput, uOutMask, iCount);
                    bHadNonType6 = true;
                    // Same write as default
                    if (uState == 0 || (uState > 1 && uState < 4)) {
                        ChannelSlot* pSlot = reinterpret_cast<ChannelSlot*>(
                            reinterpret_cast<uint8_t*>(this) + 0x1240 + uState * 0x6A0);
                        reinterpret_cast<int32_t*>(&pSlot->channels[pElem->channelIndex])[0x1C/4] = param_7;
                    }
                }
                break;
            case 5:
                FUN_004c4ba0(pElem, param_4, pOutput, uOutMask, 0);
                // Invoke callback
                if (reinterpret_cast<void(*)(void)>(this->callback3A24) == nullptr) {
                    reinterpret_cast<void(*)(SourceObject*)>(this->callback3A10)(pElem);
                }
                else {
                    reinterpret_cast<void(*)(void)>(this->callback3A24)(&this->callback3A10);
                }
                break;
            case 6:
                bHadType6 = true;
                break;
        }

        pElem = reinterpret_cast<SourceObject*>(reinterpret_cast<uint8_t*>(pElem) + 0xB0);
    } while (pElem != pEnd);

    // If only type-6 emitters were processed and none of the others, call a fallback stop function
    if (bHadType6 && !bHadNonType6) {
        FUN_004c7580(); // Stop/finalize idle sources
    }
}