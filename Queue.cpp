#include <iostream>
#include "PQueue.h"

int main()
{
	PQueue queue;
	PQueue queue_2;
	int case_ = 1;
	int pr_;
	while (case_ != 8) {
		cout << "1)Push elements in queue\n"
			<< "2)Pop top element\n"
			<< "3)Return information about 1st element\n"
			<< "4)Check if queue is empty\n"
			<< "5)Get size\n"
			<< "6)Print queue and queue_2\n"
			<< "7)Copy from queue to queue_2\n"
			<< "8)Exit\n"
			<< "0)Clear console\n";
		cin >> case_;
		switch (case_) {
		case 1:
			int l, h, m, n;
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
			break;
		case 2:
			queue.Pop();
			break;
		case 3:
			try {
				queue.GetFirst();
			}
			catch (exception e) {
				cerr << e.what() << '\n';
			}
			break;
		case 4:
			if (queue.IsEmpty()) cout << "Queue is empty\n";
			else cout << "Queue is not empty\n";
			break;
		case 5:
			cout << "What size you want to get?\n"
				<< "1)Low elements\n"
				<< "2)Medium elements\n"
				<< "3)High elements\n"
				<< "4)All elements\n";
			cin >> pr_;
			switch (pr_)
			{
			case 1: cout << queue.GetSizeL() << '\n';
				break;
			case 2: cout << queue.GetSizeM() << '\n';
				break;
			case 3: cout << queue.GetSizeH() << '\n';
				break;
			case 4: cout << queue.GetSize() << '\n';
				break;
			default: cout << "Enter existing case please";
				break;
			}
			break;
		case 6:
			queue.WriteToStream(cout);
			cout << '\n';
			queue_2.WriteToStream(cout);
			cout << '\n';
			break;
		case 7:
			queue_2 = queue;
		case 8:
			break;
		case 0:
			system("Cls");
			break;
		default:
			cout << "Enter number of existing case";
			break;
		}
	}
}