// FUNC_NAME: PresentationPlayer::playMovie
// Address: 0x0075aad0
// This function plays a movie (cutscene) in the EARS engine. It allocates a movie node,
// starts the movie playback, waits for completion or skip, and cleans up.

undefined1 __thiscall PresentationPlayer::playMovie(int this) {
    char resultLocal = 0;                          // local_71 - return value (1 if movie played to end)
    int movieNodeList;                             // local_70 - linked list node pointer
    int movieNodeNext;                             // local_6c - next node pointer
    int movieNodePrev;                             // local_68 - previous node pointer
    char movieNameBuffer[100];                     // local_64 - buffer for movie name/path
    int* globalMovieState;                         // piVar2 - global movie manager state
    int* allocNodeResult;                          // piVar3 - result of node allocation
    int movieHandle;                               // iVar4 - handle for movie playback
    bool isReady;                                  // cVar1 - check flags
    void* playerInstance;                          // piVar2 re-used - movie player object
    uint playerState;                              // uVar5 - state from virtual call

    globalMovieState = (int*)getGlobalMovieManager(); // FUN_007ffdf0
    // Initialize temporary node variables
    movieNodeList = 0;
    movieNodeNext = 0;
    movieNodePrev = 0;

    // Start movie playback: parameters from this+0x6c (some ID), this+0x50+0x5f0 (path?),
    // 0x40102 (message type), 0, 0 (flags)
    startMoviePlayback(*(int*)(this + 0x6c),
                       *(int*)(*(int*)(this + 0x50) + 0x5f0),
                       0x40102, 0, 0);             // FUN_009a4380

    // Build movie name/path using a global string constant DAT_00d92d14
    buildMovieName(this + 0x5c, movieNameBuffer, g_moviePathConstant); // FUN_005fcf80

    // Allocate a movie node from a pool
    allocNodeResult = (int*)allocateMovieNode();   // FUN_009a3d70

    // Insert the node into a linked list (if not already same)
    if (&movieNodeList != allocNodeResult) {
        int newMovieNode = *allocNodeResult;
        if (movieNodeList != newMovieNode) {
            // Release old node if present
            if (movieNodeList != 0) {
                releaseMovieNode(&movieNodeList);  // FUN_004daf90
            }
            movieNodeList = newMovieNode;
            if (newMovieNode != 0) {
                movieNodeNext = *(int*)(newMovieNode + 4);
                *(int**)(newMovieNode + 4) = &movieNodeList; // set next pointer to this node
            }
        }
    }
    movieNodePrev = allocNodeResult[2];           // third field of alloc result

    // If global state and node are valid, wait for movie to finish
    if (*globalMovieState != 0 && globalMovieState[2] != 0 && movieNodeList != 0 && movieNodePrev != 0) {
        // Wait for movie with timeout: 0x9000 (36.864s?) and 0x8000 (32.768s?)
        movieHandle = waitForMovie(globalMovieState, &movieNodeList, 0, 0xffffffff, 0, 0x9000, 0x8000); // FUN_005f7700
        if (movieHandle != 0) {
            isReady = checkMovieReady(0);          // FUN_005f6820
            if (isReady != '\0') {
                isReady = checkMovieSkipAllowed(); // FUN_005f67f0
                if (isReady != '\0') {
                    playerInstance = getMoviePlayer(movieHandle); // FUN_005f7be0
                    if (playerInstance != 0) {
                        // Call virtual function at vtable+8 (likely isFinished or getState)
                        // Returns >1 if movie completed or was skipped
                        uint (__fastcall *getStateFunc)() = (uint (__fastcall *)())(*(int*)playerInstance + 8);
                        playerState = getStateFunc();
                        if (playerState > 1) {
                            resultLocal = 1;
                        }
                    }
                    releaseMoviePlayer(playerInstance); // FUN_005f7d40
                }
            }
            endMoviePlayback(movieHandle);          // FUN_005f7860
        }
    }

    popMovieScope();                               // FUN_009a4440
    // Release the movie node if it was allocated
    if (movieNodeList != 0) {
        releaseMovieNode(&movieNodeList);           // FUN_004daf90
    }

    return resultLocal;
}