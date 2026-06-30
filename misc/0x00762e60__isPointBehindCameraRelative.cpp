// FUNC_NAME: isPointBehindCameraRelative

int isPointBehindCameraRelative(int componentOrFlag, float* pointInWorld, int unknownParam, float* pointToTest)
{
    float camToPointX, camToPointY, camToPointZ;
    float pointToTestX, pointToTestY, pointToTestZ;

    if (componentOrFlag == 0) {
        return 0;
    }
    if ((pointInWorld != (float *)0x0) && (unknownParam != 0)) {
        if (pointToTest != (float *)0x0) {
            // Get camera position (offsets 0x30, 0x34, 0x38 from some camera object)
            int* cameraData = getCameraPositionPtr(); // FUN_00471610
            float camX = *(float*)(cameraData + 0x30 / 4); // +0x30
            float camY = *(float*)(cameraData + 0x34 / 4); // +0x34
            float camZ = *(float*)(cameraData + 0x38 / 4); // +0x38

            // Vector from camera to pointInWorld
            camToPointX = *pointInWorld - camX;
            camToPointY = pointInWorld[1] - camY;
            camToPointZ = pointInWorld[2] - camZ;

            // Normalize the vector
            vectorNormalize(&camToPointX, &camToPointY, &camToPointZ); // FUN_0043a210

            // Vector from pointInWorld to pointToTest
            pointToTestX = *pointToTest - *pointInWorld;
            pointToTestY = pointToTest[1] - pointInWorld[1];
            pointToTestZ = pointToTest[2] - pointInWorld[2];

            // Dot product: (camToPoint · pointToTest)
            float dot = camToPointZ * pointToTestZ + camToPointX * pointToTestX + camToPointY * pointToTestY;

            // If dot product is negative, pointToTest is behind the plane defined by pointInWorld and camera direction
            if (dot < 0.0f) {
                return 1;
            }
        }
        return 0;
    }
    return 0;
}