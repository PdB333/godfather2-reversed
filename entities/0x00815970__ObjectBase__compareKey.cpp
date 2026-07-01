// FUNC_NAME: ObjectBase::compareKey
// Address: 0x00815970 - Compares an internal key stored at +0x54 with a given value, using a tie-breaking comparator.
int __thiscall ObjectBase::compareKey(int this, int key, int extraData) {
    // m_someKey is at offset +0x54 (likely a timestamp or priority)
    int ownKey = *(int*)(this + 0x54);
    
    if (ownKey < key) {
        return -1;  // this object is less than the comparison value
    }
    if (ownKey > key) {
        return 1;   // this object is greater
    }
    // keys are equal, fall back to secondary comparison using extraData
    return FUN_008155a0(extraData);  // secondaryCompare(extraData)
}