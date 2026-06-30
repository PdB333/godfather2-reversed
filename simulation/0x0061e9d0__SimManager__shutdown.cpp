// FUNC_NAME: SimManager::shutdown
void SimManager::shutdown(void)
{
  // +0x98: m_simulation - pointer to simulation object
  if (this->m_simulation != 0) {
    // Stop physics simulation
    FUN_00d06250(); // stopPhysics?
    FUN_00d06400(); // cleanupPhysics?
  }

  // +0xa0: m_spatialDatabase - pointer to spatial database
  if (this->m_spatialDatabase != (void*)0x0) {
    // Call destructor with 1 as delete flag
    (**(code **)*this->m_spatialDatabase)(1);
    this->m_spatialDatabase = 0;
  }

  // +0x9c: m_spatialHash - pointer to spatial hash
  if (this->m_spatialHash != (void*)0x0) {
    (**(code **)*this->m_spatialHash)(1);
    this->m_spatialHash = 0;
  }

  // +0xa8: m_safeData - pointer to safe data manager
  if (this->m_safeData != (void*)0x0) {
    (**(code **)*this->m_safeData)(1);
    this->m_safeData = 0;
  }

  // +0xa4: m_syncData - pointer to sync data manager
  if (this->m_syncData != (void*)0x0) {
    (**(code **)*this->m_syncData)(1);
    this->m_syncData = 0;
  }

  int iSimulation = this->m_simulation;
  if (iSimulation != 0) {
    FUN_00d08d20(); // simulationShutdown?
    FUN_009c8eb0(iSimulation); // destroySimulation?
    this->m_simulation = 0;
  }

  // +0xac: m_aiManager - pointer to AI manager
  if (this->m_aiManager != (void*)0x0) {
    (**(code **)*this->m_aiManager)(1);
    this->m_aiManager = 0;
  }

  // +0x94: m_isActive - flag indicating if manager is active
  // +0x90: m_masterObjectList - list of master objects
  if ((this->m_isActive == '\0') && (this->m_masterObjectList != (int*)0x0)) {
    // Call virtual function at offset +0xc (likely clear or destroy)
    (**(code **)(*this->m_masterObjectList + 0xc))();
  }
  this->m_masterObjectList = 0;

  // Global shutdown flag
  DAT_01205887 = 0;
  return;
}