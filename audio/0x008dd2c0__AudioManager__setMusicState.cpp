// FUNC_NAME: AudioManager::setMusicState
void __thiscall AudioManager::setMusicState(int state) {
    // +0x184: currentMusicState (int)
    // +0x1ac: pSoundData1 (void*)
    // +0x1b4: pSoundData2 (void*)
    // +0x1c8: pActiveSoundHandle (void*)
    
    if (state == 1) {
        SoundManager::stopSound(*(void**)(this + 0x1c8));
        SoundManager::setLoop(1);
        AudioManager::enterState1();
    } else if (state == 2) {
        SoundManager::stopSound(*(void**)(this + 0x1c8));
        SoundManager::setLoop(1);
        AudioManager::enterState2();
    } else if (state == 3) {
        SoundManager::setSoundPosition(*(void**)(this + 0x1c8));
        SoundManager::playSoundHash(0x637b907, 0, 0, 0); // sound hash for menu select/confirm
        SoundManager::stopSound(*(void**)(this + 0x1c8));
        SoundManager::setLoop(0);
        
        // Clear sound data pointers
        void* temp1 = *(void**)(this + 0x1ac);
        Memory::clearStruct(&temp1, 0);
        
        AudioManager::enterState3();
        
        // Additional clear using global constant
        int temp2 = DAT_0112fc6c; // some global sound ID or handle
        Memory::clearStruct(&temp2, 0);
        
        void** temp3 = (void**)(this + 0x1c8);
        Memory::clearStruct(temp3, 0);
        
        void* temp4 = *(void**)(this + 0x1b4);
        Memory::clearStruct(&temp4, 0);
    }
    
    *(int*)(this + 0x184) = state;
    
    // Global application update check
    if ((**(int**)(DAT_012233a0 + 4) != 0) && (**(int**)(DAT_012233a0 + 4) != 0x1f30)) {
        App::update();
    }
}