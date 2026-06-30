// FUNC_NAME: Object::Object
// Constructor for a base EARS object. Takes an allocation flag (byte) indicating if the object was heap-allocated.
// If allocated, registers the object (e.g., with a memory manager or global object list) via registerObject().

class Object {
private:
    void __thiscall baseInit();   // FUN_0068d690 – base object initialization or base constructor
    void __thiscall registerObject(); // FUN_009c8eb0 – registration when heap-allocated (e.g., for ref counting)

public:
    Object* __thiscall Object(Object* this, byte allocated) {
        baseInit();               // calls base constructor/init (FUN_0068d690)
        if (allocated & 1) {      // param_2 is a bool in practice; bit 0 indicates allocation
            registerObject();     // FUN_009c8eb0(this)
        }
        return this;              // returns this pointer
    }
};