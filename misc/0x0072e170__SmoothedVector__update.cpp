// FUNC_NAME: SmoothedVector::update

void SmoothedVector::update(float* outSmoothed) {
    // Virtual function at vtable offset 0xa4 copies the target from this+0x1b7 into a temporary
    float target[3];
    (this->vtable->getTarget)(target, reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + 0x1b7));

    float factor = gSmoothFactor; // Global time delta or smoothing factor (0x00d5c458)

    // Lerp each component towards the target
    outSmoothed[0] = (target[0] - outSmoothed[0]) * factor + outSmoothed[0];
    outSmoothed[1] = (target[1] - outSmoothed[1]) * factor + outSmoothed[1];
    outSmoothed[2] = (target[2] - outSmoothed[2]) * factor + outSmoothed[2];
}