// FUNC_NAME: ComponentManager::updateAllComponents
// Function address: 0x00519b60
// Updates all components while a certain state flag is not set.
// The manager object has:
//   +0xd4: pointer to component data (m_pData)
//   +0xd8: number of components (m_nCount)
// 
// If the flag at (m_pData+0x10) has any of bits 0x4480000 set, the update is skipped.
// Otherwise, it loops m_nCount times, each time calling updateSingleComponent on the data pointer,
// followed by two calls to processPendingEvents.

void __thiscall ComponentManager::updateAllComponents(int this)
{
    // Check if the component system is in a valid state
    // The flag at data+0x10 likely holds status bits (e.g., paused, disabled)
    if ((*(unsigned int*)(*(int*)(this + 0xd4) + 0x10) & 0x4480000) == 0)
    {
        // Loop through each component entry
        int count = *(int*)(this + 0xd8);
        for (int i = 0; i < count; i++)
        {
            // Update the component (single iteration)
            updateSingleComponent(*(int*)(this + 0xd4));
            
            // Process pending events twice (possibly to handle queued changes)
            processPendingEvents();
            processPendingEvents();
        }
    }
    return;
}