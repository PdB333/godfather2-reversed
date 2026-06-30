// FUNC_NAME: NetObject::operator=
// Copy assignment operator for NetObject. Handles deep copy of intrusive linked list head at offset 0x28.
// The function copies a large set of POD fields (size ~0x148 bytes), with special handling for a singly-linked list head.
// When the old list head is non-null and points to a different list than the source, it frees the old list via FUN_004daf90.
// Then it transfers the pointer and updates the back-pointer in the new head node.

NetObject& NetObject::operator=(const NetObject& other)
{
    // Copy first five 8-byte fields (offsets 0x00-0x27)
    this->field_0 = other.field_0;
    this->field_8 = other.field_8;
    this->field_10 = other.field_10;
    this->field_18 = other.field_18;
    this->field_20 = other.field_20;

    // Handle linked list head at offset 0x28 (member at this+0x28)
    int* thisListPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x28);
    const int* otherListPtr = reinterpret_cast<const int*>(reinterpret_cast<const char*>(&other) + 0x28);
    if (thisListPtr != otherListPtr) {
        int newHead = *otherListPtr; // list head pointer from other
        if (*thisListPtr != newHead) {
            if (*thisListPtr != 0) {
                // Free old list (likely destructor for the list nodes)
                FUN_004daf90(thisListPtr);
            }
            *thisListPtr = newHead;
            if (newHead != 0) {
                // Update back-pointer in the new head node (offset +0x04 stores pointer to the head pointer)
                *reinterpret_cast<int**>(newHead + 4) = thisListPtr;
            }
        }
    }

    // Copy subsequent fields: from offset 0x30 (byte) then many 4-byte fields up to offset 0x148
    *reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 0x30) = *reinterpret_cast<const char*>(reinterpret_cast<const char*>(&other) + 0x30); // byte at +0x30

    // Copy 4-byte fields at +0x34, +0x38, ..., +0x144 (many pairs of 4-byte groups)
    // The pattern copies two consecutive 4-byte fields per iteration (using 8-byte copies? Actually the decompiler shows separate 4-byte stores)
    // To keep faithful, we'll copy them individually as the original does.

    *(int*)((char*)this + 0x34) = *(int*)((char*)&other + 0x34);
    *(int*)((char*)this + 0x38) = *(int*)((char*)&other + 0x38);
    *(int*)((char*)this + 0x3C) = *(int*)((char*)&other + 0x3C);
    *(int*)((char*)this + 0x40) = *(int*)((char*)&other + 0x40);
    *(int*)((char*)this + 0x44) = *(int*)((char*)&other + 0x44);
    *(int*)((char*)this + 0x48) = *(int*)((char*)&other + 0x48);
    *(int*)((char*)this + 0x4C) = *(int*)((char*)&other + 0x4C);
    *(int*)((char*)this + 0x50) = *(int*)((char*)&other + 0x50);
    *(int*)((char*)this + 0x54) = *(int*)((char*)&other + 0x54);
    *(int*)((char*)this + 0x58) = *(int*)((char*)&other + 0x58);
    *(int*)((char*)this + 0x5C) = *(int*)((char*)&other + 0x5C);
    *(int*)((char*)this + 0x60) = *(int*)((char*)&other + 0x60);
    *(int*)((char*)this + 0x64) = *(int*)((char*)&other + 0x64);
    *(int*)((char*)this + 0x68) = *(int*)((char*)&other + 0x68);
    *(int*)((char*)this + 0x6C) = *(int*)((char*)&other + 0x6C);
    *(int*)((char*)this + 0x70) = *(int*)((char*)&other + 0x70);
    *(int*)((char*)this + 0x74) = *(int*)((char*)&other + 0x74);
    *(int*)((char*)this + 0x78) = *(int*)((char*)&other + 0x78);
    *(int*)((char*)this + 0x7C) = *(int*)((char*)&other + 0x7C);
    *(int*)((char*)this + 0x80) = *(int*)((char*)&other + 0x80);
    *(int*)((char*)this + 0x84) = *(int*)((char*)&other + 0x84);
    *(int*)((char*)this + 0x88) = *(int*)((char*)&other + 0x88);
    *(int*)((char*)this + 0x8C) = *(int*)((char*)&other + 0x8C);
    *(int*)((char*)this + 0x90) = *(int*)((char*)&other + 0x90);
    *(int*)((char*)this + 0x94) = *(int*)((char*)&other + 0x94);
    *(int*)((char*)this + 0x98) = *(int*)((char*)&other + 0x98);
    *(int*)((char*)this + 0x9C) = *(int*)((char*)&other + 0x9C);
    *(int*)((char*)this + 0xA0) = *(int*)((char*)&other + 0xA0);
    *(int*)((char*)this + 0xA4) = *(int*)((char*)&other + 0xA4);
    *(int*)((char*)this + 0xA8) = *(int*)((char*)&other + 0xA8);
    *(int*)((char*)this + 0xAC) = *(int*)((char*)&other + 0xAC);
    *(int*)((char*)this + 0xB0) = *(int*)((char*)&other + 0xB0);
    *(int*)((char*)this + 0xB4) = *(int*)((char*)&other + 0xB4);
    *(int*)((char*)this + 0xB8) = *(int*)((char*)&other + 0xB8);
    *(int*)((char*)this + 0xBC) = *(int*)((char*)&other + 0xBC);
    *(int*)((char*)this + 0xC0) = *(int*)((char*)&other + 0xC0);
    *(int*)((char*)this + 0xC4) = *(int*)((char*)&other + 0xC4);
    *(int*)((char*)this + 0xC8) = *(int*)((char*)&other + 0xC8);
    *(int*)((char*)this + 0xCC) = *(int*)((char*)&other + 0xCC);
    *(int*)((char*)this + 0xD0) = *(int*)((char*)&other + 0xD0);
    *(int*)((char*)this + 0xD4) = *(int*)((char*)&other + 0xD4);
    *(int*)((char*)this + 0xD8) = *(int*)((char*)&other + 0xD8);
    *(int*)((char*)this + 0xDC) = *(int*)((char*)&other + 0xDC);
    *(int*)((char*)this + 0xE0) = *(int*)((char*)&other + 0xE0);
    *(int*)((char*)this + 0xE4) = *(int*)((char*)&other + 0xE4);
    *(int*)((char*)this + 0xE8) = *(int*)((char*)&other + 0xE8);
    *(int*)((char*)this + 0xEC) = *(int*)((char*)&other + 0xEC);
    *(int*)((char*)this + 0xF0) = *(int*)((char*)&other + 0xF0);
    *(int*)((char*)this + 0xF4) = *(int*)((char*)&other + 0xF4);
    *(int*)((char*)this + 0xF8) = *(int*)((char*)&other + 0xF8);
    *(int*)((char*)this + 0xFC) = *(int*)((char*)&other + 0xFC);
    *(int*)((char*)this + 0x100) = *(int*)((char*)&other + 0x100);
    *(int*)((char*)this + 0x104) = *(int*)((char*)&other + 0x104);
    *(int*)((char*)this + 0x108) = *(int*)((char*)&other + 0x108);
    *(int*)((char*)this + 0x10C) = *(int*)((char*)&other + 0x10C);
    *(int*)((char*)this + 0x110) = *(int*)((char*)&other + 0x110);
    *(int*)((char*)this + 0x114) = *(int*)((char*)&other + 0x114);
    *(int*)((char*)this + 0x118) = *(int*)((char*)&other + 0x118);
    *(int*)((char*)this + 0x11C) = *(int*)((char*)&other + 0x11C);
    *(int*)((char*)this + 0x120) = *(int*)((char*)&other + 0x120);
    *(int*)((char*)this + 0x124) = *(int*)((char*)&other + 0x124);
    *(int*)((char*)this + 0x128) = *(int*)((char*)&other + 0x128);
    *(int*)((char*)this + 0x12C) = *(int*)((char*)&other + 0x12C);
    *(int*)((char*)this + 0x130) = *(int*)((char*)&other + 0x130);
    *(int*)((char*)this + 0x134) = *(int*)((char*)&other + 0x134);
    // 8-byte field at offset 0x138 (field_27_8)
    this->field_0x138 = other.field_0x138; // 8 bytes
    // then 4-byte fields at 0x140 and 0x144
    *(int*)((char*)this + 0x140) = *(int*)((char*)&other + 0x140);
    *(int*)((char*)this + 0x144) = *(int*)((char*)&other + 0x144);

    return *this;
}