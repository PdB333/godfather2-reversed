// FUNC_NAME: SoundManager::playStream
void __thiscall SoundManager::playStream(SoundManager* this, SoundRequestData* pRequest)
{
    int streamBankBase;
    int currentStreamId;
    int handle1, handle2;
    int unusedVar;
    void* pSoundData1 = nullptr;
    void* pSoundData2 = nullptr;
    void* pBankObject = nullptr;
    int soundIndex1, soundIndex2;
    
    // If we have a sound bank pointer, get the base of the bank (offset -0x48 seems to adjust to a base structure)
    if (this->m_pSoundBank != nullptr) {
        streamBankBase = (int)(this->m_pSoundBank) - 0x48;
    } else {
        streamBankBase = 0;
    }
    // Read the current stream ID from the bank's large array (offset 0x1f3c)
    currentStreamId = *(int*)(streamBankBase + 0x1f3c);
    this->m_currentStreamId = currentStreamId;
    // Reset timer to 0xFFFF (no timeout)
    this->m_streamTimer = 0xFFFF;
    
    if (currentStreamId != 0) {
        // Initialize the request? (FUN_007cd190)
        initRequestData(pRequest);
        
        // Save old handles and clear them
        int savedHandle2 = this->m_hStream2;
        this->m_hStream2 = 0;
        this->m_hStream1 = 0;
        int savedHandle1 = 0;   // Actually overwritten as local
        pSoundData1 = nullptr;
        pSoundData2 = nullptr;
        
        // Load/release the old handles
        int newHandle1 = SoundHandleLoader::loadOrRelease(savedHandle2);
        this->m_hStream1 = newHandle1;
        if (newHandle1 == 0) {
            // If failed, load default handle (0)
            savedHandle2 = SoundHandleLoader::loadOrRelease(0);
            this->m_hStream1 = savedHandle2;
        }
        savedHandle2 = SoundHandleLoader::loadOrRelease(this->m_hStream1);
        this->m_hStream2 = savedHandle2;
        
        // Extract data pointers from handles
        if (this->m_hStream1 != 0) {
            void* pData1 = SoundHandleLoader::getData(this->m_hStream1);
            if (pData1 != 0) {
                pSoundData1 = *(void**)((int)pData1 + 0x54);
            }
        }
        if (this->m_hStream2 != 0) {
            void* pData2 = SoundHandleLoader::getData(this->m_hStream2);
            if (pData2 != 0) {
                pSoundData2 = *(void**)((int)pData2 + 0x54);
            }
        }
        
        // Get sound indices from the request data (at +0x10)
        int* pRequestData = *(int**)((int)pRequest + 0x10);
        soundIndex1 = *(int*)((int)pRequestData + 0x3c);
        soundIndex2 = *(int*)((int)pRequestData + 0x34);
        
        // Resolve first sound effect pointer
        if (soundIndex1 >= 0 && g_audioQualityLevel >= 3) {
            int* pSoundList = *(int**)(*(int*)(this->m_currentStreamId) + 0x20);
            if (pSoundList == 0) {
                pSoundEffect1 = SoundEffectManager::getSoundEffect(0);
            } else {
                pSoundEffect1 = SoundEffectManager::getSoundEffect(pSoundList[soundIndex1]);
            }
        } else {
            pSoundEffect1 = 0;
        }
        
        // Resolve second sound effect pointer
        if (soundIndex2 >= 0) {
            int* pSoundList2 = *(int**)(*(int*)(this->m_currentStreamId) + 0x20);
            if (pSoundList2 == 0) {
                pSoundEffect2 = 0;
            } else {
                pSoundEffect2 = SoundEffectManager::getSoundEffect(pSoundList2[soundIndex2]);
            }
        } else {
            pSoundEffect2 = 0;
        }
        
        // Play the mixed audio stream
        AudioMixer::playStream(pSoundData1, pSoundData2, pSoundEffect1, pSoundEffect2);
    }
}