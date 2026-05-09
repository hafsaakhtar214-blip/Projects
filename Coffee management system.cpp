#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <string>
using namespace std;

class node
{
public:
string name;
double price;
double sale;
int quantity;
node* next;
node* back;
};

class coffee_shop
{
node* head;
node* tail;

public:
coffee_shop()
{
head = NULL;
tail = NULL;
}
bool empty()
{
return head == NULL;
}
void insert(string a, double b, int qty = 0)
{
node* temp = new node;
temp->name = a;
temp->price = b;
temp->quantity = qty;
temp->sale = 0;
temp->back = NULL;
temp->next = NULL;
if (empty())
{
head = temp;
tail = temp;
}
else
{
tail->next = temp;
temp->back = tail;
tail = temp;
}
}
void insert_bill(double sale)
{
node* temp = new node;
temp->sale = sale;
temp->back = NULL;
temp->next = NULL;
if (empty())
{
head = temp;
tail = temp;
}
else
{
tail->next = temp;
temp->back = tail;
tail = temp;
}
}
coffee_shop bill(coffee_shop& fb)
{
coffee_shop cf;
int b, c = 0;
char f;
node* d = head;
while (d != NULL)
{
d = d->next;
c++;
}
do
{
cout << "\nPlease enter your choice:";
cin >> b;
if (c<b || b<1)
{
cout << "You have put an invalid option!!" << endl;
}
else
{
d = head;
for (int i = 1; i < b; i++)
{
d = d->next;
}
int e;
cout << "Enter the quantity:";
cin >> e;
double f = e * d->price;
cf.insert(d->name, f, e);
}
cout << "\nDo you want to add something more to your cart? If yes, press 1:";
cin >> f;
} while (f == '1');
cout << "Do you wish to see the bill? If yes, press 2:" << endl;
char g;
cin >> g;
system("cls");
cout << "\n\n\n\n\t\t\t\t\t\t****GENERATING BILL****";
Sleep(1500);
system("cls");
if (g == '2')
{
node* d1 = cf.head;
int i = 0;
cout << "\n\t\t\t\t\tCOFFEE SHOP!!!!";
cout << "\n\n\t\t\t\t\t*****BILL*****\n\n" << endl;
cout << "Your Order no is: 1023" << endl;
cout << "Cashier: MS" << endl;
cout << "Payment Method: Cash" << endl;
cout << "------------------------------------------------------------------\n";
cout << left << setw(5) << "No" << setw(32) << "Name" << setw(20) << "QUANTITY" << setw(20) << "Price" << endl;
cout << "------------------------------------------------------------------\n";
double x = 0;
while (d1 != NULL)
{
i++;
cout << left << setw(5) << i << setw(35) << d1->name << setw(18) << d1->quantity << setw(18) << d1->price << endl;
x += d1->price;
d1 = d1->next;
}
cout << "------------------------------------------------------------------\n";
cout << "\nSub Total: " << x << endl;
double z = x * 0.18;
cout << "GST Tax = " << z << endl;
cout << "Service Fee = 1" << endl;
double k = x + z + 1;
cout << "Total Bill = " << k << endl;
fb.insert_bill(k);
char y;
cin >> y;
system("cls");
cout << "\n\n\n\n\t\t\t\tTHANK YOU FOR VISITING SHOP!!\n\t\t\t\t\tPLEASE VISIT US AGAIN SOON!!\n\n" << endl;
}
return fb;
}
void del(string nm)
{
if (empty())
{
cout << "Menu is empty, can't delete." << endl;
return;
}
if (head->name == nm)
{
node* d1 = head;
head = head->next;
if (head != NULL)
{
head->back = NULL;
}
else
{
tail = NULL;
}
delete d1;
cout << "Deletion is successful!" << endl;
return;
}
node* s1 = head->next;
while (s1 != NULL)
{
if (s1->name == nm)
{
if (s1 == tail)
{
tail = s1->back;
tail->next = NULL;
}
else
{
s1->back->next = s1->next;
s1->next->back = s1->back;
}
delete s1;
cout << "Deletion is successful!" << endl;
return;
}
s1 = s1->next;
}
cout << "Item not found, can't delete." << endl;
}
void search(string it)
{
bool found = false;
node* s2 = head;
while (s2 != NULL)
{
if (s2->name == it)
{
cout << "Item found:" << endl;
cout << "Name: " << s2->name << endl;
cout << "Price: " << s2->price << endl;
found = true;
 break;
}
s2 = s2->next;
}
if (!found)
{
cout << "Item not found!" << endl;
}
}
void display_billing()
{
if (empty())
{
cout << "No bills found!" << endl;
 return;
}
node* d = head;
int i = 1;
double sum = 0;
cout << "\t\tCUSTOMER BILLS\n" << endl;
cout << "CUSTOMER\t\tSALE" << endl;
while (d != NULL)
{
cout << i << "\t\t\t" << d->sale << endl;
sum += d->sale;
d = d->next;
i++;
}
cout << "Total customers = " << (i - 1) << endl;
cout << "Total Sale = " << sum << endl;
}
void display_item()
{
node* d = head;
int i = 0;
cout<<"\t\t\t***MENU***\n\n";
cout << left << setw(5) << "No" << setw(35) << "Name" << setw(10) << "Price" << endl;
cout << "-----------------------------------------------------\n";
while (d != NULL)
{
 i++;
cout << left << setw(5) << i << setw(35) << d->name << setw(10) << d->price << endl;
d = d->next;
}
}
};

