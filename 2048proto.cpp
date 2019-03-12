#include <iostream>
#include <time.h>
#include <stdio.h>
#include <fstream>

using namespace std;

//definetions
#define U  "UP"
#define D  "DOWN"
#define L  "LEFT"
#define R  "RIGHT"

// function prototypes
void Menu();
//void Play(int pX, int pY);
void HighScore();
void SelectMode();
void Classic(int cX, int cY);
void Challenge();
void Adventure();

//Classes
class Tile
{
public:
	int xPos = 0;
	int yPos = 0;
	string value = "0";
	bool age = false;
	Tile(string value, int xPos, int yPos, bool age)
	{
		this->value = value;
		this->xPos = xPos;
		this->yPos = yPos;
		this->age = age;
	}
	Tile()
	{
		xPos = 0;
		yPos = 0;
		value = "0";
		age = false;
	}
	int Upd(Tile* manip, int bX, int bY, int ind)
	{
		int row = manip[ind].yPos;
		int col = manip[ind].xPos;
		int moveScore=0;
		string state = manip[ind].value;
		if(row == 0)
		{
			return moveScore;
		}
		else if(state == "0")
		{
			return moveScore;
		}
		else if(state != "0")
		{
			for(int i=(row-1);i>=0;--i)
			{
				if ((manip[i*bY + col].value == state) && (manip[i*bY + col].age == false))
				{
					Collide(&manip[(i+1)*bY + col],&manip[row*bY + col]);
					break;
				}
				else if(manip[(i*bY) + col].value == state)
				{
					moveScore += Merge(&manip[i*bY + col],&manip[row*bY + col]);
					break;
				}  
				else if((manip[i*bY + col].value != manip[row*bY + col].value)					
					&& (manip[i*bY +col].value != "0") && (i < row))
				{
					Collide(&manip[(i+1)*bY + col],&manip[row*bY + col]);
					break;
				}
				else if(i==0)
				{
					Collide(&manip[i*bY + col],&manip[row*bY + col]);
					break;
				}
				else
				{}
			}
		}
		else
		{
			return moveScore;
		}
		return moveScore;
	}

	int Downd(Tile* manip, int bX, int bY, int ind)
	{
		int row = manip[ind].yPos;
		int col = manip[ind].xPos;
		string state = manip[ind].value;
		int moveScore=0;
		if(row == bY-1)
		{
			return moveScore;
		}
		else if(state == "0")
		{
			return moveScore;
		}
		else if(state != "0")
		{
			for(int i=row+1;i<bY;++i)
			{
				if ((manip[i*bY + col].value == state) && (manip[i*bY + col].age == false))
				{
					Collide(&manip[(i-1)*bY + col],&manip[row*bY + col]);
					break;
				}
				else if(manip[(i*bY) + col].value == state)
				{
					moveScore += Merge(&manip[i*bY + col],&manip[row*bY + col]);
					break;
				}  
				else if((manip[i*bY + col].value != manip[row*bY + col].value)					
					&& (manip[i*bY +col].value != "0") && (i > row))
				{
					Collide(&manip[(i-1)*bY + col],&manip[row*bY + col]);
					break;
				}
				else if(i == bY-1)
				{
					Collide(&manip[i*bY + col],&manip[row*bY + col]);
					break;
				}
				else
				{}
			}
		}
		else
		{
			return moveScore;
		}
		return moveScore;	
	}
	int Leftd(Tile* manip, int bX, int bY, int ind)
	{
		int row = manip[ind].yPos;
		int col = manip[ind].xPos;
		string state = manip[ind].value;
		int moveScore=0;
		if(col == 0)
		{
			return moveScore;
		}
		else if(state == "0")
		{
			return moveScore;
		}
		else if(state != "0")
		{
			for(int i=(col-1);i>=0;--i)
			{
				if ((manip[row*bY + i].value == state) && (manip[row*bY + i].age == false))
				{
					Collide(&manip[row*bY + i +1],&manip[row*bY+col]);
					break;
				}
				else if(manip[row*bY + i].value == state)
				{
					moveScore += Merge(&manip[row*bY +i],&manip[row*bY + col]);
					break;
				}  
				else if((manip[row*bY+i].value != state)					
					&& (manip[row*bY+i].value != "0") && (i < col))
				{
					Collide(&manip[row*bY + i +1],&manip[row*bY+col]);
					break;
				}
				else if(i==0)
				{
					Collide(&manip[row*bY+i],&manip[row*bY+col]);
					break;
				}
				else
				{}
			}
		}
		else
		{
			return moveScore;
		}
		return moveScore;
	}
	int Rightd(Tile* manip, int bX, int bY, int ind)
	{
		int row = manip[ind].yPos;
		int col = manip[ind].xPos;
		string state = manip[ind].value;
		int moveScore=0; 
		if(col == bX-1)
		{
			return moveScore;
		}
		else if(state == "0")
		{
			return moveScore;
		}
		else if(state != "0")
		{
			for(int i=(col+1);i<bX;++i)
			{
				if ((manip[row*bY + i].value == state) && (manip[row*bY + i].age == false))
				{
					Collide(&manip[row*bY + i -1],&manip[row*bY+col]);
					break;
				}
				else if(manip[row*bY + i].value == state)
				{
					moveScore += Merge(&manip[row*bY +i],&manip[row*bY + col]);
					break;
				} 
				else if((manip[row*bY+i].value != state)					
					&& (manip[row*bY+i].value != "0") && (i > col))
				{
					Collide(&manip[row*bY + i -1],&manip[row*bY+col]);
					break;
				}
				else if(i==bX-1)
				{
					Collide(&manip[row*bY+i],&manip[row*bY+col]);
					break;
				}
				else
				{}
			}
		}
		else
		{
			return moveScore;
		}
		return moveScore;
	}
	int Merge(Tile* a, Tile* b)
	{
		if((a->age == true)
			&& (b->age == true))
		{
			int temp = stoi(a->value);
			++temp;

			a->value = to_string(temp);
			b->value = to_string(0);
			a->age = false;
			return temp;
		}
		return 0;
	}
	void Collide(Tile* a, Tile* b)
	{
		string temp = b->value;
		b->value = "0";
		a->value=temp;
	}
};

