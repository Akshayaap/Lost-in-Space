#pragma once
#include <array>

//My own Implementation of Fast Queue
//
template <class _Ty,int SIZE>
class Queue
{
private:
	std::array<_Ty, SIZE> container;
	int front = -1;
	int rear = -1;

public:
	Queue();
	~Queue();

	inline _Ty& operator [] (int index) {
		return container[index];
	}

	void Push(_Ty data);
	_Ty Pop();
	void Clear();
	inline bool IsEmpty();
};

