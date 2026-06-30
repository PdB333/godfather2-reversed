// FUNC_NAME: EARSObject::constructor
class EARSObject {
public:
    // Constructor with flags
    void __thiscall constructor(byte initFlags) {
        // Call base initialization
        baseConstruct(); // FUN_00474ab0

        // If low bit set, call vtable function (offset 4) with this and 0
        if (initFlags & 1) {
            // Get vtable from global at offset 0x2d4 from DAT_01223410
            void** vtable = *(void***)(DAT_01223410 + 0x2d4);
            // Call second vtable entry (offset 4 bytes)
            void (__thiscall* func)(void*, int) = (void (__thiscall*)(void*, int))vtable[1];
            func(this, 0);
        }
    }

private:
    void __thiscall baseConstruct(); // defined elsewhere
};