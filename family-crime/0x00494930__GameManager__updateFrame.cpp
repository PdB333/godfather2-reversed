// FUNC_NAME: GameManager::updateFrame
void GameManager::updateFrame()
{
    // Global pre-update (e.g., timer, input polling)
    updateGlobalTimers(); // 0x00490b20

    // If streaming object exists, process it with handle and buffer
    if (this->m_pStreamingObject != nullptr)          // +0x1c0
    {
        processStreamingObject(                       // 0x0060ad20
            this->m_nStreamHandle,                    // +0x14
            this->m_pStreamingObject,                 // +0x1c0
            &this->m_streamBuffer                     // +0x1d0
        );
    }

    // Scene/game logic updates
    updateSceneLogic();   // 0x00492190
    updateRendering();    // 0x00494220
}