#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<sstream>
#include<windows.h>

using namespace std;

void adminMenu();
void passengerMenu();
void staffMenu();
void paymentM(double price);
void passengerM();


fstream userLogin;
fstream Flights;
fstream staffData;
fstream passenger;


class User{
	string name;
	string email;
	string password;
	int phone;
	
	public:
		User(){
			
		}
		User(string name, string email,string password, long phone){
			this->name=name;
			this->email=email;
			this->password=password;
			this->phone=phone;
		}
		
		string getName(){
			return name;
		}
		
        string getEmail(){
        	return email;
		}
		
		string getPass(){
			return password;
		}
		
		long phNum(){
			return phone;
		}
		
	    void login(){
	    	string email,password;
            cout<<"Enter email: ";
            cin.ignore();
            getline(cin,email);
            cout<<"Enter password: ";
            getline(cin,password);
    
           userLogin.open("users.csv",ios::in);
           string line, word;
           bool found=false;
         while(getline(userLogin,line)){
              stringstream s(line);
              getline(s,word,',');
            if(word==email){
              getline(s,word,',');
              if(word==password){
                found = true;
                break;
            }
        }
    }
    userLogin.close();
    
    if(found){
    	Sleep(1200);
        cout<<"Login successful!"<<endl<<endl;
        passengerM();
    }else{
    	Sleep(1200);
        cout<<"Invalid email or password!"<<endl;
    }
    
}	
		

      void signup(){
	     cout<<"Enter name: ";
        cin>>name;
        cout<<"Enter email: ";
        cin>>email;
        cout<<"Enter password: ";
        cin>>password;
        cout<<"Enter phone number: ";
        cin>>phone;
    
        userLogin.open("users.csv", ios::in);
        string line, word;
        bool emailE=false; 
		bool phEx=false;
		
        while(getline(userLogin,line)){
           stringstream s(line);
           getline(s,word,',');
        if(word==email){
            emailE=true;
            break;
        }
        getline(s,word,',');
        getline(s,word,',');
        getline(s,word,',');
        if(stoi(word)==phone){
            phEx=true;
            break;
        }
    }
    userLogin.close();
    
    if(emailE||phEx){
    	Sleep(1200);
        cerr<<"Error: Email or phone number already exists!"<<endl;
    }else{
        userLogin.open("users.csv",ios::app);
        userLogin<<email<<","<<password<<","<<name<<","<<phone<<endl;
        userLogin.close();
        Sleep(1200);
        cout<<"Signup successful!"<<endl;
    }
    passengerMenu();
  }
		
};

class Flight{
	string carrier;
	string fNum;
	string arCity;
	string depCity;
	string date;
	string time;
	int buiSeat;
	int ecoSeat;
	int fSeat;
	double ecoPrice;
	double buisPrice;
	double fPrice;

	public:
		
		Flight(){
	    
		}
		
		Flight(string carrier,string fNum,string arCity,string depCity,string date,string time,int buiSeat,int ecoSeat,int fSeat,double ecoPrice,
		double buisPrice,double fPrice)
		{
			this->carrier=carrier;
			this->fNum=fNum;
			this->arCity=arCity;
			this->depCity=depCity;
			this->date=date;
			this->time=time;
			this->buiSeat=buiSeat;
			this->ecoSeat=ecoSeat;
			this->fSeat=fSeat;
			this->ecoPrice=ecoPrice;
			this->buisPrice=buisPrice;
			this->fPrice=fPrice;
		}
		
		double getFPri(){
			return fPrice;
		}
		
		double getBuisPri(){
			return buisPrice;
		}
		
		double getEcoPri(){
			return ecoPrice;
		}
		
	    int getFSeat(){
	    	return fSeat;
		}
		
		int getEcoSeat(){
			return ecoSeat;
		}
		
		int getBuiSeat(){
			return buiSeat;
		}
		
		string getTime(){
			return time;
		}
		
