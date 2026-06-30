// FUNC_NAME: Texture::reallocate
// Address: 0x005db5c0
// Re-allocates a texture/surface with new dimensions, bits per pixel.
// Uses global render width/height (DAT_012056b4, DAT_012056b8) if current size mismatch.
// Allocates pixel buffer and associates a GPU resource via FUN_00606c80.
// Assigns unique IDs using global counter (DAT_0103ae2c).

void __thiscall Texture::reallocate(int bitsPerPixel)
{
    int width, height;
    char* allocResult;
    uint pixelBufferSize;
    int gpuResourceHandle;
    int* idPtr;

    width = DAT_012056b8; // global width
    // Check globals are valid and either no current texture or dimensions mismatch
    if ((DAT_012056b4 != 0) && (DAT_012056b8 != 0) &&
       ((this->textureFlags == 0) ||
        ((this->allocatedWidth != DAT_012056b4 || (this->allocatedHeight != DAT_012056b8)))))
    {
        // Update dimensions
        this->allocatedWidth = DAT_012056b4;
        this->allocatedHeight = DAT_012056b8;

        // Free old pixel buffer if exists
        if (this->pixelBuffer != 0) {
            (DAT_0119caf4)(this->pixelBuffer); // free function
        }

        // Calculate new pixel buffer size: width * height * bitsPerPixel / 8
        pixelBufferSize = (this->allocatedHeight * this->allocatedWidth * bitsPerPixel) >> 3;
        this->pixelBufferSize = pixelBufferSize;

        // Allocate new pixel buffer (calloc-like: DAT_0119caf0(size, 0))
        allocResult = (char*)(DAT_0119caf0)(pixelBufferSize, 0);
        this->pixelBuffer = allocResult;

        // Assign unique IDs (increment global counter for each)
        if (this->id1 == 0) {
            DAT_0103ae2c++; // global counter
            this->id1 = DAT_0103ae2c;
        }
        this->gpuId = 0; // reset GPU handle ID? or some slot index

        if (this->id2 == 0) {
            DAT_0103ae2c++;
            this->id2 = DAT_0103ae2c;
        }

        if (this->textureFlags == 0) {
            DAT_0103ae2c++;
            this->textureFlags = DAT_0103ae2c;
        }

        // Create GPU resource (texture) via engine call
        // FUN_00606c80 returns a handle; parameters: 9 (maybe format), 0x200000 (flags), width, height, 1 (mipmaps?), -1 (??)
        gpuResourceHandle = FUN_00606c80(9, 0x200000, this->allocatedWidth, this->allocatedHeight, 1, 0xffffffff);

        // Store resource info in a global debug/state buffer at DAT_01206880+0x14
        // The buffer seems to be a growing array of structures (vtable pointer + three ints)
        idPtr = (int*)(DAT_01206880 + 0x14);
        *((int*)idPtr) = &PTR_LAB_011273a4; // vtable pointer for resource tracker
        idPtr++;
        *idPtr = this->id2;
        idPtr++;
        *idPtr = this->textureFlags;
        idPtr++;
        *idPtr = gpuResourceHandle;
        // The buffer's internal pointer is advanced by 4 ints
        // (The original code uses pointer arithmetic on *piVar6)
    }
}