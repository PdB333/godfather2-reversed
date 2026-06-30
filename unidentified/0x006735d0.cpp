// FUN_NAME: GraphicsDevice::createRenderSurface
// Function address: 0x006735d0
// This function initializes a render surface (likely a procedural texture or backbuffer) 
// using pseudo-random dimensions derived from RNG calls. It sets up sample count, 
// allocates a scratch buffer, and calls various subroutines for surface management.

void __thiscall GraphicsDevice::createRenderSurface(uint* outHandle, // param_1: output handle (unused, set to 0)
                                                    int param3,       // param_3: maybe a flag or format, conditionally modified
                                                    int* outParams)   // param_4: array of 4 output values (width, height, depth, something)
{
    ushort sampleCount;
    int width;
    int height;
    int temp;
    uint uVar6;
    int iVar2;
    int iVar3;
    int iVar4;
    uint uVar7;
    ushort uVar8;

    // Clear output handle
    *outHandle = 0;

    // Get pointer to surface header
    int* surfaceHeader = *(int**)(this + 0x180);

    // If sample count is not set, determine it from secondary sources or default 0x800
    if (*(short*)(surfaceHeader + 0x1c) == 0) {
        uVar8 = 0x800;
        if (*(int*)(surfaceHeader + 0x20) == 0) {
            if (*(int*)(surfaceHeader + 0x28) != 0) {
                uVar8 = *(ushort*)(*(int*)(surfaceHeader + 0x28) + 0x16);
            }
        } else {
            uVar8 = *(ushort*)(*(int*)(surfaceHeader + 0x20) + 0x10c);
        }
        *(ushort*)(surfaceHeader + 0x1c) = uVar8;
    }

    sampleCount = *(ushort*)(surfaceHeader + 0x1c);
    int* someField = outParams[2];
    *(ushort*)(this + 0x17c) = sampleCount;

    // Modify param3 based on outParams conditions
    if ((someField == 0) || (outParams[1] == 0)) {
        param3 = outParams[3];
        if (param3 < 0) {
            param3 = -param3;
        }
    } else {
        param3 = 0;
    }

    // Get random values for width and height (likely from PRNG)
    width = FUN_00676010(); // getRandomInt()
    height = FUN_00676010(); // getRandomInt()

    uVar7 = (uint)sampleCount;
    *(int*)(this + 300) = width;
    *(int*)(this + 0x130) = height;

    // Get more random values for other fields
    uint r1 = FUN_00676090(); // getRandomUint()
    *(uint*)(this + 0x134) = r1;
    uint r2 = FUN_00676090(); // getRandomUint()
    *(uint*)(this + 0x138) = r2;

    // Compute actual dimensions (round to nearest integer with 0x8000 bias)
    width = (width + 0x8000) >> 16;
    height = (height + 0x8000) >> 16;

    if ((width < 1) || (height < 1)) {
        // Invalid dimensions: reset outParams
        outParams[0] = 0;
        outParams[2] = 0;
        outParams[3] = 0;
        outParams[1] = 0;
    } else {
        // Get additional random values for outParams
        outParams[0] = FUN_00676090(); // random
        outParams[2] = FUN_00676090(); // random
        outParams[3] = FUN_00676090(); // random
        outParams[1] = FUN_00676090(); // random
    }

    // Update surface header with computed dimensions
    if (*(int*)(this + 0x180) != 0) {
        *(int*)(*(int*)(this + 0x180) + 0x70) = width;
        *(int*)(*(int*)(this + 0x180) + 0x74) = height;
    }

    // Allocate or configure surface memory
    FUN_00673490(1, width, height); // allocateSurfaceMemory

    // Configure sample count twice (maybe for multisampling)
    FUN_00675010(uVar7); // configureSampleCount
    FUN_00675010(uVar7); // configureSampleCount (again)

    // Initialize scratch buffer if not present
    if (*(int*)(this + 0x18) == 0) {
        int* surface = *(int**)(this + 0x180);
        if (*(int*)(surface + 0x20) == 0) {
            uVar6 = (uint)*(ushort*)(*(int*)(surface + 0x2c) + 8);
            if ((*(int*)(surface + 0x30) != 0) &&
                (iVar2 = *(int*)(*(int*)(surface + 0x30) + 8), iVar2 <= (int)uVar6)) {
                uVar6 = iVar2 - 1;
            }
        } else {
            uVar6 = (uint)*(short*)(*(int*)(surface + 0x20) + 0x108);
        }
        uint allocSize = FUN_00673190(uVar6); // allocateBuffer
        *(uint*)(this + 0x18) = allocSize;
    }

    // Check and clear scratch buffer if dimensions changed
    int* scratchBuffer = *(int**)(this + 0x18);
    if ((*(int*)(scratchBuffer + 4) != width) || (*(int*)(scratchBuffer + 8) != width)) {
        *(int*)(scratchBuffer + 4) = width;
        *(int*)(scratchBuffer + 8) = width;
        if (0 < (int)*(size_t*)(scratchBuffer + 0xc)) {
            memset(*(void**)(scratchBuffer + 0x10), 0, *(size_t*)(scratchBuffer + 0xc));
        }
    }

    // Use the smaller dimension for stride calculation
    if (height < width) {
        width = height;
    }

    // Clear flags
    *(uint*)(this + 100) = 0;
    *(uint*)(this + 0xa0) = 0;
    *(uint*)(this + 0x178) = 0;

    // Compute stride: (width << 6) / (sampleCount * 2)
    *(int*)(this + 0x164) = (width << 6) / (int)(uVar7 * 2);

    // Finalize surface
    FUN_00675a30(*(int*)(this + 0x180)); // finalizeSurface

    return;
}