		string getCar(){
			return carrier;
		}
		
		string getFNum(){
			return fNum;
		}
		
		string getArCity(){
			return arCity;
		}
		
		string getDepCity(){
			return depCity;
		}
		
		string getDate(){
			return date;
		}
		
		void upFSeats(int seat){
			fSeat=fSeat-seat;
		}
		
		void upESeat(int seat){
			ecoSeat=ecoSeat-seat;
		}
		
		void upBSeat(int seat){
			buiSeat=buiSeat-seat;
		}
		
	void addFlight(){
		cout<<"\n****** Welcome To Add Flight*******\n";
		
		cout<<"Enter the Company Name : ";
		cin.ignore();
		getline(cin,carrier);
		cout<<"Enter the flight Number : ";
		getline(cin,fNum);
		cout<<"Enter the Arrival City : ";
		getline(cin,arCity);
		cout<<"Enter the departure city : ";
		getline(cin,depCity);
		cout<<"Enter the Date(DD/MM/YYYY) : ";
		getline(cin,date);
		cout<<"Enter the time of Flight(24hour Format) : ";
		getline(cin,time);
		cout<<"Enter Number of Buisness Seats : ";
		cin>>buiSeat;
		cout<<"Enter the price for Business Seat : ";
		cin>>buisPrice;
		cout<<"Enter Number of First-Class Seats : ";
		cin>>fSeat;
		cout<<"Enter the price for the First Class : ";
		cin>>fPrice;
		cout<<"Enter the Number of seats for Economy : ";
		cin>>ecoSeat;
		cout<<"Enter the Price for Economy : ";
		cin>>ecoPrice;
		
		  Flights.open("flights.csv", ios::app);
    Flights<<fNum<<","<<carrier<<","<<arCity<<","<<depCity<<","<<date<<","<<time<<","<<ecoPrice<<","<<buisPrice <<","<<fPrice<<","<<buiSeat<<","<<ecoSeat
	<<","<<fSeat<<endl;
    Flights.close();
    cout<<"Processing.......\n";	
   Sleep(1200);
    cout<<"Flight added successfully!"<<endl;
    adminMenu();
}
	
