void __thiscall AdvManager::heroSelectionGUIStuff(AdvManager *this, int a2, int a3)
{
  int a2a; // [sp+20h] [bp-4h]@2

  if ( *(&byte_524758 + curPlayerIdx) )
  {
    for ( a2a = 0; a2a < 4; ++a2a )
      AdvManager::involvesSettingPointBars(this, a2a, 0, 0);
    if ( curPlayer->numHeroes >= 5 )
      this->heroScrollbarKnob->offsetY = (signed __int64)((double)curPlayer->_1[1]
                                                        * (73.0
                                                         / (double)((signed int)curPlayer->numHeroes - 4))
                                                        + 195.0);
    else
      this->heroScrollbarKnob->offsetY = 232;
    if ( a2 )
      GUIWindow::repaint(this->adventureScreen, a3);
  }
}
