// FUNC_NAME: ShaderEffect::resolveHandles
// Address: 0x006127d0
// This function resolves shader constant handles from effect objects (vertex and pixel shaders).
// It stores the handles into the object's member fields for later use during rendering.

void ShaderEffect::resolveHandles(void)
{
    int handle;

    // Resolve vertex shader constants (effect at +0x10)
    if (this->vertexEffect != nullptr) {
        handle = getConstantHandle(this->vertexEffect, "LightMatrix");
        this->lightMatrixHandle = handle; // +0x18
        handle = getConstantHandle(this->vertexEffect, "g_WorldEyePosition");
        this->worldEyePositionVSHandle = handle; // +0x1C
        handle = getConstantHandle(this->vertexEffect, "matLightWVPTex");
        this->lightWVPTexHandle = handle; // +0x20
        handle = getConstantHandle(this->vertexEffect, "ZeroHalfTwoOne");
        this->zeroHalfTwoOneHandle = handle; // +0x24
        handle = getConstantHandle(this->vertexEffect, "fog_params");
        this->fogParamsVSHandle = handle; // +0x8C
        handle = getConstantHandle(this->vertexEffect, "Model");
        this->modelHandle = handle; // +0x28
        handle = getConstantHandle(this->vertexEffect, "ModelRot");
        this->modelRotHandle = handle; // +0x2C
        handle = getConstantHandle(this->vertexEffect, "ModelView");
        this->modelViewHandle = handle; // +0x30
        handle = getConstantHandle(this->vertexEffect, "ViewRot");
        this->viewRotVSHandle = handle; // +0x34
        handle = getConstantHandle(this->vertexEffect, "InvViewRot");
        this->invViewRotVSHandle = handle; // +0x38
        handle = getConstantHandle(this->vertexEffect, "ModelView");
        this->modelViewHandle2 = handle; // +0x3C (duplicate? maybe different)
        handle = getConstantHandle(this->vertexEffect, "ModelViewRot");
        this->modelViewRotHandle = handle; // +0x40
        handle = getConstantHandle(this->vertexEffect, "ViewProj");
        this->viewProjHandle = handle; // +0x44
        handle = getConstantHandle(this->vertexEffect, "InvModelView");
        this->invModelViewHandle = handle; // +0x48
        handle = getConstantHandle(this->vertexEffect, "ModelViewProj");
        this->modelViewProjHandle = handle; // +0x4C
        handle = getConstantHandle(this->vertexEffect, "Orientation");
        this->orientationHandle = handle; // +0x50
        handle = getConstantHandle(this->vertexEffect, "Translation");
        this->translationHandle = handle; // +0x54
        handle = getConstantHandle(this->vertexEffect, "TranslationViewProj");
        this->translationViewProjHandle = handle; // +0x58
        handle = getConstantHandle(this->vertexEffect, "g_BlendMatrices");
        this->blendMatricesHandle = handle; // +0x64
        handle = getConstantHandle(this->vertexEffect, "vPosScaleTranslationVS");
        this->posScaleTranslationVSHandle = handle; // +0x60
    }

    // Resolve pixel shader constants (effect at +0x14)
    if (this->pixelEffect != nullptr) {
        handle = getConstantHandle(this->pixelEffect, "g_WorldEyePosition");
        this->worldEyePositionPSHandle = handle; // +0x6C
        handle = getConstantHandle(this->pixelEffect, "g_AmbientColor");
        this->ambientColorHandle = handle; // +0x70
        handle = getConstantHandle(this->pixelEffect, "g_Tint");
        this->tintHandle = handle; // +0x74
        handle = getConstantHandle(this->pixelEffect, "fog_color");
        this->fogColorPSHandle = handle; // +0x90
        handle = getConstantHandle(this->pixelEffect, "cGamma");
        this->gammaHandle = handle; // +0x78
        handle = getConstantHandle(this->pixelEffect, "ModelView");
        this->modelViewPSHandle = handle; // +0x7C
        handle = getConstantHandle(this->pixelEffect, "ViewRot");
        this->viewRotPSHandle = handle; // +0x80
        handle = getConstantHandle(this->pixelEffect, "InvViewRot");
        this->invViewRotPSHandle = handle; // +0x84
        handle = getConstantHandle(this->pixelEffect, "g_depthBias");
        this->depthBiasHandle = handle; // +0x94
        handle = getConstantHandle(this->pixelEffect, "g_DeferredLightingSampler");
        this->deferredLightingSamplerHandle = handle; // +0xA0
        handle = getConstantHandle(this->pixelEffect, "vPosScaleTranslation");
        this->posScaleTranslationPSHandle = handle; // +0x5C

        // Call virtual function at vtable+0x34 (likely commitChanges or apply)
        (this->vtable->commitChanges)();

        // If there is a technique object at +0x98
        if (this->technique != nullptr) {
            // Call virtual function at vtable+0x04 (likely begin or release)
            (this->technique->vtable->begin)();
            // Call virtual function at vtable+0x14 (returns a byte, maybe isValid)
            this->techniqueValid = (this->technique->vtable->isValid)();
        }
    }
}