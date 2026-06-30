// FUNC_NAME: EARSObject::create
// Address: 0x004f6f00
// Role: Creates an object with optional cleanup based on flag

class EARSObject {
public:
    EARSObject* __thiscall create(byte bCleanup) {
        this->init(); // base initialization (FUN_004f5d90)
        if ((bCleanup & 1) != 0) {
            this->destroy(); // cleanup/destructor (FUN_009c8eb0)
        }
        return this;
    }
};