{
  *(_DWORD *)&combatArmyInfoLevel = level;
  CombatManager::drawBattlefield(this, 1, 0, 0, 0, 75, 1, 1);
  propagateSettingChanges();
}