// FUNC_NAME: Entity::updateVisual
void Entity::updateVisual()
{
    Visual* visual = *(Visual**)(this + 0x10); // this->pVisual
    if (visual != nullptr)
    {
        // Call vtable[1] (setPosition) with two float arguments from this+0x8 and this+0xC
        visual->setPosition(*(float*)(this + 0x8), *(float*)(this + 0xC));
        // Call vtable[3] (render) - usually takes no arguments
        visual->render();
    }
    // Post-render hook
    FUN_009c8eb0();
}