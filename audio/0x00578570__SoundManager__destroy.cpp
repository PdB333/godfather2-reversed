// FUNC_NAME: SoundManager::destroy  
// Address: 0x00578570  
// Role: Destructor for a sound/audio manager class. Cleans up an array of sound objects (each 0xE0 bytes) and a secondary audio data manager object.  

void __fastcall SoundManager::destroy(SoundManager* this)  
{  
    // Set initial vtable (likely for partial destruction)  
    this->vtable = &PTR_FUN_00e3ac08;  

    // Iterate over sound array (offset +0x2EC = m_sounds, +0x2E4 = m_numSounds)  
    if (this->m_numSounds > 0)  
    {  
        for (int i = 0; i < this->m_numSounds; i++)  
        {  
            Sound* sound = &this->m_sounds[i];  
            // Call first virtual function on each sound (likely stop/cleanup) with parameter 0  
            sound->virtualFunction0(0);  
        }  
    }  

    // Delete the sound array using global memory manager  
    // DAT_0120556c points to memory manager vtable; +4 is deallocation function  
    (**(void (__fastcall**)(void*, int))(*DAT_0120556c + 4))(this->m_sounds, 0);  

    // Update vtable for final destruction phase  
    this->vtable = &PTR_FUN_00e3ac24;  

    // Handle owned audio data manager (offset +0x64 = m_audioDataManager)  
    AudioDataManager* audioMgr = this->m_audioDataManager;  
    if (audioMgr != nullptr)  
    {  
        // Destroy first sub-object (offset 0 from audioMgr)  
        // audioMgr->data[4] is a pointer to internal object; first virtual call on it  
        (**(void (__fastcall**)(void*, int))(*(int*)(audioMgr->field_4) + 4))(audioMgr->field_0, 0);  

        // Destroy second sub-object (offset 0xC from audioMgr)  
        (**(void (__fastcall**)(void*, int))(*(int*)(audioMgr->field_4) + 4))(audioMgr->field_C, 0);  

        // Call virtual destructor on audioMgr itself (vtable+12)  
        (**(void (__fastcall**)())(*(int*)audioMgr->field_4 + 0xC))();  

        // Deallocate audioMgr  
        (**(void (__fastcall**)(void*, int))(*DAT_0120556c + 4))(this->m_audioDataManager, 0);  
    }  

    return;  
}