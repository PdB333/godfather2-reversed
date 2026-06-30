// FUNC_NAME: PlayerCharacter::calculateTotalValue

int __thiscall PlayerCharacter::calculateTotalValue() {
    float totalValue = 0.0f;
    if (this->m_upgradeIndex != 0) {
        // m_baseValue is an initial bonus (might be base reputation or damage)
        totalValue = this->m_baseValue;
        // Traverse a global linked list of upgrade bonuses (indexed by upgrade type)
        int currentNode = gUpgradeChainNext[this->m_upgradeIndex];
        while (currentNode != 0) {
            float currentBonus = gUpgradeChainValue[currentNode];
            float multiplier = getGlobalMultiplier(this->m_unknownPtr); // e.g., difficulty or time factor
            if (multiplier > 0.0f && (this->m_upgradeIndex == 2 || this->m_upgradeIndex == 3 || this->m_upgradeIndex == 4)) {
                currentBonus *= multiplier;
            }
            totalValue += currentBonus;
            currentNode = gUpgradeChainNext[currentNode];
        }
    }
    // Round to nearest integer (banker's rounding? equivalent to ROUND(x))
    int result = (int)(totalValue + 0.5f);
    return result;
}