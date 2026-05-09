#include<iostream> 
#include<iomanip> 
#include<string> 
#include<Windows.h> 
using namespace std; 
 
class music 
{protected: 
string title; 
int price; 
string artist; 
string album; 
string playtime; 
int ryear; 
public: 
music():title("\0"),price(0),artist(""),album("\0"),ryear(0),playtime("\0") 
{} 
music(string a,string b,string ab,string pt,int c,int 
d):title(a),price(d),artist(b),album(ab),playtime(pt),ryear(c) 
{} 
string get_title() 
{ 
return title; 
} 
int get_price() 
{ 
return price; 
} 
string get_artist() 
{ 
return artist; 
} 
string get_album() 
{ 
return album; 
} 
int get_pyear() 
{ 
return ryear; 
} 
string get_playtime() 
{ 
return playtime; 
} 
void set_data(string a,string ar,string al,string pt,int y, int p) 
{ 
title=a; 
price =p; 
artist=ar; 
album=al; 
playtime=pt; 
ryear=y; 
} 
virtual void input () 
{cout<<"Name: "; 
cin.ignore(); 
getline (cin, title); 
cout<<"Artist: "; 
cin.ignore(); 
getline(cin, artist); 
cout<<"Album: "; 
cin.ignore(); 
getline(cin, album); 
cout<<"Release year: "; 
cin>>ryear; 
cout<<"Playtime (in minutes): "; 
cin>>playtime; 
cout<<"Price: "; 
cin>>price; 
} 
void set_price (int p) 
{price =p; 
} 
virtual void display()=0; 
}; 
 
class cd:public music 
{protected: 
int notrack; 
public: 
cd():music(),notrack(0) 
{} 
cd(string a,string b,string ab,string pt,int c,int d,int nt):music(a,b,ab,pt,c,d),notrack(nt) 
{} 
int get_notrack() 
{return notrack; 
} 
void set_data(string a,string ar,string al,string pt,int y,int p,int nt) 
{ 
music::set_data(a,ar,al,pt,y,p); 
notrack=nt; 
} 
void input () 
{music ::input(); 
cout<<"Number of tracks: "; 
cin>>notrack;} 
void display() 
{ 
cout<<"Name:"<<title<<"\nArtist name:"<<artist<<endl; 
cout<<"Album name:"<<album<<"\nRelease year:"<<ryear; 
cout<<"\nNo of tracks in this cd:"<<notrack<<"\nPlaytime (in 
minutes):"<<playtime<<"\nPrice:"<<price<<endl; 
} 
}; 
 
class dvd: public music 
{protected: 
string regioncode; 
public: 
dvd():music(),regioncode("\0") 
{} 
dvd(string a,string b,string ab,string pt,string rc,int c,int d):music(a,b,ab,pt,c,d),regioncode(rc) 
{} 
string get_regioncode() 
{ 
return regioncode; 
} 
void set_data(string a,string ar,string al,string pt,string rc,int y, int p) 
{ 
music::set_data(a,ar,al,pt,y,p); 
regioncode=rc; 
} 
void input () 
{music :: input (); 
cout<<"Region code: "; 
getline (cin, regioncode);} 
void display() 
{ 
cout<<"Name:"<<title<<"\nArtist name:"<<artist<<endl; 
cout<<"Album name:"<<album<<"\nRelease year:"<<ryear<<"\nPlaytime (in 
minutes):"<<playtime; 
cout<<"\nRegion code:"<<regioncode<<"\nPrice:"<<price<<endl; 
} 
}; 
 
