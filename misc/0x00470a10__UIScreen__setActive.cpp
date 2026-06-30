// FUNC_NAME: UIScreen::setActive
void __thiscall UIScreen::setActive(char newActive)
{
    ushort width;
    ushort height;
    ushort combinedDim;
    char currentActive;
    uint* pBuffer;
    int* pThis_00;
    
    currentActive = this->isActive(); // FUN_004709e0
    if (newActive != currentActive) {
        // Read current screen dimensions from TLS structure
        width = *(ushort*)(**(int**)(__readfsdword(0x2c) + 0x0c));
        height = *(ushort*)(**(int**)(__readfsdword(0x2c) + 0x0e));
        
        // Update active flag at offset +0x15e
        if (newActive == '\0') {
            this->flags &= 0xefff;           // clear bit 12
        } else {
            this->flags |= 0x1000;           // set bit 12
        }
        
        // If a callback receiver exists, post an activation event
        if (this->pReceiver != 0) {          // +0x164
            currentActive = this->isActive();
            pBuffer = (uint*)(DAT_01206880 + 0x14);
            **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_0110bad0; // event vtable
            *pBuffer = *pBuffer + 4;
            *(int*)*pBuffer = (int)&this->field_0x54;   // +0x54 (delegate or data)
            *pBuffer = *pBuffer + 4;
            *(bool*)*pBuffer = currentActive != '\0';
            *pBuffer = *pBuffer + 4 & 0xfffffffc;       // align
        }
        
        // Notify listeners with dimension change
        currentActive = this->isActive();
        combinedDim = width;
        if (currentActive == '\0') {
            combinedDim = height;
        }
        (this->vtable->onSizeChange)(combinedDim, height | width); // vtable+0x5c
    }
}