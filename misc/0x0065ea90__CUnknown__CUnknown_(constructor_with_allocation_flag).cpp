// FUNC_NAME: CUnknown::CUnknown (constructor with allocation flag)
// Address: 0x0065ea90
// Base class constructor at 0x0065ea30, vtable setup helper at 0x009c8eb0.
// allocFlag == 1 typically indicates heap allocation requiring vtable patching.

class CUnknown; // Forward declaration (details unknown)

CUnknown * __thiscall CUnknown::CUnknown(byte allocFlag) {
    // Call base class constructor (assumes __thiscall with this implicit)
    FUN_0065ea30();

    // If object was heap-allocated (flag & 1), perform vtable initialization
    if ((allocFlag & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}