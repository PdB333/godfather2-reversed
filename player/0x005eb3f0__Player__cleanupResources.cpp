// FUNC_NAME: Player::cleanupResources
class Player {
public:
    // vtable function at offset 0xd0 (index 52)
    virtual void onCleanup();

    // member fields (offsets in bytes)
    void* m_pResource;    // +0x574 (index 0x15d)
    int m_flags;           // +0x578 (index 0x15e)
    void* m_pSomething;    // +0x57c (index 0x15f)
};

void __fastcall Player::cleanupResources(Player* this) {
    this->m_flags = 0;          // clear flag
    FUN_009c8f10(this->m_pResource); // release resource
    this->m_pResource = nullptr; // null resource pointer
    this->m_pSomething = nullptr; // null other pointer

    // call base class cleanup (virtual, offset +0xd0 in vtable)
    this->onCleanup();
}