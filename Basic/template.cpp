#include <iostream>

class Base
{
	public:
		Base() {
			std::cout << "Base Constructor" << std::endl;
		}

		Base(const Base&) {
			std::cout << "Base Copy Constructor" << std::endl;
		}

		virtual ~Base() {
			std::cout << "Base Deconstructor" << std::endl;
		}

		virtual void print() {
			std::cout << "Base print ..." << std::endl;
		}
};

class Derive : public Base
{
	public:
		Derive() {
			std::cout << "Derive Constructor" << std::endl;
		}

		Derive(const Derive&) {
			std::cout << "Derive Copy Constructor" << std::endl;
		}

		~Derive() {
			std::cout << "Derive Deconstructor" << std::endl;
		}

		void print() {
			std::cout << "Derive print ..." << std::endl;
		}
};

template <class T> class any
{
	public:
		any(T* t) {
			mObject = t;
		}

		void print() {
			mObject->print();
		}

	private:
		T* mObject;
};

void print(any<Base> base)
{
	base.print();
}

int main(int argc, char** argv)
{
	Derive derive;
	any<Base> a(&derive);
	print(a);

	return 0;
}
