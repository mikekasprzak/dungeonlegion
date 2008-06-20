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
		Real RadiusSum = Radius + VsRadius + Status.AttackRange;
		RadiusSum *= RadiusSum;
		
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
		Vector2D NewVelocity = (Velocity() * Real(0.9)) + Force;
		
		Pos += NewVelocity;
		Old = Temp;
		
		// Clear Collected Forces //
		Force = Vector2D(0,0);
	}
	
	inline void StepAI() {
		// Movement //
		if ( !ReachedTarget ) {
			AddForce( (GetTarget() - Pos).Normal() * Real(0.2) );
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
				gfxDrawX( GetTarget(), 5, RGB_GREEN );
			else
				gfxDrawX( GetTarget(), 3, RGB_GREY );
			
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
#endif // __Entity_H__ //
// - ------------------------------------------------------------------------------------------ - //
