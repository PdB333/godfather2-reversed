// FUNC_NAME: SomeClass::constructor

// Reconstructed constructor for an object with a vtable, a flag at +0x2c, an ID at +0x2d,
// and two data members at +0x2e and +0x2f.
// The function searches through a list of child objects (at param_3+0x1c) for one with a
// specific type hash (0x9534c6cb) to override the ID.

class SomeClass {
public:
    // Virtual table pointer (offset 0x0)
    void* vtable;

    // Other members...
    // +0x2c: byte flag (initialized to 1)
    // +0x2d: int32 ID (from global _DAT_00d5780c)
    // +0x2e: int32 anotherID (from global DAT_01205228)
    // +0x2f: int32 copyOfOffset4 (copied from this+4)

    int field_0x2c; // actually byte but stored as int for alignment? decompiled uses undefined1*
    int field_0x2d;
    int field_0x2e;
    int field_0x2f;
};

// Global data references
extern int _DAT_00d5780c;
extern int DAT_01205228;
extern void* PTR_FUN_00d7c8a8;

// Base class constructor call (address 0x008cda10)
extern void SomeBaseConstructor(int param_2, int param_3);

SomeClass* __thiscall SomeClass::constructor(SomeClass* this, int param_2, int param_3) {
    SomeBaseConstructor(param_2, param_3);

    int globalID = _DAT_00d5780c;
    int index = 0;

    this->vtable = &PTR_FUN_00d7c8a8;
    *(unsigned char*)((int)this + 0x2c) = 1;      // Set byte flag at +0x2c to 1
    this->field_0x2d = globalID;                   // +0x2d = global

    // param_3+0x20 is a 16-bit count of children
    // param_3+0x1c is an array of pointers to child objects
    if (*(short*)(param_3 + 0x20) != 0) {
        do {
            int* childPtr = *(int**)(*(int*)(param_3 + 0x1c) + index * 4);
            // Check child's type hash at offset 4
            if (childPtr[4] == 0x9534c6cb) {   // -0x6acb3935
                this->field_0x2d = *childPtr;    // Override ID with child's first field
            }
            index++;
        } while (index < *(unsigned short*)(param_3 + 0x20));
    }

    this->field_0x2e = DAT_01205228;            // +0x2e = another global
    this->field_0x2f = this->field_0x??;        // +0x2f = copy of this[1] (offset 4) - exact member name unknown
    // Note: param_1[1] corresponds to *(int*)(this + 4), which is likely a base class member

    return this;
}