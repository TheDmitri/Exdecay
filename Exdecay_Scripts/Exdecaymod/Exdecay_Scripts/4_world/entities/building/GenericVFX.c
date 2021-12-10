class GenericVFX extends ItemBase
{
	protected Particle m_particle;
	protected int m_particleID; 

	void GenericVFX() 
	{

	}

	void vfx_start()
	{
		m_particle = Particle.PlayOnObject(m_particleID, this, vector.Zero);
	}

	override bool DisableVicinityIcon()
    {
        return true;
    }
}