	void removeFlight(){
		string num;
		cout<<"Enter the flight number you want to remove : ";
		cin>>num;
		ifstream readFile("flights.csv");
        ofstream tempFile("temp.csv");
        string line,word;
        bool found=false;
        while(getline(readFile,line)) {
        stringstream s(line);
        getline(s,word,',');
        if(word!=num){
            tempFile<<line<<endl;
        }else{
            found=true;
        }
    }
        readFile.close();
        tempFile.close();
        remove("flights.csv");
        rename("temp.csv","flights.csv");
        if(found){
        	cout<<"Processing.......\n";
        	Sleep(1200);
            cout<<"Flight removed successfully!"<<endl;
        }else{
        	cout<<"Processing.......\n";
        	Sleep(1200);
            cout<<"Flight not found!"<<endl;
        }
        
        adminMenu();
}
		
void searchFlight(){
    string num;
    cout<<"Enter the flight Number: ";
    cin.ignore();
    getline(cin, num);

    ifstream readFile("flights.csv");
    string line,word;
    bool found=false;
    while(getline(readFile,line)) {
        stringstream s(line);
        getline(s,word,',');
        if(word==num){
            found=true;
            cout<<"Processing.......\n";
            Sleep(1200);
            cout<<"\n****** Here's the information of flight ******* \n";
            getline(s,word,',');
            cout<<"Carrier: "<<word<<endl;
            getline(s,word,',');
            cout<<"Arrival City: "<<word<<endl;
            getline(s,word,',');
            cout<<"Departure City: "<<word<<endl;
            getline(s,word,',');
            cout<<"Date: "<<word<<endl;
            getline(s,word,',');
            cout<<"Time: "<<word<<endl;
            getline(s,word,',');
            cout<<"Economy Price: "<<word<<endl;
            getline(s,word,',');
            cout<<"Business Price: "<<word<<endl;
            getline(s,word,',');
            cout<<"First-Class Price: "<<word<<endl;
            break;
        }
    }
    readFile.close();
    if(!found){
    	cout<<"Processing.......\n";
    	Sleep(1200);
        cout<<"Flight not found!"<<endl;
    }
    adminMenu();
 }
 
void updateFlight() {
    string num;
    int choice;
    char check;
    cout<<"\nEnter the flight number you want to update: ";
    cin>>num;

    ifstream readFile("flights.csv");
    ofstream tempFile("temp.csv");
    string line,word;
    bool found=false;

    while (getline(readFile,line)) {
        stringstream s(line);
        getline(s,word,',');

        if(word==num){
            found=true;
            vector<string> val;
            while(getline(s,word,',')){
                val.push_back(word);
            }

            do {
                cout<<"Processing.......\n";
                Sleep(1200);
                cout<<"Flight found! What do you want to update?\n";
                cout<<"1. Carrier\n";
                cout<<"2. Arrival City\n";
                cout<<"3. Departure City\n";
                cout<<"4. Date\n";
                cout<<"5. Time\n";
                cout<<"6. Business Seats\n";
                cout<<"7. Economy Seats\n";
                cout<<"8. First-Class Seats\n";
                cout<<"9. Economy Price\n";
                cout<<"10. Business Price\n";
                cout<<"11. First-Class Price\n";
                cin>>choice;
                cin.ignore(); 
                switch(choice){
                    case 1:
                        cout<<"Enter new carrier: ";
                        getline(cin, val[0]);
                        break;
                    case 2:
                        cout<<"Enter new arrival city: ";
                        getline(cin, val[1]);
                        break;
                    case 3:
                        cout<<"Enter new departure city: ";
                        getline(cin, val[2]);
                        break;
                    case 4:
                        cout<<"Enter new date: ";
                        getline(cin, val[3]);
                        break;
                    case 5:
                        cout<<"Enter new time: ";
                        getline(cin, val[4]);
                        break;
                    case 6:
                        cout<<"Enter new business seats: ";
                        cin>>val[5];
                        break;
                    case 7:
                        cout<<"Enter new economy seats: ";
                        cin>>val[6];
                        break;
                    case 8:
                        cout<<"Enter new first-class seats: ";
                        cin>>val[7];
                        break;
                    case 9:
                        cout<<"Enter new economy price: ";
                        cin>>val[8];
                        break;
                    case 10:
                        cout<<"Enter new business price: ";
                        cin>>val[9];
                        break;
                    case 11:
                        cout<<"Enter new first-class price: ";
                        cin>>val[10];
                        break;
                    default:
                        cout<<"Invalid choice. Please try again.\n";
                        break;
                }

                cout<<"Do you want to change anything again from this flight: (Y/N): ";
                cin>>check;
            }while(check=='Y'||check=='y');

           tempFile<<num;
            for (int i=0;i<val.size();i++) {
                tempFile<<","<<val[i];
            }
            tempFile<<"\n";
        }else{
            tempFile<<line<<"\n";
        }
    }

    readFile.close();
    tempFile.close();
    remove("flights.csv");
    rename("temp.csv","flights.csv");

    if(found){
        cout<<"Processing.......\n";
        Sleep(1200);
        cout<<"Flight updated successfully!\n";
    }else{
        cout<<"Processing.......\n";
        Sleep(1200);
        cout<<"Flight not found!\n";
    }

    adminMenu();
}
};


class Staff{
    string name;
    string employeeID;
    string department; 
    string role;
    string email;
    string phoneNum;
    double salary;
    
    public:
    	
