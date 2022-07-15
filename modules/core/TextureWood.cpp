//
//  TextureWood.cpp
//  Demo_AreaLight
//
//  Created by Mahmoud El Bergui on 21.04.22.
//

#include "TextureWood.h"
#include "PerlinNoise.h"
#include "CGradient.h"


namespace rt {

	// Constuctor
	CTextureWood::CTextureWood(float period) 
		: m_period(period)
//		, m_gradient(RGB(164, 116, 73), RGB(86, 47, 14))	// early an
	{}

	Vec3f CTextureWood::getTexel(const Vec3f& uvw) const
	{
		 //Getting coordinate info
		 float u = uvw.val[0];
		 float v = uvw.val[1];
		 float w = uvw.val[2];
     
		 //Increasing the alpha increase the noise effect (>1 destroyes the rings)
		 //fx,fy,fz increase -> more stiff peaks (value around 0.5 gives a more real-like wood texture)
		 //Having a small difference between fx,fy, and fz gives more realism
     
		 float noise1 = 0.60f * CPerlinNoise::noise(Point3f(0.55f * u, 0.45f * v ,0.35f * w)); //This noise function call puts noise on the rings to give wood the                                                          natural felling
		 //noise1 = noise1 - floor(noise1);
		 float noise2 = 3.70f * CPerlinNoise::noise(Point3f(20 * u, 10 * v, 10 * w));

		 //Difference between point and center of the shape
		 float value = m_period * sqrtf(w * w + u * u) + noise1; //This noise function call gives wood roughness to texture

		 //Perlin Noise
		 return m_gradient.getColor(remainder(value, 1)/* + noise2 */ );
	}
}
