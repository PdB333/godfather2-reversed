// Xbox PDB: SM_SphereizerBase::Load
// FUNC_NAME: CrimeScene::initFromData
void CrimeScene::initFromData(void)
{
  DataManager *dataMgr;
  DataNode *node;
  
  // Get the global data manager instance (singleton)
  dataMgr = DataManager::getInstance();
  this->dataMgrHandle = *dataMgr;
  
  // Get the root node for this crime scene from the data manager
  node = DataManager::getNode(dataMgr);
  this->dataNode = node;
  
  // Retrieve specific data elements: radius, center, extent
  this->radius = DataManager::getAttribute(node, "radius");
  this->center = DataManager::getAttribute(node, "center");
  this->extent = DataManager::getAttribute(node, "extent");
  
  // Initialize the 'active' flag to false
  *(uint8_t *)(this + 4) = 0;
}