    void addStaff(){
    cout<<"\n****** Welcome To Add Staff*******\n";
    
    cout<<"Enter the Name : ";
    cin.ignore();
    getline(cin,name);
    cout<<"Enter the Employee ID : ";
    getline(cin,employeeID);
    cout<<"Enter the Department : ";
    getline(cin,department);
    cout<<"Enter the Role : ";
    getline(cin,role);
    cout<<"Enter the Email : ";
    getline(cin,email);
    cout<<"Enter the Phone Number : ";
    getline(cin,phoneNum);
    cout<<"Enter the Salary : ";
    cin>>salary;
    
    staffData.open("staff.csv",ios::app);
    staffData<<employeeID<<","<<name<<","<<department<<","<<role<<","<<email<<","<<phoneNum<<","<<salary<<endl;
    staffData.close();
    cout<<"Processing.......\n";
    Sleep(1200);
    cout<<"Staff added successfully!"<<endl;
    staffMenu();
}
	
	void removeStaff(){
	  string id;
      cout<<"Enter the staff ID to remove: ";
      cin>>id;

      ifstream readFile("staff.csv");
      ofstream tempFile("temp.csv");
      string line,word;
      bool found=false;
      while(getline(readFile, line)) {
        stringstream s(line);
        getline(s,word,',');
        if(word!=id) {
            tempFile<<line<<endl;
        }else{
            found=true;
        }
    }
    readFile.close();
    tempFile.close();
    remove("staff.csv");
    rename("temp.csv","staff.csv");
    if(found){
    	cout<<"Processing.......\n";
    	Sleep(1200);
        cout<<"Staff member removed successfully!" << endl;
    }else{
    	cout<<"Processing.......\n";
    	Sleep(1200);
        cout<<"Staff member not found!" << endl;
    }
    staffMenu();
		
}
	
	void updateStaff(){
    string id;
    char check;
    cout<<"Enter the Employee ID of the staff member to update: ";
    cin>>id;

    ifstream readFile("staff.csv");
    ofstream tempFile("temp.csv");
    string line,word;
    bool found=false;
    while(getline(readFile,line)) {
        stringstream s(line);
        getline(s,word,',');
        if (word==id) {
            found=true;
            vector<string> val;
            stringstream s(line);
            string word;
            while(getline(s,word,',')) {
                val.push_back(word);
            }
            do{
            	cout<<"Processing.......\n";
            	Sleep(1200);
                cout<<"\nWhat do you want to update?\n";
                cout<<"1. Name\n";
                cout<<"2. Email\n";
                cout<<"3. Phone Number\n";
                cout<<"4. Salary\n";
                int choice;
                cin>>choice;
                string newValue;
                switch(choice) {
                    case 1:
                        cout<<"Enter new name: ";
                        cin.ignore();
                        getline(cin,newValue);
                        val[1] = newValue;
                        break;
                    case 2:
                        cout<<"Enter new email: ";
                        cin.ignore();
                        getline(cin,newValue);
                        val[4] = newValue;
                        break;
                    case 3:
                        cout<<"Enter new phone number: ";
                        cin.ignore();
                        getline(cin,newValue);
                        val[5] = newValue;
                        break;
                    case 4:
                        cout<<"Enter new salary: ";
                        cin>>newValue;
                        val[6] = newValue;
                        break;
                    default:
                        cout<<"Invalid choice. Please try again.\n";
                        break;
                }
                cout<<"Do you want to update anything else for this staff member? (Y/N) : \n";
                cin>>check;
            }while(check=='y'|| check=='Y');
            for (int i=0;i<val.size();i++) {
                tempFile<<val[i];
                if (i<val.size()-1){
                    tempFile<<",";
                }else{
                    tempFile<<endl;
                }
            }
        }else{
            tempFile<<line<<endl;
        }
    }
    readFile.close();
    tempFile.close();
    remove("staff.csv");
    rename("temp.csv","staff.csv");
    if(found){
    	cout<<"Processing.......\n";
    	Sleep(1200);
        cout<<"Staff member updated successfully!\n";
    }else{
    	cout<<"Processing.......\n";
    	Sleep(1200);
        cout<<"Staff member not found!\n";
    }
    staffMenu();
}
};

