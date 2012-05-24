int __stdcall Hero::acquireRandomArtifact(Hero *hero)
{
  int grantedArtifact; // [sp+10h] [bp-4h]@1

  grantedArtifact = GameInfo::randomArtifact(gameObject, 14, 1);
  if ( grantedArtifact == -1 )
    grantResource(hero, 6, 1000);
  else
    grantArtifact(hero, (ARTIFACT)grantedArtifact, 1, -1);
  return grantedArtifact;
}
