// FUNC_NAME: PhysicsQuery::performRaycast
int PhysicsQuery::performRaycast(int filterInfo, int* hitMaterial, int param_3, RayHitResult* outHitResult)
{
    if (this == 0) {
        return 0;
    }

    float3 rayOrigin;
    float3 rayDirection;
    char raycastBuffer[12]; // buffer for raycast function

    FUN_008970a0(&rayOrigin);
    int camera = FUN_00471610();
    float* cameraVectors = (float*)(camera + 0x20);
    rayDirection.x = cameraVectors[0] * g_rayCastDistance + rayOrigin.x;
    rayDirection.y = cameraVectors[1] * g_rayCastDistance + rayOrigin.y;
    rayDirection.z = cameraVectors[2] * g_rayCastDistance + rayOrigin.z;

    // Perform raycast from world space
    char result = FUN_007e94f0(filterInfo, &rayDirection, 
                                (undefined8*)(this + 8), // output ray start
                                (undefined8*)(this + 0x18), // output ray end
                                0x10000, // collision flags
                                0x10000400, // collision flags
                                raycastBuffer);

    if (result == '\0') {
        // Copy hit position (3 floats)
        *(undefined8*)outHitResult = *(undefined8*)(this + 8);
        *(undefined4*)((int)outHitResult + 4) = *(undefined4*)(this + 0x10);
        // Copy hit normal (3 floats)
        *(undefined8*)((int)outHitResult + 0xc) = *(undefined8*)(this + 0x18);
        *(undefined4*)((int)outHitResult + 0x14) = *(undefined4*)(this + 0x20);
        // Copy distance (square root of something)
        outHitResult->distance = SQRT(*(float*)(this + 0x14));
        // Copy additional hit info
        outHitResult->material = *hitMaterial;
        outHitResult->additionalInfo.x = **(float**)(this + 0x24);
        outHitResult->additionalInfo.y = *(float*)(*(int*)(this + 0x24) + 4);
        return 1;
    }
    return 0;
}