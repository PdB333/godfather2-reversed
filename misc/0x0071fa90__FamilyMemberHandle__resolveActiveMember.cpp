// FUNC_NAME: FamilyMemberHandle::resolveActiveMember
uint __fastcall FamilyMemberHandle::resolveActiveMember(void* this) {
    // this points to a small handle structure:
    // +0x04: pointer to family data (offset into larger FamilyManager object)
    // +0x24: family member ID (32-bit, with sentinel 0x2ca3cff6 for invalid)
    const uint kInvalidFamilyMemberID = 0x2ca3cff6;
    const int kFamilyDataOffset = 0x48;     // offset from family data pointer back to base
    const int kFlagOffset = 0x8e6;          // byte flag at base + 0x8e6 (bit 0 = active flag)
    const int kActiveMemberPtrOffset = 0x218; // pointer to active member descriptor at base + 0x218
    const int kMemberIDOffset = 0x14;       // ID field in the member descriptor

    int* familyDataPtr = *(int**)((char*)this + 4);
    int memberID = *(int*)((char*)this + 0x24);
    int* base;           // base of FamilyManager
    int* memberDescPtr;  // pointer to active member descriptor
    uint rawMemberValue; // value read from the descriptor pointer field
    uint result;         // in_EAX

    if (memberID == kInvalidFamilyMemberID) {
        // Invalid ID: result is undefined (EAX not modified); assume zero
        result = 0;
    } else {
        // Compute base from familyDataPtr (null check)
        base = familyDataPtr ? (int*)((char*)familyDataPtr - kFamilyDataOffset) : 0;
        if (base) {
            // Check if active flag is set (bit 0 of byte at base+0x8e6)
            if ((*(unsigned char*)((char*)base + kFlagOffset) & 1) != 0) {
                // Compute base again (same as before)
                int* base2 = familyDataPtr ? (int*)((char*)familyDataPtr - kFamilyDataOffset) : 0;
                if (base2) {
                    // Get pointer to active member descriptor
                    memberDescPtr = *(int**)((char*)base2 + kActiveMemberPtrOffset);
                    if (memberDescPtr) {
                        // Compare ID in descriptor with handle's memberID
                        if (*(int*)((char*)memberDescPtr + kMemberIDOffset) == memberID) {
                            // Success: read the value from descriptor pointer field and set low byte to 1
                            rawMemberValue = *(uint*)((char*)base2 + kActiveMemberPtrOffset);
                            result = (rawMemberValue & 0xFFFFFF00) | 1;
                            return result; // early return with flag set
                        }
                    }
                }
            }
        }
        // If we reach here, result is the last computed base (or 0), masked to zero low byte
        result = (uint)base & 0xFFFFFF00;
    }
    return result & 0xFFFFFF00;
}