class Passenger{
	string fName;
    string lName;
    string email;
    long ph;
    string addr;
    string passNum;
    string nation;
    string doBirth;
    string seatCLass; 
    
    public:
	
	void bookflight(){
    string fDate,arCity,depCity;
    cout<<"Enter the Flight date You want : ";
    cin>>fDate;
    cout<<"Enter the flight arrival city you want :";
    cin>>arCity;
    cout<<"Enter the departure city : ";
    cin>>depCity;

    ifstream readFile("flights.csv");
    string line, word;
    vector<Flight> flights;
    while(getline(readFile,line)) {
        stringstream s(line);
        string fNum,car,ari,dep,date,time;
        double ecoPrice,buisPrice,fPrice;
        int buiSeat,ecoSeat,fSeat;

        getline(s,fNum,',');
        getline(s,car,',');
        getline(s,ari,',');
        getline(s,dep,',');
        getline(s,date,',');
        getline(s,time,',');
        getline(s,word,',');
        ecoPrice=stod(word);
        getline(s,word,',');
        buisPrice=stod(word);
        getline(s,word,',');
        fPrice=stod(word);
        getline(s, word, ',');
        buiSeat=stoi(word);
        getline(s,word,',');
        ecoSeat=stoi(word);
        getline(s,word,',');
        fSeat=stoi(word);

        if (date==fDate&&ari==arCity&&dep==depCity) {
            Flight flight(car,fNum,ari,dep,date,time,buiSeat,ecoSeat,fSeat,ecoPrice,buisPrice,fPrice);
            flights.push_back(flight);
        }
    }
    readFile.close();

    if(flights.empty()){
        cerr<<"\nNo flights were available for this route.......\n";
    }
    else{
        cout<<"\n******* Here are the available Flights on the route ********\n";
        for(int i=0;i<flights.size();i++){
            cout<<"\tFllight No : "<<i+1<<"\n\n";
            cout<<"Flight Number : "<<flights[i].getFNum()<<endl;
            cout<<"Company : "<<flights[i].getCar()<<endl;
            cout<<"Date : "<<flights[i].getDate()<<endl;
            cout<<"Time : "<<flights[i].getTime()<<endl;
            cout<<"Buiness Class Price : $"<<flights[i].getBuisPri()<<endl;
            cout<<"First Class Price : $"<<flights[i].getFPri()<<endl;
            cout<<"Economy Price : $"<<flights[i].getEcoPri()<<endl;
        }
            
             int choice;
        cout<<"Enter the option to book a flight : ";
        cin>>choice;
        cout<<"\nEnter Some of your information \n\n";
        cout<<"Enter Your First Name : ";
        cin>>fName;
        cout<<"Enter Your Last Name : ";
        cin>>lName;
        cout<<"Enter Your Email : ";
        cin>>email;
        cout<<"Enter Your Phone Number : ";
        cin>>ph;
        cout<<"Enter Your Address : ";
        cin>>addr;
        cout<<"Enter Your Passport Number : ";
        cin>>passNum;
        cout<<"Enter Your Nationality : ";
        cin>>nation;
        cout<<"Enter Your Date of Birth : ";
        cin>>doBirth;

        cout<<"\nPlz select which seat you want to book : \n";
        cout<<"1: Buisness Seat\n";
        cout<<"2: First-Class Seat\n";
        cout<<"3: Economy Seat\n";
        int sa;
        cin>>sa;
        int seats,se;
        double price;

        switch(sa){
            case 1:
            	cout<<"How many seats do you want to book : ";
            	cin>>se;
                 seats=flights[choice-1].getBuiSeat()-se;
                if(seats>=0){
                    cout<<"Seats are Available\n";
                    seatCLass="Business calss";
                    price=se*flights[choice-1].getBuisPri();
                }
                else{
                	cout<<"No seats are available\n";
                	passengerM();
				}
				 break;
               
            case 2:
            	cout<<"How many seats do you want to book : ";
            	cin>>se;
                seats=flights[choice-1].getFSeat()-se;
                if(seats>=0){
                    cout<<"Seats are Available\n";
                    seatCLass="First-Class";
                    price=se*flights[choice-1].getFPri();
                }else{
                	cout<<"No seats are available\n";
                	passengerM();
				}
                break;
            case 3:
            	 cout<<"How many seats do you want to book : ";
            	 cin>>se;
                 seats=flights[choice-1].getEcoSeat()-se;
                if(seats>=0){
                    cout<<"Seats are Available\n";
                    seatCLass="Economy";
                    price=se*flights[choice-1].getEcoPri();
                }else{
                	cout<<"No seats are available\n";
                	passengerM();
				}
                break;
               default:
               	cout<<"You have entered the wrong choice \n";
               	passengerM();
        }

        
        ifstream readFile("flights.csv");
         ofstream tempFile("temp.csv");

     if(!readFile||!tempFile) {
    cerr<<"Error opening file."<<endl;
    passengerM(); 
    }

    string line, word;
    bool found=false;
    int buiSeat,ecoSeat,fSeat;

    while (getline(readFile,line)) {
    stringstream s(line);
    string fNum,car,ari,dep,date,time;
    double ecoPrice,buisPrice,fPrice;

    getline(s,fNum,',');
    getline(s,car,',');
    getline(s,ari,',');
    getline(s,dep,',');
    getline(s,date,',');
    getline(s,time,',');
    getline(s,word,',');
    ecoPrice=stod(word);
    getline(s,word,',');
    buisPrice=stod(word);
    getline(s,word,',');
    fPrice=stod(word);
    getline(s,word,',');
    buiSeat=stoi(word);
    getline(s,word,',');
    ecoSeat=stoi(word);
    getline(s,word,',');
    fSeat=stoi(word);

    if (fNum==flights[choice-1].getFNum()){
        found=true;
        switch(sa){
            case 1:
                buiSeat-=se;
                break;
            case 2:
                fSeat-=se;
                break;
            case 3:
                ecoSeat-=se;
                break;
        }
        tempFile<<fNum<<","<<car<<","<<ari<<","<<dep<<","<<date<<","<<time<<","<<ecoPrice<<","<<buisPrice<<","
                  <<fPrice<<","<<buiSeat<<","<<ecoSeat<<","<<fSeat<<endl;
    }else{
        tempFile<<line<<endl;
    }
}

        readFile.close();
        tempFile.close();

        remove("flights.csv");
        rename("temp.csv", "flights.csv");
        
        paymentM(price);
    
        passenger.open("passengers.csv", ios::app);
        passenger<<passNum<<","<<fName<<","<<lName<<","<<email<<","<<ph<<","<<addr<<","<<nation<<","<<
		doBirth<<","<<flights[choice - 1].getFNum()<<","<<seatCLass<<","<<se<<endl;
        passenger.close();
        }
        passengerM();
    }
  
  
  void deletePas(){
    string passNum;
    cout<<"Enter the passport number: ";
    cin>>passNum;

    ifstream file("passengers.csv");
    ofstream temp("temp.csv");

    string line;
    bool found=false;

    while(getline(file,line)){
        stringstream ss(line);
        string word;
        getline(ss,word,',');
        if (word!=passNum) {
            temp<<line<<endl;
        }else{
            found=true;
        }
}
    file.close();
    temp.close();

    if(found){
        remove("passengers.csv");
        rename("temp.csv","passengers.csv");
        cout<<"Passenger with passport number "<<passNum<<" has been deleted successfully."<<endl;
    }else{
        cout<<"Passenger with passport number "<<passNum<<" not found."<<endl;
    }
    passengerM();
} 


