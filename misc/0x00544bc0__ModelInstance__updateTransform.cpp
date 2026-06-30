// FUNC_NAME: ModelInstance::updateTransform
// Address: 0x00544bc0
// Updates the model's transform data using a transform provider child object.
// If the virtual 'shouldUpdate' returns true, calls a cleanup function and returns.
// Otherwise, if a model data pointer is valid, it constructs an identity-like vector,
// pushes/pops a transform stack (likely for debug), and calls set/get methods on the child.

#include <cstdint>

// External functions (likely debug or utility)
extern void FUN_0055dbd0();                      // cleanup/action
extern void FUN_009f2000();                      // push/pop matrix stack or debug marker

// Global constant (likely 1.0f for quaternion w-component)
extern const float DAT_00e2b1a4;

// 4-component vector (float)
struct Vector4f {
    float x, y, z;
    float w; // likely 1.0f for identity quaternion
};

// Child object pointed by model data at +0xd0
class TransformHandler {
public:
    // vtable offset 0x40: setTransform
    virtual void setTransform(Vector4f* transform); // __thiscall
    // vtable offset 0x44: getTransform (returns something via out pointer)
    virtual void getTransform(void* outData);       // __thiscall (output 4 bytes)
};

// Component stored at this + 0x2E8 (field at byte offset 0xBA * 4)
class ModelData {
public:
    // offset +0xd0: pointer to TransformHandler
    TransformHandler* m_transformHandler;
};

class ModelInstance {
    // Virtual table offset 0x19c: shouldUpdate
    virtual bool shouldUpdate() const; // __thiscall

public:
    // no explicit member declaration needed; the virtual calls are used on this
    void updateTransform() {
        // read pointer at byte offset 0x2E8 (0xBA * 4)
        ModelData* modelData = *reinterpret_cast<ModelData**>(reinterpret_cast<char*>(this) + 0x2E8);

        // if virtual method returns non-zero, cleanup and exit
        if (shouldUpdate()) {
            FUN_0055dbd0();
            return;
        }

        if (modelData != nullptr) {
            Vector4f identity;
            identity.x = 0.0f;
            identity.y = 0.0f;
            identity.z = 0.0f;
            identity.w = DAT_00e2b1a4; // likely 1.0f

            TransformHandler* handler = modelData->m_transformHandler;

            FUN_009f2000();                 // push/debug entry
            handler->setTransform(&identity);
            FUN_009f2000();                 // pop/debug exit

            // get something into a 4-byte temporary buffer
            char outBuffer[4];
            handler->getTransform(outBuffer);
        }
    }
};