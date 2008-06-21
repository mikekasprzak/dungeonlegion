// - ------------------------------------------------------------------------------------------ - //
#ifndef __Entity_H__
#define __Entity_H__
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
// Statistical constants? //
class cStatus {
public:
	int HP, MaxHP;
	int Attack;
	int Defense;
	
	Real AttackRange;
	
	Real EngageRange;
	Real EscapeRange;
	
	// ActionRate - How long between each action
	// Initative - How quickly you can perform an action initially?

	// AttackCount - How many attacks you get 
	// AttackRate - How long between each attack (multiple attacks only)

	// Swing Time?
	// Speed

	
	// Things for identifying enhancements //

public:
	cStatus() :
		HP(12),
		MaxHP(12),
		Attack(2),
		Defense(1),
		
		AttackRange( 3 ),
		EngageRange( 32 ),
		EscapeRange( 96 )
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
		//ST_WAITING,
		ST_ESCAPING,
		//ST_MOVING,
		//ST_FOLLOWING,
		//ST_ENGAGING,
		ST_ATTACKING,
		
				
		ST_END
	};
	size_t State;
	
	// AI Brain Type //
	enum {
		BR_NULL = 0,
		BR_HERO,
		BR_TROOP,
		
		BR_CLICKABLE, // Everything above this you can click on //
		
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

	int EngagableTargets;


public:
	cEntity( const Vector2D& _StartPos, const size_t _BrainType = BR_NULL, const Real _Radius = 6 ) :
		Pos( _StartPos ),
		Old( _StartPos ),
		Radius( _Radius ),
		
		State( ST_IDLE ),
		Brain( _BrainType ),
		
		Leader( 0 ),
		TargetPos( _StartPos ),
		Target( 0 ),
		ReachedTarget( true ),
		EngagableTargets( 0 )
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
	inline const Vector2D& GetTargetPos() const {
		if ( Target )
			return Target->Pos;
		// Note: This is temporary.  Once leaders can give orders, my target is always my target. //
		else if ( Leader ) {
			if ( Leader->Target )
				return Leader->Target->Pos;
			else
				return Leader->Pos;
		}
		else
			return TargetPos;
	}
	
	// Return who I'm engaging //
	inline const cEntity* GetTarget() const {
		// Note: This is temporary.  Once leaders can give orders, my target is always my target. //
		if ( Leader ) {
			if ( Leader->Target )
				return Leader->Target;
		}
		return Target;
	}
	
	// Determine if something is within my Attack Range //
	inline bool IsWithinAttackRange( const Vector2D& VsPos, const Real VsRadius ) const {
		Vector2D Diff = VsPos - Pos;
		Real RadiusSum = Radius + VsRadius + Status.AttackRange;
		RadiusSum *= RadiusSum;
		
		return Diff.MagnitudeSquared() < RadiusSum;
	}
	
	inline bool IsWithinAttackRange( const cEntity& Vs ) const {
		return IsWithinAttackRange( Vs.Pos, Vs.Radius );
	}

	// Determine if something is within my Engage Range (how close for me to go fight it) //
	inline bool IsWithinEngageRange( const Vector2D& VsPos, const Real VsRadius ) const {
		Vector2D Diff = VsPos - Pos;
		Real RadiusSum = Radius + VsRadius + Status.EngageRange;
		RadiusSum *= RadiusSum;
		
		return Diff.MagnitudeSquared() < RadiusSum;
	}
	
	inline bool IsWithinEngageRange( const cEntity& Vs ) const {
		return IsWithinEngageRange( Vs.Pos, Vs.Radius );
	}

	// Determine if something is within my Escape Range (how before I stop chasing it) //
	inline bool IsWithinEscapeRange( const Vector2D& VsPos, const Real VsRadius ) const {
		Vector2D Diff = VsPos - Pos;
		Real RadiusSum = Radius + VsRadius + Status.EscapeRange;
		RadiusSum *= RadiusSum;
		
		return Diff.MagnitudeSquared() < RadiusSum;
	}
	
	inline bool IsWithinEscapeRange( const cEntity& Vs ) const {
		return IsWithinEscapeRange( Vs.Pos, Vs.Radius );
	}

	
	inline bool IsEngaged() const {
		//return State == cEntity::ST_ATTACKING;
		if ( Target != 0 ) {
			return IsWithinAttackRange( *Target );
		}
		return false;
	}
	
public:	
	inline void StepPhysics() {
		Vector2D Temp = Pos;
		Vector2D NewVelocity = (Velocity() * Real(0.9)) + Force;
		
		Pos += NewVelocity;
		Old = Temp;
		
		// Clear Collected Forces //
		Force = Vector2D(0,0);
	}
	
	inline void StepAI() {
		// Movement //
		if ( !ReachedTarget ) {
			AddForce( (GetTargetPos() - Pos).Normal() * Real(0.2) );
		}
		
		if ( Target ) {
			Real Distance = Radius + Status.AttackRange + Target->Radius;
			ReachedTarget = (GetTargetPos() - Pos).MagnitudeSquared() < Distance * Distance;
		}
		else if ( Leader ) {
			if ( Leader->Target ) {
				Real Distance = Radius + Status.AttackRange + Leader->Target->Radius;
				ReachedTarget = (GetTargetPos() - Pos).MagnitudeSquared() < Distance * Distance;				
			}
			else {
				Real Distance = Radius + Status.AttackRange + Leader->Radius;
				ReachedTarget = (GetTargetPos() - Pos).MagnitudeSquared() < Distance * Distance;
			}
		}
		else {
			Real Distance = Radius + Status.AttackRange + Real(4);
			ReachedTarget = (GetTargetPos() - Pos).MagnitudeSquared() < Distance * Distance;
		}
	}
	
	inline void Step() {
		StepPhysics();
		StepAI();
	}
	
	inline void Draw() {
		//gfxDrawCircle( Pos, Radius + Status.EngageRange, RGB_ORANGE );
		
		if ( !Status.IsAlive() ) {
			gfxDrawX( Pos, Radius, RGB_RED );
			
			gfxDrawCircle( Pos, Radius, RGB_RED );
		}
		else if ( Brain == BR_HERO ) {
			if ( !ReachedTarget )
				gfxDrawX( GetTargetPos(), 5, RGB_GREEN );
			else
				gfxDrawX( GetTargetPos(), 3, RGB_GREY );
			
			gfxDrawCircle( Pos, Radius, RGB_PURPLE );
			
			gfxDrawCircle( Pos, Radius + Status.AttackRange, RGB_GREY );
		}
		else if ( Brain == BR_TROOP ) {
			if ( Leader == 0 )
				gfxDrawCircle( Pos, Radius, RGB_GREY );
			else
				gfxDrawCircle( Pos, Radius, RGB_SKY );
			
			gfxDrawCircle( Pos, Radius + Status.AttackRange, RGB_GREY );
		}
		else {
			gfxDrawCircle( Pos, Radius + Status.EngageRange, RGB_ORANGE );
			gfxDrawCircle( Pos, Radius + Status.EscapeRange, RGB_GREY );
			
			gfxDrawCircle( Pos, Radius, RGB_RED );
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Entity_H__ //
// - ------------------------------------------------------------------------------------------ - //
