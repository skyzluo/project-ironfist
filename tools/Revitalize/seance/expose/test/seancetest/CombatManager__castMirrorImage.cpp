void __thiscall CombatManager::castMirrorImage(CombatManager *this, int hex)
{
  int v2; // eax@62
  int v3; // eax@62
  signed __int64 v4; // qax@62
  CombatManager *thisa; // [sp+14h] [bp-3Ch]@1
  int diffY; // [sp+18h] [bp-38h]@62
  int diffX; // [sp+1Ch] [bp-34h]@62
  int tick; // [sp+20h] [bp-30h]@62
  int v9; // [sp+24h] [bp-2Ch]@7
  int l; // [sp+28h] [bp-28h]@62
  int pow; // [sp+2Ch] [bp-24h]@58
  int j; // [sp+30h] [bp-20h]@14
  signed int neighborIdx; // [sp+34h] [bp-1Ch]@18
  int imageHex; // [sp+38h] [bp-18h]@44
  int k; // [sp+3Ch] [bp-14h]@44
  int i; // [sp+40h] [bp-10h]@3
  CreatureStack *imageStack; // [sp+44h] [bp-Ch]@58
  int v18; // [sp+48h] [bp-8h]@1
  CreatureStack *creat; // [sp+4Ch] [bp-4h]@1

  thisa = this;
  creat = &this->creatures[this->combatGrid[hex].unitOwner][this->combatGrid[hex].stackIdx];
  v18 = 1;
LABEL_2:
  if ( v18 < 10 )
  {
    for ( i = 0; ; ++i )
    {
      if ( i >= 2 )
      {
        ++v18;
        goto LABEL_2;
      }
      if ( i )
      {
        if ( !(creat->creature.creature_flags & TWO_HEXER) )
          continue;
        if ( creat->facingRight == 1 )
          v9 = creat->occupiedHex + 1;
        else
          v9 = creat->occupiedHex - 1;
      }
      else
      {
        v9 = creat->occupiedHex;
      }
      for ( j = 0; j < 6; ++j )
      {
        if ( creat->facingRight == 1 )
          neighborIdx = j;
        else
          neighborIdx = 5 - j;
        if ( (creat->facingRight != 1 || neighborIdx != 1 || i || v18 != 1)
          && (creat->facingRight != 1 || neighborIdx != 4 || i || v18 != 1)
          && (creat->facingRight != 1 || neighborIdx != 4 || i != 1 || v18 > 2)
          && (creat->facingRight || neighborIdx != 4 || i || v18 != 1)
          && (creat->facingRight || neighborIdx != 1 || i || v18 != 1)
          && (creat->facingRight || neighborIdx != 1 || i != 1 || v18 > 2) )
        {
          imageHex = v9;
          for ( k = 0; k < v18; ++k )
          {
            imageHex = getHexNeighbor(imageHex, neighborIdx);
            if ( imageHex >= 0
              && imageHex < 117
              && imageHex % 13
              && imageHex % 13 != 12
              && CreatureStack::canPlaceCreature(creat, imageHex, 0, 0) )
            {
              CombatManager::createSummonedStack(
                thisa,
                thisa->currentActionSide,
                creat->creatureIdx,
                creat->quantity,
                imageHex,
                256,
                0);
              imageStack = &thisa->creatures[thisa->combatGrid[imageHex].unitOwner][thisa->combatGrid[imageHex].stackIdx];
              *(_DWORD *)&imageStack->creature.creature_flags |= 0x800u;
              pow = thisa->heroSpellpowers[thisa->currentActionSide];
              if ( Hero::hasArtifact(thisa->heroes[thisa->currentActionSide], ARTIFACT_ENCHANTED_HOURGLASS) )
                pow += 2;
              if ( Hero::hasArtifact(thisa->heroes[thisa->currentActionSide], ARTIFACT_WIZARDS_HAT) )
                pow += 10;
              imageStack->lifespan = pow;
              creat->mirrorIdx = imageStack->stackIdx;
              imageStack->mirroredIdx = creat->stackIdx;
              diffX = thisa->combatGrid[creat->occupiedHex].centerX - thisa->combatGrid[imageStack->occupiedHex].centerX;
              diffY = thisa->combatGrid[creat->occupiedHex].occupyingCreatureBottomY
                    - thisa->combatGrid[imageStack->occupiedHex].occupyingCreatureBottomY;
              CombatManager::resetStuffHapenedToCreature(thisa);
              v2 = 80 * thisa->combatGrid[imageHex].unitOwner + 4 * thisa->combatGrid[imageHex].stackIdx;
              ++*(signed int *)((char *)thisa->stuffHappenedToCreature[0] + v2);
              v3 = 80 * thisa->combatGrid[hex].unitOwner + 4 * thisa->combatGrid[hex].stackIdx;
              ++*(signed int *)((char *)thisa->stuffHappenedToCreature[0] + v3);
              CombatManager::drawBattlefield(combatManager, 0, 1, 0, 1, 75, 1, 1);
              v4 = (signed __int64)((double)getTickCount() + combatSpeedPercentages[*(_DWORD *)&combatSpeed] * 50.0);
              tick = v4;
              for ( l = 0; l < 16; ++l )
              {
                imageStack->xDrawOffset = diffX * (16 - l) / 16;
                imageStack->yDrawOffset = diffY * (16 - l) / 16;
                dword_4F7488 = 1;
                CombatManager::drawBattlefield(combatManager, 0, 0, 0, 0, 0, 1, 0);
                HeroWindowManager::redrawRectangle(
                  HeroWindowManager::instance,
                  combatScreenRedrawRectLeft,
                  combatScreenRedrawRectTop,
                  combatScreenRedrawRectRight - combatScreenRedrawRectLeft + 1,
                  combatScreenRedrawRectBot - combatScreenRedrawRectTop + 1);
                dword_4F7488 = 0;
                sleepUntilPointer(&tick);
                v4 = (signed __int64)((double)getTickCount() + combatSpeedPercentages[*(_DWORD *)&combatSpeed] * 50.0);
                tick = v4;
              }
              imageStack->xDrawOffset = 0;
              imageStack->yDrawOffset = 0;
              sub_4C3FF0(thisa, SHIDWORD(v4), 0, 1);
              CombatManager::drawBattlefield(thisa, 1, 0, 0, 0, 75, 1, 1);
              return;
            }
          }
        }
      }
    }
  }
  sprintf(globBuf, "Mirror Image spell failed!");
  display_message_window(globBuf, 1, -1, -1, -1, 0, -1, 0, -1, 0);
}
