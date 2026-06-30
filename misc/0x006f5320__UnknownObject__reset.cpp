// FUNC_NAME: UnknownObject::reset

// Reconstructed C++ method at address 0x006f5320
// Likely part of an object's cleanup/reset (called by constructors/destructors at 0x006f0ff0, 0x006f0750, etc.)
// UnknownObject layout (offsets in bytes from this):
// 0x00: somePointer (possibly int)
// 0x04: int field1
// 0x08: int field2
// 0x0C: pointerToSomething (freed via helper)
// 0x14: anotherPointer (freed via helper)
// 0x24: int field9
// 0x28: bool field10 (byte)

class UnknownObject {
public:
    void __thiscall reset() {
        int* ptrAtOffset14 = reinterpret_cast<int*>(this) + 5; // +0x14 (5*4)
        
        this->field9 = 0;   // +0x24
        this->field1 = 0;   // +0x04

        // Free pointer at +0x14 if not null
        if (*ptrAtOffset14 != 0) {
            freePointer(ptrAtOffset14);  // FUN_004daf90
            *ptrAtOffset14 = 0;
        }

        // Free pointer at +0x0C if not null
        if (this->pointerAt0C != 0) {
            freePointer(&(this->pointerAt0C)); // FUN_004daf90
            this->pointerAt0C = 0;
        }

        this->field10 = 0;  // +0x28, byte
        this->field2 = 0;   // +0x08
        this->somePointer = 0; // +0x00
    }

private:
    // Fields (not in order, just for reference)
    int* somePointer;              // +0x00
    int field1;                    // +0x04
    int field2;                    // +0x08
    int* pointerAt0C;              // +0x0C
    int* anotherPointer;           // +0x14 (actually at offset, but stored as int)
    int field9;                    // +0x24
    unsigned char field10;         // +0x28

    // Helper function (address 0x004daf90) - frees a pointer and sets it to null
    static void __fastcall freePointer(void** ptr); // defined elsewhere
};