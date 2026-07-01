// FUNC_NAME: EARSObject::isActive
// Function: 0x007eeb50 - Checks if the object is active: state is valid (not 0 or 0x48) and bit0 of flags is set.
// __fastcall: this in ecx, returns bool (byte)
class EARSObject {
public:
    // Offsets: +0x0 vtable (8 bytes), +0x4 state (int), +0x10 flags (byte)
    // state != 0 and != 0x48 indicates a non-default, non-dead state
    __fastcall bool isActive() const {
        bool result = false;
        if (*(int*)(this + 4) != 0 && *(int*)(this + 4) != 0x48) {
            if ((*(byte*)(this + 0x10) & 1) != 0) {
                result = true;
            }
        }
        return result;
    }
};