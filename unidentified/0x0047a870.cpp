// 0x0047a870: MissionManager::handleActionObjectCreation
void MissionManager::handleActionObjectCreation()
{
    uint8_t flags = *(uint8_t*)(this + 0x5e);

    if ((flags & 2) != 0)
    {
        int* pActionObj = *(int**)(this + 0x60);

        if (pActionObj == nullptr)
        {
            // No existing action object: create a "start" effect/object with type 0
            stopAudioChannel(-1);
            int* newObj = (int*)findOrCreateByHash(0, (void*)(this + 0x20), 0x137726b7, -1);
            if (newObj != nullptr)
            {
                // Set a flag (bit 0) on the new object to indicate it's active
                *(uint32_t*)(newObj + 4) |= 1;
                return;
            }
        }
        else
        {
            // Existing action object: create/update a "completion" object with type 4
            int* newObj = (int*)findOrCreateByHash(4, (void*)(this + 0x20), 0x5e1f74a6, -1);
            if (newObj != nullptr)
            {
                // Store the pointer to the original action object in the new object's value field
                *(uint32_t*)(newObj + 0xc) = (uint32_t)pActionObj;
            }
        }
    }
}