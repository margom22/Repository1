#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Car {
private:
	string brand;
	string model;

public:
	Car(string brand_, string model_){
		brand = brand_;
		model = model_;
	}

	void display() {
		cout << "Brand: " << brand << " Model: " << model << "\n";
	}

	~Car() {
	//cout << "brand " << brand << " " << "model " << model << "\n";
	}
};

int main() {

	vector<Car> car;

	ifstream file("lab1.txt");
	if (file.is_open()) {
		cout << "file is opened\n";
	}
	else {
		cout << "file is NOT opened\n";
	}

	string Model, Brand;
	while (file >> Brand >> Model) {
		
		car.push_back(Car(Brand, Model));
	}

	file.close();

	for (int i = 0; i < car.size(); ++i) {
		car[i].display();
	}

	return 0;
}
