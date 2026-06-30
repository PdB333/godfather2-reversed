// FUNC_NAME: EARSObject::EARSObject
class EARSObject {
public:
    void* vtable; // +0x00 virtual function table pointer

    // __thiscall constructor: sets vtable and calls base class initialization
    EARSObject() {
        // Store pointer to this class's virtual function table (0x00e327d8)
        this->vtable = (void*)0x00e327d8;

        // Call base class constructor/initializer at 0x0043e2e0
        // This performs base class setup (e.g., member initialization)
        // Note: In typical C++ the base constructor is called before setting vtable,
        // but here the derived vtable is set first; this initializer must not modify vtable.
        // FUN_0043e2e0(this);
    }
};