// FUNC_NAME: Texture::computeMipSize

#include <cstdint>

struct Texture {
    int width;      // +0x00
    int height;     // +0x04
    int extra;      // +0x08 (e.g., depth)
    char byte0x23;  // +0x23 (flags)
    bool initialized() const { return byte0x23 != 0; }
};

// Normally would be a member; assume internal helper
bool initTexture(Texture* tex);

int Texture::computeMipSize(char includeExtra) {
    if (!this->initialized()) {
        if (!initTexture(this)) {
            return 0;
        }
    }

    int w = this->width;
    int h = this->height;

    unsigned int uVar2 = (w + 0x60) * (h + 0x60);
    unsigned int uVar4 = w * h;

    int result = ((uVar2 + 0xe0 + (uVar2 >> 2) * 2 + w & 0xffffff80) +
                  ((uVar4 >> 2) + 0x80 & 0xffffff80) * 2 + (uVar4 + 0x80 & 0xffffff80)) * 3 + 0x478ffc;

    if (includeExtra != 0) {
        result += this->extra;
    }

    return result;
}