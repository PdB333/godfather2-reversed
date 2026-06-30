// FUNC_NAME: BoxLightEffect::constructor
// 0x00494760 - Initializes BoxLightEffect object: stores self-pointer, acquires shader system, retrieves shader parameter handles for box light rendering.

using ShaderParameterHandle = unsigned int;

extern ShaderSystem* GetShaderSystem(ShaderSystem** ppSystem); // FUN_0060a2e0
extern void BaseInitialize();                                 // FUN_004907a0
extern ShaderParameterHandle GetShaderParameterHandle(ShaderSystem* system, const char* name); // FUN_0060a580
extern void PostInitialize();                                 // FUN_004923e0

// Offsets:
// +0x14 : ShaderSystem* m_shaderSystem
// +0x2d0: BoxLightEffect* m_selfRef
// +0x2d4: ShaderParameterHandle m_boxLightInvMtx
// +0x320: ShaderParameterHandle m_boxLightFBScale (800 decimal = 0x320)
// +0x340: ShaderParameterHandle m_boxLightFBOffset

void __fastcall BoxLightEffect::constructor(BoxLightEffect* this) {
    this->m_selfRef = this;                                          // +0x2d0
    this->m_shaderSystem = GetShaderSystem((ShaderSystem**)0x0110a17c); // +0x14
    BaseInitialize();                                                // FUN_004907a0
    this->m_boxLightInvMtx = this->m_shaderSystem->GetParameterHandle("g_boxLightInvMtx");   // +0x2d4
    this->m_boxLightFBScale = this->m_shaderSystem->GetParameterHandle("g_boxLightFBScale"); // +0x320
    this->m_boxLightFBOffset = this->m_shaderSystem->GetParameterHandle("g_boxLightFBOffset");// +0x340
    PostInitialize();                                                // FUN_004923e0
}