// FUNC_NAME: SimManager::processNextSimObject
void SimManager::processNextSimObject() {
    // Increment current index (0x14c)
    m_currentIndex++;

    // Yield or allow other processing
    yield();

    // Get count from container via virtual function at vtable+8
    int count = m_container->getCount();

    // If there's at least one more element after current index
    if (m_currentIndex + 1 < count) {
        if (m_container != nullptr) {
            int index = m_currentIndex;
            int countAgain = m_container->getCount();
            // If we're not at the last element and the object type is not 3, skip incrementing
            if (index < countAgain - 1 && getObjectType(index) != 3) {
                goto done;
            }
        }
        // Otherwise, advance to next and yield again
        m_currentIndex++;
        yield();
    }
done:
    // Compute sleep duration
    float sleepDuration = g_defaultSleepDuration; // DAT_00d58cbc
    float objectSpeed = m_currentObject->speed; // +0xb0 from object at +0x100
    // If global minSpeed is less than object speed, scale sleep duration
    if (g_minSpeedThreshold < objectSpeed) {
        sleepDuration = g_timeScaleFactor / objectSpeed; // DAT_00d64f1c / speed
    }
    // Sleep for the computed duration
    sleep(sleepDuration, 0, 0, 0);
}