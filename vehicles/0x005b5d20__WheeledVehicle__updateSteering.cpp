// FUNC_NAME: WheeledVehicle::updateSteering
void WheeledVehicle::updateSteering() {
    // +0x50 : pointer to allocated steering state struct (0x30 bytes)
    if (*(int*)(this + 0x50) == 0) {
        // Allocate and zero the steering state
        SteeringState* state = (SteeringState*)g_allocFunc(0x30);
        if (state != nullptr) {
            memset(state, 0, 0x30);
        }
        *(SteeringState**)(this + 0x50) = state;

        // Copy initial data from vehicle orientation/velocity
        // +0x48, +0x4C : some vector components
        state->field_0 = *(float*)(this + 0x48);
        state->field_4 = *(float*)(this + 0x4C);

        // Compute heading angle from forward vector (x,z)
        // +0x38 = forward.x, +0x3C = forward.z
        float forwardAngle = atan2f(*(float*)(this + 0x3C), *(float*)(this + 0x38));

        // Compute lateral angle from right/up? Actually uses up vector? 
        // +0x44 = up.z, +0x40 = up.y? With negative sign.
        float lateralAngle = atan2f(-*(float*)(this + 0x40), *(float*)(this + 0x44));

        // Normalize lateralAngle to [-PI, PI]
        float normalizedLateral = lateralAngle;
        const float PI = 3.141592653589793f;
        const float TWO_PI = 6.283185307179586f;
        if (normalizedLateral >= PI) {
            normalizedLateral -= TWO_PI;
        }
        if (normalizedLateral < -PI) {
            normalizedLateral += TWO_PI;
        }

        // Blend the two angles (DAT_00e2cd54 is a weight factor)
        float blendedAngle = normalizedLateral * DAT_00e2cd54 + forwardAngle;

        // Check if blended angle exceeds steering limits
        // DAT_00e2e084 = maxSteeringAngle, DAT_0103b23c = minSteeringAngle
        if (blendedAngle > DAT_00e2e084 || blendedAngle < DAT_0103b23c) {
            // Large correction needed: use angular feedback
            state->field_18 = blendedAngle * DAT_00e44748; // angular velocity scaling

            float sinBlended = sinf(blendedAngle);
            float cosBlended = cosf(blendedAngle);

            // Condition based on which component is dominant
            if (cosBlended <= -PI || cosBlended >= PI) {
                // Use forward projection
                float invAngle = DAT_00e2b1a4 / blendedAngle;
                state->field_8 = *(float*)(this + 0x38) * invAngle * DAT_00e2b050;
                state->field_C = *(float*)(this + 0x44) * invAngle * DAT_00e2b050;
            }
            else if ((sinBlended > -PI) && (sinBlended < PI)) {
                // Use lateral projection
                float invAngle = DAT_00e2b1a4 / sinBlended;
                state->field_8 = *(float*)(this + 0x3C) * invAngle * DAT_00e2b050;
                state->field_C = *(float*)(this + 0x40) * invAngle * DAT_00e44744;
            }
            else {
                // Default fallback
                state->field_8 = DAT_00e2b050;
                state->field_C = DAT_00e2b050;
            }
        }
        else {
            // Small correction: no angular feedback
            state->field_18 = 0.0f;
            state->field_8 = *(float*)(this + 0x38) * DAT_00e2b050;
            state->field_C = *(float*)(this + 0x44) * DAT_00e2b050;
        }

        // Set remaining force/moment components from vehicle state
        state->field_1C = *(float*)(this + 0x10) * DAT_00e2b050;
        state->field_20 = *(float*)(this + 0x24) * DAT_00e44584;
        state->field_24 = *(float*)(this + 0x28) * DAT_00e44584;
        state->field_28 = *(float*)(this + 0x2C) * DAT_00e44584;
        state->field_2C = DAT_00e2b1a4; // constant scaling factor
    }
}