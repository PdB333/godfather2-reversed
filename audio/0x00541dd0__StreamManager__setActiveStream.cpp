// FUNC_NAME: StreamManager::setActiveStream
void __thiscall StreamManager::setActiveStream(int this, int newStream) {
    int oldStream;
    int managerObject;

    // Check if a pending update flag is set
    if ((*(byte *)(this + 0x12c) & 1) != 0) {
        FUN_00541bb0(1); // Flush or process pending updates
    }

    // Only act if the stream is actually changing
    if (newStream != *(int *)(this + 0x20c)) {
        // If there was an old active stream, shut it down
        if (*(int *)(this + 0x20c) != 0) {
            FUN_009f01a0(); // Begin cleanup transaction (e.g., acquire lock)
            managerObject = *(int *)(this + 0x210);
            // If the manager object has an active sub-object
            if (*(int *)(managerObject + 0x10) != 0) {
                FUN_009f1b20(managerObject); // Destroy or unload sub-object
                FUN_009f1ad0(managerObject + 8); // Clear associated data
                FUN_009f01a0(); // End cleanup transaction (e.g., release lock)
            }
            *(undefined4 *)(managerObject + 0x10) = 0; // Clear sub-object pointer
            // Call virtual method to notify of stream deactivation
            (**(code **)(*(int *)(this + 0x13c) + 8))(0);
        }

        // Store the new active stream
        *(int *)(this + 0x20c) = newStream;

        // If the new stream is valid, activate it
        if (newStream != 0) {
            FUN_009f0190(); // Begin activation transaction
            FUN_00542390(); // Prepare new stream data
            // Call virtual method with the new stream identifier
            (**(code **)(*(int *)(this + 0x13c) + 8))(newStream);
        }
    }
}