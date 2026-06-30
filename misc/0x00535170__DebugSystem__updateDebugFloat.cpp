// FUNC_NAME: DebugSystem::updateDebugFloat
// Address: 0x00535170 - Updates a debug float value and conditionally resets the transform of a debug object.

extern float g_debugFloat;                 // 0x01219b34
extern void* g_pDebugSingleton;            // 0x012058e8
extern void* g_debugSingletonInstance;     // 0x01219a70
extern int g_debugObjectIndex;             // 0x01219b20
struct DebugObjectInfo { void* pointer; }; // first field at offset 0x00, structure size 0x30
extern DebugObjectInfo* g_debugObjectArray; // 0x01219cc8
extern void* g_debugWorld;                 // 0x01219a80

void debugSetObjectTransform(void* world, void* object, float vec[4]); // 0x0060add0

void updateDebugFloat(float value)
{
    g_debugFloat = value;

    // Check if debug system is initialized and the indexed debug object is valid
    if (g_pDebugSingleton == &g_debugSingletonInstance)
    {
        DebugObjectInfo* obj = &g_debugObjectArray[g_debugObjectIndex];
        if (obj->pointer != (void*)0)
        {
            float zeroVec[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; // quaternion or position reset
            debugSetObjectTransform(g_debugWorld, obj->pointer, zeroVec);
        }
    }
}