// FUNC_NAME: Position2D::updatePosition
// Address: 0x005ce5a0
// Role: Updates a 2D position (this) towards a target position based on movement descriptor and flags.
// The movement descriptor contains a speed scale pointer and delta values.
// Flags control the mode: 0 = set target to current+delta, 2 = move current to target-delta,
// 4 = interpolate current towards target with smoothing, 8/0x10 = same for Y component.

extern float smoothingFactor; // DAT_00e2cd54

struct MovementDescriptor {
    float* speedScale; // +0x00: pointer to a structure with speed at +0x0c
    // padding/unknown fields up to +0x10
    float deltaX; // +0x10 (index 4)
    float deltaY; // +0x14 (index 5)
};

class Position2D {
public:
    float x; // +0x00
    float y; // +0x04

    // Updates position towards target based on movement descriptor and flags
    void __thiscall updatePosition(const float* target, const MovementDescriptor* movement, uint flags) {
        float scale = *(movement->speedScale + 0x3); // offset 0x0c from speedScale pointer
        float deltaX = movement->deltaX * scale;
        float deltaY = movement->deltaY * scale;

        if (flags == 0) {
            // Set target to current + delta (initialization?)
            this->x = target[0] + deltaX;
            goto updateY;
        }

        if ((flags & 4) == 0) {
            if ((flags & 2) == 0) {
                // No X movement flag, keep current X
                float currentX = this->x;
                goto setTargetX;
            }
            // Move current X to target X - delta (backwards)
            this->x = target[0] - deltaX;
        } else {
            // Interpolate current X towards target X with smoothing
            float currentX = ((target[0] - this->x) - deltaX) * smoothingFactor + this->x;
            this->x = currentX;
setTargetX:
            target[0] = currentX + deltaX;
        }

        if ((flags & 8) != 0) {
            // Move current Y to target Y - delta
            this->y = target[1] - deltaY;
            return;
        }
        if ((flags & 0x10) != 0) {
            // Interpolate current Y towards target Y with smoothing
            float currentY = ((target[1] - this->y) - deltaY) * smoothingFactor + this->y;
            this->y = currentY;
            target[1] = currentY + deltaY;
            return;
        }

updateY:
        // Default: set target Y to current Y + delta
        target[1] = this->y + deltaY;
    }
};