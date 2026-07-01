// FUNC_NAME: Vehicle::updateState
// Function address: 0x007a9da0
// This appears to be an update function for a vehicle object (likely WheeledVehicle or BaseVehicle).
// It handles state transitions (on ground/air), engine audio, physics body synchronization, and debug overlays.

void __thiscall Vehicle::updateState(void* param2, void* param3)
{
    byte debugActive;
    bool bVar1;
    int gameTimePtr;
    float speed;
    float fVar1, fVar2;
    float velocityX, velocityY, velocityZ;

    // Check debug mode or global flag (e.g., DAT_01129948 + 0x4c bit 5)
    debugActive = isDebugModeActive(); // FUN_00842870
    if ((debugActive != 0) || ((*(uint *)(DAT_01129948 + 0x4c) >> 5 & 1) != 0)) {
        this->flags_928 |= 0x10;                 // +0x928
        this->flags_929 |= 0x200;                // +0x929
        this->someGlobal = DAT_01205228;         // +0xc44
    }

    gameTimePtr = getGameTimeManager(); // FUN_00471610
    // Compare time to threshold (DAT_00d6a5c4) - maybe trigger a timed event
    if (*(float *)(gameTimePtr + 0x34) <= DAT_00d6a5c4 && DAT_00d6a5c4 != *(float *)(gameTimePtr + 0x34)) {
        // Call virtual function at +0x288 (e.g., onTimeEvent)
        (this->vtable->timeEvent)(1, this, 0);
    }

    this->flags_927 &= 0xfffeffff;               // +0x927 clear bit 16

    updateAudioContext(param3); // FUN_008978a0

    // Check cinematic state
    if (isCinematicPlaying() != '\0') { // FUN_00481620
        return; // early exit? Actually code continues, but careful: the decompiled shows if cinematic then skip else branch.
    }

    // Actually the decompiled shows: if not cinematic, then check pause state.
    if (isPauseMenuActive() != '\0') { // FUN_00481640
        bVar1 = this->vtable->isLoading(); // +0x28c
        if (bVar1 == 0) {
            this->flags_929 &= 0xfffffffe; // +0x929 clear bit 0 (subtitle off)
        } else {
            this->flags_929 |= 1;          // +0x929 set bit 0 (subtitle on)
        }
    } else {
        // Not paused, handle dialog state
        updateDialogSystem();            // FUN_0079e420
        updateHUD();                     // FUN_007a4e10

        if (isDebugCameraActive() != '\0') { // FUN_008a4380
            // Enable debug overlay: grab bit0 from object at +0x17d offset
            bool overlayBit = *(byte *)(this->somePtr17d + 0x18) & 1;
            setDebugOverlayVisibility(overlayBit); // FUN_0094da30
        }

        // Check subtitle visibility change
        byte showSubs = this->flags_929; // +0x929
        bool isSubRequired = this->vtable->isLoading(); // +0x28c
        if ((showSubs & 1) != (byte)isSubRequired) {
            if (isSubRequired == 0) {
                this->flags_929 &= 0xfffffffe; // hide subtitles
                setSubtitlesEnabled(0);        // FUN_00433c10
                // Set color for subtitles (maybe white)
                velocityX = DAT_0112b394;
                velocityY = 0.0f;
                velocityZ = (float)((uint)velocityZ & 0xffffff00); // clear fractional
                setAudioState(&velocityX, 0); // FUN_00408a00 (pass color and channel)
            } else {
                this->flags_929 |= 1;          // show subtitles
                setSubtitlesEnabled(1);        // FUN_00433c10
                velocityX = DAT_0112b8fc;
                velocityY = 0.0f;
                velocityZ = (float)((uint)velocityZ & 0xffffff00);
                setAudioState(&velocityX, 0);
            }
        }
    }

    // Handle physics body pointer (+0xb1c)
    if (this->physicsBody != 0) {
        if (isObjectReady() == '\0') { // FUN_007f7c60
            // Sync physics body transform with the vehicle's current transform (at +0x30 of gameTimeManager? Actually uses gameTimePtr+0x30)
            int transformPtr = gameTimePtr + 0x30; // likely vehicle's world transform
            syncPhysicsTransform(this->physicsBody, transformPtr); // FUN_005e6580
        } else {
            *(byte *)(this + 0xb1d) = 1; // mark as detaching
            stopPhysicsSimulation(this->physicsBody, 0, 0); // FUN_005e6820
            releasePhysicsBody(this->physicsBody); // FUN_005e6660
            *(byte *)(this + 0xb1d) = 0; // clear detach flag
            this->physicsBody = 0; // +0xb1c
        }
    }

    // Engine audio parameter updates
    if (DAT_011299a8 != 0) {
        // Calculate speed factor: compare getMaxSpeed() and getCurrentSpeed()
        fVar1 = this->vtable->getMaxSpeed(); // +0xc4
        if (fVar1 <= (float)DAT_00e44598) {
            speed = 1.0f;
        } else {
            fVar2 = this->vtable->getCurrentSpeed(); // +0xc0
            speed = fVar2 / fVar1;
        }
        setAudioEngineSpeed(speed); // FUN_008d1c50

        if (isObjectReady() == '\0') {
            // Get velocity vector from vehicle
            this->vtable->getVelocity(&velocityX); // +0x4c
            // Compute velocity magnitude and set audio parameter (RPM)
            float magnitude = sqrt(velocityX*velocityX + velocityY*velocityY + velocityZ*velocityZ);
            setAudioEngineRPM(magnitude * _DAT_00e4486c); // FUN_008d1c10
            setAudioParameter3(0); // FUN_008d1c30
            setAudioParameter4(1.0f); // FUN_008d1c70 (volume?)
        }
    }

    // Update car suspension/tires
    updateCarSuspension(); // FUN_007a8f80

    // Check if vehicle is on ground via virtual call
    bool onGround = this->vtable->isOnGround(); // +0x78
    if (onGround == 0) {
        this->flags_6e5 &= 0xffffffe9; // +0x6e5 clear certain bits
    }

    // Building/interior state check
    int building = getBuildingFromIndex(this->interiorIndex); // +0x108, FUN_0088dbb0
    if ((building != 0) && (*(int *)(building + 0x14) != 0)) {
        if (*(char *)(*(int *)(building + 0x14) + 0x50) == 3) {
            this->flags_928 |= 1; // +0x928 set bit 0 (inside interior?)
            return;
        }
        this->flags_928 &= 0xfffffffe; // clear bit 0
    }
}