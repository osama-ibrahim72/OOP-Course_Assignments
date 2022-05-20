/*
Osama Ibrahim &&   Sara Samuel 
*/
#include <iostream>
#include <fstream>
using namespace std;

class Float_Array{//parent class
public:
    int length;
    double *arr;
    Float_Array(int l)//parameterized Constructor
    {
        length=l;
        arr= new double [length];//dynamic allocation
    }
    //virtual function to polymorphism and add the elements in array
    virtual void Add (int i, double element){
            arr[i]=element;
    }
    friend ofstream& operator<< (ofstream &outf ,Float_Array* obj){//operator overloading to write in the file
        outf<<obj->length;
        outf<<" | ";
        for(int i=0;i<obj->length;i++)
        {
            outf<<"\t"<<obj->arr[i];
        }
        outf<<endl;
    }
    friend ifstream& operator>> (ifstream &inf ,Float_Array* obj){//operator overloading to read in the file
        double temp;
        for(int i=0;i<obj->length;i++)
        {
            inf>>temp;
            obj->Add(i,temp);
        }

    }
    ~Float_Array(){//destractor
        delete[] arr;
        }

};
//1st child class
class Sorted_Array : public Float_Array{
public:
    Sorted_Array(int l):Float_Array(l){}//parameterized Constructor
    virtual void Add(int i, double element)//virtual function to polymorphism and add the elements in array
    {
        arr[i]=element;
        for (int j = 0; j < i; j++)
        {
            if (arr[i] < arr[j])
            {
                double temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
};

class Front_Array : public Float_Array{
public:
    Front_Array(int s):Float_Array(s){}//parameterized Constructor
    virtual void Add(int i, double element){//virtual function to polymorphism and add the elements in array
		arr[(length-1)-i]=element;
	}

};

class Positive_Array : public Sorted_Array{
public:
    Positive_Array(int s):Sorted_Array(s){}//parameterized Constructor
    int x=0;//counter
	virtual void Add(int i, double element){//virtual function to polymorphism and add the elements in array
		if(element >0){
			Sorted_Array::Add(i-x,element);
		}
		else{
			x++;
		}
		if(i==length -1){
			length=i+1-x;//new length after filter the array
			x=0;
		}
	}
};

class Negative_Array : public Sorted_Array{
public:
    Negative_Array(int s):Sorted_Array(s){}//parameterized Constructor
    int x=0;//counter
		virtual void Add(int i,double elemant){//virtual function to polymorphism
		if(elemant <0){
			Sorted_Array::Add(i-x,elemant);
		}
		else{
			x++;
		}
		if(i==length -1){
			length=i+1-x;//new length after filter the array
			x=0;
            }
        }
};

int main(){
    string array_type;
    int len;
    string name;
    int lines=0;

    cout<<"Enter input file Name : \n";
    cin>>name;//take the name of file
    ifstream input;//create object to input file
    input.open(name);//open input file

    while(getline(input,name)){lines++;}//count lines to create array
    //restart read the input file
    input.clear();
    input.seekg(0,ios::beg);

    //dynamic allocation
    Float_Array** arrays;
    arrays = new Float_Array*[lines];
    for (int i=0;i<lines;i++){
        input>>array_type;
        input>>len;
        if(array_type=="Array") arrays[i]=new Float_Array(len);
        else if(array_type=="Sorted") arrays[i]=new Sorted_Array(len);
        else if(array_type=="Front")  arrays[i]=new Front_Array(len);
        else if(array_type=="Positive")   arrays[i]=new Positive_Array(len);
        else if(array_type=="Negative")  arrays[i]=new Negative_Array(len);
        input>>arrays[i];//take the elements of elements from the file
    }

    cout<<"enter output file name: "<<endl;
    cin>>name;//take the name of output file
    ofstream output;//create object to ourput file
    output.open(name);//open output file

    //write on the output file
    for(int i=0;i<lines;i++)output<<arrays[i];

    cout<<"Completed"<<endl;

    //close files
    input.close();
    output.close();

    //deallocation
    delete [] *arrays;

    return 0;
}
