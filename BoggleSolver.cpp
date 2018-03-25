#include "Dictionary.h"

Dictionary::Dictionary(){
	root=new Node;
	numWords=0;
}

Dictionary::Dictionary(string file){
	root=new Node;
    numWords=0;
	string word;
	ifstream INFILE;
	INFILE.open(file);
	if(INFILE.is_open()){
	while(getline(INFILE,word)){
		addWord(word);
	}
	}
}

void Dictionary::addWord(string word){
	Node*currNode;
	currNode = root;
	int index;
	for(int i = 0; i< word.length(); i++){
		index=word[i]-'a';
		if(!currNode->children[index]){
			currNode->children[index] = new Node;
			currNode->flag[index];
		}
		currNode = currNode->children[index];
	}
	currNode->flag[index]=true;
	numWords++;
	currNode->value=numWords;
}

bool Dictionary::isPrefix(string word){
	Node*curr = root;
	int index;
	for(int i = 0; i <word.length(); i++){
		index =word[i]-'a';
		if(curr->children[index]){
			curr=curr->children[index];
		}
		else{
			return false;
		}
	}
	return true;
}

bool Dictionary::isWord(string word){
	Node*curr = root;
	int index;
	for(int i = 0; i <word.length(); i++){
		index =word[i]-'a';
		if(curr->children[index]){
			curr=curr->children[index];
		}
		else{
			return false;
		}
	}
	if(curr->value != 0){
		return true;
	}
	else
	{
		return false;
	}
}

int Dictionary::wordCount(){
	return numWords;
}

bool pBoard;
void SolveBoard(string board[4][4], Dictionary& dict, Dictionary& wordsFound, bool printBoard);
void SolveBoardHelper(string board[4][4],int visited[4][4],bool tracker[4][4], Dictionary& dict, Dictionary& wordsFound,int row, int col, string str,int step, bool printBoard);
void setBoard(string board[4][4]);
void printBoard(string board[4][4],int visited[4][4]);

int main() {
	
	string board4[4][4];
	int visited[4][4]={0};
	Dictionary dict("dict.txt");

	cout << dict.wordCount() << " words loaded." << endl << endl;
		
	Dictionary wordsFound;

	setBoard(board4);
	SolveBoard(board4, dict, wordsFound, pBoard);

	return 0;
}

void SolveBoard(string board[4][4], Dictionary& dict, Dictionary& wordsFound, bool printBoard) {
int step = 1;
string word="";
int track[4][4]={0};
bool visited[4][4]={false};
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			//Initial calls to SolveBoardHelper
			SolveBoardHelper(board, track, visited, dict, wordsFound, r, c, word, step, printBoard);
		}
	}
}


void SolveBoardHelper(string board[4][4],int track[4][4], bool visited[4][4], Dictionary& dict, Dictionary& wordsFound,int row, int col, string str,int step, bool print){

	bool temp[4][4];
	copy(&visited[0][0],&visited[0][0]+16,&temp[0][0]);

	if(row < 0 || row >= 4||col< 0 || col >=4){
		return;
	}
	if(temp[row][col]){
		return;
	}

	str+=board[row][col];
	if(!dict.isPrefix(str)){
		return;
	}

	if(dict.isWord(str)&&!wordsFound.isWord(str)){
		wordsFound.addWord(str);
		if (!print){
			cout<<wordsFound.wordCount()<<" ";
			cout<<" "<<str<<endl;
		}
		track[row][col]= step;
		if(print){
			cout<<"Word: "<<str<<endl;
			cout<<"Number of words:  "<<wordsFound.wordCount()<<endl;
			printBoard(board,track);
		}
	}

		temp[row][col]=true;
		track[row][col]=step;
		step+=1;

		SolveBoardHelper(board,track,temp,dict,wordsFound,row-1,col-1,str,step, print);//upL

		SolveBoardHelper(board,track,temp,dict,wordsFound,row-1,col,str,step, print);//up

		SolveBoardHelper(board,track,temp,dict,wordsFound,row-1,col+1,str,step, print);//upR

		SolveBoardHelper(board,track,temp,dict,wordsFound,row,col+1,str,step, print);//r

		SolveBoardHelper(board,track,temp,dict,wordsFound,row+1,col+1,str,step, print);//dR

		SolveBoardHelper(board,track,temp,dict,wordsFound,row+1,col,str,step, print);//down

		SolveBoardHelper(board,track,temp,dict,wordsFound,row+1,col-1,str,step,print);//dL

		SolveBoardHelper(board,track,temp,dict,wordsFound,row,col-1,str,step,print);//L


		track[row][col]=0;
		return;
}

void setBoard(string board[4][4]){
	string s;
	char a;

	cout<<"      Enter Board      "<<endl;
	cout<<"-----------------------"<<endl;
		for(int i = 0; i < 4; i++)
				{
					cout<<"Row "<<i<<": ";
					for(int j = 0; j < 4; j++)
					{

						cin>>s;
						board[i][j]= s;
					}
				}
		cout<<"Show board (y/n) ?: ";
			cin>>a;
			cout<<endl;
			if(a=='y')
				pBoard=true;
			else
				pBoard=false;
}

void printBoard(string board[4][4],int track[4][4]){
	for(int i = 0; i < 4; i++)
		{
			cout<<"\t[ ";
				for(int j = 0; j < 4; j++)
					{
					if(track[i][j]!=0)
					 cout<<"'"<<board[i][j]<<"'";
					else
						cout<<" "<<board[i][j]<<" ";
					}
				cout<<"]"<<"\t\t[ ";
				for(int j = 0; j < 4; j++)
					{
					cout<<track[i][j]<<" ";
					}
					 cout<<"]";
					 cout<<endl;
		}
}