  void update(){
    string passNum;
    char ch;
    cout<<"Enter the passport number: ";
    cin>>passNum;

    ifstream file("passengers.csv");
    ofstream temp("temp.csv");

    string line;
    bool found=false;

    while(getline(file,line)){
        stringstream ss(line);
        string word;
        getline(ss,word,','); 
        if (word==passNum) {
            found=true;
            vector<string> val;
            stringstream s(line);
            string word;
            while(getline(s,word,',')){
                val.push_back(word);
            }
            do{
                cout<<"\nWhat do you want to update?\n";
                cout<<"1. First Name\n";
                cout<<"2. Last Name\n";
                cout<<"3. Email\n";
                cout<<"4. Phone Number\n";
                cout<<"5. Address\n";
                cout<<"6. Nationality\n";
                cout<<"7. Date of Birth\n";
                int choice;
                cin>>choice;
                string newValue;
                switch(choice) {
                    case 1:
                        cout<<"Enter new first name: ";
                        cin>>newValue;
                        val[1] = newValue;
                        break;
                    case 2:
                        cout<<"Enter new last name: ";
                        cin>>newValue;
                        val[2] = newValue;
                        break;
                    case 3:
                        cout<<"Enter new email: ";
                        cin>>newValue;
                        val[3] = newValue;
                        break;
                    case 4:
                        cout<<"Enter new phone number: ";
                        cin>>newValue;
                        val[4] = newValue;
                        break;
                    case 5:
                        cout<<"Enter new address: ";
                        cin>>newValue;
                        val[5] = newValue;
                        break;
                    case 6:
                        cout<<"Enter new nationality: ";
                        cin>>newValue;
                        val[6] = newValue;
                        break;
                    case 7:
                        cout<<"Enter new date of birth: ";
                        cin>>newValue;
                        val[7] = newValue;
                        break;
                    default:
                        cout<<"Invalid choice. Please try again.\n";
                        break;
                }
                cout<<"Do you want to update anything else? (Y/N): ";
                cin>>ch;
            }while(ch=='Y'||ch=='y');
            for (int i=0;i<val.size();i++) {
                temp<<val[i];
                if (i<val.size()-1){
                    temp<<",";
                }else{
                    temp<<endl;
                }
            }
        }else{
            temp<<line<<endl;
        }
    }
    file.close();
    temp.close();

    if(found){
        remove("passengers.csv");
        rename("temp.csv","passengers.csv");
        cout<<"Passenger information updated successfully."<<endl;
    }else{
        cout<<"Passenger with passport number "<<passNum<<" not found."<<endl;
    }
    passengerM();
}
};

