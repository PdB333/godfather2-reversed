// FUNC_NAME: EAObject::EAObject

// Reconstructed constructor for EAObject at 0x0049cd80
// This appears to be a derived class constructor (likely EA EARS engine base object)

class EAObject {
public:
    // Virtual table pointer at offset 0x00
    // Fields identified from offsets (in bytes):
    // +0xA0: dword field1 (set to 0)
    // +0xA4: dword field2 (set to 0)
    // +0xB0: short field3 (copied from source + 2)
    // +0xB2: byte field4 (low bit set, bit1 cleared)

    EAObject() = delete; // prevent default constructor; this is a placement init

    // Constructor taking three parameters (possibly object ID, owner, etc.)
    // extraout_EDX appears to be an additional pointer (e.g., sub-object or allocator)
    // In the original binary, this is likely __thiscall with this in ECX, 
    // but Ghidra shows EDI as this pointer due to inlined code.
    void __thiscall constructor(void* param_1, void* param_2, void* param_3, void* edxPointer);

private:
    // vtable pointer (defined externally)
    void* vtable;

    // Unknown fields at +0xA0, +0xA4
    int field_0xA0;
    int field_0xA4;
    // +0xB0: short
    short field_0xB0;
    // +0xB2: byte
    unsigned char field_0xB2;

    // Inline functions called
    void __thiscall baseClassConstructor();           // FUN_0060ffd0
    void __thiscall initFromParams(void* param_1, void* param_2, void* param_3); // FUN_004bfc10
    void __thiscall postConstruct();                  // FUN_0049ceb0
};

// Constructor implementation
void EAObject::constructor(void* param_1, void* param_2, void* param_3, void* edxPointer) {
    // Set vtable pointer (external symbol)
    this->vtable = &PTR_FUN_00e35238;   // offset +0x00

    // Call base class constructor
    baseClassConstructor();             // FUN_0060ffd0

    // Initialize fields at +0xA0 and +0xA4 to 0
    this->field_0xA0 = 0;               // unaff_EDI[0x28] = 0
    this->field_0xA4 = 0;               // unaff_EDI[0x29] = 0

    // Copy a short from the source pointer (edxPointer + 2) to field at +0xB0
    // edxPointer points to some data (e.g., a descriptor or outer object)
    this->field_0xB0 = *(short*)((char*)edxPointer + 2); // *(undefined2 *)(extraout_EDX + 1)

    // Set bits in field at +0xB2: clear bit1 (0x02) and set bit0 (0x01)
    this->field_0xB2 = (this->field_0xB2 & 0xFD) | 1;  // byte at +0xB2

    // Call another initialization function with original parameters
    initFromParams(param_1, param_2, param_3); // FUN_004bfc10(*extraout_EDX, param_1, param_2, param_3)
    // Note: The first argument *extraout_EDX is likely a pointer to a sub-object or allocator;
    // we assume it's passed as part of the call, but the exact mapping is unclear.

    // Final post-construction step
    postConstruct();                    // FUN_0049ceb0
}