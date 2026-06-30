// FUNC_NAME: TNLObject::TNLObject

class TNLObject {
public:
    void *vtable; // +0x00

    // Constructor (address: 0x004aee00)
    __thiscall TNLObject() {
        // Set vtable pointer to class-specific vtable (0x00e35710)
        this->vtable = reinterpret_cast<void*>(0x00e35710);
    }
};