// FUNC_NAME: BlendController::updateBlend
void __thiscall BlendController::updateBlend() {
    // Check pause flag (bit 5 of flags field at +0xC8)
    if ((*(byte*)(this + 0x32) >> 5 & 1) == 0) {
        // Virtual call to update (vtable+0x4c) with global delta time
        (this->vtable[0x4c/4])(g_deltaTime);

        // Check if blend is active? (returns 1 if active)
        if (isBlendActive()) {
            notifyBlendFinished();
        }

        float targetDuration = reinterpret_cast<float&>(this->field_0xA4);
        float currentTime = reinterpret_cast<float&>(this->field_0xA8);

        // Advance current time if not yet reached target
        if (currentTime < targetDuration) {
            float newTime = currentTime + g_deltaTime;
            this->field_0xA8 = reinterpret_cast<int&>(newTime);
            if (targetDuration < newTime) {
                this->field_0xA8 = reinterpret_cast<int&>(targetDuration);
            }

            // Compute interpolation factor (0..1)
            float t = reinterpret_cast<float&>(this->field_0xA8) / targetDuration;
            float oneMinusT = 1.0f - t;

            // Interpolate start/end values for two axes
            this->field_0x8C = reinterpret_cast<float&>(this->field_0x94) * oneMinusT +
                               reinterpret_cast<float&>(this->field_0x98) * t;
            this->field_0x90 = reinterpret_cast<float&>(this->field_0x9C) * oneMinusT +
                               reinterpret_cast<float&>(this->field_0xA0) * t;
        }
    }
}