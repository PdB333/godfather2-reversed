// FUNC_NAME: Player::getTotalReward
int __thiscall Player::getTotalReward()
{
    // Check if the reward data is ready (offset +0x2d0)
    if (this->m_bDataReady) {
        // Retrieve bonus value from index at +0x334 using an external lookup function
        int bonus = getDataValue(this->m_dataIndex);  // calls FUN_00700090
        // Return base value at +0x328 plus bonus
        return this->m_baseValue + bonus;
    }
    return 0;
}