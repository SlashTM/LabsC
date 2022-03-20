#ifndef __PQueue_defined__
#define __PQueue_defined__
#pragma once
#include <iostream>
#include <exception>
#include <string>

using namespace std;

class PQueue {
private:
	struct QItem {
		int info;
		QItem* next;
		int priority;
		QItem(int info_, int priority_) : info(info_), next(nullptr), priority(priority_) {}
	};
	QItem* front, * rear_h, * rear_m, * rear_l;
	unsigned size_h, size_m, size_l;
	void Erase();
	void Move(QItem*& a, QItem*& b);
public:
	PQueue();
	PQueue(PQueue&& Q) noexcept : front(move(Q.front)), rear_h(move(Q.rear_h)), rear_l(move(Q.rear_l)), rear_m(move(Q.rear_m)),
	size_h(move(Q.size_h)), size_l(move(Q.size_l)), size_m(move(Q.size_m)) {
		Q.front = nullptr;
		Q.rear_h = nullptr;
		Q.rear_m = nullptr;
		Q.rear_l = nullptr;
		Q.size_h = 0;
		Q.size_l = 0;
		Q.size_m = 0;
	}
	~PQueue();
	void operator =(const PQueue&);
	void Push_high(const int&);
	void Push_medium(const int&);
	void Push_low(const int&);
	void Pop();
	string GetFirst() const;
	bool IsEmpty()const;
	unsigned GetSize() const;
	unsigned GetSizeL() const;
	unsigned GetSizeM() const;
	unsigned GetSizeH() const;
	ostream& WriteToStream(ostream&);
};

#endif

