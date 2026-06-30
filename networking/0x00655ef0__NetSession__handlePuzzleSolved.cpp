// FUNC_NAME: NetSession::handlePuzzleSolved

// Address: 0x00655ef0
// Called after client solves the connection puzzle (likely part of Torque/EA anti-DoS handshake).
// Verifies the puzzle solution, logs the time taken, transitions state to "puzzle solved" (4),
// and triggers the next step in the handshake.

void NetSession::handlePuzzleSolved() {
    // +0x148, +0x133, +0x13b: Puzzle data buffers or challenge components
    // +0x144, +0x14c: Integer parameters (may be sizes or nonce values)
    bool solved = verifyPuzzleSolution(
        reinterpret_cast<const char*>(this + 0x148),
        reinterpret_cast<const char*>(this + 0x133),
        reinterpret_cast<const char*>(this + 0x13b),
        *reinterpret_cast<int*>(this + 0x144),
        *reinterpret_cast<int*>(this + 0x14c)
    );

    if (solved) {
        // +0x1a0: Timestamp when puzzle challenge was received
        int elapsed = getTimestampMs() - *reinterpret_cast<int*>(this + 0x1a0);
        debugPrint("Client puzzle solved in %d ms.", elapsed);

        // +0x1b4: Handshake state (4 = puzzle solved, ready for ack)
        *reinterpret_cast<int*>(this + 0x1b4) = 4;

        // Send acknowledgment to server (FUN_00655f50)
        sendPuzzleAck();
    }
}