class vinyl:public music 
{protected: 
double diameter; 
double rpm; 
public: 
vinyl():music(),diameter(0.0),rpm(0) 
{} 
vinyl(string a,string b,string ab,string pt,int c,int d,double da,double 
r):music(a,b,ab,pt,c,d),diameter(da),rpm(r) 
{} 
double get_diameter() 
{ 
return diameter; 
} 
double get_rpm() 
{ 
return rpm; 
} 
void set_data(string a,string ar,string al,string pt,int y,int p,double da,double r) 
{ 
music::set_data(a,ar,al,pt,y,p); 
diameter=da; 
rpm=r; 
} 
void input () 
{music :: input (); 
cout<<"Diameter: "; 
cin>>diameter; 
cout<<"Rotations per minute: "; 
cin>>rpm;} 
void display() 
{cout<<"Name:"<<title<<"\nArtist name:"<<artist<<endl; 
cout<<"Album name:"<<album<<"\nRelease year:"<<ryear<<"\nPlaytime (in 
minutes):"<<playtime; 
cout<<"\nDiameter (in inches):"<<diameter<<"\nNo of revolutions per 
minute:"<<rpm<<"\nPrice:"<<price<<endl; 
} 
}; 
 
class casette:public music 
{protected: 
int nt; 
string tc; 
public: 
casette():music(),nt(0),tc("\0") 
{} 
casette(string a,string b,string ab,string pt,int c,int d,int n,string 
t):music(a,b,ab,pt,c,d),nt(n),tc(t) 
{} 
int get_nt() 
{return nt; 
} 
string get_tc() 
{return tc; 
} 
void set_data(string a,string ar,string al,string pt,int y,int p,int n,string t) 
{ 
music::set_data(a,ar,al,pt,y,p); 
nt=n; 
tc=t; 
} 
void input () 
{  
music :: input (); 
cout<<"Number of tracks: "; 
cin>>nt; 
cout<<"Type of caseette: "; 
cin>>tc; 
} 
void display() 
{ 
cout<<"Name:"<<title<<"\nArtist name:"<<artist<<endl; 
cout<<"Album name:"<<album<<"\nRelease year:"<<ryear; 
cout<<"\nNo of tracks in this casette:"<<nt<<"\nType of cassette:"<<tc; 
cout<<"\nPlaytime (in minutes):"<<playtime<<"\nPrice:"<<price<<endl; 
} 
}; 
 
 
class searchmusic 
{ 
protected: 
int countm; 
string tm[50]; 
string art[50]; 
int idm; 
double costm; 
double cm[50]; 
int qm[50]; 
public: 
searchmusic() 
{ 
idm=0; 
countm=0; 
costm=0.0; 
for (int i=0;i<50;i++) 
{ 
tm[i]="0"; 
art[i]="0"; 
qm[i]=0; 
cm[i]=0.0; 
} 
cd(); 
dvd(); 
casette(); 
vinyl(); 
} 
 
template <class sm> 
void searchm(sm s[], int index) { 
char c, a; 
bool found; 
do { 
found = false; 
cout << "Enter the title of the song you are looking for: "; 
cin.ignore();  
getline(cin, tm[idm]); 
for (int i = 0; i <= index; i++) { 
if (tm[idm] == s[i]->get_title()) { 
found = true; 
cout<<"Enter artist of the song you are looking for: "; 
getline(cin, art[idm]); 
if (art[idm] == s[i]->get_artist()) { 
cout << endl << "Details of the song are:" << endl; 
s[i]->display(); 
cout << "Do you want to add this track to your cart? If yes, then press 1: "; 
cin >> c; 
if (c == '1') { 
cout << "How many copies of this would you like? Please enter the quantity: "; 
cin >> qm[idm]; 
cm[idm] = qm[idm] * s[i]->get_price(); 
costm += cm[idm]; 
cout << "The item has been successfully added to the cart!" << endl; 
countm++; 
idm++; 
} 
} else  
{{cout<<"Sorry we don't have it with this artist name but we have it with anyother artist 
name.\n"; 
cout<<"Do you wish to see it?If yes then press 1:"<<endl; 
char r; 
cin>>r; 
if(r=='1') 
{ 
cout << endl << "Details of the song are:" << endl; 
s[i]->display(); 
cout << "Do you want to add this track to your cart? If yes, then press 1: "; 
cin >> c; 
if (c == '1') { 
cout << "How many copies of this would you like? Please enter the quantity: "; 
cin >> qm[idm]; 
cm[idm] = qm[idm] * s[i]->get_price(); 
costm += cm[idm]; 
cout << "The item has been successfully added to the cart!" << endl; 
countm++; 
idm++; 
} 
}} 
} 
} 
} 
if (!found) 
 { 
cout << "Sorry! This song is not available." << endl; 
} 
cout << "Do you want to search again? If yes, then press 1: "; 
cin >> a; 
system ("cls"); 
} while (a == '1'); 
} 
 
template <class ms> 
void billgm(ms *c[],int index) 
{ 
tm[idm]=c[index]->get_title(); 
cout<<"How many copies you would like to order? Please enter the quantity:"; 
cin>>qm[idm]; 
cm[idm]=qm[idm]*c[index]->get_price(); 
costm=costm+(qm[idm]*c[index]->get_price()); 
cout<<"The item has successully added into the cart!"<<endl; 
countm++; 
idm++; 
} 
double getcost() 
{return costm; 
} 
void display() 
{ 
cout<<"Total cost upto now="<<costm<<endl; 
} 
}; 
 
