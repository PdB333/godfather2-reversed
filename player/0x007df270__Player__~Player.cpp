// FUNC_NAME: Player::~Player
// Function address: 0x007df270
// Destructor for Player class. Cleans up components, flags, and calls base destructor.

void __fastcall Player::~Player(Player* this)
{
    int* pComponent = reinterpret_cast<int*>(this->m_pSomeComponent); // +0x74
    // Set vtable to current class vtable
    this->vtable = &PTR_LAB_00d6f7f8;

    // Handle component cleanup
    if (pComponent != nullptr && pComponent != reinterpret_cast<int*>(0x48))
    {
        int iVar2;
        if (pComponent == nullptr)
        {
            iVar2 = 0;
        }
        else
        {
            iVar2 = reinterpret_cast<int>(pComponent) - 0x48;
        }

        // Check flags: component's bit 0xb (11) and manager's bit 0xc (12)
        if (((*(uint*)(iVar2 + 0x18c) >> 0xb) & 1) == 0 &&
            ((*(uint*)(this->m_pManager + 0x24a0) >> 0xc) & 1) == 0)
        {
            int result = sub_471610(); // Get some system handle
            sub_8B86C0(result + 0x30); // Trigger effect/sound
        }

        if (pComponent != nullptr)
        {
            sub_4DAF90(pComponent); // Release component
            this->m_pSomeComponent = nullptr;
        }
    }

    // Handle flag based on byte at +0x80
    if (this->m_bSomeFlag != '\0')
    {
        *(uint*)(this->m_pManager + 0x249c) |= 0x20000; // Set bit 17
    }

    // Clear bits 12 and 13 in manager flags
    *(uint*)(this->m_pManager + 0x24a0) &= 0xffffefff;
    *(uint*)(this->m_pManager + 0x24a0) &= 0xffffdfff;

    // Release pointer at manager+0x30c0 if non-null
    int* pPtr = reinterpret_cast<int*>(*(int*)(this->m_pManager + 0x30c0));
    if (pPtr != nullptr)
    {
        sub_4DAF90(pPtr);
        *(int*)(this->m_pManager + 0x30c0) = 0;
    }

    // Check if manager's slot matches our ID
    if (reinterpret_cast<int*>(this->m_pManager)[0x229] == this->m_someID) // +0x7c
    {
        this->m_someID = 0;
        // Call virtual function at offset 0x198 from manager's vtable
        (*(void (**)(void))(*(int*)this->m_pManager + 0x198))();
    }

    // Final component release (only if still non-null, but already set to null above)
    if (this->m_pSomeComponent != nullptr)
    {
        sub_4DAF90(this->m_pSomeComponent);
    }

    // Switch to base class vtable and call base destructor
    this->vtable = &PTR_LAB_00d6b95c;
    sub_80EA60(); // Base class destructor
}