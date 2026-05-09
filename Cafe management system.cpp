#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<string>
using namespace std;
struct customer{
	int number;
	int bill;
};

void front()
{
	cout<<"\n\n\t\t\tWELCOME\n\t\t\t\t  TO\n\t\t\t\t\tMY\n\t\t\t\t\t\tCAFE"<<endl;
	Sleep(2000);
	system("cls");
    cout << "\n\n\n\t  We have a variety of delicious items on our menu." << endl;
    cout << "\t\t  Enjoy your time here!" << endl;
}
void display(string a[], int b[], int c)
{
	cout<<left<<setw(2)<<"NO."<<left<<setw(30)<<"ITEMS:"<<setw(31)<<"PRICE:"<<endl;
	for(int i=0;i<c;i++)
	{
	  cout<<left<<setw(2)<<i<<"."<<left<<setw(30)<<a[i]<<setw(31)<<b[i]<<endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	string it[30];
	int a,b,d,e,f,cost=0,add=0,n=23;
	int idex=0,count=1;
	customer c[300];
	int pr[30];
	it[0]="Coffee";
	it[1]="Tea";
	it[2]="Green Tea";
	it[3]="Omelet";
	it[4]="Naan(Rogni)";
	it[5]="Paratha";
	it[6]="Halwa Puri(Single)";
	it[7]="Samosa[Aloo]";
	it[8]="Roll[Aloo]";
	it[9]="Chips";
	it[10]="Samosa Chaat";
	it[11]="Chana Chaat";
	it[12]="Dahi Bhalla";
	it[13]="Fruit Chaat";
	it[14]="Russian Salad";
	it[15]="Biryani";
	it[16]="Chicken Pulao";
	it[17]="Pakora";
	it[18]="Kachori";
	it[19]="Chowmein";
	it[20]="Chicken Karahi";
	it[21]="Mali Boti(Chicken)";
	it[22]="Curry(1 plate)";
	pr[0]=130;
	pr[1]=70;
	pr[2]=100;
	pr[3]=70;
	pr[4]=50;
	pr[5]=100;
	pr[6]=120;
	pr[7]=40;
	pr[8]=40;
	pr[9]=100;
	pr[10]=120;
	pr[11]=120;
	pr[12]=150;
	pr[13]=150;
	pr[14]=220;
	pr[15]=250;
	pr[16]=240;
	pr[17]=100;
	pr[18]=80;
	pr[19]=150;
	pr[20]=950;
	pr[21]=1250;
	pr[22]=150;
	front();
	Sleep(2000);
	system("cls");
	do
	{
		cout<<"\n\t\t\t****HOME PAGE****\n1.DISPLAY\n2.ADMIN\n3.EXIT\n";
	    cin>>a;
	    system("cls");

		if(a==1)
	  {
		display(it,pr,n);
		do
		{
		cout<<"\nEnter your choice:"<<endl;
		cin>>b;
		cout<<"\nEnter the quantity:"<<endl;
		cin>>d;
		for( int j=0;j<23;j++)
		{
			if(b==j)
			{
				add=pr[j]*d;
				cost=cost+add;
				
			}
		}
		cout<<"Total bill="<<cost<<endl;
		cout<<"\nDo you want to add something more in your cart? If yes then press 1 otherwise press 0:";
		cin>>e;

	    }
		while(e==1);

		c[idex].bill=cost;
		c[idex].number=count;
		count++;
		idex++;
		cost=0;
		system("cls");
		cout<<"Do you want to go back to first page? If yes then press 2 otherwise press 3:";
		cin>>f;
		system("cls");
		if(f==3)
		{
			cout<<"\n\n\n\t\t\tTHANKYOU FOR VISTING OUR CAFE\n\t\t\t\tPLEASE VISIT US AGAIN SOON"<<endl;
		}
	}

			string b,d;
			int ad,di,g,h,i,j,k,s,attempt=3;
			if(a==2)
			{
				cout<<"\n\n\n\n\t\t\t\t\t\t**ADMIN PANEL**"<<endl;
				Sleep(1000);
				system("cls");
				cout<<"ENTER YOUR NAME:"<<endl;
				cin>>b;
				system("cls");
				while(attempt>0)
				{
				cout<<"ENTER THE ADMIN PASSWORD:"<<endl;
                cin >> g;
			    attempt--;
				
                 if (g == 4506)
				  {
				    system("cls");
                    cout << "\n\n\n\n\t\t\t\tWelcome " <<b<< "!\n\t\t\t\t\tYou are now in the admin panel" << endl;
					Sleep(1500);
					system("cls");
				do
				{
				cout<<"\n\t\t\t****Admin Menu****"<<endl;
				cout<<"1.Add new product"<<endl;
				cout<<"2.Remove product"<<endl;
				cout<<"3.Show all products"<<endl;
				cout<<"4.Search the product"<<endl;
				cout<<"5.Customer detail"<<endl;
		        cin>>h;
				system("cls");
				switch(h)
				{
				case(1):
				{
					cout<<"How many products do you want to add?"<<endl;
					cin>>i;
					cout<<"Enter the following details:"<<endl;
					for(int l=0;l<i;l++)
					{
						cout<<"Product name:"<<endl;
					    cin>>it[n];
						cout<<"Product price:"<<endl;
						cin>>pr[n];
						n++;
					}
					cout<<"Do you want to display the products? if yes the press 0:";
					cin>>di;
					if(di==0)
					{
					display(it,pr,n);
					}
				}
					break;
				case(2):
				{
				  do
				 {
					display(it,pr,n);
					cout<<"Which product do you want to remove?\nEnter its serial no:";
					cin>>j;
					if(j>=0 && j<n)
					{
					cout<<"Enter its name:"<<endl;
					cin>>d;
					if(it[j]==d)
					  { 
						  for(int r=j;r<n-1;r++)
						  {
							  it[r]=it[r+1];
							  pr[r]=pr[r+1];
						  }
						  it[n-1]="";
						  pr[n-1]=0;
						  n--;
						  system("cls");
						  display(it,pr,n);
					}
					else 
						cout<<"Entered name does not match the product name given at your entered serial no.Product not removed\n";
					}
					else
						cout<<"Invalid serial no!PLease enter a valid serial no"<<endl;
					cout<<"Do you want to remove more product? If yes then press 1:";
					cin>>k;
					system("cls");
					}
					while(k==1);
				}
					break;
				case(3):
				{
					display(it,pr,n); 
				}
				break;
				case(4):
				{
					cout<<"Enter the serial no of the product you are looking of:"<<endl;
					cin>>s;
					cout<<endl;
					cout<<left<<setw(2)<<"NO."<<left<<setw(30)<<"ITEMS:"<<setw(31)<<"PRICE:"<<endl;
					for(int sr=0;sr<n;sr++)
					{
					if(sr==s)
					{
					    cout<<left<<setw(2)<<sr<<"."<<left<<setw(30)<<it[sr]<<setw(31)<<pr[sr]<<endl;
					}
					}
				}
				break;
				case(5):
				{
					cout<<left<<setw(30)<<"CUSTOMERS"<<setw(30)<<"BILLS"<<endl;
					for(int sh=0;sh<idex;sh++)
					{
						cout<<left<<setw(30)<<c[sh].number<<setw(30)<<c[sh].bill<<endl;
					}
				}
				break;
			  }
			cout<<"Do you want to go admin panel menu again? If yes then press 1:"<<endl;
			cin>>ad;
			system("cls");
			}
			while(ad==1);
			system("cls");
			break;
       }
	    else
	   {
       cout << "WRONG PASSWORD. TRY AGAIN.YOU HAVE " << attempt<< " ATTEMPT(S) LEFT."<< endl;
	   }
	   }
		cout<<"Do you want to go to home page. if yes then press 2:";
		cin>>f;
		system("cls");
	   }
	    }
	   while(f==2);

	   if(a==3)
	   {
		   cout<<"\n\t\t\t\tGOOD BYE"<<endl;
	   }
      	
		
	system("pause");
	return 0;
}