// FUN_NAME: Entity::render
void __thiscall Entity::render(int renderPass)
{
    // +0x580: pointer to render component (e.g., MeshComponent or RenderInstance)
    RenderComponent* renderComponent = *(RenderComponent**)((int)this + 0x580);
    if (renderComponent != nullptr)
    {
        // FUN_005e9d10: check if render component is valid/visible
        if (isVisibleCheck())
        {
            // Begin rendering context
            beginRender();
            // Render sub-element with flags=0 and given render pass
            renderSubMesh(0, renderPass);
            // End rendering context
            endRender();
        }
    }
    return;
}