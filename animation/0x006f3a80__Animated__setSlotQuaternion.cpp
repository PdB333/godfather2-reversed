// FUNC_NAME: Animated::setSlotQuaternion
void __thiscall Animated::setSlotQuaternion(int this, int slotIndex, const float* quat) {
    if (quat != nullptr) {
        switch (slotIndex) {
        case 0:
            // Slot 0 quaternion at offset +0x14
            *(float*)(this + 0x14) = quat[0];
            *(float*)(this + 0x18) = quat[1];
            *(float*)(this + 0x1c) = quat[2];
            *(float*)(this + 0x20) = quat[3];
            break;
        case 1:
            // Slot 1 quaternion at offset +0x48
            *(float*)(this + 0x48) = quat[0];
            *(float*)(this + 0x4c) = quat[1];
            *(float*)(this + 0x50) = quat[2];
            *(float*)(this + 0x54) = quat[3];
            break;
        case 2:
            // Slot 2 quaternion at offset +0x7c
            *(float*)(this + 0x7c) = quat[0];
            *(float*)(this + 0x80) = quat[1];
            *(float*)(this + 0x84) = quat[2];
            *(float*)(this + 0x88) = quat[3];
            break;
        case 3:
            // Slot 3 quaternion at offset +0xb0
            *(float*)(this + 0xb0) = quat[0];
            *(float*)(this + 0xb4) = quat[1];
            *(float*)(this + 0xb8) = quat[2];
            *(float*)(this + 0xbc) = quat[3];
            break;
        }
    }
}