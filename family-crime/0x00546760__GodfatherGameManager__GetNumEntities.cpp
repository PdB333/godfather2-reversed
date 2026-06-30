// FUNC_NAME: GodfatherGameManager::GetNumEntities
unsigned int __fastcall GetNumEntities(GodfatherGameManager* _this)
{
    // +0x2E8: pointer to an internal manager (likely EntityManager)
    // +0x10 from that pointer: number of active entities (count)
    return *(unsigned int*)(*(int**)((char*)_this + 0x2E8) + 0x10);
}