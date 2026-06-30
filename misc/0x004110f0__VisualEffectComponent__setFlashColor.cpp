// FUNC_NAME: VisualEffectComponent::setFlashColor
void __thiscall VisualEffectComponent::setFlashColor(void* this, byte colorIndex, uint colorData) {
    // +0x570: pointer to some color effect object (likely allocated when component is active)
    if (*(int*)((char*)this + 0x570) != 0) {
        // Prepare a color structure from the input colorData
        uint localColor = colorData;
        // FUN_004986e0 processes the color data (e.g., loads a color from a LUT)
        // It returns a pointer to a color effect structure (or modifies one)
        ColorEffect* effect = (ColorEffect*)FUN_004986e0(&localColor);
        if (effect != 0) {
            // Fill the effect structure with flash color parameters
            effect->value = (uint)colorIndex;      // +0x08: flash intensity or index
            effect->colorA = 0x300ff;             // +0x0C: first color (e.g., red tint)
            effect->colorB = 0xffff00;            // +0x10: second color (e.g., yellow tint)
            effect->padding = 0;                  // +0x14: reserved
        }
    }
}