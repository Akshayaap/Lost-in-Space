#pragma once
#include <SDL.h>
#include "..\math\Vec2.h"

class ObjInterface;
class Object
{
public:
	Object();
	Object(const Object& obj);
	Object(SDL_Renderer* renderer);
	Object(SDL_Renderer* renderer, const Vec2& pos);
	Object(SDL_Renderer* renderer, const Vec2& pos, const Vec2& v);
	Object(SDL_Renderer* renderer, const Vec2& pos, const Vec2& v, double mass);
	Object(SDL_Renderer* renderer, const Vec2& pos, const Vec2& v, double mass, double radius);
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
	virtual void SetRenderer(SDL_Renderer* renderer);

	inline void SetOmega(double omega) {
		this->omega = omega;
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
	inline double GetMass() const{
		return this->mass;
	}
	inline double GetOmega() {
		return this->omega;
	}
	inline double GetRadius() const{
		return this->radius;
	}
	inline SDL_Renderer* GetRenderer()const {
		return this->renderer;
	}
	inline ObjInterface* GetSlave()const {
		return this->slave;
	}
	inline Vec2 GetForce()const {
		return this->force;
	}
	inline double GetFScal() const {
		return this->fScal;
	}
	inline Vec2 GetFTran() const {
		return this->fTrans;
	}
	inline Vec2 GetFScalCenter()const {
		return this->fScalCenter;
	}

	virtual void Rotate(double t, const Vec2& pivot);
	virtual void Translate(const Vec2& dLoc);
	virtual void Scal(double s, const Vec2& center);
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
	Vec2 fTrans;
	Vec2 fScalCenter;

protected:
	SDL_Renderer* renderer;
	ObjInterface* slave = nullptr;
};