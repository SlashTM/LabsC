#include "PQueue.h"

void PQueue::Erase() {
	while (front != nullptr) {
		Pop();
	};
	size_m = 0;
	size_h = 0;
	size_l = 0;
}

void PQueue::Move(QItem*& a, QItem*& b)
{
	a = b;
	b = nullptr;
}

PQueue::PQueue() {
	front = nullptr;
	rear_m = nullptr;
	rear_h = nullptr;
	rear_l = nullptr;
	size_h = 0;
	size_m = 0;
	size_l = 0;
}

PQueue::~PQueue() {
	Erase();
}

void PQueue::operator = (const PQueue& Q) {
	QItem* tmp = Q.front;
	if (this == &Q) {
		return;
	}
	Erase();

	while (tmp != Q.rear_h->next) {
		Push_high(tmp->info);
		tmp = tmp->next;
	}

	while (tmp != Q.rear_m->next) {
		Push_medium(tmp->info);
		tmp = tmp->next;
	}

	while (tmp != Q.rear_l->next) {
		Push_low(tmp->info);
		tmp = tmp->next;
	}
}

void PQueue::Push_high(const int& info_) {
	QItem* tmp = new QItem(info_, 1);
	if (IsEmpty()) {
		front = tmp;
		rear_h = tmp;
	}
	if (rear_h == nullptr) {
		tmp->next = front;
		front = tmp;
		rear_h = tmp;
	}
	tmp->next = rear_h->next;
	rear_h->next = tmp;
	rear_h = tmp;
	size_h++;
}

void PQueue::Push_medium(const int& info_) {
	QItem* tmp = new QItem(info_, 2);
	if (IsEmpty()) {
		front = tmp;
		rear_m = tmp;
	}
	if (rear_m == nullptr && rear_h == nullptr) {
		tmp->next = front;
		front = tmp;
		rear_m = tmp;
	}
	if (rear_m == nullptr) {
		tmp->next = rear_h->next;
		rear_h->next = tmp;
		rear_m = tmp;
	}
	tmp->next = rear_m->next;
	rear_m->next = tmp;
	rear_m = tmp;
	size_m++;
}

void PQueue::Push_low(const int& info_) {
	QItem* tmp = new QItem(info_, 3);
	if (IsEmpty()) {
		front = tmp;
		rear_l = tmp;
	}
	if (rear_l == nullptr && rear_m == nullptr) {
		rear_h->next = tmp;
		rear_l = tmp;
	}
	if (rear_l == nullptr && rear_h == nullptr) {
		rear_m->next = tmp;
		rear_l = tmp;
	}
	if (rear_l == nullptr) {
		rear_m->next = tmp;
		rear_l = tmp;
	}
	rear_l->next = tmp;
	rear_l = tmp;
	size_l++;
}

void PQueue::Pop() {
	if (front == nullptr) {
		return;
	}
	if (front->priority == 1)
		size_h--;
	if (front->priority == 2)
		size_m--;
	if (front->priority == 3)
		size_l--;
	if (size_h == 0)
		rear_h = nullptr;
	if (size_m == 0)
		rear_m = nullptr;
	if (size_l == 0)
		rear_l = nullptr;
	QItem* tmp = front->next;
	delete front;
	front = tmp;
}

string PQueue::GetFirst() const {
	if (size_h + size_m + size_l == 0)
		throw exception("Impossible to execute \ GetFirst: queue is empty");
	else {
		string first;
		first = "First element is " + to_string(front->info) + " Priority is ";
		if (front->priority == 1) {
			first += "high";
		}
		if (front->priority == 2) {
			first += "medium";
		}
		if (front->priority == 3) {
			first += "low";
		}
		return first;
	}
}

bool PQueue::IsEmpty() const {
	return (size_h + size_m + size_l == 0);
}

unsigned PQueue::GetSize() const {
	return size_h + size_m + size_l;
}

unsigned PQueue::GetSizeM() const {
	return size_m;
}

unsigned PQueue::GetSizeH() const {
	return size_h;
}

unsigned PQueue::GetSizeL() const {
	return size_l;
}

ostream& PQueue::WriteToStream(ostream& stream)
{
	if (!IsEmpty())
	{
		QItem* tmp = front;
		while (tmp != nullptr)
		{
			stream << to_string(tmp->info);
			if (tmp->next != nullptr)
			{
				stream << ' ';
			}
			tmp = tmp->next;
		}
	}
	else
	{
		stream << "Queue is empty";
	}
	return stream;
}