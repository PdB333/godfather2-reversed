// FUNC_NAME: PacketWindow::operator=
// Address: 0x00968cc0
// Assignment operator for a 32-slot packet window structure.
// Copies the first dword, then two arrays of 32 dwords each, then three trailing dwords.

void __thiscall PacketWindow::operator=(const PacketWindow& other)
{
    int i;
    uint32_t* dest;
    uint32_t* src;

    // Copy field at offset +0x04
    *(uint32_t*)(this + 0x04) = *(uint32_t*)((uint32_t)&other + 0x04);

    // Copy first array of 32 dwords starting at offset +0x08
    dest = (uint32_t*)(this + 0x08);
    i = 32;
    do {
        *dest = *(uint32_t*)((uint32_t)&other + (uint32_t)(dest - (uint32_t*)this));
        dest++;
        i--;
    } while (i != 0);

    // Copy second array of 32 dwords starting at offset +0x88
    dest = (uint32_t*)(this + 0x88);
    i = 32;
    do {
        *dest = *(uint32_t*)((uint32_t)&other + (uint32_t)(dest - (uint32_t*)this));
        dest++;
        i--;
    } while (i != 0);

    // Copy three trailing dwords at offsets +0x108, +0x10C, +0x110
    *(uint32_t*)(this + 0x108) = *(uint32_t*)((uint32_t)&other + 0x108);
    *(uint32_t*)(this + 0x10C) = *(uint32_t*)((uint32_t)&other + 0x10C);
    *(uint32_t*)(this + 0x110) = *(uint32_t*)((uint32_t)&other + 0x110);
}