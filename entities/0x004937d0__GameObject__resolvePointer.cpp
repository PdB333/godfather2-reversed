// FUNC_NAME: GameObject::resolvePointer
undefined4 GameObject::resolvePointer(void)
{
    undefined4 result;

    updateBaseState(); // FUN_00493070 - base object update/refresh
    if (this->m_pPrimaryObject != nullptr) { // +0x270
        getSharedPointer(); // FUN_006063b0 - e.g., acquire reference, side effects
    }
    result = this->m_pSecondaryObject; // +0x284
    if (this->m_bUseSecondary != 0) { // +0x280 - flag to override result
        result = getSharedPointer(); // FUN_006063b0 - returns resolved pointer
    }
    return result;
}