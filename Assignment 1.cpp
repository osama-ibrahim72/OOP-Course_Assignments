/*
Osama Ibrahim  &&  Sara Samuel 
*/        
#include <iostream>
#include <windows.h>

using namespace std;

void SetColor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

class ColoredBox
{
	//private members
private:
	int length, width, area;
    int color=15;//15 is defult color(white)
    int color2;
    char **board;
    static int Max;
    char symbol='#';//defult symbol of box
public:
	// 1st constractor
    	ColoredBox (int l , int w )
    {
    	width=w;//set width
        length=l;//set length
        symbol='#';//defult char of board
        //dynamic allocation
		char** Dynamic=new char *[l];
        board=Dynamic;
        for(int i=0; i<l; i++)
        {
            Dynamic[i]= new char [w];
        }
        for (int x=0; x<l ;x++)
        {
            for (int y=0; y<w;y++)
            {
                Dynamic[x][y]=symbol;
            }
        }
        //set area
        area = l*w;
        //set max area
        if (area>Max)
        Max=area;
	}
	//2nd constractor
	ColoredBox (int l , int w, int col ,char s )
    {
    	width=w;//set width
        length=l;//srt length
        symbol=s;//set char of board
        color=col;//set color value 
        //dynamic allocation
        char** D=new char *[l];
        board=D;
        for(int i=0; i<l; i++)
        {
            D[i]= new char [w];
        }
        for (int x=0; x<l ;x++)
        {
            for (int y=0; y<w;y++)
            {
                D[x][y]=symbol;
            }
        }
        //set area
        area = l*w;
        //set Max area
        if (area>Max)
        Max=area;
	}
	//function to show the board
	void display()
    {
        //loop to cout board
		for (int x=0; x<length ;x++)
        {
            for (int y=0; y<width ;y++)
            {
            	SetColor(color);
                cout<<board[x][y];
            }
            SetColor(15);//return color to wite
            cout<<endl;
        }
	}
	//function to set color of object
	void setColor (int c)
    {
    	color=c;
    }
    // functtion to show transposed object
	void displayTransposed()
    {
        //loop to cout array
		for (int x=0; x<width ;x++)
        {
            for (int y=0; y<length ;y++)
            {
                SetColor(color);
                cout<<board[y][x];
            }
            cout<<endl;
            SetColor(15);//return color to white
        }
    }
	//function to show wider
	void displayWider()
    {
        //loop to cout array
		for (int x=0; x<length ;x++)
        {
            for (int y=0; y<width ;y++)
            {
                SetColor(color);
                cout<<board[x][y]<<' ';
                
            }
            SetColor(15);//return color to white
            cout<<endl;
        }
	}
	// function to show the object as chess
	void displayChess(int col2)
	{
    	int i=0;//counter
    	int j=0;//counter
    	color2=col2;//set snd clor
    	//loop to coutarray
		while(i<length)
		{
			j=0;
			while (j<width)
			{
				if((i+j)%2==0)//condiation to change color
				{
				SetColor(color);
				cout<<board[i][j];
				}
				else
				{
				SetColor(color2);
				cout<<board[i][j];
				} 
				j++;
			}
			cout<<endl;
			i++;
		}
		SetColor(15);//return color to white
	}
	//destractor
	~ColoredBox()
    {
    	for(int i=0;i<length;i++){
    		delete [ ]board[i];
    	}
    	delete [] board;
	}
	//function to retern area
    double getArea()
    {
    	return area;
	}
	//static function to return Max area 
    static int getMaxArea()
    {
    	return Max;
	}
	
};
//static installation
int ColoredBox::Max = 0;


int main()
{
    int len,wid,col,col2;
    char boxChar;
    cout<<"Enter length and width of the box separated by a space: ";
    cin>>len>>wid;
    ColoredBox* cb1;
    cb1 = new ColoredBox(len,wid);
    cb1->display();
    cout<<"Set the box to another color: ";
    cin>>col;
    cb1->setColor(col);
    cout<<"Displaying Transposed: "<<endl;
    cb1->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb1->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb1->displayChess(col2);
    cout<<endl<<"Area="<<cb1->getArea();
    cout<<endl<<"Max Area="<<cb1->getMaxArea()<<endl;
    delete cb1;

    cout<<"Enter length,width,color,character of the box separated by spaces: ";
    cin>>len>>wid>>col>>boxChar;
    ColoredBox* cb2;
    cb2 = new ColoredBox(len,wid,col,boxChar);
    cb2->display();
    cout<<"Displaying Transposed: "<<endl;
    cb2->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb2->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb2->displayChess(col2);
    cout<<"Displaying original again:"<<endl;
    cb2->display();
    cout<<endl<<"Area="<<cb2->getArea();
    cout<<endl<<"Max Area="<<cb2->getMaxArea();
    delete cb2;
    return 0;
}
