#include<iostream>
#include<iomanip>
#include<Windows.h>
#include<string>
using namespace std;
class node
{
public:
string name;
string contact;
string address;
node *next;
node *back;
};
class ad_book
{
node *head;
node *tail;
public:
ad_book()
{
head=NULL;
tail=NULL;
}
bool empty()
{
if (head==NULL)
{
return true;
}
else
return false;
}
void insert(string a,string b,string c)
{
node *temp=new node;
temp->name=a;
temp->contact=b;
temp->address=c;
temp->back=NULL;
temp->next=NULL;
if (empty())
{
            head=temp;
tail=temp;
        }
else
{
            tail->next=temp;
            temp->back=tail;
            tail=temp;
        }
}
void del(string d3)
{
    node *s1 = head;
    int flag = 0;

    if (empty())
    {
        cout << "Book is empty, can't delete" << endl;
        return;
    }
  
    if (head->name == d3)
    {
        if (head->next == NULL) 
        {
            delete head;
            head = tail = NULL;
        }
        else
        {
            head = head->next;
            head->back = NULL;
            delete s1;
        }
        flag = 1;
    }
    else
    {
       
        while (s1 != NULL)
        {
            if (s1->name == d3)
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
                flag = 1;
                break; 

            }
            s1 = s1->next;
        }
    }

    if (flag == 1)
    {
        cout << "\nDeletion is successful!!\n" << endl;
    }
    else
    {
        cout << "Data not found, can't delete" << endl;
    }
}

