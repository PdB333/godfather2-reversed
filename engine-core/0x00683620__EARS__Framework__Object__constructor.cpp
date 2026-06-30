// FUNC_NAME: EARS::Framework::Object::constructor
extern void* vtable_00d587e0; // vtable for Object class

namespace EARS {
namespace Framework {

class Object {
public:
    void* vtable; // +0x00

    // Constructor: param_2 is a flag indicating heap allocation (fromNew)
    // If fromNew is true, the object's own destructor is called (FUN_009c8eb0)
    Object(byte fromNew);
};

// Base constructor at FUN_004083d0
void __thiscall baseConstructor(Object* this);

// Destructor/cleanup at FUN_009c8eb0
void __thiscall objectDestructor(Object* this);

Object* __thiscall Object::Object(Object* this, byte fromNew) {
    this->vtable = &vtable_00d587e0; // set vtable pointer
    baseConstructor(this); // call base class constructor
    if (fromNew & 1) { // if fromNew is true, call destructor (e.g., for heap-allocated placement new)
        objectDestructor(this);
    }
    return this;
}

} // namespace Framework
} // namespace EARS