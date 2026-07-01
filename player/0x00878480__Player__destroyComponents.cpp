// FUNC_NAME: Player::destroyComponents
void __thiscall Player::destroyComponents(void)
{
    // Call base class cleanup (likely ~PlayerBase or common cleanup)
    this->cleanupBase(); // FUN_008783d0

    // Release three component pointers at offsets +0xa04, +0xa08, +0xa0c
    if (this->m_pComponent1 != nullptr) { // +0xa04
        delete this->m_pComponent1;       // FUN_004df600
    }
    if (this->m_pComponent2 != nullptr) { // +0xa08
        delete this->m_pComponent2;
    }
    if (this->m_pComponent3 != nullptr) { // +0xa0c
        delete this->m_pComponent3;
    }
}