void search(string e)
{
bool found=0;
node *s2=head;
if(empty())
{
cout<<"Cannot search as book is empty!!"<<endl;
}
else
{
while(s2!=NULL)
{
if(s2->name==e)
{
cout<<"\nINFO:\nName:"<<s2->name<<endl;
cout<<"Contact No:"<<s2->contact<<endl;
cout<<"Address:"<<s2->address<<endl;
found=1;
break;
}
else
{
s2=s2->next;
}
}
if(found==0)
{
cout<<"Person not found"<<endl;
}
}
}
void editing()
{
string a,b;
char y;
if(empty())
{
cout<<"There is no data in address book!!!"<<endl;
}
else
{
do
{
bool f=false;
cout<<"Enter the name of the person whom info you want to edit:"<<endl;
   getline(cin,a);
node *d=head;
cin.ignore();
while(d!=NULL)
{
if(d->name==a)
{
cout<<"\nPerson Info:\nName:"<<d->name<<endl;
cout<<"Contact No:"<<d->contact<<endl;
cout<<"Addresss: "<<d->address<<endl;
cout<<"\nWhat do you want to edit?\n1. Name\n2. Contact no\n3. Address"<<endl;
       char x;
       cin>>x;
       switch(x)
       {
         case ('1'):
  {
cout<<"Enter the new Name:";
cin.ignore();
getline(cin,b);
d->name=b;
f=true;
   }
   break;
       case('2'):
  {
cout<<"Enter the new Contact no:";
cin.ignore();
getline(cin,b);
d->contact=b;
f=true;
   }
  break;
      case('3'):
   {
cout<<"Enter the new Address:";
cin.ignore();
getline(cin,b);
d->address=b;
f=true;
   }
    break;
       default:
       {
         cout<<"You have entered the wrong choice !!!"<<endl;
       }
      }
cin.ignore();
      if(f==true)
     {
        cout<<"After editing Info is:\nName:"<<d->name<<endl;
        cout<<"Contact No:"<<d->contact<<endl;
        cout<<"Address: "<<d->address<<endl;
     }
break;
     }

else
{
d=d->next;
}
}
if (f==false)
{
cout<<"Cannot edit the Info. This person is not found!"<<endl;
}
cout<<"\nDo you wish to edit more info's? If yes then press 1:"<<endl;
cin>>y;
cin.ignore();
}
while (y=='1');
}
}
void display()
{
node *d=head;
int i=0;
cout << left << setw(5) << "No" << setw(35) << "Name" << setw(28) << "CONTACT NO" <<setw(25) << "ADDRESS" << endl;
cout << "---------------------------------------------------------------------------------------\n";
while(d!=NULL)
{
i++;
cout<<left<<setw(5)<<i<<setw(35)<<d->name<<setw(25)<<d->contact<<setw(18)<<d->address<<endl;
d=d->next;
}
}

};
int _tmain(int argc, _TCHAR* argv[])
{
string a,x,y,z,dl,con;
ad_book b;
char c,d,e;
cout<<"\n\n\n\n\t\t\t\t\t###################################"<<endl;
    cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
    cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
    cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
    cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
    cout<<"\t\t\t\t\t#*******ADDRESS BOOK SYSTEM*******#"<<endl;
    cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
    cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
    cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
    cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
    cout<<"\t\t\t\t\t###################################"<<endl;
Sleep(1500);
    system("cls");
int attempt=3;
    while (attempt>0)
    {
cout<<"\n\n\n\n\t\t\t\t\tEnter the Password:";
cin>>a;
attempt--;
if(a=="3705")
{
system("cls");
   cout<<"\n\n\n\n\t\t\t\t\t###################################"<<endl;
   cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
   cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
   cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
   cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
   cout<<"\t\t\t\t\t#*****WELCOME TO ADDRESS BOOK*****#"<<endl;
   cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
   cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
   cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
   cout<<"\t\t\t\t\t#"<<setw(34)<<"#"<<endl;
   cout<<"\t\t\t\t\t###################################"<<endl;
Sleep(1500);
        system("cls");
        do
{
cout<<"\n\n\t\t\t\t!!!!!!!!!!ADDRESS BOOK MENU!!!!!!!!!!\n\n\n"<<endl;
            cout<<"\t\t\t"<<left<<setw(30)<<"1. Add contact";
            cout<<"2. Show all the contacts\n\n"<<endl;
            cout<<"\t\t\t"<<left<<setw(30)<<"3. Edit contact";
            cout<<"4. Delete contact\n\n"<<endl;
       cout<<"\t\t\t"<<left<<setw(30)<<"5. Search contact";
            cout<<"6. Exit"<<endl;
cin>>c;
cin.ignore();
system("cls");
switch(c)
{
case('1'):
{
do
{
cout<<"Enter the name:";
getline(cin,x);
cout<<"Enter the contact no:";
getline(cin,y);
cout<<"Enter the address:";
getline(cin,z);
b.insert(x,y,z);
cout<<"\n\t\t\tInformation saved successfully!!"<<endl;
cout<<"Do you want to add more info? If yes then press 1:"<<endl;
cin>>d;
cin.ignore();
}
while (d=='1');
}
break;
case('2'):
{
b.display();
}
break;
case('3'):
{
b.editing();
}
break;
case('4'):
{
cout<<"enter the name of person whom info you want to delete"<<endl;
getline(cin,dl);
                b.del(dl);
}
break;
case('5'):
{
cout<<"enter name of person which you are searching:"<<endl;
getline(cin,con);
b.search(con);
}
break;
case('6'):
{
cout<<"\n\n\n\n\t\tYou have reached the end!\n\t\t\tExiting the program."<<endl;
}
break;
default:
     cout<<"Invalid choice! Please enter a valid option."<<endl;
}
if(c!=6)
 {
  cout<<"\nDo you want to go back to the home page? If yes then press 2:"<<endl;
 cin>>e;
 system("cls");
 cin.ignore();
}
}
while(c!=6 && e=='2');
cout<<"\n\n\n\n\n\t\t\t\t\tYou have reached the end!!"<<endl;
break;
}
else
{
system("cls");
cout<<"Try again.You have"<<attempt<<" left"<<endl;
}
}

system("pause");
return 0;
}
