// FUNC_NAME: Object::constructWithFlag
// Address: 0x005e1d00
// Role: Constructor with initialization flag. Calls internal init and optionally a cleanup function if bit 0 of param2 is set (likely for dynamic allocation handling).

class Object {
public:
    // __thiscall: this is passed in ecx
    // param2: flag byte (bit 0 triggers cleanup)
    // Returns this pointer
    Object* constructWithFlag(unsigned char param2) {
        this->init();           // FUN_005e1d20 - performs main construction
        if (param2 & 1) {
            this->cleanup();    // FUN_009c8eb0 - cleanup/destructor (e.g., deallocate if allocation failed)
        }
        return this;
    }

private:
    void init();    // Actual initialization code
    void cleanup(); // Cleanup code (may be destructor or deallocation)
};