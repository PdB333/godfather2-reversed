// FUNC_NAME: CGameObjectManager::GetObjectByFlag
int __thiscall CGameObjectManager::GetObjectByFlag(int bFlag)
{
    int result;
    
    if (bFlag != 0) {
        // Access this->m_pSomeObject (offset +0x4) then get m_nSomeID (offset +0xC)
        result = FUN_004f5090(*(int *)(*(int *)(this + 4) + 0xC));
        return result;
    }
    return 0;
}