#include <iostream>
#include <vector>

using namespace std;

class A
{
	public:
		A(int a) {
			cout << "Construct ..." << a << endl;
			mA = a;
		}

		A(const A& a) {
			cout << "Copy Construct ..." << a.mA << endl;
			mA = a.mA;
		}

		A& operator=(const A& a) {
			cout << "Assignment ..." << a.mA << endl;
			mA = a.mA;
			return *this;
		}

		~A() {
			cout << "Deconstruct ..." << mA << endl;
		}

		int getA() const {
			return mA;
		}

	private:
		int mA;
};

int main(int argc, char** argv)
{
	vector<A> value;
	{
		A a(1);
		A b(4);
		A c(5);
		value.push_back(a);
		value.push_back(b);
		value.push_back(c);
		cout << "value[0]=" << value[0].getA() << endl;
		cout << "value[1]=" << value[1].getA() << endl;
		cout << "value[2]=" << value[2].getA() << endl;
		cout << "Value Phrase1 End ..." << endl;
	}
	value.pop_back();
	cout << "Value Phrase2 End ..." << endl;

	vector<A*> point;
	{
		A* a = new A(2);
		point.push_back(a);
		a = new A(3);
		point.push_back(a);
		cout << "Point Phrase1 End ..." << endl;
	}
	for (vector<A*>::iterator it = point.begin(); it != point.end();) {
		delete *it;
		it = point.erase(it);
	}
	cout << "Point Phrase2 End ..." << endl;

	return 0;
}
