// FUNC_NAME: WorldObject::setDefaultPosition
void WorldObject::setDefaultPosition(void) {
    RenderManager* renderManager = (RenderManager*)getRenderManager();
    Vector3 defaultPos;
    defaultPos.x = 2;
    defaultPos.y = 16;
    defaultPos.z = 0;
    renderManager->setObjectPosition(this, &defaultPos); // virtual call via vtable
}