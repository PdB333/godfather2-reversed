// FUNC_NAME: ResourceHolder::releaseHandle (address 0x0071a7b0)
// Releases the resource handle if non‑zero, then zeros it out.
// The handle is stored at offset 0x00 of the class instance.

class ResourceHolder {
public:
    int m_handle; // +0x00

    void releaseHandle(); // __thiscall
};

// Forward declaration of the internal release function (at 0x004daf90)
void releaseResourceInternal(int handle);

void ResourceHolder::releaseHandle() {
    if (m_handle != 0) {
        releaseResourceInternal(m_handle);
        m_handle = 0;
    }
}