#include <iostream>
#include <string>

bool ignoreCaseEqual(char c1, char c2)
{
	return toupper(c1) == toupper(c2);
}

int main(int argc, char** argv)
{
	std::string str1 = "0a:be:dd:ff:7e:4f";
	std::string str2 = "0A:BE:DD:FF:7E:4F";

	if (str1 == str2) {
		std::cout << "case equal" << std::endl;
		return 0;
	}

	if (str1.size() == str2.size() && std::equal(str1.begin(), str1.end(), str2.begin(), ignoreCaseEqual)) {
		std::cout << "ignore case equal" << std::endl;
	} else {
		std::cout << "not equal" << std::endl;
	}

	return 0;
}
