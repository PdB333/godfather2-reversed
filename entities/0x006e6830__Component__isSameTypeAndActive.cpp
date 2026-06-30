// FUNC_NAME: Component::isSameTypeAndActive
// Function address: 0x006e6830
// Checks if the component's type ID (derived from mTypeIndex at +0x60) matches the given typeId
// and the active flag at +0x8a (bit 0) is set. Returns true if both conditions are met.

struct Component {
    // +0x60: int mTypeIndex;  // type index, if non-zero subtract 0x48 to get actual type ID
    // +0x8a: char mFlags;     // bit 0 = active flag
};

bool __thiscall Component::isSameTypeAndActive(int typeId) {
    int thisTypeId;

    if (this->mTypeIndex == 0) {
        thisTypeId = 0;
    } else {
        thisTypeId = this->mTypeIndex - 0x48;
    }

    // Return true if type ID matches and the active flag is set (bit 0)
    if (thisTypeId != typeId) {
        return false;
    }
    return (this->mFlags & 1) != 0;
}