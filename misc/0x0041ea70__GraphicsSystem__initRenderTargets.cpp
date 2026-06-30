// FUNC_NAME: GraphicsSystem::initRenderTargets

// Function address: 0x0041ea70
// Initializes 3x3 RGBA textures, a 32x32 border texture, a 1x1 depth texture,
// and registers a material/shader pair in the global render list.
void GraphicsSystem::initRenderTargets(void)
{
    // Constants from globals (likely D3DCOLOR values)
    uint fillColor1 = DAT_00e2b1a4;  // +0x00e2b1a4
    uint fillColor2 = DAT_00e4494c;  // +0x00e4494c
    uint fillColor3 = DAT_00e4474c;  // +0x00e4474c

    // Zero out flags/state
    DAT_01205368 = 0;   // Texture handle for 32x32
    DAT_01205370 = 0;   // +0x01205370
    _DAT_01205374 = 0;  // +0x01205374
    DAT_01205359 = 0;   // +0x01205359
    DAT_0120535a = 0;   // +0x0120535a
    DAT_0120535b = 0;   // +0x0120535b
    DAT_0120537c = 0;   // +0x0120537c

    // Initialize a 3x3 grid of render target data (array at 0x01163670)
    // Each element is 0x84 bytes, structure has offsets: -0x20 (8 dwords) + 0x70 + 4 + ...
    // Likely each tile is a separate target or a mip level.
    RenderTileBlock* tileBlock = (RenderTileBlock*)&DAT_01163670; // +0x01163670
    for (int tileX = 0; tileX < 3; tileX++)
    {
        for (int tileY = 0; tileY < 3; tileY++)
        {
            // Fill 8 dwords starting at offset -0x20 within each tile struct
            uint* tileData = (uint*)tileBlock + tileX * 3 + tileY; // simplified offset?
            // Actually per-loop: puVar3 starts at base, increments by 0x10 each inner iteration
            // and each outer iteration adds 0x84 to base. We'll reconstruct logic:

            // Write fill constants to 8 consecutive dwords at specific offsets
            tileData[-8] = fillColor1;    // +0x?? (offset -0x20)
            tileData[-7] = 0;             // +0x?? 
            tileData[-6] = 0;
            tileData[-5] = 0;
            tileData[-4] = 0;
            tileData[-3] = fillColor1;    // +0x?? 
            tileData[-2] = 0;
            tileData[-1] = 0;
            tileData[0]  = 0;
            tileData[1]  = 0;
            tileData[2]  = fillColor1;    // +0x??
            tileData[3]  = 0;
            tileData[4]  = 0;
            tileData[5]  = 0;
            tileData[6]  = 0;
            tileData[7]  = fillColor1;    // +0x1C

            // Write extra constants at +0x70 and +0x74 (offsets from tile)
            uint* extra = tileData + 0x1C; // approximate, actual offsets from decompiler
            extra[5] = 0;                // +0x70
            extra[0] = 0;                // +0x70? unclear, likely two separate writes
        }
        // After each row, set more data at +0x1D8 (e.g., +0x76*4 from base)
        tileBlock[0x76] = 0;
        tileBlock[0x77] = fillColor2;
        tileBlock[0x78] = fillColor3;
        tileBlock = (RenderTileBlock*)((char*)tileBlock + 0x84);
    }
    DAT_01205378 = 0; // +0x01205378

    // Create the 32x32 texture
    uint texture32 = createTexture(8, 0x300080, 32, 32, 1, 0xffffffff); // 0x300080: format, 32x32, 1 mip
    DAT_01205368 = texture32;

    // Lock the texture surface and fill a 32x32 grid with border (black) and interior (white)
    Surface surface;
    int result = lockTexture(texture32, 2, 0, &surface); // 2: mip level, 0: flags?
    if (result != 0)
    {
        byte* pixels = (byte*)surface.pixels;
        int pitch = surface.pitch;
        for (int y = 0; y < 32; y++)
        {
            for (int x = 0; x < 32; x++)
            {
                // Set border pixels (column 0, column 31, row 0, row 31) to 0 (black)
                // All other pixels to 0xFF (white)
                if (x == 0 || x == 31 || y == 0 || y == 31)
                    pixels[y * pitch + x] = 0;
                else
                    pixels[y * pitch + x] = 0xFF;
            }
        }
        unlockTexture(&surface);
    }

    // Create a 1x1 texture with format 0x410080, 1 mip, and get its handle
    uint texture1 = createTexture(8, 0x410080, 1, 1, 1, 0xffffffff);
    int handle = getTextureHandle(texture1, 1); // Returns handle or -1
    if (handle == -1)
    {
        releaseTexture(texture1, 0);
        texture1 = 0xffffffff;
    }
    DAT_0120536c = texture1; // Store the handle

    // Create another texture (type 3) with size from globals
    DAT_0120535c = createTexture(3, 0x210098, DAT_0120587c, DAT_01205880, 1, 0xffffffff); // width/height from globals

    // Register a new entry in the global render material list (at 0x01222330)
    // Each entry is 12 bytes: two function pointers (0x41e6e0, 0x41e710) and a byte (0x80)
    // The list has a maximum of 32 entries and ensures first byte <= 0x80
    if (DAT_012224a8 != 0)
    {
        byte* listEntries = &DAT_01222330;
        for (uint i = 0; i < DAT_012224a8; i++)
        {
            if (listEntries[i * 12] > 0x80) // First byte of each entry
            {
                logError(); // FUN_00609bf0
                return;
            }
        }
    }
    if (DAT_012224a8 < 32)
    {
        int index = DAT_012224a8;
        // Write first 8 bytes: two function pointers (packed as little-endian)
        *(uint64*)(&DAT_01222328 + index * 8) = 0x41e7100041e6e0; // Actually 0x41e6e0 and 0x41e710
        // Write next 4 bytes: 0x80 (depth or priority?)
        *(uint32*)(&DAT_01222330 + index * 12) = 0x80; // Actually at offset index*12, but the base is different? We adjust.
        DAT_012224a8++;
    }
    return;
}