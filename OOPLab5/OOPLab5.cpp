#include <iostream>
#include <conio.h>
using namespace std;

class Animal {
public:
	void sound() {//метод sound -- будет использоваться для демонстрации ситуаций перекрывания метода
		printf("Animal :: sound()\n");
	}
	virtual void size() {//виртуальный метод size
		printf("Animal :: size()\n");
	}
	virtual string classname() {
		return "Animal";
	}
	virtual bool isA(string who) {
		return (who == "Animal");
	}
};
class Cat : public Animal {//создание класса потомка от Animal
public:
	void caatch() {//метод caatch
		printf("Cat caatch\n");//
	}
	void sound()  {//метод sound -- происходит ПЕРЕОПРЕДЕЛЕНИЕ метода
		printf("meow\n");
	}
	void size() {//виртуальный метод size
		printf("Small\n");
	}
	string classname() {
		return "Cat";
	}
	bool isA(string who) {
		return (who == "Cat" || Animal::isA(who));
	}
};
class Dog : public Animal {//создание еще одного класса 
public:
	void chase() {//метод chase
		printf("Dog chase\n");
	}
	void sound() {//метод sound -- происходит ПЕРЕОПРЕДЕЛЕНИЕ метода
		printf("wow\n");
	}
	void size() {//виртуальный метод size
		printf("Big\n");
	}
	string classname() {
		return "Dog";
	}
	bool isA(string who) {
		return (who == "Dog" || Animal::isA(who));
	}
};
/*Когда вызывается виртуальный метод, а когда базовый*/
class Base {
public:
	virtual void foo() {
		printf("Base\n");
	}
	//Для проверки механизма передачи объектов как параметров в функции
	Base() {//конструктор по умолчанию
		printf("Конструктор Base\n");
	}
	Base(Base& obj) {//копирующий конструктор
		printf("Констуктор Base& obj\n");
	}
	/*Base(Base* obj) {//копирующий конструктор
		printf("Констуктор Base* obj\n");
	}*/
	virtual ~Base() {
		printf("Деструктор Base::Base()\n");
	}

};
class Desc : public Base {
public:
	void foo(){
		printf("Desc\n");
	}
	//Для проверки механизма передачи объектов как параметров в функции
	Desc() {//конструктор по умолчанию
		printf("Конструктор Desc\n");
	}
	//копирующий конструктор
	Desc(Desc& obj) {
		printf("Констуктор Desc& obj\n");
	}
	/*Desc(Desc* obj) {//копирующий конструктор
		printf("Констуктор Desc* obj\n");
	}*/
	~Desc() {
		printf("Деструктор Desc::Desc()\n");
	}
	
};
class Desc2 : public Desc {
public:
	void foo() {
		printf("Desc2\n");
	}
	~Desc2(){
		printf("Деструктор Desc2::Desc2()\n");
	}
	Desc2() {//конструктор по умолчанию
		printf("Конструктор Desc2\n");
	}
	/*Desc2(Desc* obj) {//копирующий конструктор
		printf("Констуктор Desc* obj\n");
	}*/
	//копирующий конструктор
	Desc2(Desc2& obj) {
		printf("Констуктор Desc2& obj\n");
	}
};

void func1(Base obj) { 
	printf("func1\n");
};
void func2(Base* obj) { 
	printf("func2\n");
};
void func3(Base& obj) { 
	printf("func3\n");
};


int main() {
	setlocale(LC_ALL, "Russian");
	
	printf("Перекрывание методов \n");
	printf("Создание класса потомка(перекрывание метода):\n");
	Dog dog;//при создании обекта класса потомка
	dog.sound();//вызывается метод класса потомка
	
	printf("Помещение объекта класса потомка в переменную базового класса(базовый метод не перекрывается):\n");
	Animal* cat = new Cat();//помещаем объект класса потомка в пееменную базового класса
	cat->sound();//вызывается метод базового класса

	printf("\n");
	printf("\n");

	printf("Виртуальные методы \n");
	dog.size();//функции выполняет «наиболее» дочерний метод, который существует между родительским и дочерними классами. 
	cat->size();//независимо от того в переменной какого класса находится объект класса потомка

	printf("\n");
	printf("\n");

	printf("Какой метод вызывается\n");
	Base* f1 = new Desc();//так как в классе предке метод объявлен с идентификатором virtual
	f1->foo();//то у объектов класса потомка  будет вызываться свой метод
	delete f1;

	Desc* f2 = new Desc2();
	f2->foo();
	delete f2;

	Base* f3 = new Desc2();
	f3->foo();
	delete f3;

	printf("\n");
	printf("\n");


	Animal *a1 = new Animal();
	Animal* a2 = new Cat();


	printf("1. Проверка на принадлежность с помощью string\n");
	cout << a1->classname() << endl;//вызывается метод того класса, который определяет объект
	cout << a2->classname() << endl;//так как classname - виртуальный метод

	printf("2. Проверка на принадлежность с помощью isA\n");

	if (a1->isA("Cat"))//a1 объект класса Animal, поэтому он проверку на Cat не пройдет
		printf("Проверка пройдена\n");
	else printf("Проверка не пройдена\n");


	if (a2->isA("Cat"))//a2 проверку пройдет
		printf("Проверка пройдена\n");
	else printf("Проверка не пройдена\n");

	printf("Небезопасное приведение типов\n");
	((Cat*)a1)->caatch();
	printf("Безопасное приведение типов - dinamic_cast\n");
	
	Animal* zoo[2];
	for (int i = 0; i < 2; i++) {
		zoo[i] = new Animal();
	}
	Dog* dd = dynamic_cast<Dog*>(zoo[1]);//с помощью dynamic_cast приводим к типу объекта класса Dog
	dd->chase();//и теперь можем вызвать специфический метод класса Dog

	printf("Передача объектов в параметры функции\n");
	Base base1;
	func1(base1);
	printf("\n");
	
	Base* base2 = new Base();
	func2(base2);
	printf("\n");

	Base base3;
	func3(base3);
	printf("\n");

	Desc desc1;
	func1(desc1);
	printf("\n");

	Desc* desc2 = new Desc();
	func2(desc2);
	printf("\n");

	Desc desc3;
	func3(desc3);
	printf("\n");

	return 0;
}