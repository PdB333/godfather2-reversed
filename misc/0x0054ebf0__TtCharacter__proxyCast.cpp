// FUNC_NAME: TtCharacter::proxyCast
// Function address: 0x0054ebf0
// This function performs a character proxy raycast (line-of-sight or collision query).
// It is used extensively and the code warns about being called too much.
// Parameters:
//   this      - pointer to TtCharacter object
//   param_2   - pointer to start position (3 floats)
//   param_3   - pointer to end position (3 floats)
//   param_4   - unknown (likely flags/user data)
//   param_5   - unknown (likely color or type)
//   param_6   - unknown (likely color or type)
//   param_7   - unknown (likely color or type)
//   param_8   - optional output: hit object ID (pointer)
//   param_9   - optional output: hit position (3 floats pointer)
//   param_10  - optional output: hit normal or additional data (pointer)
// Returns: 0 if hit, 1 if no hit (or vice versa based on flag)

undefined1 __thiscall TtCharacter::proxyCast(int this, undefined4* startPos, undefined4* endPos, undefined4 param4, undefined4 param5, undefined4 param6, undefined4 param7, undefined4* outHitObject, undefined4* outHitPosition, undefined4* outHitNormal)
{
    undefined4* tlsBuffer;
    uint64_t timeStamp;
    LPVOID tlsValue;
    uint randomFlags;
    undefined4 result;
    int componentPtr;
    undefined1 returnValue;
    int tempStack[2];
    undefined** tablePtr;
    undefined4 inputData;
    char successFlag;
    uint flags;
    undefined4 startX, startY, startZ;
    undefined4 endX, endY, endZ;
    float adjustedEndY;
    undefined4 localVar;
    undefined4 color1, color2, color3;
    undefined4 unknown1, unknown2;
    // ... many stack variables

    // Profiling: record start of function call
    tlsValue = TlsGetValue(DAT_01139830);
    tlsBuffer = *(undefined4**)((int)tlsValue + 4); // +0x04: current buffer pointer
    if (tlsBuffer < *(undefined4**)((int)tlsValue + 0xc)) // +0x0c: buffer end
    {
        *tlsBuffer = "TtCharacter Proxy Cast Could be Called way too much"; // warning message
        timeStamp = rdtsc();
        tempStack[0] = (int)timeStamp;
        tlsBuffer[1] = tempStack[0];
        *(undefined4**)((int)tlsValue + 4) = tlsBuffer + 3; // advance pointer
    }

    // Retrieve component pointer from this+0x18 (likely a physics or cast component)
    componentPtr = *(int*)(this + 0x18);
    // Get a handle from that component +0x10
    result = *(undefined4*)(componentPtr + 0x10);

    returnValue = 1; // assume no hit initially

    // Call a debug/profiling function (maybe start/end of profile block)
    FUN_0045cbe0();

    // Set up initial raycast structure (start position)
    // Constants from global data
    inputData = DAT_00e2b1a4; // likely some default value
    // Start position (from param_2)
    startX = *startPos;
    startY = startPos[1];
    startZ = startPos[2];
    // Adjust Y by an offset
    adjustedEndY = (float)startY + DAT_00e2cb90; // +0x? offset (e.g., ground height)
    // Build a local structure for the raycast start
    // ... (stack layout)
    // This structure is passed to FUN_00549b60 (maybe a raycast setup function)
    FUN_00549b60(result, &inputData, 0); // 0 might be a flag

    // Check if a callback or function pointer exists at componentPtr+0x20 relative to componentPtr+0x10
    // The condition: (int*(char*)(componentPtr + 0x20) + componentPtr + 0x10) != 0
    // This is likely a vtable or function pointer check
    if ((int)*(char*)(componentPtr + 0x20) + componentPtr + 0x10 != 0)
    {
        // Call a function to get a random number or seed
        FUN_004af8c0(tempStack, 0x2001); // 0x2001 might be a flag/type
        int randomVal = 0;
        if (tempStack[0] != 0)
            randomVal = tempStack[0];
        if (randomVal != 0)
        {
            randomFlags = FUN_0043b490(); // get random flags
            goto LAB_0054ecfd;
        }
    }
    randomFlags = 0;

LAB_0054ecfd:
    // Build the main raycast structure with flags and colors
    flags = (randomFlags & 0xfff) << 0x10 | 0x3e0; // mask and combine flags
    // Set up colors from constants
    color1 = DAT_00e44598; // maybe color values
    color2 = DAT_00e44598;
    color3 = param7; // color from param
    // End position (from param_3)
    endX = *endPos;
    endY = endPos[1];
    endZ = endPos[2];
    adjustedEndY = (float)endY + DAT_00e2cb90; // same offset
    // Additional parameters
    unknown1 = param4;
    unknown2 = param5;
    // ... set other stack fields

    // Set up a pointer to a lookup table (PTR_LAB_00e39f2c or PTR_LAB_00dc471c)
    // Based on whether output parameters are provided
    if (outHitObject == nullptr && outHitPosition == nullptr && outHitNormal == nullptr)
    {
        // No outputs requested: use a simple raycast table
        tablePtr = &PTR_LAB_00e39f2c;
        // Set up the input structure (stack layout)
        // ... (omitted for brevity)
        FUN_009e7fd0(/* stack structure */, &endPos, &tablePtr, 0);
        if (successFlag != 0) // check if hit was detected
            returnValue = 0; // hit
    }
    else
    {
        // Outputs requested: use a different table (raycast with hit info)
        tablePtr = &PTR_LAB_00dc471c;
        // Additional data for output
        // ... (stack setup)
        FUN_009e7fd0(/* stack structure */, &endPos, &tablePtr, 0);
        if (tempStack[0] != 0) // indicates hit
        {
            if (outHitObject != nullptr)
            {
                // Convert handle to object ID
                result = FUN_004afca0(/* handle from stack */);
                *outHitObject = result;
            }
            if (outHitPosition != nullptr)
            {
                // Copy hit position from stack
                outHitPosition[0] = /* x */;
                outHitPosition[1] = /* y */;
                outHitPosition[2] = /* z */;
            }
            if (outHitNormal != nullptr)
            {
                *outHitNormal = /* normal from stack */;
            }
            returnValue = 0; // hit
        }
    }

    // Profiling: record end of function call
    tlsValue = TlsGetValue(DAT_01139830);
    tlsBuffer = *(undefined4**)((int)tlsValue + 4);
    if (tlsBuffer < *(undefined4**)((int)tlsValue + 0xc))
    {
        *tlsBuffer = &DAT_00e39c6c; // end marker
        timeStamp = rdtsc();
        tlsBuffer[1] = (int)timeStamp;
        *(undefined4**)((int)tlsValue + 4) = tlsBuffer + 3;
    }

    return returnValue;
}