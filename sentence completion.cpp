//2020244- Mohsin Zia
//2020474- Irtaza Haider

#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<windows.h>
#include<iomanip>

using namespace std;

//to move cursor at x, y in console
void gotoxy(int x,int y)                                                // For placing cursor on screen
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

struct adjListNode
{
	int data;
	adjListNode* next;
};

struct adjList
{
	adjListNode* head;
};

struct Graph
{
	int vertices;
	adjList* array;
};

//to add nodes
adjListNode* newAdjListNode(int data)
{		
	adjListNode* newNode=new adjListNode;
	newNode->data=data;	
	newNode->next=NULL;
	
	return newNode;
}

//to create graph
Graph* createGraph(int v)
{	 
	Graph* newGraph=new Graph;
	newGraph->vertices=v;
	newGraph->array=new adjList[v];
	
	for(int i=0;i<v;i++)
	{
		newGraph->array[i].head=NULL;
	}

	return newGraph;
}

//to add edges in graph
void addEdge(Graph* grp,int source,int destination)
{	
	adjListNode* newNode = newAdjListNode(destination);	//Creating a new node.
	
	adjListNode* temp = grp->array[source].head;
	
	if(temp == NULL)
	{
		grp->array[source].head = newNode;
		return;		
	}
	
	while(temp->next != NULL)
		temp = temp->next;
		
	temp->next = newNode;
}

//to print graph, you can use it in main function
void printGraph(Graph* grp, string words[])
{	
	for(int i=0;i<grp->vertices;i++)
	{	
		adjListNode* start=grp->array[i].head;	
		cout<<endl<<words[i]<<" --> ";

		while(start!=NULL)
		{
			cout<<words[start->data];
			start=start->next;
			cout<<" , ";		
		}
		cout<<endl;
	}
}

//if space is in last, remove it
string removeLastSpace(string s)
{
	if(s[s.length()-1] == ' ')
	{
		string w("");
		for(int j=0;j<s.length()-1; j++)
				w = w+s[j];
		return w;
	}
	return s;
}

//to get last word from whole sentence
string getLastWord(string s)
{
	bool noSpace = true;
	
	for(int i=0;i<s.length();i++)
	{
		if(s[i] == ' ')
		{
			noSpace = false;
			break;
		}
	}
	
	if(noSpace)
	{
		return s;
	}
	
	s = removeLastSpace(s);
	
	flag:
	string w("");
	
	for(int i=0;i<s.length();i++ )
	{
		if(s[i] == ' ')
		{
			for(int j=i+1;j<s.length(); j++)
				w = w+s[j];
				
			break;
		}
	}
	
	for(int i=0; i<w.length();i++)
	{
		if(w[i] == ' ')
		{
			s = w;
			goto flag;
		}
	}
	
	return w;
}

//to find word from array of words
int find(string word, string words[], int count)
{
	for(int i = 0; i<count; i++)
		if(word == words[i])
			return i;
}

//to show suggestions for last word from sentence
string* showSuggestions(Graph* g, string words[], string givenWord, int count)
{	
	string word = getLastWord(givenWord);
	
	int i = find(word, words, count);
	adjListNode* temp = g->array[i].head;
	
	string* sWords = new string[9] ;
	for(int j = 0;temp != NULL && j<9 ; j++ )
	{
		sWords[j] = words[temp->data];
		temp = temp->next;
	}		
	
	cout<<setw(5)<<"0- NONE";
	for(int j=0;j<9;j++)
	{
		if(sWords[j] == "\0" )
			break;
			
		cout<<setw(5)<<j+1<<"- "<<sWords[j];
	}
	
	return sWords;
}

//to show suggestion for first time
string* setup()
{
	string* sWords = new string[9];
	sWords[0] = "this";
	sWords[1] = "hey";
	sWords[2] = "hello";
	sWords[3] = "i";
	sWords[4] = "cat";
	
	cout<<setw(5)<<"0- NONE";
	for(int j=0;j<9;j++)
	{
		if(sWords[j] == "\0" )
			break;
			
		cout<<setw(5)<<j+1<<"- "<<sWords[j];
	}
	return sWords;
}

int main()
{	
	fstream f;
	fstream s;		//sheet to make edges of graph
	string temp;	//to read words from file	
	int count = 0;
	char character;
	string* sWords = new string[9];
	string wordx("");
	
	f.open("words.txt");
	s.open("sheet.txt");	
	
	//to count total words from sheet
	while(temp != "endHere")
	{
		getline(f,temp);
		if(temp[0] == '-' || temp == "endHere" || temp == "" || temp == "\n")
			continue;
		count++;
	}
	
	string* wordList = new string[count];
	
	f.seekg(0);
	
	//to store words in array
	for(int j = 0; j<count ; j++)
	{
		f>>temp;
		if(temp[0] == '-' || temp == "endHere" || temp=="" || temp=="\n")
		{
			j--;
			continue;
		}
		wordList[j] = temp;
	}
	
	//making graph of words
	Graph* g = new Graph;
	g = createGraph(count);
	
	for(int i = 0;i<count; i++ )
	{
		for(int j=0; j<count ; j++)
		{
			int c;		
			s>>c;
			if(c!=0)
			{
				addEdge(g, i, j);	
			}	
		}
	}

//you can uncomment this to see our graph	
//	printGraph(g, wordList);
	
	starting:
	gotoxy(85, 4);
	cout<<"Only small characters are allowed!";	
	
	gotoxy(85, 5);
	cout<<"Press enter to exit!";		
		
	gotoxy(7, 5);	
	cout<<"Type here: ";
		
	gotoxy(7, 15);
	sWords = setup();
	
	while (character = getch())	
	{
		system("CLS");
		gotoxy(85, 4);
		cout<<"Only small characters are allowed!";	
		
		gotoxy(85, 5);
		cout<<"Press enter to exit!";
		
		gotoxy(7, 5);
		cout<<"Type here: ";

		if(character == '\b')
		{
			wordx[wordx.length()-1] = '\0';
			string temp;
			for(int i = 0 ; wordx[i] != '\0' && i < wordx.length()-1 ; i++)
				temp += wordx[i];
				
			wordx = temp;
		}
		else if(character == '0')
		{
			wordx += " ";
		}	
		else if(character>='1' && character<='9')
		{
			wordx += " ";
			wordx += sWords[character-49];
		}
		else if(character == '\r')
		{
			system("CLS");
			gotoxy(7, 5);
			cout<<"You typed: "<<wordx<<endl<<endl<<endl;
			return 0;
		}
		else
		{
			wordx += character;			
		}
		
		cout<<wordx;	
		
		gotoxy(7, 15);
		sWords = showSuggestions(g, wordList, wordx, count);
	}
}
