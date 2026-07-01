// FUNC_NAME: UnknownClass::~UnknownClass
// Function Address: 0x007df780
// Role: Destructor for an unknown class. Calls base destructor (0x007df270) and optionally
//       deallocates memory via operator delete (0x00624da0) if the deallocationFlag (byte param)
//       has bit 0 set. This matches the typical VC++ destructor pattern with a hidden bool parameter.

class UnknownClassBase {
public:
    void __thiscall ~UnknownClassBase();
};

class UnknownClass : public UnknownClassBase {
public:
    void __thiscall ~UnknownClass(unsigned char deallocationFlag);
};

void __thiscall UnknownClass::~UnknownClass(unsigned char deallocationFlag) {
    // Call base destructor (FUN_007df270)
    this->~UnknownClassBase();

    // If the object was heap-allocated (deallocationFlag & 1), free memory (FUN_00624da0)
    if (deallocationFlag & 1) {
        ::operator delete(this);
    }
}