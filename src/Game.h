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

// - ------------------------------------------------------------------------------------------ - //
class cImpulse {
public:
	Vector2D Pos;
	
	Real InnerRadius;
	Real InnerForce;
	
	Real OuterRadius;
	Real OuterForce;
	
	
	// Cached Variables //
	Real ForceDiff;
	Real RadiusDiff;
	Real InvRadiusDiff;	
	
	Real OuterRadiusSquared;
	Real InnerRadiusSquared;
	
public:
	inline cImpulse(
		const Vector2D& _Pos,
		const Real& _InnerRadius, const Real& _InnerForce,
		const Real& _OuterRadius, const Real& _OuterForce
		) :
		Pos( _Pos ),
		InnerRadius( _InnerRadius ), InnerForce( _InnerForce ),
		OuterRadius( _OuterRadius ), OuterForce( _OuterForce ),
		ForceDiff( _InnerForce - _OuterForce ),
		RadiusDiff( _OuterRadius - _InnerRadius ),
		InvRadiusDiff( Real::One / RadiusDiff ),
		OuterRadiusSquared( _OuterRadius * _OuterRadius ),
		InnerRadiusSquared( _InnerRadius * _InnerRadius )
	{
	}

public:
	// Get the force on you, given your position //
	inline Vector2D GetForce( const Vector2D& _Pos ) const {
		Vector2D Line = _Pos - Pos;
		
		if ( Line.MagnitudeSquared() > OuterRadiusSquared ) {
			return Vector2D::Zero;
		}
		else if ( Line.MagnitudeSquared() <= InnerRadiusSquared ) {
			Vector2D LineNormal = Line.Normal();

			return (LineNormal * InnerForce);
		}
		else {
			// Linear Impulses //
			Real Mag = Line.NormalizeRet();
			Real ForceScalar = (RadiusDiff - ( Mag - InnerRadius )) * InvRadiusDiff;
			return (Line * (ForceDiff * ForceScalar));
			
			// Exponential Impulses //
//			Real Mag = Line.NormalizeRet();
//			Mag -= InnerRadius;
//			Real ForceScalar = Mag*Mag / (RadiusDiff*RadiusDiff); // * InvRadiusDiff;
//			return Line * (ForceDiff * (Real::One - ForceScalar));
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cStatus {
public:
	int HP, MaxHP;
	int Attack;
	int Defense;
	
	Real AttackRange;
	
	// Things for identifying enhancements //

public:
	cStatus() :
		HP(12),
		MaxHP(12),
		Attack(2),
		Defense(1),
		
		AttackRange( 3 )
	{
	}

public:
	inline bool IsAlive() const {
		return HP != 0;
	}
	
	inline int GetHP() const {
		return HP;
	}
	
	inline void AddHP( const int _HP ) {
		HP += _HP;
		
		if ( HP < 0 )
			HP = 0;
		else if ( HP > MaxHP )
			HP = MaxHP;
	}

public:
	inline int GetAttack() const {
		// TODO: Apply modifiers //
		return Attack;
	}
	
	inline int GetDefense() const {
		// TODO: Apply modifiers //
		return Defense;
	}

public:
	// Calculate damage dealt to an opponent //
	inline int CalculateDamage( const cStatus& Vs ) const {
		int Damage = GetAttack() - Vs.GetDefense();
		if ( Damage > 0 )
			return Damage;
		else
			return 0;
	}
};

// - ------------------------------------------------------------------------------------------ - //
class cEntity {
public:
	// Physics Variables//
	Vector2D Pos, Old;
	Real Radius;
	
	Vector2D Force;

public:
	// Distinction Variables //
	cStatus Status;

	// AI State Variables //	
	enum {
		ST_NULL = 0,
		ST_IDLE,
		//ST_MOVING,
		//ST_FOLLOWING,
		//ST_ENGAGING,
		ST_ENGAGED,
		
				
		ST_END
	};
	size_t State;
	
	// AI Brain Type //
	enum {
		BR_NULL = 0,
		BR_HERO,
		BR_TROOP,
		
		BR_CLICKABLE,
		
		BR_RECRUITABLE,
		BR_NEUTRAL,
		BR_ENEMY,
		
		BR_END
	};
	size_t Brain;
	
	
	// AI Variables //
	cEntity* Leader;
	
	Vector2D TargetPos;
	cEntity* Target;
	
	bool ReachedTarget;


public:
	cEntity( const Vector2D& _StartPos, const size_t _BrainType = BR_HERO, const Real _Radius = 6 ) :
		Pos( _StartPos ),
		Old( _StartPos ),
		Radius( _Radius ),
		
		State( ST_IDLE ),
		Brain( _BrainType ),
		
		Leader( 0 ),
		TargetPos( _StartPos ),
		Target( 0 ),
		ReachedTarget( true )
	{
	}

public:
	// Calculate the current velocity from positions //
	inline const Vector2D Velocity() {
		return (Pos - Old);
	}
	
	// Accumulate a force/impulse //
	inline void AddForce( const Vector2D& _Force ) {
		Force += _Force;
	}
	
	// Given a surface contact, change the old position to reflect off that surface //
	//   "Reflect" is a value from 0 to 1, depending on how much energy to retain (0-100%) //
	inline void ApplyReflection( const Vector2D& _ContactNormal, const Real Reflect = Real::One) {
		// Calculate the Reflection //
		Real ReflectionStrength = (Velocity() * _ContactNormal) * (Real::One + Reflect);
		
		// Reflect only if you oppose the direction of the Contact Normal //
		if ( ReflectionStrength > Real::Zero ) {
			// Apply the reflection to Old Position //
			Old += ReflectionStrength * _ContactNormal;
		}
	}
	
	// Proper "Area" fomula //
	inline Real Area() const {
		return Real::Pi * Radius * Radius;
	}
	
	// Specialty Area formula, for Circle vs. Circle tests.  One less multiply. //
	inline Real CircleArea() const {
		return Radius * Radius;
	}
	
	inline Real RadiusSquared() const {
		return Radius * Radius;
	}

public:
	// Return where I should be going //
	inline const Vector2D& GetTarget() const {
		if ( Target )
			return Target->Pos;
		else if ( Leader ) {
			if ( Leader->Target )
				return Leader->Target->Pos;
			else
				return Leader->Pos;
		}
		else
			return TargetPos;
	}
	
	// Determine if something is within my Attack Range //
	inline bool IsWithinAttackRange( const Vector2D& VsPos, const Real VsRadius ) const {
		Vector2D Diff = VsPos - Pos;
		Real RadiusSum = RadiusSquared() + (VsRadius * VsRadius);
		RadiusSum += Status.AttackRange * Status.AttackRange;
		
		return Diff.MagnitudeSquared() < RadiusSum;
	}
	
	inline bool IsWithinAttackRange( const cEntity& Vs ) const {
		return IsWithinAttackRange( Vs.Pos, Vs.Radius );
	}
	
	inline bool IsEngaged() const {
		return State == cEntity::ST_ENGAGED;	
	}
	
public:	
	inline void StepPhysics() {
		Vector2D Temp = Pos;
		Vector2D NewVelocity = (Velocity() * Real(0.98)) + Force;
		
		Pos += NewVelocity;
		Old = Temp;
		
		// Clear Collected Forces //
		Force = Vector2D(0,0);
	}
	
	inline void StepAI() {
		// Movement //
//		Vector2D TargetVector = GetTarget() - Pos;
//		Real Length = TargetVector.NormalizeRet();
//		
//		Vector2D Vel = Velocity();
//		Real Speed = Vel.NormalizeRet();
//		
//		
//		
//		if ( Length > Real(0.2) )
//			Length = Real(0.2);
//			
//		Pos += TargetVector * Length;
		
		
//		// Movement Hack //
		if ( !ReachedTarget ) {
			AddForce( (GetTarget() - Pos).Normal() * Real(0.05) );
		}
		
		if ( Target ) {
			Real Distance = Radius + Status.AttackRange + Target->Radius;
			ReachedTarget = (GetTarget() - Pos).MagnitudeSquared() < Distance * Distance;
		}
		else if ( Leader ) {
			if ( Leader->Target ) {
				Real Distance = Radius + Status.AttackRange + Leader->Target->Radius;
				ReachedTarget = (GetTarget() - Pos).MagnitudeSquared() < Distance * Distance;				
			}
			else {
				Real Distance = Radius + Status.AttackRange + Leader->Radius;
				ReachedTarget = (GetTarget() - Pos).MagnitudeSquared() < Distance * Distance;
			}
		}
		else {
			Real Distance = Radius + Status.AttackRange + Real(4);
			ReachedTarget = (GetTarget() - Pos).MagnitudeSquared() < Distance * Distance;
		}
	}
	
	inline void Step() {
		StepPhysics();
		StepAI();
	}
	
	inline void Draw() {
		if ( Brain == BR_HERO ) {
			if ( !ReachedTarget )
				gfxDrawCross( GetTarget(), 5, RGB_GREEN );
			else
				gfxDrawCross( GetTarget(), 3, RGB_GREY );
			
			gfxDrawCircle( Pos, Radius, RGB_PURPLE );
			
			gfxDrawCircle( Pos, Radius + Status.AttackRange, RGB_GREY );
		}
		else if ( Brain == BR_TROOP ) {
			gfxDrawCircle( Pos, Radius, RGB_SKY );
			
			gfxDrawCircle( Pos, Radius + Status.AttackRange, RGB_GREY );
		}
		else
			gfxDrawCircle( Pos, Radius, RGB_RED );
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cExitPortal { 
public:
	Vector2D Pos;
	Real Radius;

public:
	inline cExitPortal( const Vector2D& _Pos, const Real _Radius = 16 ) :
		Pos( _Pos ),
		Radius( _Radius )
	{
	}
	
public:
	inline void Step() {
		
	}
	
	inline void Draw() { 
		gfxDrawCircle( Pos, Radius, RGB_YELLOW );
	}
};
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
							cEntity( Map.Element[idx].Center, cEntity::BR_HERO, 12 )
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
						// Leadership hack //
						Entity.back().Leader = &Entity[CurrentHero];
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
						Entity.back().State = cEntity::ST_ENGAGED;
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
			Entity[CurrentHero].TargetPos = Camera.Mouse;
			Entity[CurrentHero].Target = 0;
			Entity[CurrentHero].ReachedTarget = false;
			
			for ( size_t idx = 0; idx < Entity.size(); idx++ ) {
				if ( idx == CurrentHero )
					continue;
					
				if ( Entity[idx].Brain < cEntity::BR_CLICKABLE )
					continue;
				
				if ( Test_Point_Vs_Sphere2D( Camera.Mouse, Entity[idx].Pos, Entity[idx].Radius ) ) {
					Entity[CurrentHero].Target = &Entity[idx];
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
			// Step all un-touched Entities //
			for ( size_t idx2 = idx+1; idx2 < Entity.size(); idx2++ ) {
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
//						// If the other guy is my leader //
//						if ( Entity[idx].Leader == &Entity[idx2] ) {
//							// Since E2 is my leader, make my mass not affect him //
//							E1Mass = 0;
//						}
//						else if ( Entity[idx2].Leader == &Entity[idx] ) {
//							// Since E1 is my leader, make my mass not affect him //
//							E2Mass = 0;
//						}
						
						// If the other guy is my target //
						if ( Entity[idx].Target == &Entity[idx2] ) {
							// Since E2 is my target, my mass shouldn't affect him //
							E1Mass = 0;
						}
						else if ( Entity[idx2].Target == &Entity[idx] ) {
							// Since E1 is my target, my mass shouldn't affect him //
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
					}
					
					// Sum the Masses //
					Real MassSum = E1Mass + E2Mass;
					
					// Move the positions //					
					Entity[idx].Pos -= (Line * Diff) * (Real::One - (E1Mass / MassSum));
					Entity[idx2].Pos += (Line * Diff) * (Real::One - (E2Mass / MassSum));
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
