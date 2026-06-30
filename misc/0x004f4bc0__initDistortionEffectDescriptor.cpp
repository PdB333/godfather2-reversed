// FUNC_NAME: initDistortionEffectDescriptor

// Global distortion effect descriptor structure initialization
// Returns pointer to the initialized descriptor (size 40 bytes)
// Offsets documented in structure

static DistortionEffectDescriptor* initDistortionEffectDescriptor(void)
{
    // Set base pointer to a global pointer table (likely containing function pointers or vtable)
    // +0x00: pointer to a table at 0xe377e8 (likely vtable or handler list)
    $(ADDR 0x01218fb0) = (void*)&PTR_LAB_00e377e8;

    // +0x04: human-readable name string
    $(ADDR 0x01218fb4) = "Distortion";

    // +0x08: four-character code for effect identification (little-endian: ".dst")
    $(ADDR 0x01218fb8) = 0x2e647374; // ".dst"

    // +0x0C: some integer flag (0 = disabled?)
    $(ADDR 0x01218fbc) = 0;

    // +0x10: initialization parameter (e.g., blend mode or priority)
    $(ADDR 0x01218fc0) = 3;

    // +0x14: another flag
    $(ADDR 0x01218fc4) = 0;

    // +0x18: resource size or buffer length (0x800 = 2048 bytes)
    $(ADDR 0x01218fc8) = 0x800;

    // +0x1C: reserved or padding
    $(ADDR 0x01218fcc) = 0;

    // +0x20: reserved or padding
    $(ADDR 0x01218fd0) = 0;

    // +0x24: reserved or padding
    $(ADDR 0x01218fd4) = 0;

    // Return address of the descriptor itself
    return (DistortionEffectDescriptor*)0x01218fb0;
}