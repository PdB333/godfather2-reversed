// FUNC_NAME: PostEffect::initialize
void __fastcall PostEffect::initialize()
{
    // +0x10: renderer pointer
    this->renderer = getRenderer();
    
    // +0x14: first shader (e.g., "DeferredLighting")
    this->shader1 = getShader(PTR_DAT_010bea80); // "DeferredLighting" or similar
    
    // Set default render state
    setDefaultRenderState();
    
    // +0xa8: copy of shader1 (maybe a separate slot for backbuffer shader)
    this->shaderBackbuffer = this->shader1;
    
    // +0xa4: second shader (e.g., "SSAO" or "PostProcess")
    this->shader2 = getShader(PTR_DAT_010bea70); // "PostProcess" or similar
    
    // Get parameter handles for shader2
    this->colorTextureHandle = getParameterHandle(this->shader2, "ColorTexture");       // +0xac
    this->depthTextureHandle = getParameterHandle(this->shader2, "DepthTexture");       // +0xb0
    this->nBufferHandle      = getParameterHandle(this->shader2, "g_nBuffer");          // +0xb4
    this->texelSizeHandle    = getParameterHandle(this->shader2, "g_TexelSize");        // +0xb8
    this->barrierWeightsHandle = getParameterHandle(this->shader2, "g_BarrierAndWeights"); // +0xbc
    
    // Get parameter handles for shaderBackbuffer
    this->bbTextureHandle    = getParameterHandle(this->shaderBackbuffer, "bb_texture"); // +0xc0
    this->bbTexelSizeHandle  = getParameterHandle(this->shaderBackbuffer, "g_TexelSize"); // +0xc4
    
    // Get half-pixel offset handles for both shaders
    this->halfPixelOffsetHandle1 = getParameterHandle(this->shader1, "g_halfPixelOffset"); // +0xe4
    this->halfPixelOffsetHandle2 = getParameterHandle(this->shaderBackbuffer, "g_halfPixelOffset"); // +0xe8
}