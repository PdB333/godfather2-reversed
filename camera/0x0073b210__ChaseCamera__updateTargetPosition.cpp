// FUNC_NAME: ChaseCamera::updateTargetPosition
void __thiscall ChaseCamera::updateTargetPosition(const Vector3& targetPos)
{
    // Check if the initial camera setup flag (0x10) is not set
    if ((this->flags & 0x10) == 0) {
        // If we have a valid camera manager ID
        if (this->cameraMgrId != 0) {
            ChaseCameraManager* mgr = GetSingleton(DAT_0113105c);
            if (mgr != nullptr) {
                // Clear a bit in the manager's state (likely camera ready flag)
                mgr->stateFlags &= 0xfffb;
            }
        }
        // Mark the initial setup as done
        this->flags |= 0x10;
    }

    // Resolve the target camera object (second camera singleton)
    ChaseCameraObject* camObj;
    if (this->cameraMgrId == 0) {
        camObj = nullptr;
    } else {
        camObj = GetSingleton(DAT_01131064);
    }

    // Check if the camera initialization flag (0x20) is not set
    if ((this->flags & 0x20) == 0) {
        if (camObj != nullptr) {
            // Initialize camera mode (arg 0 likely means chase mode)
            SetCameraMode(0);
        }
        this->flags |= 0x20;
    }

    // Determine which parent transform to use based on a type field
    int parentTransform;
    if ((this->parentType == 0) || (this->parentType == 0x48)) {
        parentTransform = 0;
    } else {
        parentTransform = this->parentTransformIndex;
    }

    // Copy the target position (12 bytes: x,y,z)
    camObj->targetPos = targetPos;  // copies 8 bytes + 4 bytes from targetPos

    // Set camera orientation/offset based on whether a scale factor is present
    if (this->useScaleFactor == 0) {
        // No scaling: copy directly from parent transform
        camObj->orientation.x = *(float*)(parentTransform + 0xb0);  // +0xb0 likely pitch or yaw
        camObj->orientation.y = *(float*)(parentTransform + 0xb8);  // +0xb8 likely roll or distance
    } else {
        // Scale the orientation/offset value
        camObj->orientation.x = *(float*)(parentTransform + 0xb0) * DAT_00d5eee4;
        camObj->orientation.y = *(float*)(parentTransform + 0xb8);
    }
}