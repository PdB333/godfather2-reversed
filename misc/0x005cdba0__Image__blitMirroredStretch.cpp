// FUNC_NAME: Image::blitMirroredStretch
// Address: 0x005cdba0
// This function performs a mirrored and stretched blit from source image to destination image.
// It handles horizontal mirroring and vertical scaling by copying rows and then interpolating columns.

// Assumed structure for an image:
struct Image {
    int* data;      // +0x00: pixel data (ARGB?)
    int width;      // +0x04: width in pixels
    int height;     // +0x08: height in pixels
    int stride;     // +0x0C: bytes per row (may include padding)
};

// External low-level pixel copy functions (defined elsewhere)
void copyLine(int* src, int* dst, int step, int scale);   // copies one row with step (1 or -1) and scaling factor
void copyColumn(int srcStride, int dstStride, int height); // interpolates/combines columns vertically

void __thiscall Image::blitMirroredStretch(Image* this, Image* dst) {
    float factor = DAT_00e44698;                     // some constant factor from data
    float scale = DAT_00e2b1a4;                      // scaling factor
    FUN_00b9af10();                                  // likely a setup (e.g., multiply)

    int iVar3 = (int)((scale - (float)factor) * DAT_00e44690);  // final scaling parameter

    // First: copy rows with horizontal mirroring
    uint row = 0;
    if (this->height != 0) {
        do {
            // Copy forward row
            copyLine(this->data + this->stride * row,
                     dst->data + dst->stride * row,
                     1, iVar3);
            // Copy backward row (mirrored)
            copyLine(this->data + this->stride * row + this->width - 1,
                     dst->data + dst->stride * row + dst->width - 1,
                     -1, iVar3);
            row++;
        } while (row < (uint)this->height);
    }

    // Second: vertical column interpolation (stretch)
    int rows = this->height;        // number of source rows
    int srcStride = this->stride;
    int dstStride = dst->stride;

    if ((this->width & 0xFFFFFFFC) != 0) {          // if width is multiple of 4
        int numBlocks = ((this->width & 0xFFFFFFFC) - 1) / 4 + 1;  // number of 4-pixel blocks
        do {
            copyColumn(srcStride, dstStride, rows - 1);
            copyColumn(-srcStride, -dstStride, rows - 1);
            numBlocks--;
        } while (numBlocks != 0);
    }

    return;
}