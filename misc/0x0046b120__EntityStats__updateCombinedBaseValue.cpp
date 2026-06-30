// FUNC_NAME: EntityStats::updateCombinedBaseValue
// Address: 0x0046b120
// Role: Combines two base attribute values (index 1 and 2) and applies the sum to a derived attribute.

void __thiscall EntityStats::updateCombinedBaseValue(EntityStats* this) {
    int baseValue1 = getBaseAttribute(1);   // FUN_0046af90: returns base stat at index 1
    int baseValue2 = getBaseAttribute(2);   // FUN_0046af90: returns base stat at index 2
    setCombinedValue(this, baseValue1 + baseValue2); // FUN_0046aed0: stores the sum into combined attribute
    return;
}