// FUNC_NAME: ObjectManager::setObjectQuaternionByKey
void __thiscall ObjectManager::setObjectQuaternionByKey(void* thisPtr, int keyID, float* quaternion) {
    int index = findObjectIndexByKey(&keyID);  // FUN_00949380
    if (index >= 0) {
        // +0x60: pointer to array of objects, each entry 8 bytes: { int something, void* objectPtr }
        int objectPtr = *(int*)(*(int*)((char*)thisPtr + 0x60) + 4 + index * 8);
        // Write 4 floats (quaternion) at offset 0x130 within the object
        *(float*)(objectPtr + 0x130) = quaternion[0];
        *(float*)(objectPtr + 0x134) = quaternion[1];
        *(float*)(objectPtr + 0x138) = quaternion[2];
        *(float*)(objectPtr + 0x13c) = quaternion[3];
    }
}