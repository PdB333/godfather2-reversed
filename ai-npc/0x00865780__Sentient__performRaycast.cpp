// FUNC_NAME: Sentient::performRaycast
void __thiscall Sentient::performRaycast(int thisPtr, int inputHandle, int* outResult)
{
    // Extract data from input handle (12 bytes)
    char extractedData[12];
    extractDataFromInput(inputHandle, extractedData);

    // Initialize output to 0 (no hit)
    *outResult = 0;

    // Read position from this+0x1050 (Vector3)
    Vector3 position;
    position.x = *(float*)(thisPtr + 0x1050);
    position.y = *(float*)(thisPtr + 0x1054);
    position.z = *(float*)(thisPtr + 0x1058);

    // Get direction or distance from some function (fills float[3])
    float direction[3];
    getForwardVector(direction); // likely fills direction[0] with forward x, etc.

    // Prepare parameters for raycast
    int someField = *(int*)(thisPtr + 0x1148); // e.g., collision group or transform index
    int zero1 = 0, zero2 = 0, zero3 = 0, zero4 = 0;

    // Transform position using someField (e.g., world transform)
    transformPosition(&position, someField, outResult, 0, 0, 0, 0);

    // Perform the actual raycast
    performRaycastInternal(extractedData, (float)(double)direction[0], &position, someField, outResult, zero1, zero2, zero3, zero4);
}