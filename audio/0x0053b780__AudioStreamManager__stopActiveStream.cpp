// FUNC_NAME: AudioStreamManager::stopActiveStream
void AudioStreamManager::stopActiveStream(char bUpdatePosition, float param2)
{
    // +0x01125388: g_currentStreamIndex (dword index into stream state array)
    // +0x01125389: g_currentHandleIndex (byte index into handle array)
    // +0x011252e8: g_pAudioDataManager
    // +0x011252ec: g_pStreamManager
    // +0x01125400: g_streamStateArray (struct size 0x38)
    // +0x011254b0: g_handleArray (struct size 0x3c)
    // +0x012234c4: g_pPositionProvider (object with vtable, e.g. Camera or Player)

    AudioDataManager* pAudioDataMgr = reinterpret_cast<AudioDataManager*>(DAT_011252e8);
    StreamManager* pStreamMgr = reinterpret_cast<StreamManager*>(DAT_011252ec);
    uint32_t streamIdx = DAT_01125388;  // dword index
    uint8_t handleIdx = DAT_01125389;   // byte index

    // Release first two slots of the stream state array
    StreamState* pStreamState = &g_streamStateArray[streamIdx];
    if (pStreamState->ptr0 != nullptr) {
        pAudioDataMgr->freeBuffer(pStreamState->ptr0);  // FUN_0060b020
    }
    if (pStreamState->ptr4 != nullptr) {
        pAudioDataMgr->freeHandle(pStreamState->ptr4);  // FUN_0060aea0
    }

    // Now handle the handle array
    HandleState* pHandleState = &g_handleArray[handleIdx];
    if (pHandleState->ptr0 != nullptr) {
        if (bUpdatePosition && (*(int*)(DAT_012234c4 + 0x24) != 0)) {
            // Get position from the provider (e.g., Camera or Player)
            int* pPositionProvider = *(int**)(DAT_012234c4 + 0x24);
            int (*getPositionFunc)(void*) = (int(*)(void*))(*(int*)pPositionProvider)[1];  // vtable[1]
            int iVar1 = getPositionFunc((void*)((int)this + 0x30));
            if (iVar1 != 0) {
                // Update stream position with 3D vector and param
                float pos[3];
                pos[0] = *(float*)(iVar1 + 0x20);
                pos[1] = *(float*)(iVar1 + 0x24);
                pos[2] = *(float*)(iVar1 + 0x28);
                float param = param2;

                pStreamMgr->addPositionedData(pHandleState->ptr0 + 0x10, pos);  // FUN_0060add0
                pStreamMgr->addPositionedData(pHandleState->ptr4, &pos);        // FUN_0060add0
                pAudioDataMgr->addPositionedData(pStreamState->ptr8, iVar1);     // FUN_0060add0
                pAudioDataMgr->addPositionedData(pStreamState->ptrC, *(int*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 0x24) + 0x70);
                return;
            }
        }
        // Fallback: clear position
        float zeroPos[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        pAudioDataMgr->addPositionedData(pStreamState->ptr8, &zeroPos);  // FUN_0060add0
    }
    return;
}