void paymentM(double price){
	srand(time(0));
	int c;
	bool ch=false;
	string pay;
	cout<<"\nYour Total Payment will be $"<<price<<endl<<endl;
	cout<<"\n Which payment method you want to choose\n1: Credit Card\n2: Paypal\n3: Zelle\n";
	cout<<"Enter the choice :";
	cin>>c;
	
	do{
		switch(c){
		case 1:
			pay="Credit Card";
			ch=false;
		break;
		case 2:
			pay="Paypal";
			ch=false;
		break;
		case 3:
			pay="Zelle";
			ch=false;
		break;
		default:
			cout<<"You have selected the wrong option : \n";
			cout<<"Kindly Select the right option : \n";
		    ch=true;
		  break;
	    }
	}while(ch);
	
	cout<<"Processing the Payment of $"<<price<<"\n";
	Sleep(1200);
	
	cout<<"\nPayment recived \n";
	cout<<"Recipet number : "<<rand()<<endl;
	
	cout<<"Your Booking is confirmed\n";
	cout<<"\n** Thanks For Booking with us **\n";
}


void mainMenu(){
	int choice;
	int pass=1001;
	cout<<"----------Flight Mangement System-----------\n";
	cout<<"1: Admin\n";
	cout<<"2: Passenger\n";
	cout<<"3: Exit\n";

	
	do{
		cout<<"Enter the choice : ";
		cin>>choice;
		
		switch(choice){
		case 1:
			cout<<"Enter the admin pass to continue....\n";
			cin>>pass;
			if(pass==1001){
			adminMenu();	
			}
			else{
				cout<<"you have entered wrong pass\n";
			}
			break;
		case 2:
			passengerMenu();
			break;
		case 3:
			Sleep(1200);
			cout<<"******* Thanks for choosing us *******\n";
			cout<<"Exiting.........\n";
			exit(0);
			break;
		default:
			cout<<"Kindly enter right choice.....\n";
			break;
 	}
  }while(choice!=3);
}

