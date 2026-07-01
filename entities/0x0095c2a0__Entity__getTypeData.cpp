// FUNC_NAME: Entity::getTypeData
// Function at 0x0095c2a0. Returns a value from a global table indexed by a member at offset +0x1c (likely mTypeIndex).
uint32_t Entity::getTypeData() const {
    // mTypeIndex is at offset +0x1c
    return sTypeDataTable[this->mTypeIndex];
}