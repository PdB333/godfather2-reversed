// FUNC_NAME: GameRefSender::sendGameRef
void GameRefSender::sendGameRef(int* gameRefIds, uint param3) {
    // Check if the game reference IDs are non-zero
    if (gameRefIds[0] != 0 || gameRefIds[1] != 0) {
        // Get the core manager singleton (e.g., GameManager)
        CoreManager* coreMgr = GameManager::getInstance(); // FUN_00ad8d40
        if (coreMgr) {
            // Get the networking or debug subsystem (vtable+0x34)
            NetworkSystem* netSys = coreMgr->getNetworkSystem();
            if (netSys) {
                // Get the sender object (vtable+0x3c)
                GameRefSender* sender = netSys->getGameRefSender(); // vtable+0x3c
                // Call a setup method (vtable+0x74) – likely initialize message
                sender->beginMessage(); // vtable+0x74
            }
        }

        // Get the global string for "gameRefSender" (likely from a string table)
        const char* strSender = GlobalStringTable::get("gameRefSender"); // FUN_004d3b00
        if (strSender == nullptr) {
            strSender = "gameRefSender"; // fallback if null
        }

        // Copy the string into local buffer (12 bytes)
        char senderBuf[12];
        char* dst = senderBuf;
        const char* src = strSender;
        char ch;
        do {
            ch = *src;
            *dst = ch;
            src++;
            dst++;
        } while (ch != '\0');

        // There was a suspicious check on an uninitialized local (likely a bug in decompilation)
        // Skipping the call to the function pointer if non-zero (seems like a leftover)

        // Same for "gameRefReceiver"
        const char* strReceiver = GlobalStringTable::get("gameRefReceiver");
        if (strReceiver == nullptr) {
            strReceiver = "gameRefReceiver";
        }
        char receiverBuf[44];
        dst = receiverBuf;
        src = strReceiver;
        do {
            ch = *src;
            *dst = ch;
            src++;
            dst++;
        } while (ch != '\0');

        // Create a message writer object (e.g., XMLWriter) – FUN_00b0bf90
        MessageWriter* writer = MessageWriter::create(); // 0x8b61b5
        // Set content type to "text/plain"
        writer->setContentType("text/plain"); // vtable+0x10 (first call)
        // Set up the message with sender and receiver and a callback pointer + length
        writer->startMessage("gameRefReceiver", &senderBuf, &callbackPtr, 12); // vtable+0x10 (second call)

        // Get the core manager again
        CoreManager* coreMgr2 = GameManager::getInstance();
        if (coreMgr2) {
            // Initialize a buffer (size 0x200)
            char buffer[0x200];
            memset(buffer, 0, 0x200); // FUN_00ae9750

            // Get the network session (vtable+0x2c)
            NetSession* session = coreMgr2->getNetSession(); // vtable+0x2c
            // Send the game reference message with writer – vtable+0xc
            session->sendGameRef(buffer, param3, gameRefIds, 1, writer, 1, 0, 2);

            // Get the session's network object (vtable+0x0)
            NetObject* obj = session->getNetObject(); // vtable+0x0
            // Send the final message (vtable+0x10)
            obj->sendMessage(&buffer, &LAB_008b5b40, uStack_3c, uStack_2c);

            // Cleanup buffer (FUN_00ae97f0)
            cleanupBuffer(buffer);
        }

        // Destroy the writer
        MessageWriter::destroy(writer); // FUN_00ad60c0
    }
}