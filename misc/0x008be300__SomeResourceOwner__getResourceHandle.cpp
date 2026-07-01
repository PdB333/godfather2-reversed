// FUNC_NAME: SomeResourceOwner::getResourceHandle
// Address: 0x008be300
// Lazy initialization: returns address of resource handle at +0xac,
// initializing it via an external function if the flag at +0xb0 is zero.

class SomeResourceOwner {
public:
    int m_unk80;        // offset +0x80 – likely a resource identifier/ID
    // ... (other fields, skipped for brevity)
    int m_handle;       // offset +0xac – the resource handle (pointer-sized)
    int m_initialized;  // offset +0xb0 – non‑zero after first init
};

// Forward declaration of the init function (called when m_initialized == 0)
void initResourceFromId(int identifier, int* outHandle);

int __fastcall SomeResourceOwner::getResourceHandle(SomeResourceOwner* this)
{
    if (this->m_initialized == 0) {
        initResourceFromId(this->m_unk80, &this->m_handle);
    }
    // Return the address of the handle field (converted to int for pointer arith)
    return (int)&this->m_handle;
}