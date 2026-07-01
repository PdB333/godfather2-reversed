// FUNC_NAME: Player::canPerformActionOnEntity
undefined4 __fastcall Player::canPerformActionOnEntity(int this)
{
    char cResult;
    int pEntity;
    
    // Get entity pointer from entity ID stored at +0x13C (m_targetEntityID)
    pEntity = (int)getEntityByID(*(uint*)(this + 0x13C));
    
    if ((pEntity != 0) && (*(int*)(pEntity + 0xFC) != 0) && (*(int*)(*(int*)(pEntity + 0xFC) + 0x3C) == 0))
    {
        // Check action conditions using entity pointer, two fields from this (likely output params)
        cResult = checkActionConditions(pEntity, (int)(this + 0x158), (int)(this + 0x144), (char*)(this + 0x16C));
        if ((cResult != '\0') && (*(char*)(this + 0x16C) != '\0'))
        {
            return 1;
        }
    }
    return 0;
}