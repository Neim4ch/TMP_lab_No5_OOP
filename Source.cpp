#include "Source.h"
using namespace std;
void feature::InData(ifstream& ifst) {
	ifst >> director;
}
void feature::Out(ofstream& ofst) {
	ofst << "It is feature film. Director is " << director << endl;
}

void documentary::InData(ifstream& ifst) {
	ifst >> year;
}
void documentary::Out(ofstream& ofst) {
	ofst << "It is documentary film. It's year of creation is " << year << endl;
}
void animation::InData(ifstream& ifst) {
	int t;
	ifst >> t;
	switch (t)
	{
	case 1:
		woc = DRAWN;
		break;
	case 2:
		woc = DOLL;
		break;
	case 3:
		woc = STOP_MOTION;
		break;
	}
}
void animation::Out(ofstream& ofst) {
	switch (woc)
	{
	case 0:
		ofst << "It is animation film. It's way of creation is drawing." << endl;
		break;
	case 1:
		ofst << "It is animation film. It's way of creation is using dolls" << endl;
		break;
	case 2:
		ofst << "It is animation film. It's way of creation is stop motion" << endl;
		break;
	}
}

string vowels = "AEIOUYaeiouy";

int film::countVowels()
{
	int cnt = 0;
	for (int i = 0; i < name.length(); i++)
	{
		if (vowels.find(name[i]) < vowels.length())cnt++;
	}
	return cnt;
}

film* film::In(ifstream& ifst) {
	film* fl;
	int k;
	ifst >> k;	
	switch (k) {
	case 1:
		fl = new feature;
 		break;
	case 2:
		fl = new animation;
		break;
	case 3:
		fl = new documentary;
		break;
	default:
		return 0;
	}
	ifst >> fl->name;
	fl->InData(ifst);

	ifst >> fl->country;
	return fl;
}
Node::Node(film* newpic)
{
	pic = newpic;
	next = NULL;
}
container::container()
{
	head = NULL;
	head = NULL;
	size = 0;
}
// ??????? ?????????? ?? ?????????
void container::Clear() {
	head = NULL;
	curr = NULL;
	size = 0;
}

void container::In(ifstream& ifst) {
	while (!ifst.eof()) {
		Node* newNode;
		newNode = new Node((film::In(ifst)));
		if (head == NULL)
		{
			head = newNode;
			size = 1;
		}
		else
		{
			curr = head;
			while (curr->next != NULL)
			{
				curr = curr->next;
			}
			curr->next = newNode;
			size++;
		}
	}
}
void container::Out(ofstream& ofst) {
	ofst << "Container contents " << size
		<< " elements." << endl;
	//Sort();

	int i = 0;
	curr = head;
	while (curr != NULL)
	{
		ofst << i << ": ";
		curr->pic->OutName(ofst);
		curr->pic->Out(ofst);
		ofst << "The picture was filmed in " << curr->pic->country << ".\n";
		ofst << "Number of vowels = ";
		OutCntVowels(ofst);
		ofst << endl;
		curr = curr->next;
		i++;
	}
}
void container::OutCntVowels(ofstream& ofst)
{
	ofst << curr->pic->countVowels();
}

bool film::cmp(film& f)
{
	return countVowels() < f.countVowels();
}

void container::Sort()
{
	curr = head;
	Node* currj = head;
	while (curr != NULL)
	{
		currj = curr;
		while (currj != NULL)
		{
			if (curr->pic->cmp(*currj->pic))
			{
				swap(curr->pic, currj->pic);
			}
			currj = currj->next;
		}
		curr = curr->next;
	}
}
void film::OutName(ofstream& ofst)
{
	ofst << "This is " << name << ". ";
}
void feature::OutFeature(ofstream& ofst)
{
	Out(ofst);
}
void film::OutFeature(ofstream& ofst)
{
	ofst << endl;
}

void container::OutFeature(ofstream& ofst) {
	int i = 0;
	curr = head;
	while (curr != NULL)
	{
		ofst << i << ": ";
		if (curr->pic)curr->pic->OutFeature(ofst);
		curr = curr->next;
		i++;
	}
}


bool fileCheck(ifstream& ifst)
{
	bool result = true;
	string digits = "0123456789";
	char tmp[100];
	string tmps;

	
	if (!ifst.is_open())
	{
		cout << "Input file was not found.";
		exit(1);
	}
	int cnt = 1;
	//type check
	while (!ifst.eof())
	{
		ifst.getline(tmp, 100, '\n');
		tmps = (tmp);
		if (tmps == "")
		{
			cout << cnt << " film: The type is a blank string.\n";
			result = false;
			exit(1);
		}
		for (int i = 0; i < tmps.length(); i++)
		{
			if (!(digits.find(tmps[i]) < digits.length()))
			{
				cout << cnt << " film: Type definition contains incorrect characters.\n";
				result = false;
				exit(1);
			}
		}
		int type = std::stoi(tmps);
		if (type <= 0 || type > 3)
		{
			cout << cnt << " film: Type is out of range.\n";
			result = false;
			exit(1);
		}
		//
		//name
		ifst.getline(tmp, 100, '\n');
		tmps = (tmp);
		if (tmps == "")
		{
			cout << cnt << " film: The name of the film is a blank string.\n";
			result = false;
			exit(1);
		}
		//
		//type pole
		switch (type)
		{
		case 1:
		{
			//director
			ifst.getline(tmp, 100, '\n');
			tmps = (tmp);
			if (tmps == "")
			{
				cout << cnt << " film: The director's name of the film is a blank string.\n";
				result = false;
				exit(1);
			}
			break;
		}
		case 2:
		{
			//woc
			ifst.getline(tmp, 100, '\n');
			tmps = (tmp);
			if (tmps == "")
			{
				cout << cnt << " film: The way of creation of the film is a blank string.\n";
				result = false;
				exit(1);
			}
			for (int i = 0; i < tmps.length(); i++)
			{
				if (!(digits.find(tmps[i]) < digits.length()))
				{
					cout << cnt << " film: The way of creation contains incorrect characters.\n";
					result = false;
					exit(1);
				}
			}
			int type = std::stoi(tmps);
			if (type <= 0 || type > 3)
			{
				cout << cnt << " film: Way of creation is out of range.\n";
				result = false;
				exit(1);
			}
			break;
		}
		case 3:
		{
			//year
			ifst.getline(tmp, 100, '\n');
			tmps = (tmp);
			if (tmps == "")
			{
				cout << cnt << " film: The year of creation of the film is a blank string.\n";
				result = false;
				exit(1);
			}
			for (int i = 0; i < tmps.length(); i++)
			{
				if (!(digits.find(tmps[i]) < digits.length()))
				{
					cout << cnt << " film: The year of creation contains incorrect characters.\n";
					result = false;
					exit(1);
				}
			}
			int year = std::stoi(tmps);
			if (year <= 0 || year > 2022)
			{
				cout << cnt << " film: The year of creation is out of range.\n";
				result = false;
				exit(1);
			}
			break;
		}
		}
		//
		//country
		ifst.getline(tmp, 100, '\n');
		tmps = (tmp);
		if (tmps == "")
		{
			cout << cnt << " film: The film's country is a blank string.\n";
			result = false;
			exit(1);
		}
		//
		cnt++;
	}


	return result;
}