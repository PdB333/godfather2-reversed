// FUNC_NAME: StreamManager::updateStreamProcessing
// Address: 0x006bf2b0
// Role: Processes pending assets in the streaming queue. Iterates over an array of asset IDs,
// checks a quality/version condition, and registers them with the engine. Also updates internal
// buffer lists.

void __thiscall StreamManager::updateStreamProcessing(StreamManager* this) {
    InternalStreamData* internalData;
    uint32_t qualityLevel;
    uint32_t assetId;
    uint32_t qualityThreshold;
    uint32_t assetCount;

    internalData = this->m_internalData; // +0x10
    qualityThreshold = internalData->m_qualityThreshold; // +0x38

    // Append this->m_currentChunk (at +0x28) to the stream buffer at internalData+0xa8
    // The third parameter comes from a config object at this+0x18, offset 0x54 (e.g. streamFlags)
    FUN_006beed0(&internalData->m_streamBuffer, // +0xa8
                 &this->m_currentChunk,         // +0x28
                 this->m_config->m_streamFlags); // *(this+0x18)->+0x54

    assetCount = internalData->m_pendingAssetCount; // +0xa0
    for (uint32_t i = 0; i < assetCount; i++) {
        assetId = internalData->m_pendingAssets[i]; // array at internalData+0x9c, i*4 bytes
        qualityLevel = FUN_00791750(); // returns a quality/version number
        if (qualityLevel > 2) {
            FUN_008bf280(assetId, 2, qualityThreshold, 0); // register asset with quality=2, threshold, flag=0
        }
    }

    // Append the entire pending asset array itself to the same list (maybe to track references)
    FUN_006beed0(&internalData->m_pendingAssets, // +0x9c (address of array pointer)
                 &this->m_currentChunk,         // +0x28
                 this->m_config->m_streamFlags);
}