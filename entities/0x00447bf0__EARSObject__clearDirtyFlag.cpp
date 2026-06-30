// FUNC_NAME: EARSObject::clearDirtyFlag
// Sets the byte at +0xC4 (likely dirty/replication flag) to 0.
// Address: 0x00447bf0
class EARSObject {
public:
    void __thiscall clearDirtyFlag() {
        // +0xC4: byte indicating dirty/updated state
        *(unsigned char*)(this + 0xC4) = 0;
    }
};