class Board
{
public:
	int x;
	int y;
	int score = 0;
	bool paused = true;
	bool bUp,bDown,bLeft,bRight = false;
	Tile* array = new Tile[1];
	Tile* testB = new Tile[1];
	Board(int x, int y)
	{
		this->x = x;
		this->y = y;
		array = new Tile[x*y];
		for (int i = 0; i < x * y; ++i)
		{
			array[i].value = "0";
			array[i].xPos = i%x;
			array[i].yPos = i/y;
			array[i].age = true;
		}
	}
	~Board()
	{
		delete [] array;
	}
	void PrintBoard()
	{
		int count = 0;
		for (int i = 0; i < y; ++i)
		{
			for (int j = 0; j < x; ++j)
			{
				cout << array[count].value;
				//cout << array[count].xPos;
				//cout << array[count].yPos;
				//cout << array[count].age;
				cout << " ";
				++count;	
			}
			cout << endl;
		}	
	}
	void PrepBoard()
	{	
		int created = 0;

		while(created != 2)
		{
			AddTile();
			++created;	
		}
	}
	void AddTile()
	{
		srand(time(NULL));
		bool added = false;
		while(!added)
		{
			int evenOrOdd = rand() % 2;
			int ranInt = rand() % (x * y);
			//even
			if(evenOrOdd)
			{	
				if(array[ranInt].value == "0")
				{
					array[ranInt].value = "1";
					array[ranInt].age = true;
					added = true;
				}
			}
			//odd
			else
			{	
				if(array[ranInt].value == "0")
				{
					array[ranInt].value = "2";
					array[ranInt].age = true;
					added = true;
				}
			}
		}	
	}
	string Arrows()
	{
		char input;
		bool go=true;
		bool pause;
		string direction;
		while(go)
		{
			cin.get(input);
			switch (input)
			{
				case '8':
					if(!bUp)
					{
						direction = U;
						go = false;
					}
					break;
				case '2':
					if(!bDown)
					{
						direction = D;
						go =  false;
					}
					break;
				case '4':
					if(!bLeft)
					{
						direction = L;
						go =  false;
					}
					break;
				case '6':
					if(!bRight)
					{
						direction = R;
						go =  false;
					}
					break;
				case 'q':
					pause = true;
					go=false;
					break;
				default:
					break;
			}
		}
		if (pause)
		{
			return "pause";
		}
		return direction;
	}
	void ResetAge()
	{
		for (int i = 0; i < x * y; ++i)
		{
			array[i].age = true;
		}
	}
	bool Move(string dir)
	{		
		paused=true;
		bool resQuit = true;
		if (dir == U)
		{
			for (int i = 0; i< x*y; ++i)
			{
				score += array->Upd(array, x, y, i);
			}
		}
		else if (dir == D)
		{
			for (int i = x*y-1; i>=0; --i)
			{
				score += array->Downd(array, x, y, i);
			}
		}
		else if(dir == L)
		{
			for( int i = 0; i<x*y;++i)
			{
				score += array->Leftd(array,x,y,i);

			}
		}
		else if(dir == R)
		{
			for( int i = x*y-1; i>=0;--i)
			{
				score += array->Rightd(array,x,y,i);
			}
		}
		else if(dir == "pause")
		{
			char resOrQuit;
			cout << "You are paused!\n"
				<< "Enter 'p' to resume\n"
				<< "Enter 'q' to quit\n";
			cin >> resOrQuit;
			if (resOrQuit=='q')
				resQuit=false;
			paused=false;
		}
		else 
			cout << "NOT VALID\n";
		ResetAge();
		return resQuit;
	}
	bool Lose()
	{
		bool same = false;
		int currentScore = score;
		string * temp = new string[x*y];
		for (int i = 0; i<x*y; ++i)
		{
			temp[i]=array[i].value;
		}
		Move(U);
		bUp = Compare(temp);
		Reassign(temp);
		Move(D);
		bDown = Compare(temp);
		Reassign(temp);
		Move(L);
		bLeft = Compare(temp);
		Reassign(temp);
		Move(R);
		bRight = Compare(temp);
		Reassign(temp);
		score = currentScore;
		if(bUp && bDown && bLeft && bRight)
			same = true;
		return same;
	}
	void Reassign(string tArr[])
	{
		for (int i =0; i <x*y; ++i)
		{
			array[i].value=tArr[i];
		}
	}
	bool Compare(string sArr[])
	{
		bool equivalent = true;
		for (int i = 0; i<x*y; ++i)
		{
			if (sArr[i]!=array[i].value)
			{
				equivalent=false;
			}
		}

		return equivalent;
	}
	bool Full()
	{
		bool full = true;
		for (int i =0; i<x*y; ++i)
		{
			if(array[i].value == "0")
			{
				full = false;
			}
		}
		return full;
	}
};

