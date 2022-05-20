/*
the authors are osama & Joeshwoa
the purpose of program is online shopping system that adds and sells items
*/
#include <iostream>
using namespace std;

class Item
{
	private://private members
        int ID;
		string name;
		int quantity;
		double price;
		static int num_of_items;//static variable to generate Id
	public:
	    //parameterized Constructor
		Item(string n,int q,double p){
			name=n;
			quantity=q;
			price=p;
			num_of_items++;//generate Id
			ID=num_of_items;
		}
		//copy Constructor
		Item(Item& obj){
			name=obj.name;
			quantity=obj.quantity;
			price =obj.price;
			ID=obj.ID;
		}
		//default Constructor
		Item(){
			name ="non";
			quantity=0;
			price=0;
		}
		//Setters
		void Set_Name(string n){
		    name=n;
		}
		void Set_Quantity(int q){
			quantity=q;
		}
		void set_price(double p){
			price =p;
		}
		//Getters
        int get_ID()const{
			return ID;
		}
		string get_Name()const{
			return name;
		}
		double get_price()const{
			return price;
		}
		int get_quantity()const{
			return quantity;
		}
        //overloading operator == to comp
		bool operator==(Item& obj)
		{
			if (name== obj.name)
			{
				return true;
			}
			else return false;
		}
		void operator+=(Item& obj){
			quantity+=obj.quantity;
		}
		void operator-=(Item& obj){
			quantity-=obj.quantity;
		}
		//operator overloading to input details of object
		friend istream& operator>>(istream& is , Item& obj)
		{
		    cout<<"\nEnter name of Item : ";
		    is>>obj.name;
		    cout<<"Enter quantity : ";
		    is>>obj.quantity;
		    cout<<"Enter price : ";
		    is>>obj.price;
		    return is;

		}
		//operator overloading to prunt details of object
		friend ostream& operator<<(ostream& os, Item& obj)
		{
			os<<"\nID :"<<obj.ID<<"\n"<<"Name :"<<obj.name<<"\n"<<"quantity :"<<obj.quantity<<"\n"<<"Price : "<<obj.price<<"\n";
			return os;
		}

};

int Item::num_of_items=0;//static variable to generate Id

class Seller
{
	private://private members
		string name;
		string e_mail;
		Item *items;
		int maxitems;
	public:
	    //parameterized Constructor
		Seller(string n,string mail,int max){
			name=n;
			e_mail=mail;
			maxitems=max;
			items=new Item[maxitems];//dynamic allocation
			for (int i=0;i<maxitems;i++){
				Item obj;//("non",0,0);
				items[i]=obj;

			}
		}
        //operator overloading to input details of seller
		friend istream& operator>>(istream& is, Seller& obj)
		{
			cout<<"Enter your name :  ";
			is>>obj.name;
			cout<<"\nEnter your E-mail :  ";
			is>>obj.e_mail;
			cout<<"\nEnter store capacity :  ";
			is>>obj.maxitems;
			return is;
		}
		//operator overloading to print details of seller
		friend ostream& operator <<(ostream& os,Seller& obj){
			os<<"your name :  "<<obj.name;
			os<<"\nyour E-mail :  "<<obj.e_mail;
			os<<"\nstore capacity :  "<<obj.maxitems<<"\n";
			return os;
		}
		//function to add item to array of items takes object of class Item and returns boolean value
		bool Add_Item(Item& obj){
			int temp=0;//variable to check adding item
			//if add quantity to object exist in array
			for (int i=0 ; i<maxitems;i++){
				if (items[i]==obj)
				{
					items[i]+=obj;
					temp++;
					return true;
				}
			}
			//if add anew item
			for (int i=0; i<maxitems;i++)
			{
				if (items[i].get_Name()=="non")
				{
					items[i]=obj;
					temp++;
					return true;
				}
			}
			//if failed adding item
			if (temp==0)
			return false;
		}
		//function to sell item takes name and quantity of item and returns boolean value
		bool Sell_Item(string n,int q){
			int temp=0;//variable to check selling item
			Item obj;
			obj.Set_Quantity(q);
			//search to find item to sell
			for (int i=0 ; i<maxitems;i++){
				if (n==items[i].get_Name())
				{
					temp++;
					if (q<=items[i].get_quantity())
					{
						items[i]-=obj;
					}
					else
					{
						cout<<"There is only "<<items[i].get_quantity()<<" left for this item\n";
						items[i].Set_Quantity(0);
					}
					return true;
				}

			}
			if (temp==0)//if not found item
			return false;
		}
		//function to print details of items takes no parameters and returns nothing
		void Print_Item(){

			for (int i=0;i<maxitems;i++)
			{
				if (items[i].get_Name()=="non")
                    break;
                else
				cout<<items[i];
			}
		}
		//function to find item of items by id take id of item and returns object of class item
		Item Find_Item(int id)
		{
			int temp=0;
			for(int i=0;i<maxitems;i++)
			{
				if(items[i].get_ID()==id)
                {
                    cout<<items[i];
                    temp++;
                    return items[i];
                }

			}
			if (temp==0)cout<<"Not Found this item";
			Item i;
			return i;
		}
		//destractor
		~Seller()
		{
			delete []items;
		}



};


int main ()
{
    //take the detials of seller
    string name,e_mail;
    int cap;
    cout<<"Enter your name :  ";
	cin>>name;
	cout<<"Enter your E-mail :  ";
	cin>>e_mail;
	cout<<"Enter store capacity :  ";
	cin>>cap;
	Seller s1(name,e_mail,cap);//create a new seller
	bool check=true;//variable to loop
	int temp;
	while (check)
	{
		cout<<"\n---------------------\n";
		cout<<"1. print my info\n2. add an item\n3. sell an item\n4. print items\n5. find an item by Id\n6. Exit\n";
		cout<<"---------------------\n";
		cin>>temp;//take choice from user
		switch(temp)
		{
			case 1 : cout<<s1;//print details of seller
					break;
			case 2 : {
					 Item I1("",0,0);
					 cin>>I1;//take details of item
					 //add item
					 if(s1.Add_Item(I1)){cout<<"Done\n";}
					 else{cout<<"Failed\n";}
					}break;

			case 3 : {cout<<"\nEnter item's name  :"; string nameee; cin>>nameee;//take name
		   			 cout<<"Enter item's quantity  :"; int quaaant; cin>>quaaant;//take quantity to sell
		   			 if(s1.Sell_Item(nameee,quaaant)){cout<<"Done\n";}
		   			 else{cout<<"Failed\n";}
				     break;
					}
			case 4 : {
					s1.Print_Item();//show items
					break;
					}
			case 5 : {
					 cout<<"\nEnter ID "; int id; cin>>id;//take id
					 s1.Find_Item(id);
					break;
					}
			case 6 : { cout<<"Thank You";
                        check = false;}
                        break;
			default : cout<<"Wrong choice try again\n";
		}
	}
	return 0;

}
