// FUNC_NAME: SoundManager::triggerPositionalSound
void __thiscall SoundManager::triggerPositionalSound(SoundManager* this) {
    int* pSoundSource;
    int* pTransform;
    Vector4 localPos;

    // Check if we have a valid sound source and its transform (offset +0x1e0 is sound source, +8 is transform)
    if ((*(int*)((int)this + 0x1e0) != 0) && (*(int*)(*(int*)((int)this + 0x1e0) + 8) != 0)) {
        // Get the listener/camera position from the global audio system
        pTransform = (int*)getAudioListenerTransform();
        // Read position components (offsets 0x30, 0x34, 0x38 correspond to x,y,z)
        localPos.x = *(float*)(pTransform + 0x30);
        localPos.y = *(float*)(pTransform + 0x34);
        localPos.z = *(float*)(pTransform + 0x38);
        localPos.w = 0.0f;
        // Play the sound at that position (second param 0 = no looping)
        playPositionalSound(&localPos, 0);
    }
}