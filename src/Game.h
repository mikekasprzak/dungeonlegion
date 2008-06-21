// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_H__
#define __Game_H__
// - ------------------------------------------------------------------------------------------ - //
#include <AllegroGraphics/Graphics.h>
#include <AllegroGraphics/GraphicsDraw.h>
// - ------------------------------------------------------------------------------------------ - //
#include <PolyMap/PolyMap.h>
#include <AdvancedGeometry/PointVsSphere2D.h>
#include <AdvancedGeometry/PointVsPairRect2D.h>
#include <AdvancedGeometry/PointVsShapeRect2D.h>
#include <AdvancedGeometry/PointVsRadiusRect2D.h>
// - ------------------------------------------------------------------------------------------ - //
#include <AdvancedGeometry/PointVsPolygon2D.h>
#include <AdvancedGeometry/PointVsEdgedPolygon2D.h>
#include <AdvancedGeometry/PointVsCapsuleChain2D.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Impulse.h"
#include "Entity.h"
#include "ExitPortal.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cGame {
public:
	cPolyMap Map;

	std::vector<cImpulse> Impulse;

		
	std::vector<cEntity> Entity;
	int CurrentHero;
	
	std::vector<cExitPortal> ExitPortal;
		

	// Note all the collision Polygons //
	std::vector<cPolyMapElement*> Collision;

public:
	int BoundsIndex;
	
	inline const cPolyMapElement& GetBounds() {
		// TODO: Make this instead give a rectangle, or some identifyable value for none //
		return Map.Element[BoundsIndex];
	}
	
