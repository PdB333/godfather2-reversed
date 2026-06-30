// FUNC_NAME: CameraManager::setCachedTransform
// Address: 0x0053a430
// Copies a 32-byte camera transform (two consecutive 16-byte blocks) into static cache.
// If active camera manager is valid and certain fields match, forwards the first 8 bytes to a stream.

#include <cstring>

// Globals – names inferred from decompilation
extern unsigned char gCachedTransform0[16];  // _DAT_0121b910
extern unsigned char gCachedTransform1[16];  // _DAT_0121b920
extern CameraManager* gActiveCameraManager; // DAT_012058e8 (pointer to current camera manager)
extern CameraManager gCameraManagerInstance; // DAT_0121b740 (static instance)
extern int gCameraFieldA;                    // DAT_0121b754
extern int gCameraFieldB;                    // DAT_0121bbcc
extern void* gCameraBuffer;                  // DAT_0121bb88 (target buffer for stream write)

// Forward declaration of the low-level write function
void writeToStream(int, void*, const void*, int); // FUN_0060ab00

struct Transform32 {
    unsigned char block0[16];
    unsigned char block1[16];
};

void CameraManager::setCachedTransform(const Transform32* pTransform)
{
    // Clear or copy the two 16-byte blocks
    if (pTransform == nullptr) {
        memset(gCachedTransform0, 0, sizeof(gCachedTransform0));
        memset(gCachedTransform1, 0, sizeof(gCachedTransform1));
    } else {
        memcpy(gCachedTransform0, pTransform->block0, sizeof(gCachedTransform0));
        memcpy(gCachedTransform1, pTransform->block1, sizeof(gCachedTransform1));
    }

    // Only proceed if we are the active camera manager and internal fields match
    if ((gActiveCameraManager == &gCameraManagerInstance) &&
        (gCameraFieldA == gCameraFieldB))
    {
        // Write the first 8 bytes of the cached transform to the stream buffer
        writeToStream(gCameraFieldB, gCameraBuffer, gCachedTransform0, 8);
    }
}