#ifndef __LQueue_defined__
#define __LQueue_defined__
#include <iostream>
#include <exception>
#include <string>
#include <utility>

using namespace std;

#pragma region

class LQueue {
private:
	struct QItem {
		int info;
		QItem *next;
		string priority;
		QItem(int info_, string priority_) : info(info_), next(nullptr), priority(move(priority_)) {}
	};
	QItem *front, *rear_h, *rear_m, *rear_l;
	unsigned size_h, size_m, size_l;
	void Erase();
public:
	LQueue();
	LQueue(LQueue&);
	~LQueue();
	void operator =(const LQueue &);
	void Push_high(const int &);
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

#pragma endregion

#pragma region
void LQueue::Erase() {
	while (front != nullptr) {
		Pop();
	};
	size_m = 0;
	size_h = 0;
	size_l = 0;
}

LQueue::LQueue() {
	front = nullptr;
	rear_m = nullptr;
	rear_h = nullptr;
	rear_l = nullptr;
	size_h = 0;
	size_m = 0;
	size_l = 0;
}

LQueue::LQueue(LQueue& Q) {
	if (this == &Q) {
		return;
	}
	Erase();
	QItem* tmp = Q.front;
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

LQueue::~LQueue() {
	Erase();
}

void LQueue::operator = (const LQueue& Q) {
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

void LQueue::Push_high(const int& info_) {
	QItem* tmp = new QItem(info_, "High");
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

void LQueue::Push_medium(const int& info_) {
	QItem* tmp = new QItem(info_, "Medium");
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

void LQueue::Push_low(const int& info_) {
	QItem* tmp = new QItem(info_, "Low");
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

void LQueue::Pop() {
	if (front == nullptr) {
		return;
	}
	if (front->priority == "High")
		size_h--;
	if (front->priority == "Medium")
		size_m--;
	if (front->priority == "Low")
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

string LQueue::GetFirst() const {
	if (size_h + size_m + size_l == 0)
		throw exception("Impossible to execute \ GetFirst: queue is empty");
	else {
		string first;
		first = "First element is " + to_string(front->info) + " Priority is " + front->priority;
		return first;
	}
}

bool LQueue::IsEmpty() const {
	return (size_h + size_m + size_l == 0);
}

unsigned LQueue::GetSize() const {
	return size_h + size_m + size_l;
}

unsigned LQueue::GetSizeM() const {
	return size_m;
}

unsigned LQueue::GetSizeH() const {
	return size_h;
}

unsigned LQueue::GetSizeL() const {
	return size_l;
}

ostream& LQueue::WriteToStream(ostream& stream)
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

#pragma endregion

#pragma region
int main()
{
	int l, h, m, n;
	LQueue queue;
	cout << "Enter number of high priority numbers: " << '\n';
	cin >> h;
	cout << "Enter number of mid priority numbers: " << '\n';
	cin >> m;
	cout << "Enter number of low priority numbers: " << '\n';
	cin >> l;
	cout << "Enter high priority numbers: ";
	for (int i = 0; i < h; i++) {
		cin >> n;
		queue.Push_high(n);
	}
	cout << "Enter mid priority numbers: ";
	for (int i = 0; i < m; i++) {
		cin >> n;
		queue.Push_medium(n);
	}
	cout << "Enter low priority numbers: ";
	for (int i = 0; i < l; i++) {
		cin >> n;
		queue.Push_low(n);
	}
	if (queue.IsEmpty())
		cout << "There is no elements in queue";
	else {
		cout << "Number of high priority elements: " << queue.GetSizeH() << '\n';
		cout << "Number of mid priority elements: " << queue.GetSizeM() << '\n';
		cout << "Number of low priority elements: " << queue.GetSizeL() << '\n';
		cout << "Number of elements: " << queue.GetSize() << '\n';
	}
	
	queue.GetFirst();
	cout << "Queue is ";
	queue.WriteToStream(cout);

	queue.Pop();

	cout << '\n' << "After poping 1st element queue is ";
	queue.WriteToStream(cout);
}
#pragma endregion