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
//class cParticle {
//public:
//	Vector2D Pos, Old;
//	Real Radius;
//	
//	Vector2D Force;
//
//	
//	int Polarity;
//
//public:
//	cParticle( const Vector2D& _StartPos, const Vector2D& _Direction, const int _Polarity = 0 ) :
//		Pos( _StartPos ),
//		Old( _StartPos - _Direction ),
//		Radius( 4 ),
//		Polarity( _Polarity )
//	{
//	}
//	
//	// TODO: Add constructor that takes a PolyMapElement or Generator, and does the random calculation //
//
//public:
//	inline const Vector2D Velocity() {
//		return (Pos - Old);
//	}
//	
//	inline void AddForce( const Vector2D& _Force ) {
//		Force += _Force;
//	}
//	
//	inline void ApplyReflection( const Vector2D& _ContactNormal ) {
//		// Calculate the Reflection //
//		Real ReflectionStrength = (Velocity() * _ContactNormal) * Real(2);
//		
//		// Reflect only if you oppose the direction of the Contact Normal //
//		if ( ReflectionStrength > Real::Zero ) {
//			// Apply the reflection to Old Position //
//			Old += ReflectionStrength * _ContactNormal;
//		}
//	}
//public:	
//	inline void Step() {
//		Vector2D Temp = Pos;
//		Vector2D NewVelocity = (Velocity() * Real(0.98)) + Force;
//		//Vector2D NewVelocity = Velocity() + Force;
//		Real Speed = NewVelocity.NormalizeRet();
//		if ( Speed < Real(0.4) )
//			Speed = Real(0.4);
//		
//		Pos += NewVelocity * Speed;
//		Old = Temp;
//		
//		// Clear Collected Forces //
//		Force = Vector2D(0,0);
//	}
//	
//	inline void Draw() { 
//		gfxDrawCircle( Pos, Radius, RGB_PURPLE );
//	}
//};
// - ------------------------------------------------------------------------------------------ - //
//class cGenerator {
//public:
//	Vector2D Pos;
//	Real Radius;
//	
//	Vector2D Direction;
//	
//	int Count;
//public:
//	// Clock/Generation Mechanisms //
//	bool Enabled;
//	int Ticks;
//	int TicksUntilNextSpawn;
//	
//	inline bool StepClock() {
//		if ( Enabled ) {
//			Ticks++;
//			if ( TicksUntilNextSpawn == Ticks ) {
//				if ( Count > 0 ) {
//					Count--;
//					
//					Ticks = 0;
//					return true;	
//				}
//			}
//		}
//		return false;
//	}
//
//
//public:
//	inline cGenerator( const Vector2D& _Pos, const Real _Radius, const int _Count ) :
//		Pos( _Pos ),
//		Radius( _Radius ),
//		Direction( Vector2D( 0, -1 ) ),
//		Count( _Count ),
//		
//		Enabled( true ),
//		Ticks( 0 ),
//		TicksUntilNextSpawn( 60 )
//	{
//	}
//	
//	inline cGenerator( const cPolyMapElement& Element ) :
//		Pos( Element.Center ),
//		Radius( 12 ),
//		Direction( Vector2D( -1, -2 ).Normal() ),
//		Count( 30 ),
////		Radius( Element.Data[0].f ),
////		Direction( Vector2D( 0, -1 ) ),
////		Count( Element.Data[1].i ),
//		
//		Enabled( true ),
//		Ticks( 0 ),
//		TicksUntilNextSpawn( 60 )
//	{
//	}
//
//public:
//	inline void Step() {
//		
//	}
//	
//	inline void Draw() { 
//		if ( Enabled && Count ) {
//			gfxDrawCircle( Pos, ((Ticks>>2) == 0) ? Radius - Real(2) : Radius, RGB_SKY );
//		}
//		else {
//			gfxDrawCircle( Pos, Radius, RGB_BLUE );			
//		}
//	}
//};
// - ------------------------------------------------------------------------------------------ - //
class cStatus {
public:
	int HP, MaxHP;
	int Attack;
	int Defense;
	
	Real AttackRange;
	
