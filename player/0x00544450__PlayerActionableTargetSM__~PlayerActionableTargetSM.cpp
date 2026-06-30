// FUNC_NAME: PlayerActionableTargetSM::~PlayerActionableTargetSM

void __fastcall PlayerActionableTargetSM::destructor(PlayerActionableTargetSM* this)
{
    int* instance;
    int refCount;
    TimerObject* timerObj;

    // Set vtable to base class pointers (early destructor step)
    *this = &VTABLE_PlayerActionableTargetSM;
    this->vtableBase1 = &VTABLE_Base1;
    this->vtableBase2 = &VTABLE_Base2;
    this->vtableBase3 = &VTABLE_Base3;
    this->vtableBase4 = &VTABLE_Base4;
    this->vtableBase5 = &VTABLE_Base5;
    this->vtableBase6 = &VTABLE_Base6;

    // Check global flag (maybe "engine is active")
    if (gEngineActiveFlag() == false) {
        return;
    }

    // Release managed pointer (e.g., a behavior object)
    instance = this->managedBehavior;  // +0xd8
    if (instance != 0 && *(int*)(instance + 8) != 0) {
        FUN_009ec070(instance);  // Release function
    }

    // Decrement timer count and possibly fire for each timer object (+0xdd, +0xe2, etc.)
    timerObj = this->timer0xdd;  // +0xdd
    if (timerObj != 0 && timerObj->refCount != 0) {
        timerObj->counter--;
        if (timerObj->counter == 0) {
            timerObj->vtable->onTimerFire(1);  // Virtual call with argument 1
        }
    }

    timerObj = this->timer0xe2;  // +0xe2
    if (timerObj != 0 && timerObj->refCount != 0) {
        timerObj->counter--;
        if (timerObj->counter == 0) {
            timerObj->vtable->onTimerFire(1);
        }
    }

    timerObj = this->timer0xe1;  // +0xe1
    if (timerObj != 0 && timerObj->refCount != 0) {
        timerObj->counter--;
        if (timerObj->counter == 0) {
            timerObj->vtable->onTimerFire(1);
        }
    }

    timerObj = this->timer0xda;  // +0xda
    if (timerObj != 0 && timerObj->refCount != 0) {
        timerObj->counter--;
        if (timerObj->counter == 0) {
            timerObj->vtable->onTimerFire(1);
        }
    }

    timerObj = this->timer0xdf;  // +0xdf
    if (timerObj != 0 && timerObj->refCount != 0) {
        timerObj->counter--;
        if (timerObj->counter == 0) {
            timerObj->vtable->onTimerFire(1);
        }
    }

    timerObj = this->timer0xe0;  // +0xe0
    if (timerObj != 0 && timerObj->refCount != 0) {
        timerObj->counter--;
        if (timerObj->counter == 0) {
            timerObj->vtable->onTimerFire(1);
        }
    }

    timerObj = this->timer0xde;  // +0xde
    if (timerObj != 0 && timerObj->refCount != 0) {
        timerObj->counter--;
        if (timerObj->counter == 0) {
            timerObj->vtable->onTimerFire(1);
        }
    }

    timerObj = this->timer0xe3;  // +0xe3
    if (timerObj != 0 && timerObj->refCount != 0) {
        timerObj->counter--;
        if (timerObj->counter == 0) {
            timerObj->vtable->onTimerFire(1);
        }
    }

    // Handle a special activity timer (e.g., interpolated animation)
    if (this->specialActivityTimer != 0) {  // +0xcc
        FUN_00557020();  // Stop or pause related system
        timerObj = this->specialActivityTimer;
        if (timerObj != 0 && timerObj->refCount != 0) {
            timerObj->counter--;
            if (timerObj->counter == 0) {
                timerObj->vtable->onTimerFire(1);
            }
        }
        this->specialActivityTimer = 0;
    }

    // Restore vtable to final base (purecall) and call base destructor
    this->vtableBase6 = &VTABLE_FinalBase;
    this->vtableBase5 = &VTABLE_Purecall;
    FUN_00542920();  // Call base class destructor
    return;
}