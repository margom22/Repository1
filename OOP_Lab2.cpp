#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Product {
private:
	string name;
	int amount;
	double price;
	
public:

	Product(string _name = "", int _amount = 0, double _price = 0.00)
		: name(_name), amount(_amount), price(_price) {} //список инициализации

	// Геттеры
	string getName() const { return name; }
	int getAmount() const { return amount; }
	double getPrice() const { return price; }

	// Сеттеры
	void setName(const string& _name) { name = _name; }
	void setAmount(int _amount) { amount = _amount; }
	void setPrice(double _price) { price = _price; }

	//ввод данных с клавиатуры
	void inputFromKeyboard() {
		cout << "name: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');//очистка буффера строки
		getline(cin, name);

		cout << "amount: ";
		cin >> amount;

		cout << "price: ";
		cin >> price;
	}
	
};

class Store {
private: 
	vector<Product> products; 
public:
	//конструктор по умолчанию
	Store() {
		cout << "Store is open!" << endl;
	}

	// Перегруженный конструктор для добавления товаров в теле программы
	Store(const Product& product) {
		products.push_back(product);
		cout << "Store is open with: " << product.getName() << "\n";
	}



	// Метод для добавления товара через ввод с клавиатуры
	void addProductFromInput() {
		Product newProduct;
		newProduct.inputFromKeyboard();
		addProduct(newProduct);
	}

	// Метод для добавления товара в контейнер
	void addProduct(const Product& product) {
		products.push_back(product);
		cout << "Product added: " << product.getName() << "\n";
	}

	// Метод - показать все товары
	void showProducts() {
		if (products.empty()) {
			cout << "Store is empty!\n";
			return;
		}

		for (const auto& product : products) {
			cout << "- " << product.getName() << " " << product.getAmount() << " (" << product.getPrice() << " rub.)\n";
		}
		cout << "Products available: " << products.size() << "\n";
	}

	// Деструктор
	~Store() {
		cout << "Resourses are cleared\n";
	}

};

void MenuDisplay() {
	cout << "Welcome! Enter a number to:" << endl;
	cout << "1. Add a product" << endl;
	cout << "2. Show available products" << endl;
	cout << "3. Exit" << endl;
	cout << '\n';
}

int main() {

	Store store;
	Product product;
	MenuDisplay();

	//
	//Product existingProduct("Apple", 15, 120.0);
	//Store store2(existingProduct);

	int comm = 0;
	while (comm != 3) {
		cin >> comm;
		switch (comm) {
			case 1: 
				store.addProductFromInput();
				cout << '\n'; 
				break;

			case 2: store.showProducts();; cout << '\n'; break;

			case 3: cout << "Goodbye!" << endl; cout << '\n'; break;

			default: cout << "instructions unclear" << endl; cout << '\n'; break;
		}
	} 
		
	return 0;
}
