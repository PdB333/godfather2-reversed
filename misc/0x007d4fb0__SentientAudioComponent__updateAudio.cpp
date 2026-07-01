// FUNC_NAME: SentientAudioComponent::updateAudio
void __fastcall SentientAudioComponent::updateAudio(SentientAudioComponent* this)
{
    int* pOldNode;
    int iNode1;
    int iNewNode;
    int* pListHead2;
    undefined4* pAudioMgr;
    int uiResult;
    int* iSoundInstance;
    void* this1;
    undefined4 uVar5;
    undefined4 uVar6;
    int* pListHead1;
    // Parameter struct for audio creation (size=0x14?)
    undefined4 audioCreateParams[3];
    
    // Get character data pointer (offset +0x58)
    CharacterData* charData = *(CharacterData**)(this + 0x58);
    
    // Check bit 4 of flags at charData+0x8e0
    // This flag indicates whether the character should process audio/camera updates
    if ((*(uint*)(charData + 0x8e0) >> 4 & 1) != 0)
    {
        // Get a new audio node from the camera/audio pool
        iNewNode = FUN_007ff880();
        if (iNewNode == 0)
        {
            iNode1 = 0;
        }
        else
        {
            iNode1 = iNewNode + 0x48;  // Node header? 
        }
        
        // Manage linked list at this+0x9c (camera/audio list head)
        pListHead1 = (int*)(this + 0x9c);
        if (*pListHead1 != iNode1)
        {
            if (*pListHead1 != 0)
            {
                FUN_004daf90(pListHead1);  // Remove old node from list
            }
            *pListHead1 = iNode1;  // Set new head
            if (iNode1 != 0)
            {
                *(undefined4*)(this + 0xa0) = *(undefined4*)(iNode1 + 4);  // Store previous next?
                *(int**)(iNode1 + 4) = pListHead1;  // Set node's prev pointer to list head
            }
        }
        
        // Update subsystems
        FUN_007ab120();  // Update camera/audio manager
        FUN_00896e60();  // Update visual effects
        FUN_00460840();  // Update HUD
        
        // Get audio manager pointer
        pAudioMgr = (undefined4*)FUN_009c8f80();
        audioCreateParams[0] = 2;
        audioCreateParams[1] = 0x10;
        audioCreateParams[2] = 0;
        // Call virtual function to allocate sound object (0x80 = some sound type)
        uiResult = (**(code**)*pAudioMgr)(0x80, &audioCreateParams);
        if (uiResult != 0)
        {
            iSoundInstance = (int*)FUN_006d9ee0();  // Create sound instance
        }
        else
        {
            iSoundInstance = 0;
        }
        
        // Manage another linked list at this+0x94 (sound list head)
        pListHead2 = (int*)(this + 0x94);
        if (*pListHead2 != (int)iSoundInstance)
        {
            if (*pListHead2 != 0)
            {
                FUN_004daf90(pListHead2);  // Remove old sound instance
            }
            *pListHead2 = (int)iSoundInstance;  // Set new head
            if (iSoundInstance != 0)
            {
                *(undefined4*)(this + 0x98) = *(undefined4*)(iSoundInstance + 4);  // Store previous next
                *(int**)(iSoundInstance + 4) = pListHead2;  // Set node's prev pointer
            }
        }
        
        // Set sound instance properties from global constants
        iSoundInstance = (int*)*pListHead2;
        *(undefined4*)(iSoundInstance + 0x24) = DAT_00d5efd4;  // Some audio pitch/volume
        *(undefined4*)(iSoundInstance + 0x20) = _DAT_00d5780c; // Some offset/position
        
        FUN_006d9da0();  // Play sound
        FUN_00424ea0(*(undefined4*)(&DAT_00002494 + (int)charData), *pListHead2, 0);  // Attach sound to character
        
        // UI/HUD related allocation
        uVar5 = FUN_00799100(0x20);  // Allocate 0x20 bytes (UI element?)
        uVar6 = (**(code**)(*(int*)((int)charData + 0x1f30) + 8))(uVar5);  // Virtual call on character data
        FUN_00444660(uVar6, uVar5);  // Register UI object
        
        // If camera/audio node is present and not a special reserved node (0x48), and component pointer exists…
        if (((*pListHead1 != 0) && (*pListHead1 != 0x48)) && (*(int**)(this + 0x88) != 0))
        {
            (**(code**)(**(int**)(this + 0x88) + 4))();  // Call component update
        }
        
        FUN_006913c0(5);  // Set update timer to 5 (ms?)
        *(undefined4*)(this + 0xc0) = _DAT_00d5780c;  // Store timestamp or counter
        return;
    }
    else
    {
        // Fallback update if flag not set
        FUN_00624d00();
        return;
    }
}