#include <bits/stdc++.h>
using namespace std;
namespace fs = std::filesystem;

string randomFileNameGenerator()
{
	stringstream s1;
	stringstream s2;
	srand(time(0));

	unsigned int randFirst = rand();
	s1 << randFirst;

	srand(time(0));
	unsigned int randSecond = rand();

	s2 << randSecond;

	string eventFileName = s1.str() + "Event" + s2.str();

	return eventFileName;

}

class Events
{
	public:
		string eventName,
		eventDescription,
		eventDate,
		eventOrganizer,
		eid;

	void setEventDetails()
	{
		cout << "\nEnter event name ";
		cin.ignore();
		getline(cin, eventName);
		eventName = "event name : " + eventName + "\n";

		cout << "\nenter event description ";
		getline(cin, eventDescription);
		eventDescription = "event description : " + eventDescription + "\n";

		cout << "\nenter event date(DD/MM/YY) ";
		getline(cin, eventDate);
		eventDate = "event date : " + eventDate + "\n";

		cout << "\nenter event organizer name ";
		getline(cin, eventOrganizer);
		eventOrganizer = "organizer name : " + eventOrganizer + "\n";
	}

};

class EventFunctions: public Events
{
	public: void viewAllEvents()
	{
		string path = "events";
		system("CLS");

		for (const auto &entry: fs::directory_iterator(path))
		{
			string finalPath;
			stringstream s1;
			stringstream s2;
			s1 << entry.path();
			s2 << s1.str().erase(0, 9);
			finalPath = "events/" + s2.str();
			finalPath = finalPath.substr(0, finalPath.size() - 1);
			//cout<<finalPath;
			ifstream MyReadFile;
			string myText;
			//	inf.open(finalPath.c_str());
			MyReadFile.open((finalPath).c_str());
			cout << "\n";
			while (getline(MyReadFile, myText))
			{
				cout << myText << endl;
			}

			cout << "\n\noooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\n";
		}
	}

	int Authenticate(string type = "user")
	{
		system("CLS");
		string uid, password;
		cout << "enter username ";
		cin >> uid;

		cout << "enter password ";
		cin >> password;

		string suffix;

		if (type == "user")
		{
			suffix = "auth/";
		}
		else
		{
			suffix = "auth/superuser/";
		}

		string file = suffix + uid + ".txt";
		ifstream myfile;
		myfile.open(file.c_str());

		if (myfile)
		{
			string mystring;
			myfile >> mystring;

			if (password != mystring)
			{
				return 0;	//password incorrect
			}
			else
			{
				return 1;	//Authenticated
			}
		}
		else
		{
			return 3;	//incorrect username
		}
	}

	void WriteEvent()
	{
		cout << endl;
		int auth = Authenticate();
		system("CLS");

		if (auth == 1)
		{
			cout << "\nAuthenticated\n";
			Events obj;
			obj.setEventDetails();
			ofstream outf;
			string randomNum = randomFileNameGenerator();
			obj.eid = "event id is : " + randomNum;
			outf.open(("events/" + randomNum + ".txt").c_str(), ios_base::app);

			outf.write((char*) &(obj.eventName[0]), strlen(obj.eventName.c_str()));
			outf.write((char*) &(obj.eventDescription[0]), strlen(obj.eventDescription.c_str()));
			outf.write((char*) &(obj.eventDate[0]), strlen(obj.eventDate.c_str()));
			outf.write((char*) &(obj.eventOrganizer[0]), strlen(obj.eventOrganizer.c_str()));
			outf.write((char*) &(obj.eid[0]), strlen(obj.eid.c_str()));

			outf.close();
		}
		else if (auth == 0)
		{
			cout << "\nIncorrect Passowrd\n";
		}
		else if (auth == 3)
		{
			cout << "\nIncorrect Username\n";
		}
	}

	void createEventFile()
	{
		string fileName = "events/" + randomFileNameGenerator() + ".txt";
		ofstream outfile(fileName.c_str());
		setEventDetails();
		outfile.close();
	}

	void deleteEvent()
	{
		system("CLS");
		int auth = Authenticate("su");
		system("CLS");

		if (auth == 1)
		{
			string inputEid, fileName;
			cout << "\nAuthenticated\n";
			cout << "\n enter event id for deleting the event ";
			cin >> inputEid;

			fileName = "events/" + inputEid + ".txt";

			int result = remove(fileName.c_str());

			if (result == 0)
			{
				cout << "\nFILE DELETED\n";
			}
			else if (result == -1)
			{
				cout << "\nENTER CORRECT EVENT ID\n";
			}
		}
		else if (auth == 0)
		{
			cout << "\nIncorrect Passowrd\n";
		}
		else if (auth == 3)
		{
			cout << "\nIncorrect Username\n";
		}
	}
};

int main()
{
	int query;
	EventFunctions ee;

	while (true)
	{
		cout << "\n To View all the events press 1\n";
		cout << "\n To Create an event press 2\n";
		cout << "\n To Delete an event press 3\n";
		cout << "\n To Exit press 4\n";

		cin >> query;

		switch (query)
		{
			case 1:
				{
				 		//viewing all the events
					system("CLS");
					ee.viewAllEvents();
					break;
				}

			case 2:
				{
				 		//creating events
					//login	
					ee.WriteEvent();
					break;
				}

			case 3:
				{
				 		//deleting events
					ee.deleteEvent();
					break;
				}

			case 4:
				{
					exit(0);
					break;
				}
		}
	}
}