int _tmain(int argc, _TCHAR* argv[])
{
coffee_shop item, cust, bil;
int a;
char y;
char w;
item.insert("CAPPACINO", 115);
item.insert("LATTE", 130);
item.insert("COLD COFFEE", 220);
item.insert("CHOCOLATE BISCUIT (4 pcs)", 180);
item.insert("MACAROON (4 pcs)", 300);
item.insert("BROWNIE", 140);
item.insert("PASTRY (CREAM OR CHOCOLATE)", 160);
item.insert("SUGAR PUFFS (250gm)", 400);
item.insert("SALTED PUFFS (250gm)", 350);
cout << "\n\n\n\n\t\t\tWELCOME\n\t\t\t\t  TO\n\t\t\t\t\tMY\n\t\t\t\t\t     COFFEE\n\t\t\t\t\t\t     SHOP!!!" << endl;
Sleep(1500);
system("cls");
cout << "\n\n\n\t  We have a variety of delicious items on our menu." << endl;
cout << "\t\t  Enjoy your time here!" << endl;
Sleep(1500);
system("cls");
do
{
cout << "\n\t\t\t****HOME PAGE****\n1.DISPLAY\n2.ADMIN\n3.EXIT\n";
cout<<"Enter your choice:"<<endl;
cin >> a;
system("cls");
if (a == 1)
{
item.display_item();
item.bill(bil);
}
else if (a == 2)
{
string f;
cout << "\n\n\n\n\t\t\t\t\tEnter the password:";
cin >> f;
cin.ignore();
if (f =="2005")
{
system("cls");
cout << "\n\n\n\n\n\t\t\t\t\t****Welcome to admin panel!!****" << endl;
Sleep(1500);
system("cls");
char b;
do
{
cout << "\t\t\tADMIN PANEL!!" << endl;
cout << "1. Add Product" << endl;
cout << "2. Search Product" << endl;
cout << "3. Delete Product" << endl;
cout << "4. Total Sale" << endl;
cout << "5. Product Display" << endl;
cout<<"\nEnter your choice:"<<endl;
cin >> b;
system("cls");
cin.ignore();
if(b=='1')
{
char z;
do
{
string it;
double b;
char y;
cout<<"Enter the product name:"<<endl;
getline(cin,it);
cout<<"Enter the price of the product:"<<endl;
cin>>b;
item.insert(it,b);
cout<<"\nItem is added successfully!!"<<endl;
cout<<"\nDo you want to add more items? If yes then press 1:"<<endl;
cin>>z;
cin.ignore();
cout<<endl;
}
while (z=='1');
cout<<"Do you want to see the menu.Press 1:"<<endl;
cin>>y;
if(y=='1')
{
system("cls");
item.display_item();
}
}
else if (b == '2')
{
char z;
 string ti;
do
{
 cout << "Enter name of item for whom you are searching:" << endl;
 getline(cin, ti);
 item.search(ti);
cout<<"\nDo you want to search more items? If yes then press 1:"<<endl;
cin>>z;
cout<<endl;
cin.ignore();
}
while (z=='1');
}
else if (b == '3')
{
string mn;
char y,z;
do
{
 cout << "Enter name of item you want to delete:" << endl;
getline(cin, mn);
 item.del(mn);
cout<<"\nDo you want to delete more items? If yes then press 1:"<<endl;
cin>>z;
cout<<endl;
cin.ignore();
}
while (z=='1');
cout<<"Do you want to see the menu.Press 1:"<<endl;
cin>>y;
if(y=='1')
{
system("cls");
item.display_item();
}
}
 else if (b == '4')
{
	bil.display_billing();
 }
else if(b=='5')
{
item.display_item();
}
else
cout<<"You have entered the wrong choice!!"<<endl;
cout<<"\nDo you want to go back to the admin panel.Press 2:"<<endl;
cin>>w;
system("cls");
}
while(w=='2');
}
 }
 cout << "Do you wish to go back to the Homepage? If yes, press 1:" << endl;
 cin >> y;
system("cls");
 } while (y == '1');
cout<<"\n\n\n\t\t\t\tYou have reached the end of program!!\n\n"<<endl;
    system("pause");
    return 0;
}
