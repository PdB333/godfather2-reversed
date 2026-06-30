// FUNC_NAME: UISprite::render
// Function address: 0x006209c0
// Role: Renders a 2D UI sprite if visible. Computes transform from sprite resource and parent, then pushes render state.

extern void calculateSpriteTransform(int resourceHandle, int parentTransform, int zero, char* outTransform);
extern void pushRenderState();
extern void setRenderColor(int flags, int color);
extern void setRenderTransform(int id, char* transform);
extern void popRenderState();

extern int DAT_00e2cd48; // global constant, unknown usage

void UISprite::render() {
    // +0xa8: visibility flag (nonzero means visible)
    if (*(int*)(this + 0xa8) != 0) {
        // 8-byte buffer for 2D transform (e.g., translation or scale/rotation)
        char transform[8];

        // Compute transform:
        // +0x8: sprite resource handle
        // +0xa4: pointer to parent object
        // parent+0x10: some transform value from parent
        calculateSpriteTransform(
            *(int*)(this + 0x8),
            *(int*)(*(int*)(this + 0xa4) + 0x10),
            0,
            transform
        );

        // These variables appear unused; possibly part of a larger stack structure
        int dummy1 = DAT_00e2cd48;             // +0x00
        int spriteColor = *(int*)(this + 0x38); // +0x38: sprite color (ARGB)
        int dummy2 = 0;                       // +0x08

        pushRenderState();
        // Set full alpha (0x3f800000 = 1.0f)
        setRenderColor(0, 0x3f800000);
        setRenderTransform(0, transform);
        popRenderState();
    }
}