	// Things for identifying enhancements //
	
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
		
				
		ST_END
	};
	size_t State;
	
	
	// AI Variables //
	cEntity* Leader;
	Vector2D TargetPos;
	cEntity* Target;


public:
	cEntity( const Vector2D& _StartPos ) :
		Pos( _StartPos ),
		Old( _StartPos ),
		Radius( 6 ),
		
		State( ST_IDLE ),
		
		Leader( 0 ),
		TargetPos( _StartPos ),
		Target( 0 )
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
	
public:	
	inline void Step() {
		Vector2D Temp = Pos;
		Vector2D NewVelocity = (Velocity() * Real(0.98)) + Force;
		
		Pos += NewVelocity;
		Old = Temp;
		
		// Clear Collected Forces //
		Force = Vector2D(0,0);
		
		// Movement Hack //
		AddForce( (GetTarget() - Pos).Normal() * Real(0.05) );
	}
	
	inline void Draw() { 
		gfxDrawCross( GetTarget(), 3, RGB_GREEN );
		
		gfxDrawCircle( Pos, Radius, RGB_PURPLE );
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cHero {
public:
	// Physics Variables//
	Vector2D Pos, Old;
	Real Radius;
	
	Vector2D Force;
	
	bool Inside;

public:
	// Distinction Variables //
	cStatus Status;
	
	// AI Variables //
	Vector2D Target;



public:
	cHero( const Vector2D& _StartPos ) :
		Pos( _StartPos ),
		Old( _StartPos ),
		Radius( 6 ),
		Target( _StartPos )
	{
		Inside = false;
	}

public:
	inline const Vector2D Velocity() {
		return (Pos - Old);
	}
	
	inline void AddForce( const Vector2D& _Force ) {
		Force += _Force;
	}
	
	inline void ApplyReflection( const Vector2D& _ContactNormal ) {
		// Calculate the Reflection //
		Real ReflectionStrength = (Velocity() * _ContactNormal) * Real(2);
		
		// Reflect only if you oppose the direction of the Contact Normal //
		if ( ReflectionStrength > Real::Zero ) {
			// Apply the reflection to Old Position //
			Old += ReflectionStrength * _ContactNormal;
		}
	}
public:	
	inline void Step() {
		Vector2D Temp = Pos;
		Vector2D NewVelocity = (Velocity() * Real(0.98)) + Force;
		
		Pos += NewVelocity;
		Old = Temp;
		
		// Clear Collected Forces //
		Force = Vector2D(0,0);
		
		
		AddForce( (Target - Pos).Normal() * Real(0.05) );
	}
	
	inline void Draw() { 
		gfxDrawCross( Target, 3, RGB_GREEN );
		
		if ( Inside )
			gfxDrawCircle( Pos, Radius, RGB_PURPLE );
		else
			gfxDrawCircle( Pos, Radius, RGB_YELLOW );
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
class cEnemy {
public:
	// Physics Variables//
	Vector2D Pos, Old;
	Real Radius;
	
	Vector2D Force;

public:
	// Distinction Variables //
	cStatus Status;
	
	// AI Variables //
	Vector2D Target;



public:
	cEnemy( const Vector2D& _StartPos ) :
		Pos( _StartPos ),
		Old( _StartPos ),
		Radius( 8 ),
		Target( _StartPos )
	{
	}

public:
	inline const Vector2D Velocity() {
		return (Pos - Old);
	}
	
	inline void AddForce( const Vector2D& _Force ) {
		Force += _Force;
	}
	
	inline void ApplyReflection( const Vector2D& _ContactNormal ) {
		// Calculate the Reflection //
		Real ReflectionStrength = (Velocity() * _ContactNormal) * Real(2);
		
		// Reflect only if you oppose the direction of the Contact Normal //
		if ( ReflectionStrength > Real::Zero ) {
			// Apply the reflection to Old Position //
			Old += ReflectionStrength * _ContactNormal;
		}
	}
public:	
	inline void Step() {
		Vector2D Temp = Pos;
		Vector2D NewVelocity = (Velocity() * Real(0.98)) + Force;
		
		Pos += NewVelocity;
		Old = Temp;
		
		// Clear Collected Forces //
		Force = Vector2D(0,0);
		
		
		AddForce( (Target - Pos).Normal() * Real(0.05) );
	}
	
	inline void Draw() { 
		gfxDrawCircle( Pos, Radius, RGB_RED );
	}
};
// - ------------------------------------------------------------------------------------------ - //
//class cMagnet {
//public:
//	Vector2D Pos;
//	Real Radius;
//	
//	int Polarity;
//public:
//	inline cMagnet( const Vector2D& _Pos, const Real _Radius, const int _Polarity ) :
//		Pos( _Pos ),
//		Radius( _Radius ),
//		Polarity( _Polarity )
//	{
//	}
//	
//	inline cMagnet( const cPolyMapElement& Element ) :
//		Pos( Element.Center ),
//		Radius( 12 ),
//		Polarity( 1 )
////		Radius( Element.Data[0].f ),
////		Polarity( Element.Data[1].i )
//	{
//	}	
//
//public:
//	inline void Step() {
//		
//	}
//	
//	inline void Draw() { 
//		gfxDrawCircle( Pos, Radius, RGB_ORANGE );
//	}
//};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cGame {
public:
	cPolyMap Map;

	std::vector<cImpulse> Impulse;
//	std::vector<cParticle> Particle;

	std::vector<cHero> Hero;
	
	std::vector<cEnemy> Enemy;
		
	std::vector<cEntity> Entity;
	int CurrentHero;
	
	std::vector<cExitPortal> ExitPortal;
		
//	std::vector<cGenerator> Generator;
//	std::vector<cCollector> Collector;
//	std::vector<cMagnet> Magnet;
	
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
						printf(" + Bounding Rectangle Set\n");
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
						Hero.push_back( cHero(Map.Element[idx].Center) );
						//CurrentHero = Entity.size() - 1;
						printf(" + Added Hero\n");
						break;
					}
					case 2: {
						// Exit Portal //
						ExitPortal.push_back( cExitPortal(Map.Element[idx].Center) );
						printf(" + Added Exit Portal\n");
						break;
					}
					case 11: {
						// Enemy //
						Enemy.push_back( cEnemy(Map.Element[idx].Center) );
						printf(" + Added Enemy\n");
						break;
					}
					case 12: {
						// Enemy //
						Entity.push_back( cEntity(Map.Element[idx].Center) );
						printf(" + Added Entity\n");
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
		if ( mouse_b == 1 )
			if ( Entity.size() )
				Entity[CurrentHero].TargetPos = Camera.Mouse;
		
		
		// Step all Generators //
//		for ( size_t idx = 0; idx < Generator.size(); idx++ ) {
//			Generator[idx].Step();
//			if ( Generator[idx].StepClock() ) {
//				Vector2D Offset = 
//					Generator[idx].Direction.Tangent() * 
//					(((Real::Random() * Real(2)) - Real::One) * Generator[idx].Radius );
//				Particle.push_back( cParticle( Generator[idx].Pos + Offset, Generator[idx].Direction ) );
//			}
//		}
		// Step all Collectors //
		for ( size_t idx = 0; idx < ExitPortal.size(); idx++ ) {
			ExitPortal[idx].Step();
			// TODO: Add Impulse 
			Impulse.push_back( 
				cImpulse(
					ExitPortal[idx].Pos,
					0, -0.01,
					48, 0
					)
				);
		}
//		// Step all Magnets //
//		for ( size_t idx = 0; idx < Magnet.size(); idx++ ) {
//			Magnet[idx].Step();
//			// TODO: Add Impulse //
//			Impulse.push_back( 
//				cImpulse(
//					Magnet[idx].Pos,
//					0, -0.02,
//					128, 0
//					)
//				);
//		}
//
//
		// Step all Heroes //
		for ( size_t idx = 0; idx < Hero.size(); idx++ ) {
			Hero[idx].Step();

			// Apply Impulses //
			for ( size_t idx2 = 0; idx2 < Impulse.size(); idx2++ ) {
				Hero[idx].AddForce( Impulse[idx2].GetForce( Hero[idx].Pos ) );
			}
			
			// Test for Collisions Vs. Polygons //
			Hero[idx].Inside = false;
			for ( size_t idx2 = 0; idx2 < Collision.size(); idx2++ ) {
				//if ( !TestCircleVsPolygon2D( Hero[idx].Pos, Hero[idx].Radius, &Collision[idx2]->Vertex[0], Collision[idx2]->Vertex.size() ) )
				if ( Test_Point_Vs_CapsuleChain2D( Hero[idx].Pos, &Collision[idx2]->Vertex[0], Collision[idx2]->Vertex.size(), Hero[idx].Radius ) )
				{
					Hero[idx].Inside = true;
				
					Vector2D EdgePoint = Nearest_InnerEdgePoint_On_CapsuleChain2D( 
						Hero[idx].Pos,
						&Collision[idx2]->Vertex[0],
						Collision[idx2]->Vertex.size(),
						Hero[idx].Radius
						);
					
					Hero[idx].Pos = EdgePoint;
				}
			}
		
			// Test for Collisions Vs. Collectors //
			for ( size_t idx2 = 0; idx2 < ExitPortal.size(); idx2++ ) {
				if ( Test_Point_Vs_Sphere2D( Hero[idx].Pos, ExitPortal[idx2].Pos, ExitPortal[idx2].Radius ) ) {
					
					// Kill Hero //
					Hero.erase( Hero.begin() + idx );
					idx--;
					break;
				}
			}
		}

		// Step all Enemies //
		for ( size_t idx = 0; idx < Enemy.size(); idx++ ) {
			Enemy[idx].Step();

			// Apply Impulses //
			for ( size_t idx2 = 0; idx2 < Impulse.size(); idx2++ ) {
				Enemy[idx].AddForce( Impulse[idx2].GetForce( Enemy[idx].Pos ) );
			}
			
			// Test for Collisions Vs. Polygons //
//			for ( size_t idx2 = 0; idx2 < Collision.size(); idx2++ ) {
//				if ( !TestCircleVsPolygon2D( Enemy[idx].Pos, Enemy[idx].Radius, &Collision[idx2]->Vertex[0], Collision[idx2]->Vertex.size() ) ) {
//					Vector2D EdgePoint = NearestPointOnEdgeOfPolygon2D( 
//						Enemy[idx].Pos,
//						//Enemy[idx].Radius,
//						&Collision[idx2]->Vertex[0],
//						Collision[idx2]->Vertex.size()
//						);
//					
//					Enemy[idx].Pos = EdgePoint;
//				}
//			}
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
		
			// Test for Collisions Vs. Collectors //
			for ( size_t idx2 = 0; idx2 < ExitPortal.size(); idx2++ ) {
				if ( Test_Point_Vs_Sphere2D( Entity[idx].Pos, ExitPortal[idx2].Pos, ExitPortal[idx2].Radius ) ) {
					
					// Kill Hero //
					Entity.erase( Entity.begin() + idx );
					idx--;
					break;
				}
			}
		}

		// TODO: Figure out the pushing rules //
		// Step all Heroes Vs Enemies //
//		for ( size_t idx = 0; idx < Hero.size(); idx++ ) {
//			// Step all Enemies //
//			for ( size_t idx2 = 0; idx2 < Enemy.size(); idx2++ ) {
//			
//			}
//		}	

		// Remove all Impulses //
		Impulse.clear();
	}
	
	
	inline void Draw() {
		// Draw all Heroes //
		for ( size_t idx = 0; idx < Hero.size(); idx++ ) {
			Hero[idx].Draw();
		}
	
		// Draw all Enemies //
		for ( size_t idx = 0; idx < Enemy.size(); idx++ ) {
			Enemy[idx].Draw();
		}

		// Draw all Entities //
		for ( size_t idx = 0; idx < Entity.size(); idx++ ) {
			Entity[idx].Draw();
		}
		
		
		// Draw all ExitPortals //
		for ( size_t idx = 0; idx < ExitPortal.size(); idx++ ) {
			ExitPortal[idx].Draw();
		}

		// Draw all Particles //
//		for ( size_t idx = 0; idx < Particle.size(); idx++ ) {
//			Particle[idx].Draw();
//		}
		
		
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
