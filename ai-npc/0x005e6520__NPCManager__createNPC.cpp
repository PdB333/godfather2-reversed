// FUNC_NAME: NPCManager::createNPC
undefined4 NPCManager::createNPC(int npcObject, undefined4 templateId)
{
    undefined4 result;
    
    result = 0;
    if (npcObject != 0) {
        // Initialize base class fields and data
        initBase(npcObject);
        // Initialize NPC-specific fields and data
        initSpecific(npcObject);
        // Register the NPC with the global NPCManager and return a handle (templateId used for lookup)
        result = registerNPC(g_npcManager, templateId);
    }
    return result;
}