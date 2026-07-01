// FUNC_NAME: TimeOfDayCurve::evaluate

#include <cstdint>

// Represents a time-of-day curve with a smooth transition between two values.
// Layout (relative to this):
// +0x34: uint8_t minValue - value at the start/end of transition
// +0x35: uint8_t maxValue - value in the middle (plateau)
// +0x36: uint8_t startHour - start hour of the curve center
// +0x37: uint8_t startMinute - start minute of the curve center
// +0x38: uint8_t endHour - end hour of the curve center
// +0x39: uint8_t endMinute - end minute of the curve center
// +0x3a: uint8_t transitionWidthMinutes - total width of transition in minutes
class TimeOfDayCurve {
public:
    uint8_t minValue;               // +0x34
    uint8_t maxValue;               // +0x35
    uint8_t startHour;              // +0x36
    uint8_t startMinute;            // +0x37
    uint8_t endHour;                // +0x38
    uint8_t endMinute;              // +0x39
    uint8_t transitionWidthMinutes; // +0x3a

    // Evaluates the curve at the current game time.
    // Returns the interpolated (or plateau) value as a float.
    float evaluate() const
    {
        // Global flag to enable time-of-day logic (checked externally)
        if (DAT_0112a53c == 0) {
            return 0.0f;
        }

        // Get current time of day (fills a struct with hour/minute)
        struct TimeOfDay {
            uint8_t minute; // +0x00
            uint8_t hour;   // +0x04? Actually the functions expects a 8-byte buffer
            // But we only use hour and minute; the decompiler suggests local_14[8] and then local_c=hour, local_8=minute
        } currentTime;
        getCurrentTimeOfDay(&currentTime); // FUN_00826540

        // Compute current time in minutes from midnight
        uint16_t currentMinutes = (uint16_t)(currentTime.hour * 60 + currentTime.minute);

        // Compute start and end times of the curve (center points)
        uint16_t startMinutes = (uint16_t)(startHour * 60 + startMinute);
        uint16_t endMinutes = (uint16_t)(endHour * 60 + endMinute);
        uint8_t halfWidth = transitionWidthMinutes >> 1;

        // Check if current time is within overall range [start - halfWidth, end + halfWidth]
        uint16_t lowerBound = startMinutes - halfWidth; // might wrap, but game likely handles modulo
        uint16_t upperBound = endMinutes + halfWidth;
        if (currentMinutes < lowerBound || currentMinutes >= upperBound) {
            // Outside range -> return minimum value
            return (float)minValue;
        }

        // Check if we are in the plateau region (between start+half and end-half)
        if (currentMinutes <= endMinutes - halfWidth && startMinutes + halfWidth <= currentMinutes) {
            return (float)maxValue;
        }

        // Rising edge (early part): interpolate from min to max
        if (currentMinutes <= startMinutes + halfWidth) {
            // Note: currentMinutes - startMinutes + halfWidth => distance from lower bound
            float t = (float)(currentMinutes - startMinutes + halfWidth) / (float)transitionWidthMinutes;
            return (float)minValue + t * (float)(maxValue - minValue);
        }

        // Falling edge (late part): interpolate from max back to min
        {
            float t = (float)(currentMinutes - endMinutes + halfWidth) / (float)transitionWidthMinutes;
            // For falling edge, direction is reversed: start at max, go to min
            return (float)maxValue - t * (float)(maxValue - minValue);
        }
    }
};