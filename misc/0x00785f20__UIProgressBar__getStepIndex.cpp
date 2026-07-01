//FUNC_NAME: UIProgressBar::getStepIndex
int __thiscall UIProgressBar::getStepIndex(int stepCount, float minProgress, float maxProgress, ProgressData* progressData) {
    // If no progress data provided, try to get from internal storage
    if (progressData == nullptr) {
        if (this->progressDataPtr == nullptr) {
            this->progressDataPtr = createProgressData(0);
        }
        progressData = this->progressDataPtr;
        if (progressData == nullptr) {
            return 0;
        }
    }

    // Get current progress value from the data object (offset +0x20)
    float currentProgress = progressData->currentProgress;

    // Clamp currentProgress to maxProgress if positive
    if (currentProgress > 0.0f) {
        if (currentProgress > maxProgress) {
            currentProgress = maxProgress;
        }
    } else {
        currentProgress = 0.0f;
    }

    // Compute progress relative to the range [minProgress, maxProgress]
    float progressInRange = currentProgress - minProgress;
    if (progressInRange < 0.0f) {
        progressInRange = 0.0f;
    }

    // Map to step index (0-based)
    int index = (int)((progressInRange / (maxProgress - minProgress)) * (float)stepCount);

    // If within range and index is less than stepCount, return 1-based index
    if ((minProgress <= currentProgress) && (index < stepCount)) {
        return index + 1;
    }
    return index;
}