// FUNC_NAME: Transform::blend
// Reconstructed C++ function for interpolating between two Transform structures.
// param_1: pointer to destination Transform
// param_2: pointer to source Transform A
// param_3: pointer to source Transform B
// param_4: blend factor (0.0 = A, 1.0 = B)
void Transform::blend(Transform* dest, const Transform* a, const Transform* b, float t)
{
    // The Transform structure has a type byte at offset 0.
    // Type 0 = invalid/identity, Type 2 = valid with data.
    // Followed by two sub-structures:
    //   - Sub1 (8 floats) at offset 4: likely dual quaternion or combined rotation/translation?
    //   - Sub2 (4 floats) at offset 36: probably translation (vec3) + extra (e.g. scale?)
    char typeA = a->type;
    char typeB = b->type;

    if (typeA != 2) {
        // Source A is invalid
        if (typeB == 2) {
            // Only B is valid: copy B to dest
            dest->type = 2;
            // Copy first sub-structure (8 floats)
            for (int i = 0; i < 8; i++) {
                dest->sub1[i] = b->sub1[i];
            }
            // Copy second sub-structure (4 floats)
            for (int i = 0; i < 4; i++) {
                dest->sub2[i] = b->sub2[i];
            }
        } else {
            // Both invalid
            dest->type = 0;
        }
        return;
    }

    // Source A is valid
    dest->type = 2;

    if (typeB == 2) {
        // Both valid: interpolate
        // Interpolate first sub-structure using a specialized function (likely dual quaternion SLERP)
        // FUN_005781f0 is called with dest->sub1 and blend factor t.
        // It modifies dest->sub1 in place, presumably interpolating between a->sub1 and b->sub1.
        dualQuatSlerp(dest->sub1, t); // Note: actual implementation unknown; might use a->sub1 and b->sub1 internally.

        // Linearly interpolate second sub-structure (vec4) between a and b
        dest->sub2[0] = (1.0f - t) * a->sub2[0] + t * b->sub2[0];
        dest->sub2[1] = (1.0f - t) * a->sub2[1] + t * b->sub2[1];
        dest->sub2[2] = (1.0f - t) * a->sub2[2] + t * b->sub2[2];
        dest->sub2[3] = (1.0f - t) * a->sub2[3] + t * b->sub2[3];
    } else {
        // Only A is valid: copy A to dest
        for (int i = 0; i < 8; i++) {
            dest->sub1[i] = a->sub1[i];
        }
        for (int i = 0; i < 4; i++) {
            dest->sub2[i] = a->sub2[i];
        }
    }
}