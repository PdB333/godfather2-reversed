// FUNC_NAME: PhysicsUtil::sphereVsSphereSweep
// Address: 0x0084c940
// Role: Swept sphere vs sphere collision test. Returns 1 if collision detected,
//       and writes the collision fraction (0 <= t <= 1) to param_7.
// Parameters:
//   param_1 - start position of moving sphere? (but used as part of direction vector)
//   param_2 - end position of moving sphere? (reverse?)
//   param_3 - start position of static sphere?
//   param_4 - end position of static sphere?
//   param_5 - radius of first sphere
//   param_6 - radius of second sphere
//   param_7 - output collision fraction
// Note: The math appears to solve a quadratic for the fraction t such that
//   |(param_1-param_2) + t*(param_3-param_4)| = (param_5+param_6)
//   but with the dot product of the two direction vectors. This is consistent with
//   a relative velocity approach if the spheres have equal but opposite velocities? 
//   Possibly a simplified test for line segments.

// Globals (likely constants)
extern float DAT_00e44564; // ≈ 0.0f
extern float DAT_00e44598; // ≈ 1e-6f (epsilon)

int sphereVsSphereSweep(float *p1, float *p2, float *p3, float *p4,
                        float r1, float r2, float *resultFraction)
{
    // Difference vectors (direction of motion for each pair?)
    float dx1 = p1[0] - p2[0];
    float dy1 = p1[1] - p2[1];
    float dz1 = p1[2] - p2[2];

    float dx2 = p3[0] - p4[0];
    float dy2 = p3[1] - p4[1];
    float dz2 = p3[2] - p4[2];

    // Squared lengths
    float len2_2 = dy2*dy2 + dx2*dx2 + dz2*dz2;
    float len2_1 = dy1*dy1 + dx1*dx1 + dz1*dz1;

    // Squared sum of radii
    float sumRadii2 = (r1 + r2) * (r1 + r2);

    // If second vector is not degenerate (length^2 > epsilon)
    if (DAT_00e44598 <= len2_2) {
        // Dot product of the two direction vectors
        float dotVal = dx1*dx2 + dy1*dy2 + dz1*dz2;

        // Discriminant: (dot)^2 - (len2_1 - sumRadii2) * len2_2
        float disc = dotVal*dotVal - (len2_1 - sumRadii2) * len2_2;

        if (0.0f <= disc) {
            // Compute t values ( minus dot +/- sqrt(disc) ) / len2_2
            float t = DAT_00e44564 - dotVal;  // Negate dot if DAT_00e44564 is 0

            float t1, t2;
            if (DAT_00e44598 < disc) {
                float sqrtDisc = sqrtf(disc);
                t2 = t + sqrtDisc;   // plus
                t1 = t - sqrtDisc;   // minus
            } else {
                t1 = t;
                t2 = t;  // discriminant zero, single root
            }

            // Choose earliest positive collision
            if (0.0f <= t2) {
                if (t1 <= 0.0f) {
                    *resultFraction = 0.0f;
                } else {
                    *resultFraction = t1 / len2_2;
                }
                return 1;  // collision
            }
        }
    }
    else {
        // If second direction is degenerate (point-like), check if first vector length <= sum radii
        if (len2_1 <= sumRadii2) {
            *resultFraction = 0.0f;
            return 1;
        }
    }

    return 0;  // no collision
}