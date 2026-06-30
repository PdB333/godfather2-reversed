// FUNC_NAME: EARS::Framework::Object::Object
// Address: 0x00728040
// Role: Constructor for Object class, calls base class constructor and conditionally calls cleanup routine based on flag.

namespace EARS {
namespace Framework {

class Object {
public:
    // Constructor with flag; if (flag & 1) != 0, a cleanup/destructor is invoked
    __thiscall Object(byte flag) {
        // Call base class constructor (address 0x00727eb0)
        this->baseConstructor();
        // If the lowest bit is set, call cleanup (address 0x009c8eb0)
        if (flag & 1) {
            this->cleanup();
        }
    }
};

} // namespace Framework
} // namespace EARS