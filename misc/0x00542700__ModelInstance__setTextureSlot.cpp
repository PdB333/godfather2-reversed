// FUNC_NAME: ModelInstance::setTextureSlot
void ModelInstance::setTextureSlot()
{
    uint32_t textureId = *(uint32_t *)(this + 0x20); // +0x20: default texture slot ID
    // Check if the material type of the linked renderable is 0xb (e.g., specular or detail map type)
    int* renderable = *(int**)(this + 0x50); // +0x50: pointer to renderable object (e.g., Renderable or Mesh)
    if (*(int*)(*(int*)(renderable) + 0xc) == 0xb) // +0xc: type field at vtable+0xc?
    {
        textureId = *(uint32_t *)(this + 0x24); // +0x24: alternate texture slot ID
    }
    // Apply the chosen texture to the renderable
    FUN_005566a0(renderable, textureId);
}