// FUNC_NAME: ChaseCamera::~ChaseCamera
void __thiscall ChaseCamera::destructor(ChaseCamera* this) {
    // Set vtable to the most-derived class vtable (ChaseCamera)
    this->vtablePtr = &CHASE_CAMERA_VTABLE;

    // +0x1D: flag indicating whether the contained subobject (e.g., a base camera or component) should be destroyed
    if (this->destroySubObject) {
        // +0x58: pointer to the subobject's vtable (e.g., Camera component)
        // call subobject's destruction method (vtable offset 0x25C)
        ((void (*)(void))(*(int*)(this->subObject->vtablePtr + 0x25C)))();
    }

    // Get the singleton CameraManager instance
    CameraManager* cameraMgr = CameraManager::getInstance();

    // +0x78: pointer to be unregistered from the camera manager
    // Call CameraManager::unregisterCamera (vtable slot 1, offset +4)
    ((void (*)(void*))(*(int*)cameraMgr->vtablePtr + 4))(this->unregisterKey);

    // Set vtable to base class (e.g., CameraBase) before final destruction
    this->vtablePtr = &CAMERA_BASE_VTABLE;

    // Call base destructor or operator delete
    Camera::baseDestructor();
}