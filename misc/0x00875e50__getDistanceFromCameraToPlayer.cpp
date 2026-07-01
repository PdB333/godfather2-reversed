// FUNC_NAME: getDistanceFromCameraToPlayer
// Function at 0x00875e50 - Computes the Euclidean distance from the camera to the player's world position.
// Uses a singleton player getter, a camera singleton getter, and a vector transform (by the camera's view matrix).

#include <cmath>

struct Vector3 {
    float x, y, z;
};

struct Matrix {
    float data[4][4]; // assuming 4x4
};

// These are placeholders for the actual extern functions from the game binary.
// FUN_005466b0: Likely returns a pointer to the Player object (0 if invalid).
extern void* __cdecl getPlayerSingleton();
// FUN_00471610: Likely returns a pointer to the Camera object.
extern void* __cdecl getCameraSingleton();
// FUN_004a07f0: Transforms a vector by a matrix: out = matrix * in (possibly homogeneous?).
extern void __cdecl transformVector(Vector3* out, const Vector3* in, const Matrix* mat);

float __cdecl getDistanceFromCameraToPlayer() {
    float distance = 0.0f;
    void* playerCheck = getPlayerSingleton();
    if (playerCheck != nullptr) {
        void* playerPtr = getPlayerSingleton(); // second call – same function, gets the player pointer again
        // Read player's world position at offset 0x1A0 (three floats).
        Vector3 playerPos = *reinterpret_cast<Vector3*>(static_cast<char*>(playerPtr) + 0x1A0);

        void* cameraPtr = getCameraSingleton();
        if (cameraPtr != nullptr) {
            // Camera's view matrix is at offset 0x10.
            Matrix* viewMatrix = reinterpret_cast<Matrix*>(static_cast<char*>(cameraPtr) + 0x10);

            Vector3 transformed;
            transformVector(&transformed, &playerPos, viewMatrix);

            // Compute the length of the transformed vector, which is the distance from the camera.
            distance = std::sqrt(transformed.x * transformed.x + transformed.y * transformed.y + transformed.z * transformed.z);
        }
    }
    return distance;
}