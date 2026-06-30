// FUNC_NAME: EARSObject::setMaterialOverride
void __thiscall EARSObject::setMaterialOverride(void* this, void* pOverride, void* pSource)
{
    *(uint8_t*)((int)pOverride + 4) = 0; // clear flag at offset +0x4

    void* source;
    if (pSource != NULL) {
        source = pSource;
    } else {
        // use default material from global data: DAT_01223480->someManager->defaultMaterial
        source = *(void**)(*(int*)(*(int*)DAT_01223480 + 0x24) + 0x6c);
    }
    // copy material data into override buffer; offset 0xC0 is the material slot
    FUN_009eb910((int)this + 0xc0, source, pOverride);
}