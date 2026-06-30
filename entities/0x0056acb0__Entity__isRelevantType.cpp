// FUNC_NAME: Entity::isRelevantType
// Function at 0x0056acb0 checks if this->type field falls within a set of recognized IDs.
// Returns 1 if type is 5-10, 11, 14-16, 18, 20, or 26; otherwise 0.
int __thiscall SomeClass::isRelevantType(void)
{
    // First 4 bytes of object (offset 0x00) is a type indicator.
    int type = *(int *)this;
    switch (type) {
    default:
        return 0;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:   // 11
    case 0xe:   // 14
    case 0xf:   // 15
    case 0x10:  // 16
    case 0x12:  // 18
    case 0x14:  // 20
    case 0x1a:  // 26
        return 1;
    }
}