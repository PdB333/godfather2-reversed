// FUNC_NAME: EARS::Framework::Object::~Object
// Function at 0x006aa4d0: Destructor for a base object containing four sub‑objects with custom destructors.
// Sub‑object layout (each 16 bytes):
//   +0x00: pointer to managed object (0x04, 0x14, 0x24, 0x34)
//   +0x04: unknown (4 bytes) [offset+0x04 within sub‑object]
//   +0x08: unknown (4 bytes) [offset+0x08 within sub‑object]
//   +0x0C: destructor function pointer (0x10, 0x20, 0x30, 0x40)
// Vtable pointer set to PTR_FUN_00d5d9b0 (base vtable)

void __fastcall EARS::Framework::Object::~Object(Object* this)
{
    // Set vtable pointer to the base class vtable
    this->vtable = &PTR_FUN_00d5d9b0;

    // Destroy fourth sub‑object (offset +0x34)
    if (this->subObj4.ptr != 0) {
        this->subObj4.destructor(this->subObj4.ptr);
    }

    // Destroy third sub‑object (offset +0x24)
    if (this->subObj3.ptr != 0) {
        this->subObj3.destructor(this->subObj3.ptr);
    }

    // Destroy second sub‑object (offset +0x14)
    if (this->subObj2.ptr != 0) {
        this->subObj2.destructor(this->subObj2.ptr);
    }

    // Destroy first sub‑object (offset +0x04)
    if (this->subObj1.ptr != 0) {
        this->subObj1.destructor(this->subObj1.ptr);
    }
}