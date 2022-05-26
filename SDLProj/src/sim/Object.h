#pragma once
#include <SDL.h>
#include "..\math\Vec2.h"

class Object
{
public:
	Object();
	Object(Vec2& pos);
	~Object();
	virtual void Update();
	virtual void Render();
	virtual void Reset();
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

	virtual void Rotate(double t);
	virtual void Translate(const Vec2& v);
	virtual void Scal(double s);
protected:
	Vec2 pos;
	double orientation;
	double omega;
	Vec2 v;
	Vec2 acc;
};