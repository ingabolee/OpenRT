//
//  TextureWood.cpp
//  Demo_AreaLight
//
//  Created by Mahmoud El Bergui on 21.04.22.
//

#include "TextureWood.h"
#include "PerlinNoise.h"


namespace rt{

          namespace {
               /**
               @Brief Function to interpolate between pillar two wood colors
               @param value value that we want to map
               @return mapped color
               */
               Vec3f woodMap(float value){
               
               Vec3f earlyWood = Vec3f(0.2862745,0.45490196,0.64313725);
               Vec3f lateWood = Vec3f(0.054901,0.184313,0.337254);
               Vec3f color = (Vec3f) ((lateWood - earlyWood) * value + earlyWood);
                    
               return color;
               // (int) ((r2 - r1) * val + r1)
               }
          }
          
	Vec3f CTextureWood::getTexel(const Vec3f& uvw) const
	{
		//Getting coordinate info
		float u = uvw.val[0];
		float v = uvw.val[1];
		float w = uvw.val[2];
  
          CPerlinNoise pn;
          //Increasing the alpha increase the noise effect (>1 destroyes the rings)
          //fx,fy,fz increase -> more stiff peaks (value around 0.5 gives a more real-like wood texture)
          //Having a small difference between fx,fy, and fz gives more realism
          
          double n = 0.6 * pn.noise(Point3f(0.55f * u, 0.45f * v ,0.35f * w)); //This noise function call puts noise on the rings to give wood the                                                          natural felling
          //n = n - floor(n);
              
		//Difference between point and center of the shape
		float value = m_period * sqrtf(w * w + u * u) + n; //This noise function call gives wood roughness to texture
          
          double n1 = 3.70 * pn.noise(Point3f(20 * u , 10 * v , 10 * w));
          
          
          //Perlin Noise
          Vec3f color = woodMap(remainder(value, 1) + n1);
		return color;
	}
}
