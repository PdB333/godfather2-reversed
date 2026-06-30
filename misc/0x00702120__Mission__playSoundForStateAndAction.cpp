// FUNC_NAME: Mission::playSoundForStateAndAction
// Address: 0x00702120
// This function dispatches a sound ID based on the current mission state (offset +0x2DC) and action (offset +0x510).
// It calls AudioDataManager::playSound with the appropriate hash constant.

void __fastcall Mission::playSoundForStateAndAction(Mission* this)
{
    int state = *(int*)((char*)this + 0x2DC);  // mission state (1-4)
    int action = *(int*)((char*)this + 0x510); // action index (2-4)

    switch (state)
    {
    case 1:
        if (*(int*)((char*)this + 0x334) == 2) // some sub-state check (e.g., player faction)
        {
            if (action == 2)
            {
                AudioDataManager::playSound(0x985812f7);
                return;
            }
            if (action == 3)
            {
                AudioDataManager::playSound(0x25fc86b6);
                return;
            }
            if (action == 4)
            {
                AudioDataManager::playSound(0xb3a0fa75);
                return;
            }
        }
        else
        {
            if (action == 2)
            {
                AudioDataManager::playSound(0x51b3bb3b);
                return;
            }
            if (action == 3)
            {
                AudioDataManager::playSound(0xdf582efa);
                return;
            }
            if (action == 4)
            {
                AudioDataManager::playSound(0x6cfca2b9);
                return;
            }
        }
        break;

    case 2:
        if (action == 2)
        {
            AudioDataManager::playSound(0xa0c7cd29);
            return;
        }
        if (action == 3)
        {
            AudioDataManager::playSound(0x2e6c40e8);
            return;
        }
        if (action == 4)
        {
            AudioDataManager::playSound(0xbc10b4a7);
            return;
        }
        break;

    case 3:
        if (action == 2)
        {
            AudioDataManager::playSound(0x27800d64);
            return;
        }
        if (action == 3)
        {
            AudioDataManager::playSound(0xb5248123);
            return;
        }
        if (action == 4)
        {
            AudioDataManager::playSound(0x42c8f4e2);
            return;
        }
        break;

    case 4:
        if (action == 2)
        {
            AudioDataManager::playSound(0xa3d16d66);
            return;
        }
        if (action == 3)
        {
            AudioDataManager::playSound(0x3175e125);
            return;
        }
        if (action == 4)
        {
            AudioDataManager::playSound(0xbf1a54e4);
        }
        break;
    }
}