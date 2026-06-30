// FUNC_NAME: CameraManager::registerCamera
int* CameraManager::registerCamera(int* cameraObj)
{
    char activeFlag;
    int head;
    float* positionData;
    short animIndex;
    int* ptr;
    int index;
    int unknownVal;
    float dx, dy, dz;
    float localX, localY, localZ;
    int localArray[3];

    // Get the CameraManager singleton (global pointer)
    CameraManager* manager = (CameraManager*)getCameraManager();
    head = manager->head;
    cameraObj[0] = head; // next pointer
    cameraObj[1] = 0;    // prev pointer = null initially
    if (head != 0) {
        cameraObj[1] = *(int*)(head + 4); // set prev to old head's prev
        *(int**)(head + 4) = cameraObj;   // old head's prev = this
    }
    cameraObj[2] = manager->someData; // store some data from manager

    head = manager->head;
    if (head != 0) {
        positionData = (float*)manager->someData; // position pointer from manager
        activeFlag = *(char*)(positionData + 5);   // flag at offset +20? (5 floats = 20 bytes)
        unknownVal = getPlayerCameraTransform();
        // Compute local vector from player to manager's position, transformed by camera rotation
        localX = *positionData - *(float*)(unknownVal + 0x30);
        localY = positionData[1] - *(float*)(unknownVal + 0x34);
        localZ = positionData[2] - *(float*)(unknownVal + 0x38);
        unknownVal = getPlayerCameraTransform();
        float rot00 = *(float*)(unknownVal + 0x10);
        float rot01 = *(float*)(unknownVal + 0x14);
        float rot02 = *(float*)(unknownVal + 0x18);
        // Transform vector (dot with rotation matrix rows)
        float transformedX = rot00 * localX + rot01 * localY + rot02 * localZ;
        float transformedY = rot01 * transformedX + localY;
        float transformedZ = rot02 * transformedX + localZ;
        transformedX = rot00 * transformedX + localX;

        if (activeFlag != '\0') {
            // Check squared distance against threshold
            if (transformedZ*transformedZ + transformedY*transformedY + transformedX*transformedX <= DAT_00d61b08) {
                animIndex = FUN_006eb670(activeFlag);
                int childObj = FUN_005f5c20(head, *(int*)(head + 0x20) + (uint)(ushort)(*(short*)(positionData + 4) + animIndex) * 0x10 + *(int*)(head + 0x24) + 4 * 0x24);
                FUN_005f7ba0(childObj);
                if (localX != 0.0f) {
                    FUN_004daf90(&localX);
                }
                return cameraObj;
            }
            if (activeFlag != '\0') {
                animIndex = FUN_006eb670(activeFlag);
                index = *(int*)(head + 0x20) + (uint)(ushort)(*(short*)(positionData + 4) + animIndex) * 0x10 + *(int*)(head + 0x24) + 4 * 0x24;
                unknownVal = getPlayerCameraTransform();
                FUN_004a08d0(&localX, (float*)(unknownVal + 0x30), positionData, index);
                localX = localX - *(float*)(unknownVal + 0x30);
                localY = localY - *(float*)(unknownVal + 0x34);
                localZ = localZ - *(float*)(unknownVal + 0x38);
                if (localX*localX + localZ*localZ + localY*localY <= DAT_00d61b08) {
                    int childObj2 = FUN_005f5c20(head, index);
                    FUN_005f7ba0(childObj2);
                    if (localArray[0] == 0) {
                        return cameraObj;
                    }
                    FUN_004daf90(localArray);
                    return cameraObj;
                }
            }
        }
        return cameraObj;
    }
    return cameraObj;
}