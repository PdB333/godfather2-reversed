// FUNC_NAME: GlowEffect::initShaders
class GlowEffect {
public:
    // Offset 0x10: first shader handle (unknown type)
    int m_hShaderA; // +0x10
    int m_hShaderB; // +0x14
    // ... (many shader handles)
    int m_hShaderC; // +0x164? Actually offset order is mixed; we'll use exact offsets.
    // We'll use offsets as defined in the function.

    // For simplicity, declare members with offsets in comments.
    void initShaders();
};

// Assume typedef for shader handle
typedef int ShaderHandle;
typedef int ShaderParamHandle;

// External functions (real names from game)
ShaderHandle createShaderHandle();
ShaderHandle loadShader(const char* stringPtr); // Actually takes pointer to string resource
void unknownInit(); // FUN_006127d0
ShaderParamHandle getShaderParamHandle(ShaderHandle shader, const char* paramName);

// Global flag (likely platform-dependent)
extern bool g_isXbox360; // DAT_0120575b

void GlowEffect::initShaders() {
    ShaderHandle h1, h2;
    ShaderParamHandle param;

    // Initialize first two shader handles
    h1 = createShaderHandle();
    this->m_hShaderA = h1; // +0x10
    h2 = loadShader(&PTR_DAT_010be020); // some string resource
    this->m_hShaderB = h2; // +0x14

    unknownInit(); // FUN_006127d0

    // Store copies of these handles at different offsets
    *(int*)((char*)this + 0x164) = this->m_hShaderB; // +0x164 = h2
    *(int*)((char*)this + 0x160) = this->m_hShaderA; // +0x160 = h1

    // Load more shaders
    ShaderHandle h3 = loadShader(&PTR_DAT_010be030); // dither shader?
    *(int*)((char*)this + 0x170) = h3; // +0x170

    ShaderHandle h4 = loadShader(&PTR_DAT_010be050); // depth shader?
    *(int*)((char*)this + 0x16c) = h4; // +0x16c

    ShaderHandle h5 = createShaderHandle();
    *(int*)((char*)this + 0x168) = h5; // +0x168

    ShaderHandle h6 = createShaderHandle();
    *(int*)((char*)this + 0x180) = h6; // +0x180

    ShaderHandle h7 = loadShader(&PTR_DAT_010be060); // screen color shader?
    *(int*)((char*)this + 0x184) = h7; // +0x184

    *(int*)((char*)this + 0x174) = 0; // +0x174
    *(int*)((char*)this + 0x178) = 0; // +0x178

    // Branch based on platform
    if (!g_isXbox360) {
        // Xbox 360 path
        ShaderHandle h8 = createShaderHandle();
        *(int*)((char*)this + 0x174) = h8;
    } else {
        // PS3 path
        ShaderHandle h8 = createShaderHandle();
        *(int*)((char*)this + 0x174) = h8;
    }

    ShaderHandle h9 = createShaderHandle();
    *(int*)((char*)this + 0x178) = h9;

    ShaderHandle h10 = loadShader(&PTR_DAT_010be040);
    *(int*)((char*)this + 0x17c) = h10;

    // ---- Set up parameter handles ----

    // From shader at +0x160 (first shader)
    ShaderParamHandle p1 = getShaderParamHandle(*(int*)((char*)this + 0x160), "gVFGlowInfo");
    *(int*)((char*)this + 0x130) = p1; // +0x130
    *(int*)((char*)this + 0x134) = 0; // +0x134
    *(int*)((char*)this + 0x148) = 0; // +0x148
    *(int*)((char*)this + 0x15c) = 0; // +0x15c

    if (*(int*)((char*)this + 0x174) != 0) {
        ShaderHandle shader = *(int*)((char*)this + 0x174);
        ShaderParamHandle p2 = getShaderParamHandle(shader, "gVFGlowInfo");
        *(int*)((char*)this + 0x134) = p2;
        if (!g_isXbox360) {
            // Xbox 360
            ShaderParamHandle p3 = getShaderParamHandle(shader, "queryModulateAlpha");
            *(int*)((char*)this + 0x15c) = p3;
        } else {
            // PS3
            ShaderParamHandle p3 = getShaderParamHandle(shader, "modulate_sampler_vs");
            *(int*)((char*)this + 0x148) = p3;
        }
    }

    // Initialize more parameters to zero
    *(int*)((char*)this + 0x12C) = 0; // offset 300 decimal = 0x12C
    *(int*)((char*)this + 0x138) = 0;
    *(int*)((char*)this + 0x144) = 0;
    *(int*)((char*)this + 0x154) = 0;
    *(int*)((char*)this + 0x158) = 0;

    if (*(int*)((char*)this + 0x178) != 0) {
        ShaderHandle shader2 = *(int*)((char*)this + 0x178);
        ShaderParamHandle p4 = getShaderParamHandle(shader2, "screen_color_vs");
        *(int*)((char*)this + 0x12C) = p4;
        if (!g_isXbox360) {
            // Xbox 360
            ShaderParamHandle p5 = getShaderParamHandle(shader2, "queryModulateAlpha");
            *(int*)((char*)this + 0x158) = p5;
        } else {
            // PS3
            ShaderParamHandle p5 = getShaderParamHandle(shader2, "modulate_by_corona_info_vs");
            *(int*)((char*)this + 0x138) = p5;
            ShaderParamHandle p6 = getShaderParamHandle(shader2, "modulate_sampler_vs");
            *(int*)((char*)this + 0x144) = p6;
            ShaderParamHandle p7 = getShaderParamHandle(shader2, "gModulateInfo");
            *(int*)((char*)this + 0x154) = p7;
        }
    }

    // Remaining parameter handles from other shaders
    ShaderParamHandle p8 = getShaderParamHandle(*(int*)((char*)this + 0x17c), "primary_sampler");
    *(int*)((char*)this + 0x13c) = p8;

    ShaderParamHandle p9 = getShaderParamHandle(*(int*)((char*)this + 0x16c), "depth_sampler");
    *(int*)((char*)this + 0x140) = p9;

    ShaderParamHandle p10 = getShaderParamHandle(*(int*)((char*)this + 0x170), "dither_sampler");
    *(int*)((char*)this + 0x14c) = p10;

    ShaderParamHandle p11 = getShaderParamHandle(*(int*)((char*)this + 0x170), "dithering_control");
    *(int*)((char*)this + 0x150) = p11;
}