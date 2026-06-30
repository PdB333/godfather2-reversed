// FUNC_NAME: DonControlGadget::initTextureHandles
void DonControlGadget::initTextureHandles() {
    // Initialize left and right texture slot buffers (3 entries each)
    // gLeftTexSlot and gRightTexSlot are global static arrays of size 3
    initSlotBuffer(&gLeftTexSlot, 3);   // FUN_0049c6e0
    initSlotBuffer(&gRightTexSlot, 3); // FUN_0049c6e0

    // Obtain handles for each slot buffer
    int leftHandle = getSlotHandle(&gLeftTexSlot);   // FUN_004dafd0
    int rightHandle = getSlotHandle(&gRightTexSlot); // FUN_004dafd0

    // Store handles at offsets +0x18 and +0x1c in the gadget
    this->m_leftTexHandle = leftHandle;   // +0x18
    this->m_rightTexHandle = rightHandle; // +0x1c

    // If a default global texture exists, assign it to the texture slot at +0x8
    if (gDefaultTexture != 0) {
        assignTextureToSlot(this + 8, &gDefaultTexture); // FUN_00407e60
    }
}