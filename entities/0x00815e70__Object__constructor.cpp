// FUNC_NAME: Object::constructor
// Address: 0x00815e70
// Role: Constructor for Object base class. Calls base initializer and conditionally frees memory if ownMem flag is set (bit 0 of param_2).

class Object {
public:
    Object(byte ownMem);  // ownMem & 1 triggers memory release
    virtual ~Object();
private:
    void baseInitialize(); // FUN_00815d20 - base class initialization
    void releaseMemory();  // FUN_009c8eb0 - likely operator delete or pool deallocation
};

Object::Object(byte ownMem) {
    baseInitialize(); // +0x00: base class construction stub
    if ((ownMem & 1) != 0) {
        releaseMemory(); // free memory if flag indicates allocation ownership
    }
    // return this (implicit in __thiscall)
}