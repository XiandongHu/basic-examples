#include <iostream>
#include <set>

using namespace std;

int main(int argc, char** argv)
{
	set<int> array;
	array.insert(1);
	array.insert(6);
	array.insert(3);
	pair<set<int>::iterator, bool> p = array.insert(1);
	if (p.second) {
		cout << "insert 1 success ..." << endl;
	} else {
		cout << "insert 1 failed ..." << endl;
	}
	p = array.insert(2);
	if (p.second) {
		cout << "insert 2 success ..." << endl;
	} else {
		cout << "insert 2 failed ..." << endl;
	}

	if (array.find(2) != array.end()) {
		cout << "2 found ..." << endl;
	} else {
		cout << "2 not found ..." << endl;
	}

	for (set<int>::iterator it = array.begin(); it != array.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	
	return 0;
}
