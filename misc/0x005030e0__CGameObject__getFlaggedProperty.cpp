// FUNC_NAME: CGameObject::getFlaggedProperty

class CGameObject {
public:
    // +0x4: pointer to internal data structure
    void* m_pInternalData; 
    // ... (other members)
};

// Internal data structure referenced via this->m_pInternalData
struct InternalData {
    // +0xC: handle or key used as parameter to processing function
    unsigned int m_handle;
};

// External callee: FUN_005024a0 (likely a hash/ID conversion or resource lookup)
extern unsigned int __cdecl FUN_005024a0(unsigned int param);

// Member function: if flag is non-zero, retrieves an internal handle and processes it
unsigned int __thiscall CGameObject::getFlaggedProperty(int flag) {
    if (flag != 0) {
        InternalData* data = reinterpret_cast<InternalData*>(this->m_pInternalData);
        unsigned int handle = data->m_handle;
        return FUN_005024a0(handle);
    }
    return 0;
}