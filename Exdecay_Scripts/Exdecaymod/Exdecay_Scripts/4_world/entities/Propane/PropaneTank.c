class Ex_PropanTank_BT extends Inventory_Base
{
	override void EEKilled (Object killer)
	{
		super.EEKilled(killer);

	 	Explode(DT_EXPLOSION, "M67Grenade_Ammo");
	};
	override void OnExplosionEffects (Object source, Object directHit, int componentIndex, string surface, vector pos, vector surfNormal, float energyFactor, float explosionFactor, bool isWater, string ammoType)
	{
		if ( !GetGame().IsServer() || !GetGame().IsMultiplayer() )
		{	
			vector n = surfNormal.VectorToAngles() + "0 90 0";
		
			Particle p2 = Particle.Play(ParticleList.EXPLOSION_LANDMINE, pos);
			p2.SetOrientation(n);

			Particle p3 = Particle.Play(ParticleList.IMPACT_METAL_RICOCHET, pos);
			p3.SetOrientation(n);
		
			Particle p4 = Particle.Play(ParticleList.IMPACT_GRAVEL_RICOCHET, pos);
			p4.SetOrientation(n);
		}
	}	
};