class shop:public searchmusic 
{ 
protected: 
int n; 
public: 
shop() 
{ 
n=0; 
searchmusic(); 
} 
void display() 
{ 
double cost; 
if(countm>-1) 
{ 
cout<<"\n\t\t\t\t\t\t***BILL***\n\n"<<endl; 
cout<<left<<setw(5)<<"NO"<<setw(47)<<"ITEMS"<<setw(50)<<"QUANTITY"<<setw(50)<<"PRIC
ES"<<endl; 
cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl; 
int count=0; 
for(int i=0;i<=countm;i++) 
{ 
if (qm[i]>0 && cm[i]>0)  
{ 
count++; 
cout<<left<<setw(3)<<count<<setw(50)<<tm[i]<<setw(50)<<qm[i]<<setw(50)<<cm[i]<<endl; 
} 
} 
cout<<"\n\nTotal bill="<<costm<<endl; 
int or=0; 
for (int i =0; i<=countm; i++) 
{or++;} 
cout<<"Order No:780"<<or<<endl; 
char s; 
string ad,name,contact; 
cout<<"\n\nWould you prefer home delivery or pickup?\nFor homedelivery press 1 and For 
pickup press 2:"<<endl; 
cin>>s; 
if(s=='1') 
{ 
cout<<"\n\nPlease enter your name:"; 
cin.ignore(); 
getline(cin,name); 
cout<<"\nPlease enter your contact no:"; 
cin.ignore(); 
getline(cin,contact); 
cin.ignore(); 
cout<<"\nPlease enter your address:"<<endl; 
getline(cin,ad); 
cin.ignore(); 
cout<<"\n\nYou will get your delivery within 2 to 3 weeks.\n\tThankyou for shopping from 
us\n\n"<<endl; 
} 
else 
cout<<"\n\n\n\t\t\tThankyou for shopping from us!Visit us again soon\n\n"<<endl; 
} 
} 
}; 
 
class music_admin  
{ 
public: 
music_admin()  
{} 
template <class type> 
void remove_item(type items[], int& num, int index) { 
if (index >= 0 && index <= num) { 
for (int i = index; i <=num - 1; ++i) { 
items[i] = items[i + 1]; 
} 
num--; 
cout << "Item removed successfully!" << endl; 
} else { 
cout << "Invalid index. Item not removed." << endl; 
} 
} 
template <class T> 
void change_price(T items[], int index) { 
int new_price; 
cout << "Old Price: " << items[index]->get_price() << endl; 
cout << "Enter New Price: "; 
cin >> new_price; 
items[index]->set_price(new_price); 
} 
  
template <typename T> 
T* add_item()  
{ 
T* new_item = new T(); 
new_item->input(); 
return new_item; 
} 
}; 
template <class t> 
void display_music(t *a[],int idx) 
{ 
cout<<left<<setw(6)<<"NO"<<setw(59)<<"TITLE"<< setw(55)<<"ARTIST"<<endl<<endl; 
for(int i=0;i<=idx;i++) 
{ 
cout<<left<<setw(3)<<i+1<<setw(60)<<a[i]->get_title()<< setw(60)<<a[i]->get_artist()<<endl; 
} 
} 
 
