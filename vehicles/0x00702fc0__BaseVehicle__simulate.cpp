// FUNC_NAME: BaseVehicle::simulate
void __fastcall BaseVehicle::simulate(BaseVehicle* this)
{
    // +0x4f8: simulationState (set to 2 = ACTIVE)
    this->simulationState = 2;

    PhysicsManager* mgr = PhysicsManager::getInstance();
    bool onGround = mgr->vtable->isOnGround();
    float euler[3]; // roll, pitch, yaw
    float pos[3];
    Matrix4 worldMatrix;

    if (!onGround) {
        Vector3::zero(&euler[0], &euler[1], &euler[2], &worldMatrix, 0);
        // alternatively: getEulerAngles with NULLs for some?
        // Actually FUN_00701bc0 takes multiple outputs; assume it fills local vars
        // We'll use meaningful names: extractedRoll, extractedPitch, extractedYaw, extractedMatrix
        float extractedRoll, extractedPitch, extractedYaw;
        Matrix4 extractedMatrix;
        Vector3::zero(&extractedRoll, &extractedPitch, &extractedYaw, &extractedMatrix, 0);
        // but the code shows: FUN_00701bc0(&fStack_e4, &fStack_d4, &fStack_fc, &uStack_f0, 0);
        // So it writes to four outputs. We'll represent them as roll, pitch, yaw and a quaternion/vector.
        // Actually second param is pitch, third is yaw, fourth is something like forward vector? 
        // Since we don't have exact signatures, we'll abstract.
    } else {
        Vector3::zero(&euler[0], NULL, NULL, NULL, 0);
        // Get vehicle transform
        int transformPtr = VehicleTransform::getTransform(); // FUN_00471610
        // +0x10: quaternion rotation part, +0x18: translation.x? Actually:
        // uVar1 = *(undefined8 *)(iVar5 + 0x10); -> two floats for quaternion imaginary? 
        // fStack_e8 = *(float *)(iVar5 + 0x18); -> maybe translation.z?
        // Then compute cross product with world up?
        // We'll keep as complex vector math.
    }

    // Build rotation matrix from Euler angles
    Matrix4 rotationMatrix;
    Vector3::buildRotationMatrix(&euler[0], &rotationMatrix); // FUN_007011f0

    // Check if running in network simulation mode
    if (isNetworkSimulation()) // FUN_00481620
    {
        // Get delta time
        float dt = (float)getSimulationDeltaTime(); // FUN_00702d70
        float timeMultiplier = dt;
        if (this->physConfig != NULL) // +0x2d4
        {
            timeMultiplier = dt * this->physConfig->vtable->getMultiplier();
        }

        // Input state
        uint inputFlags = this->inputFlags; // +0x2e8
        uint inputValue = this->inputValue; // +0x2ec
        if (this->inputSourceFlags & 4) // +0x2d8 bit2
        {
            inputFlags = this->alternateInputFlags; // +0x2e0
            inputValue = this->alternateInputValue; // +0x2e4
        }

        // Traction/speed values
        float engineForce = *(float*)((uint)&this->engineForce); // +0x1d8
        float speed = this->speed; // +0x474

        // Get traction manager for scaling
        TractionManager* tractionMgr = TractionManager::getInstance(); // FUN_007079c0
        if (tractionMgr != NULL)
        {
            float scale = (this->inputSourceFlags & 4) ? gTractionScaleAlt : gTractionScale;
            speed = scale * tractionMgr->globalTraction * speed;
        }

        // Main vehicle physics integration
        VehicleForces::apply( // FUN_00852880
            mgr, this,
            this->field_0x364, this->field_0x350,
            speed, engineForce,
            this->field_0x324, (uint)-1,
            &euler[0], &inputState, // local vectors
            &rotMatrix, &finalMatrix,
            timeMultiplier, timeMultiplier, 0,
            this->field_0x334,
            inputFlags, inputValue,
            &rotationMatrix,
            this->field_0x37c, 0,
            this->field_0x48c,
            this->field_0x494,
            this->field_0x490,
            this->field_0x498,
            this->field_0x488,
            this->field_0x49c
        );

        // Clamp input to low byte
        inputFlags = inputFlags & 0xFFFFFF00;
        // Check if ground flag and network-driven
        if ((this->inputSourceFlags & 4) && mgr != NULL && (mgr->someFlag & 1))
        {
            inputFlags = (inputFlags & 0x00FFFFFF) | 1; // set bit0
        }
        setNetworkInputState(inputFlags); // FUN_00856970

        if (this->physConfig != NULL)
        {
            this->physConfig->vtable->postPhysics(); // vtable+8
        }

        float animTime = (float)getAnimationTime(); // FUN_00701920
        setSimulationTime(animTime); // FUN_00702e90
    }

    // Decrement counter
    this->simulationTicks--; // +0x328

    // Deceleration if non-zero
    if (this->decelerationFactor != 0.0f) // +0x344
    {
        Vector3 decel;
        decel.x = 0.0f;
        decel.y = 0.0f;
        decel.z = this->decelerationFactor;
        Vector3::applyDeceleration(&decel, 0); // FUN_00408a00
    }

    // Finalize simulation
    Simulation::finalize(); // FUN_00701ab0
}