int main()
{

	bool functioning = true;
	char user;
	while (functioning)
	{
		Menu();
		cin.get(user);
		switch (user)
		{
			case 'p':
				SelectMode();
				break;
			case 'h':
			HighScore();
				break;
			case 'q':
				functioning=false;
				break;
			default:
				cout << "Invalid Input\n";
		}
		cin.ignore(1000,'\n');
	}
	cout << "Okay Bye Bye";
	cin.get();
	return 0;
}

void Menu()
{
	cout << "Hey, welcome to a really lousy version of 2048\n"
	<<"If you want to play input (p)\n"
	<<"If you want to check out the highscores input (h)\n"
	<<"If you want to exit input (q)\n";
}
/*void Play(int pX, int pY)
{
	//int sizeX;
	//int sizeY;
	bool run = true;
	char userChoice;

	//cout << "Enter size of array as X space Y:";
	//cin >> sizeX >> sizeY;
	Board game(pX,pY);
	game.PrepBoard();
	cout << "GameScore:" << game.score << endl;
	game.PrintBoard();
	cout<< endl;
	while(run)
	{
		if(game.Lose())
		{
			run =false;
			cout << "Aww you lost\n";
			//cin.ignore();
			cin.get();
		}
		else
		{
			run = game.Move(game.Arrows());
			// need this test or else game will loop forever and crash
			if(!game.Full()&&game.paused)
			{
				game.AddTile();
			}
			if(run)
			{	
				cout << "GameScore:" << game.score << endl;
				game.PrintBoard();
				cout << endl;
			}
		}
	}
}*/
void SelectMode()
{
	char uIn;
	cout << "Which would you like to play?\n" 
		<< "Classic (c)\n"
		<< "Adventure (a)\n"
		<< "Challenge (x)\n";
	cin >>  uIn;
	switch (uIn)
	{
		case 'c':
			Classic(4,4);
			break;
		case 'a':
			break;
		case 'x':
			break;
	}	
}
void HighScore()
{
	ifstream myFile;
	string line;
	myFile.open("highscore.txt");
	while (getline(myFile,line))
	{
		cout << line << endl;
	}
	myFile.close();
	cout << endl;
}
void Classic(int cX, int cY)
{
	bool run = true;
	char userChoice;

	Board game(cX,cY);
	game.PrepBoard();
	cout << "GameScore:" << game.score << endl;
	game.PrintBoard();
	cout<< endl;
	while(run)
	{
		if(game.Lose())
		{
			run =false;
			cout << "Aww you lost\n";
			cin.get();
		}
		else
		{
			run = game.Move(game.Arrows());
			// need this test or else game will loop forever and crash
			if(!game.Full() && game.paused)
			{
				game.AddTile();
			}
			if(run)
			{	
				cout << "GameScore:" << game.score << endl;
				game.PrintBoard();
				cout << endl;
			}
		}
	}
}
void Adventure()
{}
void Challenge()
{}