void adminMenu(){
	int choice;
	bool check=false;
	
	cout<<"\n-------Admin-------\n";
	cout<<"1: Add flight\n";
	cout<<"2: Remove Flight\n";
    cout<<"3: Search Flight\n";
    cout<<"4: Update Flight\n";
    cout<<"5: Manage Staff\n";
    cout<<"6: Return to main menu\n";
    
    Flight flight;
    
    do{
    	cout<<"Enter the option : \n";
        cin>>choice;
    	switch(choice){
    	case 1:
    	    flight.addFlight();
    	    break;
    	case 2:
    		flight.removeFlight();
    		break;
    	case 3:
    		flight.searchFlight();
    		break;
    	case 4: 
    	    flight.updateFlight();
    	    break;
    	case 5:
    		staffMenu();
    	break;
    	case 6:
    		mainMenu();
    		break;
    	default:
    		cout<<"Enter the right choice : ";
    		check=true;
    		break;
	    }
	}while(check);

}

void staffMenu(){
	int choice;
	cout<<"-------- Welcome to Staff menu------------\n";
	cout<<"1: Add Staff \n";
	cout<<"2: Remove staff\n";
	cout<<"3: Update\n";
	cout<<"4: Return to main menu\n";

	
	Staff s;
	
	do{
		cout<<"Enter Option : ";
     	cin>>choice;
     	
		switch(choice){
		case 1:
			s.addStaff();
		break;
		case 2:
			s.removeStaff();
		break;
		case 3:
			s.updateStaff();
		break;
		case 4:
			mainMenu();
		break;
		default:
			cout<<"OOPs!  Wrong choice...\n";
	}
}while(choice!=4);
	
	
}

void passengerM(){
	bool c=false;
	cout<<"<--------Passenger Menu----------->\n\n";
	cout<<"1: Book a flight\n";
	cout<<"2: Cancel Booking\n";
	cout<<"3: Update Information\n";
	cout<<"4: Return to mainMenu\n";
	cout<<"-------------------\n";
	
	int choice;
	
	Passenger p;
	do{
		cout<<"Enter option : ";
	    cin>>choice;
		switch(choice){
		case 1:
			p.bookflight();
		break;
		case 2:
			p.deletePas();
		break;
		case 3:
			p.update();
		break;
		case 4:
			mainMenu();
		break;
		default:
			cout<<"Plz enter the the right choice...\n";
		break;
	
	   }
    }while(choice!=4);

}

void passengerMenu(){
	int choice;
	User user;
	cout<<"-------Welcome to Passenger Menu-------\n";
	cout<<"1: Login\n";
	cout<<"2: Sign up\n";
	cout<<"3: Return to mainMenu\n";
	
	do{
		cout<<"Enter the Option : ";
		cin>>choice;
		
		switch(choice){   
		case 1:
			user.login();
		break;
		case 2:
			user.signup();
		break;	
		case 3:
			mainMenu();
		break;
		default:
			cout<<"Enter the right choice....\n";
		break;
	}
}while(choice!=3);
	
}

int main(){
	mainMenu();
}