public:
	inline cGame() :
		Map( "TestMap.txt" ),
		CurrentHero( 0 ),
		BoundsIndex( 0 )
	{
		printf( "- Game Init -\n" );

		// Find the bounds rectangle //
		for ( size_t idx = 0; idx < Map.Element.size(); idx++ ) {
			if ( Map.Element[idx].Type == PME_RECT ) {
				switch (Map.Element[idx].Id) {
					case 1: {
						printf(" + Camera Bounding Rectangle Set\n");
						BoundsIndex = idx;
						break;
					}
				};
			}
			else if ( Map.Element[idx].Type == PME_SPHERE ) {
				// What type of Sphere is it? //
				switch (Map.Element[idx].Id) {
					case 1: {
						// Hero //
						Entity.push_back( 
							cEntity( Map.Element[idx].Center, cEntity::BR_HERO, 14 )
							);
						CurrentHero = Entity.size() - 1;
						printf(" + Added Hero\n");
						break;
					}
					case 4: {
						// Exit Portal //
						ExitPortal.push_back( cExitPortal(Map.Element[idx].Center) );
						printf(" + Added Exit Portal\n");
						break;
					}
					case 5: {
						// Troop //
						Entity.push_back( 
							cEntity( Map.Element[idx].Center, cEntity::BR_TROOP, 8 )
							);
						printf(" + Added Troop\n");
						break;
					}
					case 11: {
						// Enemy //
						Entity.push_back( 
							cEntity( Map.Element[idx].Center, cEntity::BR_ENEMY, 16 )
							);
						printf(" + Added Enemy 1\n");
						break;
					}
					case 12: {
						// Enemy //
						Entity.push_back( 
							cEntity( Map.Element[idx].Center, cEntity::BR_ENEMY, 36 )
							);
						//Entity.back().State = cEntity::ST_ATTACKING;
						//Entity.back().Status.HP = 0;
						printf(" + Added Enemy 2\n");
						break;
					}	
				};
			}
			else if ( Map.Element[idx].Type == PME_POLY ) {
				// For now, asume all polygons are collision //
				Collision.push_back( &Map.Element[idx] );
				printf(" + Added Collision Polygon\n");
			}
		}
		
	}
	
	inline void Step() {
		// Magnet Moving Hack //
		if ( mouse_b == 1 ) {
			for ( size_t idx2 = 0; idx2 < Collision.size(); idx2++ ) {
				if ( Test_Point_Vs_Polygon2D( Camera.Mouse, &Collision[idx2]->Vertex[0], Collision[idx2]->Vertex.size() ) ) {
					Entity[CurrentHero].TargetPos = Camera.Mouse;
					Entity[CurrentHero].Target = 0;
					Entity[CurrentHero].ReachedTarget = false;
					
					for ( size_t idx = 0; idx < Entity.size(); idx++ ) {
						if ( !Entity[idx].Status.IsAlive() )
							continue;
						
						if ( idx == CurrentHero )
							continue;
							
						if ( Entity[idx].Brain < cEntity::BR_CLICKABLE )
							continue;
						
						if ( Test_Point_Vs_Sphere2D( Camera.Mouse, Entity[idx].Pos, Entity[idx].Radius ) ) {
							Entity[CurrentHero].Target = &Entity[idx];
						}
					}
					
					break;			
				}
			}			
		}
		
		
		// Step all Collectors //
		for ( size_t idx = 0; idx < ExitPortal.size(); idx++ ) {
			ExitPortal[idx].Step();
			
			// Add an impulse that pulls them towards us //
			Impulse.push_back( 
				cImpulse(
					ExitPortal[idx].Pos,
					0, -0.01,
					48, 0
					)
				);
		}
		
		// Step all Entities //
		for ( size_t idx = 0; idx < Entity.size(); idx++ ) {
			Entity[idx].Step();

			// Apply Impulses //
			for ( size_t idx2 = 0; idx2 < Impulse.size(); idx2++ ) {
				Entity[idx].AddForce( Impulse[idx2].GetForce( Entity[idx].Pos ) );
			}
		
			// Test for Entity Collisions Vs. Collectors //
			for ( size_t idx2 = 0; idx2 < ExitPortal.size(); idx2++ ) {
				if ( Test_Point_Vs_Sphere2D( Entity[idx].Pos, ExitPortal[idx2].Pos, ExitPortal[idx2].Radius + Entity[idx].Radius ) ) {
					// Kill Entity //
					Entity.erase( Entity.begin() + idx );
					idx--;
					
					// Break out of the for loop //
					break;
				}
			}
		}

		// Collision detection Versus all Entities //
		for ( size_t idx = 0; idx < Entity.size(); idx++ ) {
			if ( !Entity[idx].Status.IsAlive() )
				continue;
			// Step all un-touched Entities //
			for ( size_t idx2 = idx+1; idx2 < Entity.size(); idx2++ ) {	
				if ( !Entity[idx2].Status.IsAlive() )
					continue;

				// If there's a brain compatability match (i.e. Join me) //
				if ( (Entity[idx].Brain == cEntity::BR_HERO) || (Entity[idx2].Brain == cEntity::BR_HERO) ) {
					if ( (Entity[idx].Brain == cEntity::BR_TROOP) ) {
						if ( (Entity[idx].Leader == 0 ) ) {
							if ( Entity[idx2].IsWithinAttackRange( Entity[idx] ) ) {
								Entity[idx].Leader = &Entity[idx2];
								printf("Recruited Entity %i\n", idx);
							}
						}
					}
					else if ( (Entity[idx2].Brain == cEntity::BR_TROOP) ) {
						if ( (Entity[idx2].Leader == 0 ) ) {
							if ( Entity[idx].IsWithinAttackRange( Entity[idx2] ) ) {
								Entity[idx2].Leader = &Entity[idx];
								printf("Recruited Entity %i\n", idx2);
							}
						}						
					}
				}
				
				// If one of us is an enemy //
				if ( (Entity[idx].Brain == cEntity::BR_ENEMY) || (Entity[idx2].Brain == cEntity::BR_ENEMY) ) {
					if ( (Entity[idx].Brain != cEntity::BR_ENEMY) || (Entity[idx2].Brain != cEntity::BR_ENEMY) ) {
						if ( Entity[idx].Brain != cEntity::BR_HERO ) {
							if ( Entity[idx].State == cEntity::ST_IDLE ) {
								if ( Entity[idx].Target == 0 ) {
									if ( Entity[idx].IsWithinEngageRange( Entity[idx2] ) ) {
										Entity[idx].Target = &Entity[idx2];
										printf("%i Targeted %i\n", idx, idx2);
									}
								}
							}
						}
						if ( Entity[idx2].Brain != cEntity::BR_HERO ) {
							if ( Entity[idx2].State == cEntity::ST_IDLE ) {
								if ( Entity[idx2].Target == 0 ) {
									if ( Entity[idx2].IsWithinEngageRange( Entity[idx] ) ) {
										Entity[idx2].Target = &Entity[idx];
										printf("%i Targeted %i\n", idx2, idx);
									}
								}
							}
						}
					}
				}
				
				// Test for collision versus other object //
				if ( Test_Point_Vs_Sphere2D( Entity[idx].Pos, Entity[idx2].Pos, Entity[idx2].Radius + Entity[idx].Radius ) ) {
					Vector2D Line = Entity[idx2].Pos - Entity[idx].Pos;
					Real Length = Line.NormalizeRet();
					Real RadiusSum = Entity[idx2].Radius + Entity[idx].Radius;
					
					Real Diff = RadiusSum - Length;
					
					// Less Mass, easier to push bigger guys //
//					Real E1Mass = Entity[idx].Radius;
//					Real E2Mass = Entity[idx2].Radius;
					// Greater Mass, harder to push big guys, more correct ratio //
					Real E1Mass = Entity[idx].CircleArea();
					Real E2Mass = Entity[idx2].CircleArea();
					
					// Test various properties to figure out if one of them should not be moved //
					{
						// If the other guy is my leader //
						if ( Entity[idx].Leader == &Entity[idx2] ) {
							// Since E2 is my leader, make my mass not affect him //
							E1Mass = 0;
						}
						else if ( Entity[idx2].Leader == &Entity[idx] ) {
							// Since E1 is my leader, make my mass not affect him //
							E2Mass = 0;
						}
						
						// So long as we don't have the same leader, obey the "no pushing //
						//   if engaged" rule. //
						else if ( (Entity[idx].Leader == 0) || (Entity[idx].Leader != Entity[idx2].Leader) ) {
							// If the other guy is engaged in combat //
							if ( Entity[idx2].IsEngaged() ) {
								// E2 is already planted and engaged in a battle, I shouldn't move him //
								E1Mass = 0;
							}
							else if ( Entity[idx].IsEngaged() ) {
								// E1 is already planted and engaged in a battle, I shouldn't move him //
								E2Mass = 0;
							}
						}
						
						// If the other guy is my target //
						else if ( Entity[idx].Target == &Entity[idx2] ) {
							// Since E2 is my target, my mass shouldn't affect him //
							E1Mass = 0;
						}
						else if ( Entity[idx2].Target == &Entity[idx] ) {
							// Since E1 is my target, my mass shouldn't affect him //
							E2Mass = 0;
						}
						
					}
					
					// Sum the Masses //
					Real MassSum = E1Mass + E2Mass;
					
					// Move the positions //					
					Entity[idx].Pos -= (Line * Diff) * (Real::One - (E1Mass / MassSum));
					Entity[idx2].Pos += (Line * Diff) * (Real::One - (E2Mass / MassSum));
				}
			}
		}	

		// Solve versus polygon collision border //
		for ( size_t idx = 0; idx < Entity.size(); idx++ ) {
			// Test for Collisions Vs. Polygons //
			for ( size_t idx2 = 0; idx2 < Collision.size(); idx2++ ) {
				if ( Test_Point_Vs_CapsuleChain2D( Entity[idx].Pos, &Collision[idx2]->Vertex[0], Collision[idx2]->Vertex.size(), Entity[idx].Radius ) )
				{
					Vector2D EdgePoint = Nearest_InnerEdgePoint_On_CapsuleChain2D( 
						Entity[idx].Pos,
						&Collision[idx2]->Vertex[0],
						Collision[idx2]->Vertex.size(),
						Entity[idx].Radius
						);
					
					Entity[idx].Pos = EdgePoint;
				}
			}
		}		

		// Remove all Impulses //
		Impulse.clear();
	}
	
	
	inline void Draw() {
		// Draw all Entities //
		for ( size_t idx = 0; idx < Entity.size(); idx++ ) {
			Entity[idx].Draw();
		}
		
		
		// Draw all ExitPortals //
		for ( size_t idx = 0; idx < ExitPortal.size(); idx++ ) {
			ExitPortal[idx].Draw();
		}
		
		
		// Draw Elements //
		for ( size_t idx = 0; idx < Map.Element.size(); idx++ ) {
			// What kind of element is it? //
			if ( Map.Element[idx].Type == PME_POLY ) {
				// What type of Polygon is it? //
				switch (Map.Element[idx].Id) {
					default: 
					case 1: {
						gfxDrawClosedPolygonWithNormals( &Map.Element[idx].Vertex[0], Map.Element[idx].Vertex.size(), RGB_PUKE );
						gfxDrawCircle( Map.Element[idx].Center, 0 );
									
						break;
					}
				};
			}
			
			else if ( Map.Element[idx].Type == PME_SPHERE ) {
				// What type of Sphere is it? //
				switch (Map.Element[idx].Id) {
					default: 
					case 1: {
						gfxDrawCircle( Map.Element[idx].Center, Map.Element[idx].Data[0].f);
						gfxDrawCircle( Map.Element[idx].Center, 0 );
									
						break;
					}
				};
			}

			else if ( Map.Element[idx].Type == PME_NODE ) {
				// What type of Node is it? //
				switch (Map.Element[idx].Id) {
					default: 
					case 1: {
						gfxDrawRadiusBox( Map.Element[idx].Center, 3 );
						gfxDrawCircle( Map.Element[idx].Center, 0 );
									
						break;
					}
				};
			}

			else if ( Map.Element[idx].Type == PME_RECT ) {
				// What type of Rectangle is it? //
				switch (Map.Element[idx].Id) {
					default: 
					case 1: {
						gfxDrawRect( Map.Element[idx].Vertex[0], Map.Element[idx].Vertex[1] );
						gfxDrawCircle( Map.Element[idx].Center, 0 );
									
						break;
					}
				};
			}
		}
		
		// Draw Links //
		for ( size_t idx = 0; idx < Map.Link.size(); idx++ ) {
			// What type of link is it? //
			//if ( Map.Link.Type == 1 )
			{
				gfxDrawLine( Map.Element[ Map.Link[idx].a ].Center, Map.Element[ Map.Link[idx].b ].Center );
			}
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_H__ //
// - ------------------------------------------------------------------------------------------ - //
