// FUNC_NAME: Animation::advance

void __thiscall Animation::advance(void) {
    float currentValue;
    char isPaused;
    float stepSize;
    float tempMatrix[4][4]; // 4x4 matrix on stack, constructed as uniform scale

    // Check if animation is paused via global/game state
    isPaused = isGamePaused(); // FUN_0040edb0
    stepSize = gDeltaTime; // DAT_012067e8

    if (isPaused == '\0') {
        currentValue = this->currentValue; // +0x14

        // Determine direction: move toward min/max bounds
        // +0x0c = minValue, +0x10 = maxValue
        if (currentValue < this->minValue) {
            if (currentValue <= this->maxValue) {
                this->directionFlag = 1; // +0x30: 0=decreasing, 1=increasing
            }
        } else {
            this->directionFlag = 0;
        }

        // Compute step: speed * delta * global scale
        stepSize = this->speed * stepSize * gSpeedScale; // _DAT_00d5c458

        // Update current value based on direction
        if (this->directionFlag == '\0') {
            this->currentValue = currentValue - stepSize;
        } else {
            this->currentValue = currentValue + stepSize;
        }

        // Build a uniform scaling matrix from global scale factor
        // _DAT_00d5780c is the scale value (likely 1.0f)
        buildScalingMatrix(tempMatrix, gScaleFactor);

        // Combine the scalar currentValue with output data (+0x20) into the matrix
        buildTransformFromScalar(this->currentValue, this->outputData, tempMatrix); // FUN_0056c040

        // Apply the resulting matrix (e.g., to object's world transform)
        applyTransform(tempMatrix); // FUN_00610040
    }
}