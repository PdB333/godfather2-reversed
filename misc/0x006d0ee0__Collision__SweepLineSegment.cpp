// FUNC_NAME: Collision::SweepLineSegment
// Function address: 0x006d0ee0
// Role: Performs a swept line segment intersection test against a shape defined by global parameters.
// Returns 0 if hit (with distance out), 1 if miss.

__thiscall int Collision::SweepLineSegment(const Vector4& start, const Vector4& end, float* outDistance) {
    float fVar9;
    float local_f4;
    int   local_f0;

    // Copy input points (x,y,z,w)
    float startX = start.x;
    float startY = start.y;
    float startZ = start.z;
    float startW = start.w;
    float endX   = end.x;
    float endY   = end.y;
    float endZ   = end.z;
    float endW   = end.w;

    // Some global tolerance
    FUN_00a64b00(g_tolerance);

    // Initialize a 6-element buffer (likely for a swept sphere: point0, point1, radius? or AABB)
    float buf[6];
    buf[0] = 0.0f; buf[1] = 0.0f; buf[2] = 0.0f; buf[3] = 0.0f; buf[4] = 0.0f; // indices 0..5
    // Actually decompiled: local_e0[1-4]=0, local_e0[0]=_DAT_00d5780c, local_e0[5]=same.
    // We'll set them directly:
    float infiniteVal = g_infinite; // _DAT_00d5780c
    buf[0] = infiniteVal;
    buf[1] = 0.0f;
    buf[2] = 0.0f;
    buf[3] = 0.0f;
    buf[4] = 0.0f;
    buf[5] = infiniteVal;

    // Another float set to infinite
    float extraFloat = infiniteVal; // local_b8

    // Additional zero floats (maybe for padding)
    float zero1 = 0.0f, zero2 = 0.0f, zero3 = 0.0f, zero4 = 0.0f;

    // This pointer will point to the buffer
    float* bufPtr = buf;

    // Stack struct (44 bytes) used as a query object
    char queryStruct[44]; // local_30
    memset(queryStruct, 0, sizeof(queryStruct)); // not exactly, but decompiled shows many zeros

    // Setup query struct fields (some offsets guessed)
    // 0x00: pointer to buf (float*)
    // 0x04: int (initialized to 0)
    // 0x08: int (initialized to -1)
    // 0x0C: char (0)
    // 0x0D: char (0)
    // 0x0E: short (0)
    // 0x10: int (0)
    // 0x14: char (0)
    // 0x15: char (127)
    // 0x16: char (0)
    // ... more fields

    struct CollisionQuery {
        float* buffer;      // +0x00
        int    field4;      // +0x04
        int    field8;      // +0x08
        char   fieldC;      // +0x0C
        char   fieldD;      // +0x0D
        short  fieldE;      // +0x0E
        int    field10;     // +0x10
        char   field14;     // +0x14
        char   field15;     // +0x15 (0x7f)
        char   field16;     // +0x16
        // ... more up to 44 bytes
    };

    CollisionQuery* local_190 = (CollisionQuery*)queryStruct;
    local_190->buffer = buf;
    local_190->field4 = 0;
    local_190->field8 = -1;
    local_190->fieldC = 0;
    local_190->fieldD = 0;
    local_190->fieldE = 0;
    local_190->field10 = 0;
    local_190->field14 = 0;
    local_190->field15 = 0x7f; // 127, maybe some flag
    local_190->field16 = 0;

    // Assign input points to the query struct (offsets 0x30-0x3f?)
    // Decompiler placed them at local_b0, a4, a8, ac, and later local_140 etc.
    // But those are separate stack variables; they might be fields of the query struct.
    // Actually the decompiler shows they are stored before the call to FUN_009e7fd0.
    // Let's assign them to the query struct.
    // We'll assume the query struct extends beyond 44 bytes, or the function copies them elsewhere.
    // Since we don't know the exact layout, we'll store them in a small array.
    float startCopy[4] = {startX, startY, startZ, startW};
    float endCopy[4]   = {endX, endY, endZ, endW};

    // Some setup function
    FUN_00a64fd0();

    // Set field15 to the offset between some addresses (likely size of part of struct)
    local_190->field15 = (char)(&local_190->field8 - (char*)local_190); // +0x0D? Actually decompiled: local_177 = &local_190 - &local_17c. But local_17c is a local variable.
    // This is messy; we'll ignore for simplicity.

    // More global constants
    float someConst = DAT_00d5ccf8; // local_148
    local_190->fieldD = 0;
    local_190->fieldE = 0;

    // Allocate or get an object (maybe a shape)
    local_190->field10 = FUN_00540c60(0xC, 0x17, 0); // returns something

    // Some more global floats
    float globalA = DAT_00e44598; // local_130, local_12c
    float globalB = DAT_00e445dc; // local_f4, local_11c

    // Setup pointers for collision query
    // There is a pointer to a vtable? PTR_LAB_00dc471c -> local_120
    // We'll assume it's a function table or shape descriptor
    void* shapeVTable = (void*)PTR_LAB_00dc471c; // local_120

    // These are probably passed to the collision function
    local_f0 = 0;
    local_f4 = globalB;

    // Actually local_f4 and local_11c are separate; we'll set them as locals
    float local_f4 = globalB;
    float local_11c = globalB;

    // Store start and end points into the query struct (or somewhere)
    // The decompiler shows them at offsets from local_140 etc.
    // We'll assume they are part of a local struct that gets passed.
    // For now, just keep them in local variables.
    // local_140 = endX, etc. but we already have them.

    // The main collision query call
    // It expects pointers to the query struct, start/end points, and a vtable.
    FUN_009e7fd0(&local_190, &startCopy, &shapeVTable, &shapeVTable);
    // Note: arguments are pointers

    // Check result
    if (local_f0 == 0) {
        // No hit
        if (outDistance == NULL) {
            return 1; // miss
        }
        // else fall through to set large distance? Actually decompiled fall through
    }
    else {
        if (local_f4 >= 0.0f) {
            // Hit with positive distance
            if (outDistance != NULL) {
                *outDistance = local_f4;
            }
            return 0; // hit
        }
        // Negative distance: shape is inside start? Do additional check
        if (outDistance == NULL) {
            // Check if the line direction is pointing out of the shape
            fVar9 = FUN_006d0200(&start, &end); // might compute dot product of segment with something
            // Compare with tolerance
            if ( -g_tolerance < fVar9 * local_f4 ) {
                return 1; // miss
            }
            else {
                return 0; // hit
            }
        }
    }

    // Fallback: set distance to infinity and return miss
    if (outDistance != NULL) {
        *outDistance = g_infinite;
    }
    return 1;
}