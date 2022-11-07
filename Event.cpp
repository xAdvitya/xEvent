#include<bits/stdc++.h>
#include <string>
using namespace std;
namespace fs = std::filesystem;
string randomFileNameGenerator(){
	
	stringstream s1;
	stringstream s2;
	srand(time(0));
	
	unsigned int randFirst = rand();
	s1<<randFirst;
	
	srand(time(0));	
	unsigned int randSecond = rand();
		
	s2<<randSecond;
	
	string eventFileName=s1.str()+"Event"+s2.str();
	
	return eventFileName;
	
}

class Events{
	string eventName,
	eventDescription,
	eventDate,
	eventOrganizer,
	eid;
	
	public:
		void setEventName(){
			cout<<"set event name ";
			cin>>eventName;
			cout<<"endl";
		}
		

		
		void viewEventDetails(){
			cout<<"event name "<<eventName<<endl;
			cout<<"event description "<<eventDescription<<endl;
			cout<<"event Date "<<eventDate<<endl;
			cout<<"event oraganizer "<<eventOrganizer<<endl;
		}
		
		
		void createEventFile(){
			string fileName= "events/"+randomFileNameGenerator()+".txt";
			ofstream outfile(fileName.c_str());
			setEventName();
			outfile.close();
		}
		
		
};

class EventFunctions:public Events{
	
	public:
		void viewAllEvents(){	
		string path = "events";
    	for (const auto & entry : fs::directory_iterator(path))	{
    		
    		string finalPath;
    		stringstream s1;
    		stringstream s2;
			s1<<entry.path();
			s2 << s1.str().erase(0,9);
			cout<<s2.str()<<endl;
			finalPath ="events/"+s2.str();
			finalPath= finalPath.substr(0, finalPath.size()-1);
			cout<<finalPath<<endl;
//			cout<<finalPath;
			
			ifstream inf;
			inf.open(finalPath.c_str());
			Events obj1;
			inf.read((char *)&obj1,sizeof(obj1));
			obj1.viewEventDetails();
			inf.close();
	}
			
		}
	void WriteEvent(){
		
	Events obj;
	obj.setEventName();
	ofstream outf;
	outf.open("11850Event11850.txt");
	outf.write((char *)&obj,sizeof(obj));
	outf.close();
	}
	
};

class Login{
	string uid,password;
	public:
		void Authenticate(){
			cout<<"enter username ";
			cin>>uid;
			
			cout<<"enter password ";
			cin>>password;
			
			string file = "auth/"+uid+".txt";
			ifstream myfile;
			myfile.open(file.c_str());
			
			if(myfile){
				
				string mystring;
				myfile >> mystring;
				
				if(password != mystring){
					cout<<"password incorrect"<<endl;
				}
				else{
					cout<<"Authenticated"<<endl;
				}
		}
		else{
			cout<<"enter correct username"<<endl;
		}
				
		}
	
};

//viewer
//creator
//superuser


int main(){
//	Login l1;
//	Events e1;
//	l1.Authenticate();
//	int query;
//	e1.createEventFile();
//	

EventFunctions ee;

ee.WriteEvent();
ee.viewAllEvents();

//		
//switch(query){
//		
//		case 1:{
//			//viewing all the events
//			break;
//		}
//		
//		case 2:{
//			//creating events
//				//login
//			break;
//		}
//		
//		case 3:{
//			 //deleting events
//			break;
//		}
//		case 4:{
//			//searching events by keywords
//			break;
//		}
//			
//}
		
	
}
