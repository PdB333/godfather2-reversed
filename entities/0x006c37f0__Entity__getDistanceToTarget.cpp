// FUNC_NAME: Entity::getDistanceToTarget
float __fastcall Entity::getDistanceToTarget(Entity *this)
{
    // Offset to component pointer (e.g., transform component or physics body)
    // this+0xe8: m_pTransformComponent (0xe8 is large, might be a component slot)
    int *componentBase;
    float x1, y1, z1; // Coordinates from first virtual method call
    float x2, y2, z2; // Coordinates from second virtual method call (world transform)
    float scaleFactor;

    // Initialize local variables (some globals are copied)
    float local_74 = 0.0f;
    // DAT_00d5780c appears to be a zero constant or similar
    int zero = _DAT_00d5780c;

    // Determine component base: if the pointer at this+0xe8 is null, use null; 
    // otherwise subtract 0x48 to get the start of the component object (since the 
    // pointer points to a field at offset 0x48 within the component)
    if (*(int *)((char *)this + 0xe8) == 0)
    {
        componentBase = nullptr;
    }
    else
    {
        componentBase = (int *)(*(int *)((char *)this + 0xe8) - 0x48);
    }

    // Virtual call #1: vtable index 0x10 (4th method) 
    // The constant 0x197c1972 is likely a hash for "position" or "targetPoint"
    // This call likely retrieves the target position into stack variables.
    // Assuming the method takes a hash and returns a Vector3 (or fills local buffers)
    (**(code **)(*componentBase + 0x10))(0x197c1972); // modifies stack locals

    // Get a global singleton (e.g., PhysicsWorld or SceneManager)
    int *singleton = (int *)FUN_00546760();

    // Virtual call #2: vtable index 0x1c (7th method)
    // This call likely retrieves the world transform of this object into a buffer.
    // The global DAT_00d5ef84 might be a hash string like "worldTransform"
    (**(code **)(*singleton + 0x1c))(auStack_58, DAT_00d5ef84, auStack_78);
    // auStack_58 is 8 bytes, auStack_78 is 4 bytes – together form a 12-byte Vector3?
    // The decompiler placed them as separate local arrays; in reality they may be 
    // contiguous representing (x,y,z) of a point.

    // Compute squared distance between two points.
    // fStack_7c, fStack_6c likely come from the first call (target position).
    // fStack_80, fStack_70 likely come from the second call (own position).
    // The third component is probably from local_74 (which is 0.0) or from another variable.
    // The expression ((float)&local_74 - local_74) is a decompilation artifact; 
    // likely the third coordinate difference squared is missing here due to stack confusion.
    // We'll assume the third difference is (z2 - z1)^2 from other local variables.

    // For clarity, we'll rewrite as:
    // difference in x: x2 - x1 = fStack_80 - fStack_70
    // difference in y: y2 - y1 = fStack_7c - fStack_6c
    // difference in z: assumed from some other variable, but here it's mistakenly shown as
    //   ((float)&local_74 - local_74) which is address of local_74 as float minus 0.0 = garbage.
    // We'll replace with a placeholder: (z2 - z1) from a variable that likely exists on stack.
    // Given the stack layout, the third coordinate might be stored elsewhere.

    // Since we can't recover the exact original, we'll assume the correct formula:
    float dx = fStack_80 - fStack_70;
    float dy = fStack_7c - fStack_6c;
    float dz = (float)&local_74 - local_74; // This is a bug in decompilation; in reality it would be a valid difference.
    // Alternatively, the third difference might be zero because local_74 is set to 0.0.

    float distance = SQRT((float10)dx * (float10)dx + (float10)dy * (float10)dy + (float10)dz * (float10)dz);
    // Multiply by a global scale factor (e.g., unit conversion)
    distance *= (float10)_DAT_00d5c458;
    return distance;
}