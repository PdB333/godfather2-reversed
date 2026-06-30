// FUNC_NAME: AudioDataManager::Initialize
void __thiscall AudioDataManager::Initialize(AudioDataManager* this, bool createStreamA, ConfigData* configData)
{
    if (createStreamA) {
        StreamHandle streamA = CreateDefaultStream();
        this->streamAHandle = streamA; // +0x10
    }
    if (configData != nullptr) {
        StreamHandle streamB = CreateStreamFromConfig(configData);
        this->streamBHandle = streamB; // +0x14
    }
    InitInternal();
    InitSubsystem();
}