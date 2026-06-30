// FUNC_NAME: EntityList::addAllSentients
void EntityList::addAllSentients()
{
    // Get global SimManager singleton (FUN_00ad8d40)
    SimManager* simMgr = SimManager::getInstance();
    if (simMgr == nullptr)
        simMgr = nullptr; // redundant but original code

    // Get SentientManager via vtable +0x34
    SentientManager* sentientMgr = simMgr->getSentientManager(); // vtable[0x34/4] = 0x0d

    // Get the sentient list/iterator via vtable +0x24 on SentientManager
    SentientList* sentientList = sentientMgr->getSentientList(); // vtable[0x24/4] = 0x09

    // Get number of sentients via vtable +0x20 on the list
    uint32 count = sentientList->getCount(); // vtable[0x20/4] = 0x08

    // Iterate over all sentients
    for (uint32 i = 0; i < count; ++i)
    {
        // Get sentient at index via vtable +0x24 on list
        Sentient* sentient = sentientList->getSentient(i); // vtable[0x24/4] = 0x09
        if (sentient)
        {
            // Add this sentient to the entity list via vtable +0x20 on this
            this->addSentient(sentient); // vtable[0x20/4] = 0x08
        }
    }
}