// FUNC_NAME: Camera::attachToTarget
// Address: 0x00581910
// This function initializes a Camera component, links it to a target object (typically a ChaseCamera or CameraManager),
// and calls a virtual function on the target after storing pointers.

#include <cstdint>

class Camera {
public:
    // Fields (offsets relative to this):
    // +0x00: uint32_t field_0;         // set to 0
    // +0x04: uint32_t field_4;         // set to 0  
    // +0x08: uint32_t field_8;         // set to 0
    // +0x0C: void* targetHandle;       // result from createCameraTarget
    // +0x10: Camera* owner;            // pointer to parent/target camera

    // Parameter: target - the camera or object this camera should attach to (e.g., a ChaseCamera).
    void attachToTarget(Camera* target);
};

// Forward declaration of the helper function that creates a camera target handle from a zero vector.
// The exact name is unknown; we assume it returns a handle.
void* createCameraTarget(uint32_t* vec3Zero); // returns handle

void Camera::attachToTarget(Camera* target) {
    // Temporary zero vector (three uint32_t's, though logically floats)
    uint32_t localVec[3] = {0, 0, 0};

    // Create a target handle (e.g., a reference point or a camera node) from the zero vector.
    this->targetHandle = createCameraTarget(localVec);

    // Store the owner/target camera pointer.
    this->owner = target;

    // Call virtual function at vtable index 2 (offset +0x08) on the target.
    // This likely notifies the target that the camera has been attached.
    (*(void (**)())(*(uint32_t*)target + 8))();

    // Reset three fields to zero (possibly position or flags).
    this->field_0 = 0;
    this->field_4 = 0;
    this->field_8 = 0;
}