// FUNC_NAME: ChaseCamera::activate
void __fastcall ChaseCamera::activate(ChaseCamera* this)
{
    // Global pointer to the currently active camera instance
    if (DAT_012058e8 == this) {
        // Already active: mark it as deactivated
        this->isActive = 0; // +0xa4
    }
    else {
        // Activate this camera
        this->isActive = 1; // +0xa4
        DAT_012058e8 = this;
        // Release resources from old cameras (likely previous active camera)
        FUN_0060a460(this->field_0x10); // +0x10 handle or pointer
        FUN_0060a460(this->field_0x14); // +0x14 handle or pointer
    }
    // If camera has secondary resources enabled
    if (this->hasResources != '\0') { // +0xc0
        // Update or configure additional components (e.g., screen effects, HUD overlays)
        FUN_0060add0(this->resourceManager, this->param1, &this->transform1); // +0x104, +0xf8, +0xe0
        FUN_0060add0(this->resourceManager, this->param2, &this->transform2); // +0x104, +0xf4, +0xd0
        FUN_0060aa90(this->resourceManager, this->param3, this->param4); // +0x104, +0xfc, +0xf0
    }
    return;
}