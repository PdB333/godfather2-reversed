// FUNC_NAME: CameraManager::snapshotCameraMatrices

#include <cstdint>

// Global source matrices (current camera transforms)
// Each source is a 4x4 matrix (16 floats) stored at the given base addresses.
// These are likely updated each frame by the camera system.
static volatile uint32_t& gSourceMatrix0 = *(uint32_t*)0x011f69b0; // Base for bit 0
static volatile uint32_t& gSourceMatrix1 = *(uint32_t*)0x011f69f0; // Base for bit 1 (first set)
static volatile uint32_t& gSourceMatrix2 = *(uint32_t*)0x011f6b30; // Base for bit 1 (second set)
static volatile uint32_t& gSourceMatrix3 = *(uint32_t*)0x011f6a30; // Base for bit 2

// History buffers: each holds up to 8 matrices (0x40 bytes each = 64 bytes)
static volatile uint32_t gCameraHistory0[8][16] = *(uint32_t(*)[8][16])0x011f6c00; // 8 * 64 = 512 bytes
static uint32_t& gCameraHistory0Count = *(uint32_t*)0x011f6bf0;

static volatile uint32_t gCameraHistory1[8][16] = *(uint32_t(*)[8][16])0x011f7020;
static uint32_t& gCameraHistory1Count = *(uint32_t*)0x011f7010;

static volatile uint32_t gCameraHistory2[8][16] = *(uint32_t(*)[8][16])0x011f6e10;
static uint32_t& gCameraHistory2Count = *(uint32_t*)0x011f6e00;

static volatile uint32_t gCameraHistory3[8][16] = *(uint32_t(*)[8][16])0x011f7230;
static uint32_t& gCameraHistory3Count = *(uint32_t*)0x011f7220;

// Helper: copy 16 uint32s from src to dest
inline void copyMatrix(uint32_t* dest, const uint32_t* src) {
    for (int i = 0; i < 16; ++i) {
        dest[i] = src[i];
    }
}

void CameraManager::snapshotCameraMatrices(uint8_t flags) {
    // Bit 0: snapshot into history buffer 0 (main gameplay camera?)
    if ((flags & 1) != 0 && gCameraHistory0Count < 8) {
        uint32_t slot = gCameraHistory0Count * 16; // 16 floats per entry
        copyMatrix(&gCameraHistory0[0][slot], &gSourceMatrix0);
        gCameraHistory0Count++;
    }

    // Bit 1: snapshot into history buffers 1 and 2 (chase camera or cinematic?)
    if ((flags & 2) != 0) {
        if (gCameraHistory1Count < 8) {
            uint32_t slot = gCameraHistory1Count * 16;
            copyMatrix(&gCameraHistory1[0][slot], &gSourceMatrix1);
            gCameraHistory1Count++;
        }

        if (gCameraHistory2Count < 8) {
            uint32_t slot = gCameraHistory2Count * 16;
            copyMatrix(&gCameraHistory2[0][slot], &gSourceMatrix2);
            gCameraHistory2Count++;
        }
    }

    // Bit 2: snapshot into history buffer 3 (collision camera?)
    if ((flags & 4) != 0 && gCameraHistory3Count < 8) {
        uint32_t slot = gCameraHistory3Count * 16;
        copyMatrix(&gCameraHistory3[0][slot], &gSourceMatrix3);
        gCameraHistory3Count++;
    }
}