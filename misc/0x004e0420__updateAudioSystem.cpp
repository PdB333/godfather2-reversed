// FUNC_NAME: updateAudioSystem
void updateAudioSystem(void)
{
    // Get the global audio manager instance
    AudioManager* audioMgr = getAudioManager();
    
    // Update the audio system (process pending audio events, mix, etc.)
    audioManagerUpdate(audioMgr);
}