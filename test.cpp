#include <vector>

int main() {
	std::vector<int> asdf = {
		1,
		3,
		7
	};

	asdf.erase(asdf.begin() + 5);
}
