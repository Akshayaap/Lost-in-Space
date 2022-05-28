#pragma once
#include <SDL.h>
#include "..\math\Vec2.h"

class Vec2;
class Object
{
public:
	Object();
	Object(const Object& obj);
	Object(SDL_Renderer* renderer);
	Object(SDL_Renderer* renderer, const Vec2& pos);
	Object(SDL_Renderer* renderer, const Vec2& pos, const Vec2& v);
	Object(SDL_Renderer* renderer, const Vec2& pos, const Vec2& v, double mass);
	Object(SDL_Renderer* renderer, const Vec2& pos, const Vec2& v, double mass,double radius);
	~Object();
	virtual void Update();
	virtual void Render();
	virtual void Reset();
	virtual void Interact(const Object& obj);
	virtual void PostProcessing();

	inline void SetPos(const Vec2& pos) {
		this->pos = pos;
	}
	inline void SetVel(const Vec2& v) {
		this->v = v;
	}
	inline void SetAcc(const Vec2& acc) {
		this->acc = acc;
	}
	inline void SetOrientation(const double orientation) {
		this->orientation = orientation;
	}
	inline void SetMass(double mass) {
		this->mass = mass;
	}
	inline void SetRadius(double radius) {
		this->radius = radius;
	}
	inline void SetRenderer(SDL_Renderer* renderer) {
		this->renderer = renderer;
	}
	
	inline Vec2 GetPos()const {
		return this->pos;
	}
	inline Vec2 GetVel()const {
		return this->v;
	}
	inline Vec2 GetAcc()const {
		return this->acc;
	}
	inline double GetOrientation()const {
		return this->orientation;
	}
	inline double GetMass() {
		return this->mass;
	}
	inline double GetRadius() {
		return this->radius;
	}
	inline SDL_Renderer* GetRenderer() {
		return this->renderer;
	}

	virtual void Rotate(double t,const Vec2& pivot);
	virtual void Translate(const Vec2& dLoc);
	virtual void Scal(double s,const Vec2& center);
protected:
	Vec2 pos;
	double orientation;
	double omega;
	Vec2 v;
	Vec2 acc;
	double mass;
	double radius;
	Vec2 force;

protected:
	double fScal = 1;
	Vec2 fScalCenter = Vec2(0, 0);
	Vec2 fTrans = Vec2(0, 0);

protected:
	SDL_Renderer* renderer;
};