int _tmain(int argc, _TCHAR* argv[]) 
{ 
 music *cm[100],*dv[100],*v[100],*ct[100]; 
 shop sh[50]; 
 char a,c,g,h,x, la; 
 char o,p; 
 int count=0; 
 int ch,z,zee; 
 z=-1; 
 int n=-1; 
 int m=-1; 
 int l=-1; 
    int k=-1; 
 music_admin admin; 
   
cm[++k]=new cd("Thriller", "Michael Jackson", "Thriller", "5:57",1982, 200, 9); 
cm[++k]=new cd("Bohemian Rhapsody", "Queen", "A Night at the Opera", "5:55",1975,250, 12); 
cm[++k]=new cd("Hotel California", "Eagles", "Hotel California", "6:30", 1976,120,9); 
cm[++k]=new cd("Stairway to Heaven", "Led Zeppelin", "Led Zeppelin IV", "8:02",1971,200,8); 
cm[++k]=new cd("Smells Like Teen Spirit", "Nirvana", "Nevermind", "5:01", 1991,300, 12); 
cm[++k]=new cd("Like a Rolling Stone", "Bob Dylan", "Highway 61 Revisited", "6:13", 1965,150, 
9); 
cm[++k]=new cd("Wonderwall", "Oasis", "(What's the Story) Morning Glory?", "4:18", 
1995,250, 12); 
cm[++k]=new cd("Sweet Child o' Mine", "Guns N' Roses", "Appetite for Destruction", "5:56", 
1987,250, 12); 
  
dv[++l]=new dvd("Thriller", "Michael Jackson", "Thriller", "14:00", "Region 1", 1982, 1000); 
dv[++l]=new dvd("Bohemian Rhapsody", "Queen", "A Night at the Opera", "06:00", "Region 2", 
1975, 1200); 
dv[++l]=new dvd("Hotel California", "Eagles", "Hotel California", "6:00", "Region 1", 1976, 900); 
dv[++l]=new dvd("Stairway to Heaven", "Led Zeppelin", "Led Zeppelin IV", "08:00", "Region 2", 
1971, 1100); 
dv[++l]=new dvd("Imagine", "John Lennon", "Imagine", "03:00", "Region 1", 1971, 800); 
dv[++l]=new dvd("Smells Like Teen Spirit", "Nirvana", "Nevermind", "05:00", "Region 2", 1991, 
1000); 
dv[++l]=new dvd("Boogie Wonderland", "Earth, Wind & Fire", "I Am", "04:00", "Region 1", 
1979, 900); 
dv[++l]=new dvd("Billie Jean", "Michael Jackson", "Thriller", "05:00", "Region 2", 1983, 1100); 
 
ct[++m]=new casette("Thriller", "Michael Jackson", "Thriller", "42:00", 1982,1200, 9, "Normal 
Bias"); 
ct[++m]=new casette("Hotel California", "Eagles", "Hotel California","43:00", 1976, 1400, 9, 
"Chrome"); 
ct[++m]=new casette("Bohemian Rhapsody", "Queen", "A Night at the Opera","40:00", 1975, 
1100, 12, "Normal Bias"); 
ct[++m]=new casette("Stairway to Heaven", "Led Zeppelin", "Led Zeppelin IV","42:00", 1971, 
1300, 8, "Chrome"); 
ct[++m]=new casette("Billie Jean", "Michael Jackson", "Thriller","42:00", 1982, 1200, 9, "Normal 
Bias"); 
ct[++m]=new casette("Smells Like Teen Spirit", "Nirvana", "Nevermind","42:00", 1991, 800, 12, 
"Chrome"); 
ct[++m]=new casette("Sweet Child O' Mine", "Guns N' Roses", "Appetite for 
Destruction","54:00", 1987, 1500, 12, "Normal Bias"); 
ct[++m]=new casette("Like a Rolling Stone", "Bob Dylan", "Highway 61 Revisited","51:00", 1965, 
1600, 9, "Chrome"); 
 
v[++n]=new vinyl("Imagine", "John Lennon", "Imagine","39:00", 1971,2400, 12, 33.33); 
v[++n]=new vinyl("Dark Side of the Moon", "Pink Floyd", "The Dark Side of the Moon","42:00", 
1973,2900,12,33.33); 
v[++n]=new vinyl("Abbey Road", "The Beatles", "Abbey Road","47:00", 1969, 2700, 12, 33.33); 
v[++n]=new vinyl("Back in Black", "AC/DC", "Back in Black", "42:00", 1980, 2550, 12, 33.33); 
v[++n]=new vinyl("Rumours", "Fleetwood Mac", "Rumours","39:00", 1977,2730, 12,33.33); 
v[++n]=new vinyl("The Wall", "Pink Floyd", "The Wall","81:00 (1 hour,21 min)", 1979, 3400, 
12,33.33); 
v[++n]=new vinyl("Born to Run", "Bruce Springsteen", "Born to Run","39:00", 1975, 2200, 12, 
33.33); 
v[++n]=new vinyl("The Joshua Tree", "U2", "The Joshua Tree","50:00", 1987,2800, 12,33.33); 
 
cout<<"\n\n\n\n\n"; 
cout << setw(38) << "WELCOME" << endl; 
cout << setw(42) << "TO" << endl; 
cout << setw(50) << "MUSIC" << endl; 
cout << setw(59) << "SHOP!!!" << endl; 
Sleep(1500); 
system("cls"); 
cout<<"\n\n\n\n\n\t\t\tHere you can find a wide variety of music albums"<<endl; 
cout<<"\t\tExplore our categories, check out the best sellers, and find new releases.\n"; 
cout<<"\t\t\t\t\tHappy shopping!\n"; 
Sleep(2500); 
system("cls"); 
do 
{ 
cout<<"\n\t\t\t*HOME PAGE*\n\n1. BROWSE STORE\t\t2. ADMIN\n3. EXIT\n"; 
cout<<"\nEnter your choice:"; 
cin>>a; 
system("cls"); 
if(a=='1') 
{ 
do 
{ 
system("cls"); 
cout<<"Choose the type of music you want to browse:\n\n1. CD\n2. DVD\n3. Vinyl\n4. 
Cassette"<<endl; 
cout<<"Enter your choice:"<<endl; 
cin>>g; 
system("cls"); 
if(g=='1') 
{ 
cout<<"\t\t\t***CD MENU***"<<endl; 
cout<<"\n1. Display all CD's\n2. Search for CD\n\nEnter your choice:"; 
cin>>h; 
system("cls"); 
if(h=='1') 
{ 
cout<<"\n\t\t\t**CD LIST**\n"<<endl; 
display_music(cm,k); 
char dw; 
do 
{ 
cout<<"\nAre you interested in any CD from this list? If yes then enter your choice:"; 
cin>>ch; 
cout<<endl; 
int s; 
s=k+1; 
if(ch<=s) 
{ 
ch--; 
cout<<"Details of this CD are:"<<endl; 
cm[ch]->display(); 
cout<<"\nDo you want to add this CD in your cart?.If yes then press 1:"<<endl; 
cin>>x; 
if(x=='1') 
{ 
sh[count].billgm(cm,ch); 
}} 
else  
cout<<"Invalid choice!"<<endl; 
cout<<"Do you want to choose any other CD from this list?If yes then press 1:"<<endl; 
cin>>dw; 
} 
while(dw=='1'); 
} 
if(h=='2') 
{ 
sh[count].searchm(cm,k); 
} 
} 
if(g=='2') 
{ 
cout<<"\t\t\t**DVD MENU**"<<endl; 
cout<<"\n1. Display all DVD's\n2. Search for DVD\n\nEnter your choice:"; 
cin>>h; 
system("cls"); 
if(h=='1') 
{ 
cout<<"\n\t\t\t***DVD LIST***\n"<<endl; 
display_music(dv,l); 
char dw; 
do 
{ 
cout<<"\nAre you interested in any DVD from this list? If yes then enter your choice:"; 
cin>>ch; 
cout<<endl; 
int s; 
s=l+1; 
if(ch<=s) 
{ 
ch--; 
cout<<"Details of this DVD are:"<<endl; 
dv[ch]->display(); 
cout<<"\nDo you want to add this DVD in your cart?.If yes then press 1:"<<endl; 
cin>>x; 
if(x=='1') 
{ 
sh[count].billgm(dv,ch); 
} 
} 
else  
cout<<"Invalid choice!"<<endl; 
cout<<"Do you want to choose any other DVD from this list?If yes then press 1:"<<endl; 
cin>>dw; 
} 
while(dw=='1'); 
} 
if(h=='2') 
{ 
sh[count].searchm(dv,l); 
} 
} 
if(g=='3') 
{ 
cout<<"\t\t\t**VINYL MENU**"<<endl; 
cout<<"\n1. Display all vinyl\n2. Search for vinyl\n\nEnter your choice:"; 
cin>>h; 
system("cls"); 
if(h=='1') 
{ 
cout<<"\n\t\t\t***VINYL LIST***\n"<<endl; 
display_music(v,n); 
char dw; 
do 
{ 
cout<<"\nAre you interested in any VINYL from this list? If yes then enter your choice:"; 
cin>>ch; 
cout<<endl; 
int s; 
s=n+1; 
if(ch<=s) 
{ 
ch--; 
cout<<"Details of this VINYL are:"<<endl; 
v[ch]->display(); 
cout<<"\nDo you want to add this VINYL in your cart?.If yes then press 1:"<<endl; 
cin>>x; 
if(x=='1') 
{ 
sh[count].billgm(v,ch); 
} 
} 
else  
cout<<"Invalid choice!"<<endl; 
cout<<"Do you want to choose any other Vinyl from this list?If yes then press 1:"<<endl; 
cin>>dw; 
} 
while(dw=='1'); 
} 
if(h=='2') 
{ 
sh[count].searchm(v,n); 
} 
} 
if(g=='4') 
{ 
cout<<"\n\t\t\t**CASSETTE MENU**\n"<<endl; 
cout<<"\n1. Display all Cassette's\n2. Search for Cassette\n\nEnter your choice:"; 
cin>>h; 
system("cls"); 
if(h=='1') 
{ 
cout<<"\t\t\t***CASSETTE LIST***\n\n"<<endl; 
display_music(ct,m); 
char dw; 
do 
{ 
cout<<"\nAre you interested in any cassette from this list? If yes then enter your choice:"; 
cin>>ch; 
cout<<endl; 
int s; 
s=m+1; 
if(ch<=s) 
{ 
ch--; 
cout<<"Details of this Cassette are:"<<endl; 
ct[ch]->display(); 
cout<<"\nDo you want to add this Cassette in your cart?.If yes then press 1:"<<endl; 
cin>>x; 
if(x=='1') 
{sh[count].billgm(ct,ch); 
} 
} 
else  
cout<<"Invalid choice!"<<endl; 
cout<<"Do you want to choose any other cassette from this list?If yes then press 1:"<<endl; 
cin>>dw; 
} 
while(dw=='1'); 
} 
if(h=='2') 
{ 
sh[count].searchm(ct,m); 
}   
} 
cout<<"Do you want to go back to music menu page?If yes then press 1:"; 
cin>>o; 
system("cls"); 
} 
while(o=='1'); 
cout<<"Do you want to see your bill?If yes then press 1:"<<endl; 
cin>>p; 
system("cls"); 
if(p=='1') 
{ 
cout<<"\n\n\n\n\n\n\n\n\t\t\t\t****GENERATING BILL***"; 
Sleep(1500); 
system("cls"); 
sh[count].display(); 
count++; 
} 
} 
else if ( a== '2') 
{  //ADMIN 
cout<<"\n\n\n\n\n\t\t\t\t\t\***ADMIN PANEL***"<<endl; 
//PASSWORD IS 2004 
Sleep(1500); 
system("cls"); 
cout<<"Username: Admin123 \nPassword: "; 
int pass; 
cin>>pass; 
system ("cls"); 
if (pass==2004) 
{ 
cout<<"\n\n\n\n\n\n\n\n\t\t\t\t\t\tWELCOME TO THE ADMIN PANEL!!!!"<<endl; 
Sleep(1500); 
system("cls"); 
int iop=0,oop =0, pop=0, lee=0, pro=0, lar=0; 
do  
{ 
cout << "What do you want to administer?\n" ; 
cout << "1. CDs\n2. DVDs\n3. Cassettes\n4. Vinyls\n5. Display all\n6. Customer detail\n7. Total 
Earning\n\n Enter your choice: ";  
cin>>la; 
system ("cls"); 
if (la == '1') 
{  
do 
{ 
cout << "Do you want to:\n1. Add CD\n2. Remove CD\n3. Change Price\n\n Enter your choice: 
"; 
cin >> zee; 
system("cls"); 
if (zee == 1)  
{    
cm[++k] = admin.add_item<cd>(); 
system ("cls"); 
cout<<"\n\t\t\t**CD LIST**\n"<<endl; 
display_music(cm,k); 
} 
else if (zee == 2) 
{ 
cout<<"\n\t\t\t**CD LIST**\n"<<endl; 
display_music(cm,k); 
cout << "Enter the serial number of the CD you want to remove: "; 
int j; 
cin >> j; 
system ("cls"); 
admin.remove_item(cm, k, j - 1); 
cout<<"\n\t\t\t**CD LIST**\n"<<endl; 
display_music(cm,k); 
} 
else if (zee == 3) { 
cout<<"\n\t\t\t**CD LIST**\n"<<endl; 
display_music(cm,k); 
cout << "Enter serial number of the CD you want to change the price of: "; 
int i; 
cin >> i; 
system("cls"); 
admin.change_price(cm, i - 1); 
system ("cls"); 
cout<<"\n\t\t\t**CD LIST**\n"<<endl; 
display_music(cm,k); 
} else 
{cout<<"Invalid choice."<<endl; 
}  
cout<<"\n Press 1 to administer CDs again and 2 to go back to the Admin Panel: "; 
cin>>pop;  
system ("cls"); 
}  
while (pop==1);   
} 
else if ( la == '2') 
{ 
do  
{ 
cout << "Do you want to:\n1. Add DVD\n2. Remove DVD\n3. Change Price\n"; 
cin >> zee; 
system("cls"); 
if (zee == 1)  
{     
dv[++l] = admin.add_item<dvd>(); 
system("cls"); 
cout<<"\n\t\t\t**DVD LIST**\n"<<endl; 
display_music(dv,l); 
} 
else if (zee == 2)  
{ 
cout<<"\n\t\t\t**DVD LIST**\n"<<endl; 
display_music(dv,l); 
cout << "Enter the serial number of the DVD you want to remove: "; 
int j; 
cin >> j; 
system("cls"); 
admin.remove_item(dv, l, j - 1); 
cout<<"\n\t\t\t**DVD LIST**\n"<<endl; 
display_music(dv,l); 
}  
else if (zee == 3) 
{ 
cout<<"\n\t\t\t**DVD LIST**\n"<<endl; 
display_music(dv,l);  
cout<<"Enter serial number of the DVD you want to change the price of: "; 
int i; 
cin >> i; 
system("cls"); 
admin.change_price(cm, i - 1); 
system ("cls"); 
cout<<"\n\t\t\t*DVD LIST**\n"<<endl; 
display_music(dv,l); 
} 
else 
cout<<"Invalid choice."<<endl; 
cout<<"\nPress 1 to administer DVDs again and 2 to go back to the Admin Panel: "; 
cin>>lee; system ("cls"); 
} 
 while (lee==1); 
}  
else if (la == '3') 
{ 
do  
{ 
cout << "Do you want to:\n1. Add Cassette\n2. Remove Cassette\n3. Change Price\n"; 
cin >> zee; 
system("cls");  
if (zee == 1) { 
ct[++m] = admin.add_item<casette>(); 
system("cls");                
cout<<"\n\t\t\t**CASSETTE LIST**\n"<<endl; 
display_music(ct,m); 
} 
else if (zee == 2) { 
cout<<"\n\t\t\t**CASSETTE LIST**\n"<<endl; 
display_music(ct,m); 
cout << "Enter the serial number of the CD you want to remove: "; 
int j; 
cin >> j; 
system("cls"); 
admin.remove_item(ct, m, j - 1); 
cout<<"\n\t\t\t**CASSETTE LIST**\n"<<endl; 
display_music(ct,m); 
}else if (zee == 3) { 
cout<<"\n\t\t\t**CASSETTE LIST**\n"<<endl; 
display_music(ct,m); 
cout << "Enter serial number of the Cassettes you want to change the price of: "; 
int i; 
cin >> i; 
system("cls"); 
admin.change_price(ct, i - 1); 
system ("cls"); 
cout<<"\n\t\t\t**CASSETTE LIST**\n"<<endl; 
display_music(ct,m); 
} 
else 
cout<<"Invalid choice."<<endl; 
cout<<"\n Press 1 to administer Cassettes again and 2 to go back to the Admin Panel: "; 
cin>>pro; system ("cls"); 
} 
 while (pro == 1); 
}  
else if ( la == '4') 
{   
do  
{      
cout << "Do you want to:\n1. Add Vinyl\n2. Remove Vinyl\n3. Change Price\n"; 
cin >> zee; 
system("cls"); 
if (zee == 1) { 
v[++n] = admin.add_item<vinyl>(); 
system("cls"); 
cout<<"\n\t\t\t**VINYL LIST**\n"<<endl; 
display_music(v,n); 
} else if (zee == 2) { 
cout<<"\n\t\t\t**VINYL LIST**\n"<<endl; 
display_music(v,n); 
cout << "Enter the serial number of the CD you want to remove: "; 
int j; 
cin >> j; 
system("cls"); 
admin.remove_item(v, n, j - 1); 
cout<<"\n\t\t\t**VINYL LIST**\n"<<endl; 
display_music(v,n); 
} else if (zee == 3) { 
cout<<"\n\t\t\t**VINYL LIST**\n"<<endl; 
display_music(v,n); 
cout << "Enter serial number of the CD you want to change the price of: "; 
int i; 
cin >> i; 
system("cls"); 
admin.change_price(v, i - 1); 
cout<<"\n\t\t\t**VINYL LIST**\n"<<endl; 
display_music(v,n); 
} 
else 
cout<<"Invalid choice."<<endl; 
cout<<"\n Press 1 to administer Vinyls again amd 2 to go back to Admin Panel: "; 
cin>>lar; 
system ("cls"); 
} 
while (lar == 1); 
} 
else if ( la == '5') 
{ 
cout<<"\n\t\t\t**VINYL LIST**\n"<<endl; 
display_music(v,n); 
cout<<"\n\t\t\t**CASSETTE LIST**\n"<<endl; 
display_music(ct,m); 
cout<<"\n\t\t\t**DVD LIST**\n"<<endl; 
display_music(dv,l); 
cout<<"\n\t\t\t**CD LIST**\n"<<endl; 
display_music(cm,k); 
} 
else if (la=='6') 
{ 
cout << left << setw(30) << "CUSTOMERS" << setw(30) << "BILLS" << endl; 
for (int i=0;i<count;i++) 
{ 
cout<<left<<setw(30)<<i+1<<setw(30)<<sh[i].getcost()<<endl; 
} 
} 
else if (la=='7') 
{ 
double t=0.0; 
for(int i=0;i<=count;i++) 
{ 
t=t+sh[i].getcost(); 
} 
cout<<"Your total earning="<<t<<endl; 
} 
else  
cout<<"Invalid Choice."; 
cout<<"\n\nPress 1 to go back to the Admin Panel:"; 
cin>>oop; 
system ("cls"); 
} 
while (oop==1); 
}  
} 
else if ( a== '3') 
{ 
cout<<"\n\n\n\n\t\tYou have reached the end!\n\t\t\tExiting the shop.";  
} 
else  
{ 
cout<<"Invalid Choice."; 
}  
cout<<"\n\nWish to go back to homepage?If yes then press 1:"; 
cin>>c; 
system("cls"); 
}  
while (c == '1'); 
system("pause"); 
return 0; 
 }  