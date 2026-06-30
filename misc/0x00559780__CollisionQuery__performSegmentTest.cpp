// FUNC_NAME: CollisionQuery::performSegmentTest
// Address: 0x00559780
// Performs a segment/ray cast against the collision world.
// The object (this) holds a function pointer for the actual query implementation.
// param_3 is a float array describing the segment (first 8 floats: start offset, end offset?).
// param_4 is additional collision flags/context.
// Returns a pointer to a byte flag (hit result) via param_2.

class CollisionQuery {
public:
    virtual void someVFunc(unsigned char* flag, float* segment, int params); // vtable+0x20

    // +0x00: vtable pointer
    // +0x20: float startOffset[4] (x,y,z,w)
    // +0x30: (0x0c*4) possibly unused? Actually param_1[0xc] not used
    // +0x34: int collisionWorldID? (param_1[0xd])
    // +0x38: int resultFlags (param_1[0xe])
    // +0x40: Code* raycastFunc (param_1[0x10])
    // +0x44: int raycastParam (param_1[0x11])

    unsigned char* performSegmentTest(unsigned char* outHit, float* segment, int collisionMask) {
        *outHit = 0;
        this->resultFlags = 0;

        Code* raycastFunc = this->raycastFunc;
        if (raycastFunc != nullptr) {
            // Build two points: start = (this->startOffset + segment[0..3]), end = (this->startOffset + segment[4..7])
            float start[4];
            start[0] = this->startOffset[0] + segment[0];
            start[1] = this->startOffset[1] + segment[1];
            start[2] = this->startOffset[2] + segment[2];
            start[3] = this->startOffset[3] + segment[3];

            float end[4];
            end[0] = this->startOffset[0] + segment[4];
            end[1] = this->startOffset[1] + segment[5];
            end[2] = this->startOffset[2] + segment[6];
            end[3] = this->startOffset[3] + segment[7];

            // Also extract segment[8] and segment[9] (unused here, passed to raycastFunc?)
            float extra0 = segment[8];
            float extra1 = segment[9];

            uint result = raycastFunc(this->collisionWorldID, start, *(int*)(collisionMask + 0x10), this->raycastParam);
            this->resultFlags = ~result; // Inverted result

            if (result == 0) {
                goto cleanup;
            }
        }

        FUN_00557e20(); // some helper (e.g., post-process or error handling)

        // Call virtual function to finalize
        unsigned char localFlag = 0;
        this->someVFunc(&localFlag, segment, collisionMask);
        *outHit = (unsigned char)((uint)someRegister >> 24); // Low byte of some register/result

    cleanup:
        this->resultFlags = 0;
        return outHit;
    }

private:
    // Fields based on param_1 offsets
    // +0x00: vtable (implicit)
    // +0x20: float startOffset[4]; // offset 0x20 (8 ints)
    // +0x30: unknown (offset 0x30, index 0xc? not used)
    // +0x34: int collisionWorldID; // offset 0x34 (0xd)
    // +0x38: int resultFlags; // offset 0x38 (0xe)
    // +0x40: Code* raycastFunc; // offset 0x40 (0x10)
    // +0x44: int raycastParam; // offset 0x44 (0x11)
};