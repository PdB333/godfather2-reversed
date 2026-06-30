// FUNC_NAME: CameraManager::updateGlobalCameraTarget
void CameraManager::updateGlobalCameraTarget() {
    // Check if there is a valid camera target object (offset +0x98: pointer to target object)
    if (this->field_0x98 != 0) {
        // Resolve a handle or ID from field_0x9c to get the target's transform pointer
        // FUN_0061f770 likely returns a pointer to some object (e.g., transform component)
        void* targetTransform = FUN_0061f770(this->field_0x9c);
        if (targetTransform != 0) {
            // Copy position from transform's offset +0x30, +0x34, +0x38 (likely 3 floats)
            gCameraTargetPositionX = *(float*)((char*)targetTransform + 0x30);
            gCameraTargetPositionY = *(float*)((char*)targetTransform + 0x34);
            gCameraTargetPositionZ = *(float*)((char*)targetTransform + 0x38);
            // Copy a byte flag from this object at offset +0x8d to global validity flag
            gCameraTargetValid = *(char*)((char*)this + 0x8d);
        } else {
            // No valid target, clear global position and flag
            gCameraTargetPositionX = 0.0f;
            gCameraTargetPositionY = 0.0f;
            gCameraTargetPositionZ = 0.0f;
            gCameraTargetValid = 0;
        }
    }
}