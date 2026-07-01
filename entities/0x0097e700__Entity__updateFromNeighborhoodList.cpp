// FUNC_NAME: Entity::updateFromNeighborhoodList
void __thiscall Entity::updateFromNeighborhoodList(float* newPos, int listParam, uint extraData)
{
    // +0xF0: position (4 floats, likely position + something)
    // +0x102: bit flags (bit0 = dirty position, bit1 = perception active)
    // +0xA4: pointer to some state (cleared when perception deactivated)
    // +0xA8, +0xB4, +0xC0: arrays of known component pointers (size 8 each)

    // Check if new position equals current position
    bool posEqual = (newPos[0] == *(float*)(this + 0xF0)) &&
                    (newPos[1] == *(float*)(this + 0xF4)) &&
                    (newPos[2] == *(float*)(this + 0xF8)) &&
                    (newPos[3] == *(float*)(this + 0xFC));

    bool perceptionActive = (*(byte*)(this + 0x102) >> 1) & 1;

    if (posEqual && !perceptionActive)
    {
        return;
    }

    if (!posEqual)
    {
        if (!perceptionActive)
        {
            // No perception active, just update position
            *(uint*)(this + 0xA4) = 0; // Clear pointer
        }
        else
        {
            // Perception active but position unchanged? Actually this handles posEqual && perceptionActive case
            *(ushort*)(this + 0x102) &= 0xFFFD; // Clear perception active flag
        }

        // If the dirty position flag (bit0) is set, update and return early
        if (*(byte*)(this + 0x102) & 1)
        {
            *(ushort*)(this + 0x102) &= 0xFFFE; // Clear dirty flag
            *(float*)(this + 0xF0) = newPos[0];
            *(float*)(this + 0xF4) = newPos[1];
            *(float*)(this + 0xF8) = newPos[2];
            *(float*)(this + 0xFC) = newPos[3];
            return;
        }
    }

    // Full update path: scan list and gather perception data
    float dt = *(float*)(listParam + 4);
    if (dt > _DAT_00d8fd94) dt = _DAT_00d8fd94; // Clamp delta time

    float localPos[3];
    localPos[0] = newPos[0];
    localPos[1] = newPos[1] - DAT_00d75ca0; // Some elevation offset?
    localPos[2] = newPos[2];

    // Initialize perception arrays
    float perceptionFloats[8] = {0};
    uint perceptionFlags[8] = {0};
    uint someArray[8] = {0};
    uint anotherArray[8] = {0};
    uint componentArray[8] = {0};

    FUN_00a64b00(extraData); // Possibly batch start

    // Build a transform matrix? (using globals)
    float matrix[3][3] = {0}; // Actually uses local_410..local_3e4 as 3x4 matrix, simplified
    // ... (omitted initialization for brevity, actual code copies from globals and zeros)

    FUN_009f0c70(local_370, &local_410, 0); // Some spatial query

    // Setup ray or sphere
    Vector3 origin(localPos[0], localPos[1], localPos[2]);
    Vector3 direction(0,0,0); // Not used?
    undefined* hitListBuffer = local_2f0; // 400 bytes buffer
    uint bufferSize = 0x80000008; // Some flags
    int hitCount = 0;
    uint paramBuffer = DAT_00e445dc;
    undefined** queryPtr = &PTR_LAB_00d8fd8c;

    FUN_009e7fd0(local_160, &origin, &queryPtr, 0); // Perform query

    if (hitCount < 1)
    {
        // No objects - clear perception arrays and set perception active flag
        FUN_0097cd60(); // Clear array 1
        FUN_0097ce70(); // Clear array 2
        FUN_0097cf90(); // Clear array 3
        FUN_0097d100(); // Clear array 4
        *(ushort*)(this + 0x102) |= 2; // Set perception active flag
    }
    else
    {
        // Process each hit
        int numFloats = 0;
        int numSpecials = 0;
        int numThings = 0;
        int numComponents = 0;

        for (int i = 0; i < hitCount; i++)
        {
            // Each hit record is 0x30 bytes, +0x28 offset points to another structure, +0x10 byte indicates type
            int* hitRecord = (int*)(local_300 + i * 0x30);
            int entityPtr = *(int*)(hitRecord + 0x28);
            int entityOffset = *(char*)(entityPtr + 0x10) + entityPtr; // Possibly entity address adjustment

            if (entityOffset == 0)
                continue;

            // Get component from hash
            int* componentPtr = (int*)FUN_004af8c0(&localPos, 0xa1e6d360); // Some global component
            if (componentPtr == 0)
                continue;

            int componentHash = *componentPtr;

            if (componentHash == 0x17f92c3a) // Perception float collector
            {
                int result = FUN_0097c3a0(entityOffset);
                if (result != 0 && FUN_006b4440() != 0 && numFloats < 8)
                {
                    perceptionFloats[numFloats] = *(float*)(result + 0xC);
                    numFloats++;
                }
            }
            else if (componentHash == 0x32fc9cdc) // Some aura/effect
            {
                int result = FUN_0097c350(entityOffset, this + 0xA8);
                if (result != 0 && numSpecials < 8)
                {
                    someArray[numSpecials] = *(uint*)(result + 0xC);
                    numSpecials++;
                }
            }
            else if (componentHash == 0x2bb07a8a) // Another component type
            {
                int result = FUN_0097c350(entityOffset, this + 0xB4);
                if (result != 0 && numThings < 8)
                {
                    anotherArray[numThings] = *(uint*)(result + 0xC);
                    numThings++;
                }
            }
            else if (componentHash == 0x4bbd6cc6) // Yet another
            {
                int result = FUN_0097c350(entityOffset, this + 0xC0);
                if (result != 0 && numComponents < 8)
                {
                    componentArray[numComponents] = *(uint*)(result + 0xC);
                    numComponents++;
                }
            }
        }

        // Finalize perception data
        FUN_0097d1b0(newPos, someArray, numSpecials, anotherArray, numThings, componentArray, numComponents, perceptionFloats, numFloats);
    }

    // Cleanup: memory deallocation for query buffer
    if ((int)local_2f8 >= 0)
    {
        uint size = local_2f8 & 0x3fffffff;
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(local_300, size * 0x30, 0x17);
    }

    FUN_009f0cb0(); // End of query

    // Update position
    *(float*)(this + 0xF0) = newPos[0];
    *(float*)(this + 0xF4) = newPos[1];
    *(float*)(this + 0xF8) = newPos[2];
    *(float*)(this + 0xFC) = newPos[3];
}