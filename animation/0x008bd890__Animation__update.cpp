//FUNC_NAME: Animation::update
void Animation::update() {
    if (this != nullptr && this->state != 7) {
        setActive(true);                     // Enable animation processing
        float elapsedTime = getElapsedTime(); // Get current time from engine
        if (this->state != 7) {
            reset();                         // Reset animation state
            setParameter(6, elapsedTime);    // Set animation progress (parameter 6 = time)
        }
    }
}