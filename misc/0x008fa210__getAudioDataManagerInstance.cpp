// FUNC_NAME: getAudioDataManagerInstance
// Address: 0x008fa210
// Returns a pointer to the AudioDataManager instance (global + 0x380 offset)
// The global DAT_0112af68 likely points to the main game object or manager container.
AudioDataManager* getAudioDataManagerInstance()
{
    return (AudioDataManager*)(*(uint32_t*)0x0112af68 + 0x380);
}