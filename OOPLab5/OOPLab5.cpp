#include <iostream>
#include <conio.h>
using namespace std;

class Animal {
public:
	void sound() {//����� sound -- ����� �������������� ��� ������������ �������� ������������ ������
		printf("Animal :: sound()\n");
	}
	virtual void size() {//����������� ����� size
		printf("Animal :: size()\n");
	}
	virtual string classname() {
		return "Animal";
	}
	virtual bool isA(string who) {
		return (who == "Animal");
	}
};
class Cat : public Animal {//�������� ������ ������� �� Animal
public:
	void caatch() {//����� caatch
		printf("Cat caatch\n");//
	}
	void sound()  {//����� sound -- ���������� ��������������� ������
		printf("meow\n");
	}
	void size() {//����������� ����� size
		printf("Small\n");
	}
	string classname() {
		return "Cat";
	}
	bool isA(string who) {
		return (who == "Cat" || Animal::isA(who));
	}
};
class Dog : public Animal {//�������� ��� ������ ������ 
public:
	void chase() {//����� chase
		printf("Dog chase\n");
	}
	void sound() {//����� sound -- ���������� ��������������� ������
		printf("wow\n");
	}
	void size() {//����������� ����� size
		printf("Big\n");
	}
	string classname() {
		return "Dog";
	}
	bool isA(string who) {
		return (who == "Dog" || Animal::isA(who));
	}
};
/*����� ���������� ����������� �����, � ����� �������*/
class Base {
public:
	virtual void foo() {
		printf("Base\n");
	}
	//��� �������� ��������� �������� �������� ��� ���������� � �������
	Base() {//����������� �� ���������
		printf("����������� Base\n");
	}
	Base(Base& obj) {//���������� �����������
		printf("���������� Base& obj\n");
	}
	/*Base(Base* obj) {//���������� �����������
		printf("���������� Base* obj\n");
	}*/
	virtual ~Base() {
		printf("���������� Base::Base()\n");
	}

};
class Desc : public Base {
public:
	void foo(){
		printf("Desc\n");
	}
	//��� �������� ��������� �������� �������� ��� ���������� � �������
	Desc() {//����������� �� ���������
		printf("����������� Desc\n");
	}
	//���������� �����������
	Desc(Desc& obj) {
		printf("���������� Desc& obj\n");
	}
	/*Desc(Desc* obj) {//���������� �����������
		printf("���������� Desc* obj\n");
	}*/
	~Desc() {
		printf("���������� Desc::Desc()\n");
	}
	
};
class Desc2 : public Desc {
public:
	void foo() {
		printf("Desc2\n");
	}
	~Desc2(){
		printf("���������� Desc2::Desc2()\n");
	}
	Desc2() {//����������� �� ���������
		printf("����������� Desc2\n");
	}
	/*Desc2(Desc* obj) {//���������� �����������
		printf("���������� Desc* obj\n");
	}*/
	//���������� �����������
	Desc2(Desc2& obj) {
		printf("���������� Desc2& obj\n");
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
	
	printf("������������ ������� \n");
	printf("�������� ������ �������(������������ ������):\n");
	Dog dog;//��� �������� ������ ������ �������
	dog.sound();//���������� ����� ������ �������
	
	printf("��������� ������� ������ ������� � ���������� �������� ������(������� ����� �� �������������):\n");
	Animal* cat = new Cat();//�������� ������ ������ ������� � ��������� �������� ������
	cat->sound();//���������� ����� �������� ������

	printf("\n");
	printf("\n");

	printf("����������� ������ \n");
	dog.size();//������� ��������� ��������� �������� �����, ������� ���������� ����� ������������ � ��������� ��������. 
	cat->size();//���������� �� ���� � ���������� ������ ������ ��������� ������ ������ �������

	printf("\n");
	printf("\n");

	printf("����� ����� ����������\n");
	Base* f1 = new Desc();//��� ��� � ������ ������ ����� �������� � ��������������� virtual
	f1->foo();//�� � �������� ������ �������  ����� ���������� ���� �����
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


	printf("1. �������� �� �������������� � ������� string\n");
	cout << a1->classname() << endl;//���������� ����� ���� ������, ������� ���������� ������
	cout << a2->classname() << endl;//��� ��� classname - ����������� �����

	printf("2. �������� �� �������������� � ������� isA\n");

	if (a1->isA("Cat"))//a1 ������ ������ Animal, ������� �� �������� �� Cat �� �������
		printf("�������� ��������\n");
	else printf("�������� �� ��������\n");


	if (a2->isA("Cat"))//a2 �������� �������
		printf("�������� ��������\n");
	else printf("�������� �� ��������\n");

	printf("������������ ���������� �����\n");
	((Cat*)a1)->caatch();
	printf("���������� ���������� ����� - dinamic_cast\n");
	
	Animal* zoo[2];
	for (int i = 0; i < 2; i++) {
		zoo[i] = new Animal();
	}
	Dog* dd = dynamic_cast<Dog*>(zoo[1]);//� ������� dynamic_cast �������� � ���� ������� ������ Dog
	dd->chase();//� ������ ����� ������� ������������� ����� ������ Dog

	printf("�������� �������� � ��������� �������\n");
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