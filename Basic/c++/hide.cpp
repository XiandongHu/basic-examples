#include <iostream>

class Base
{
	public:
		Base() {
			std::cout << "Base Constructor" << std::endl;
		}

		virtual ~Base() {
			std::cout << "Base Deconstructor" << std::endl;
		}

	public:
		void func() {
			std::cout << "Base func()" << std::endl;
		}

		void func(int i) {
			std::cout << "Base func(int), i=" << i << std::endl;
		}

		virtual void func(float f) {
			std::cout << "Base func(float), f=" << f << std::endl;
		}
};

class Derive : public Base
{
	public:
		Derive() {
			std::cout << "Derive Constructor" << std::endl;
		}

		~Derive() {
			std::cout << "Derive Deconstructor" << std::endl;
		}

	public:
		virtual void func(float f) {
			std::cout << "Derive func(float), f=" << f << std::endl;
		}
};

int main(int argc, char** argv)
{
	Derive* d = new Derive();
	d->func(1);
	delete d;

	return 0;
}
