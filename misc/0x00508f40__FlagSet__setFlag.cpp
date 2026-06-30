// FUNC_NAME: FlagSet::setFlag
// Function at 0x00508f40: Sets or clears a bit in a flags field.
// The class has a uint32 flags member at offset 0x00.
class FlagSet {
    uint32 flags; // +0x00
public:
    void __thiscall setFlag(uint32 mask, bool set) {
        if (set) {
            flags |= mask;
        } else {
            flags &= ~mask;
        }
    }
};