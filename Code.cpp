#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <dos.h>
using namespace std;
string *slice(string name, char chare)
{
    string *data = new string[7];
    string test;
    int k = 0, j = 0, l = 0;
    for (int i = 0; i < name.size(); i++)
    {
        test = name.substr(j, l);
        if (name[i] == chare)
        {
            data[k] = test;
            k++;
            j = i + 1;
            l = 0;
            continue;
        }
        l++;
    }
    return data;
}

class Patient
{
    int id;
    string name;
    int age;
    string phoneNumber;
    string bloodGroup;
    string gender;
    string email;

public:
    Patient()
    {
    }
    Patient(int id, string name, string phoneNumber, string bloodGroup, string gender, string email)
    {
        this->id = id;
        this->name = name;
        this->phoneNumber = phoneNumber;
        this->bloodGroup = bloodGroup;
        this->gender = gender;
        this->email = email;
    }
    void setid()
    {
        // cin >> this->id
        while (!(cin >> this->id))
        {

            cout << "Error: this is not right data type for ID." << endl;
            system("pause");
            cout << "Enter Paitent ID             : ";
            cin.clear();
            cin.ignore(123456, '\n');
        }
    }
    void setname()
    {
        cin.ignore();
        getline(cin, this->name);
    }
    void setAge()
    {
        while (!(cin >> this->age))
        {
            cout << "Error: this is not right data type for Age." << endl;
            cout << "Enter Paitent Age             : ";
            cin.clear();
            cin.ignore(123456, '\n');
        }
    }
    void setPhoneNumber()
    {
        cin >> this->phoneNumber;
    }
    void setBloodGroup()
    {
        cout << "  Enter Patient Blood Group    : ";
        cin >> this->bloodGroup;
        if (this->bloodGroup == "AB+" || this->bloodGroup == "AB-" ||
            this->bloodGroup == "A+" || this->bloodGroup == "A-" ||
            this->bloodGroup == "B+" || this->bloodGroup == "B-" ||
            this->bloodGroup == "O+" || this->bloodGroup == "O-")
        {
        }
        else
        {
            cout << "Wrong Blood Group!" << endl;
            this->setBloodGroup();
        }
    }
    void setGender()
    {
        cin >> this->gender;
        if ((this->gender == "M") || (this->gender == "F") || (this->gender == "m") || (this->gender == "f"))
        {
        }
        else
        {
            cout << "Error: incorrent input." << endl;
            cout << "Enter Patient Gender(M/F)         : ";
            this->setGender();
        }
    }
    void setEmail()
    {
        cin >> this->email;
    }
    // =================================================================
    int getid()
    {
        return this->id;
    }
    string getname()
    {
        return this->name;
    }
    int getAge()
    {
        return this->age;
    }
    string getPhoneNumber()
    {
        return this->phoneNumber;
    }
    string getBloodGroup()
    {
        return this->bloodGroup;
    }
    string getGender()
    {
        return this->gender;
    }
    string getEmail()
    {
        return this->email;
    }
};


class Appointment{
    public:

    int patientId;
    int priority;
    string time;
    string date;
    int day;
    int month;
    int year;

    Appointment(){
		this->patientId = 0;
		this->priority = 10;
		this->time = "";
		this->date = "";
		this->day = 0;
		this->month = 0;
		this->year = 2022;
	}
    
    Appointment* newAppointment(){
    	Appointment* temp = new Appointment();
    	setDate();
    	setTime();
    	return temp;
	}

    void setTime(){
    	cout << "Enter Appointment Time: ";
        cin >> this->time;
    }

    void setDay(string day){
        this->day = stoi(day);
    }

    void setMonth(string month){
        this->month = stoi(month);
    }

    void setYear(string year){
        this->year = stoi(year);
    }

    void setDate(){
    	cout << "Enter Appointment Date: ";
        cin >> this->date;
        setDay(date.substr(0, 2));
        setMonth(date.substr(3, 5));
        setYear(date.substr(6, 8));
    }

    void setPatientId(int patientId){
        this->patientId = patientId;
    }

    void setPriority(int priority){
        this->priority = priority;
    }

    string getDate(){
        return date;
    }

    string getTime(){
        return time;
    }

    int getDay(){
		return day;
	}

    int getMonth(){
		return month;
	}

	int getYear(){
		return year;
	}

    int getPatientId(){
        return patientId;
    }
    int getPriority(){
        return priority;
    }
};


class AppointmentQueue{
    public:
    	
    const static int TOTAL_SLOT = 10;
    int nextSlot;
    Appointment* queue;
    
    AppointmentQueue(){
    	queue = new Appointment[TOTAL_SLOT];
    	nextSlot = 0;
	}

    void makeAppointment(int patientId, int priority){
        queue[nextSlot].setPatientId(patientId);
        queue[nextSlot].setPriority(priority);
        queue[nextSlot].setDate();
        queue[nextSlot].setTime();
        nextSlot++;

        if(nextSlot > 0){
    		for (int i = nextSlot/2 - 1; i >= 0; i--){
				heapify(i);
			}
        }
    }
	  
    void heapify(int i){
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;

        if(left < nextSlot && queue[left].priority < queue[smallest].priority){
            smallest = left;
        }
        else{
            smallest = i;
        }
        
        if(right < nextSlot && queue[right].priority < queue[smallest].priority){
            smallest = right;
        }

		Appointment temp = queue[i];
		queue[i] = queue[smallest];
		queue[smallest] = temp;
			
        if(smallest != i){
            heapify(smallest);
        }

        for(int i =0;i<nextSlot;i++){
            cout<<endl<<queue[i].patientId;
        }
    }

    void deQueue(){
		Appointment temp = queue[0];
		queue[0] = queue[nextSlot-1];
		queue[nextSlot-1] = temp;

		nextSlot--;

        for (int i = nextSlot/2 - 1; i >= 0; i--){
				heapify(i);
		}
	}


};


class Hospital
{
public:
    AppointmentQueue* appointmentQueue;
    Patient* patient;
    int Data_Size;
    string totalData[10000];
    string appointmentAllData[100];

    Hospital(){
        appointmentQueue = new AppointmentQueue();
        Data_Size = loadAllData();
        loadAllAppointmentData();
    }



    int loadAllData()
    {
        string lines;
        int i = 0;
        fstream myFile;
        myFile.open("Patientdata.txt", ios::in);
        if (myFile.is_open())
        {
            while (getline(myFile, lines))
            {
                totalData[i] = lines;
                i++;
            }
        }
        myFile.close();
        return i;
    }

    int loadAllAppointmentData()
    {
        appointmentQueue->nextSlot = 0;
        string lines;
        string *temp;
        int i = 0;
        fstream myFile;
        myFile.open("Appointmentdata.txt", ios::in);
        if (myFile.is_open())
        {
            while (getline(myFile, lines))
            {
                // [appointmentQueue->nextSlot] = lines;
                cout<<lines<<endl;
                temp = slice(lines, '|');
                appointmentQueue->queue[i].patientId = stoi(temp[0]);
                appointmentQueue->queue[i].priority = stoi(temp[1]);
                appointmentQueue->queue[i].time = temp[2];
                appointmentQueue->queue[i].date = temp[3];
                i++;
            }
        }
        appointmentQueue->nextSlot = i;
        for (int j = appointmentQueue->nextSlot/2 - 1; j >= 0; j--){
            appointmentQueue->heapify(j);	
		}

        myFile.close();
        // i = appointmentQueue->nextSlot;
        return i;
    }


    void beforeMakeAppointment(int patientId){
        int priority;

        cout << "Enter patient severity: ";
        cin >> priority;

        this->appointmentQueue->makeAppointment(patientId, priority);
        saveAppointment();
    }

    bool saveAppointment(){
        fstream myFile;
        string appointmentData;
        myFile.open("AppointmentData.txt", ios::out);
        for(int i=0; i < appointmentQueue->nextSlot ; i++){
            appointmentData = to_string(appointmentQueue->queue[i].getPatientId()) + "|" + to_string(appointmentQueue->queue[i].getPriority()) + "|" + appointmentQueue->queue[i].getTime() + "|" + appointmentQueue->queue[i].getDate() + "|\n";

            // cout<< appointmentData << endl;

            if (myFile.is_open()){
                myFile << appointmentData;
            }
        }
        
        myFile.close();
        
        return true;
    }

    bool savePatientData(){
        fstream myFile;
        string appointmentData;
        myFile.open("Patientdata.txt", ios::out);
        for(int i=0; i < Data_Size ; i++){
            if (myFile.is_open()){
                myFile << totalData[i] << endl;
            }
        }
        
        myFile.close();
        
        return true;
    }


    void deletePatientAppointment(int id)
    {
        for(int i=0;i<appointmentQueue->nextSlot;i++){
            if(appointmentQueue->queue[i].patientId == id){
                Appointment temp = appointmentQueue->queue[appointmentQueue->nextSlot-1];
                appointmentQueue->queue[appointmentQueue->nextSlot] = appointmentQueue->queue[i];
                appointmentQueue->queue[i] = temp;
                appointmentQueue->nextSlot--;
                for (int j = appointmentQueue->nextSlot/2 - 1; j >= 0; j--){
                    appointmentQueue->heapify(j);
			    }
            }
        }
        saveAppointment();

        cout << "Message : This Patient data has been removed succesfully." << endl;
    }

    void displayAllAppointment()
    {
        system("cls");
        fstream myFile;
        myFile.open("AppointmentData.txt", ios::in);
        if (myFile.is_open())
        {
            string lines;
            string *data;
            int i = 1;
            cout << " -----------------------------------------------------------------------------------------------" << endl;
            cout << "|\t\t\t\tHOSPITAL'S ALL PATIENT APPOINTMENT\t\t\t\t|" << endl;
            cout << " -----------------------------------------------------------------------------------------------" << endl;
            cout << "|  ID\tSeverity\tTime\tDate" << endl;
            cout << " -----------------------------------------------------------------------------------------------" << endl;
            while (getline(myFile, lines))
            {
                data = slice(lines, '|');
                cout << "  " << data[0] << "\t    " << data[1] << "\t\t" << data[2] << "\t" << data[3] << endl;
                i++;
            }
        }
        myFile.close();
    }


    bool registerPatient()
    {
        system("cls");
        cout << " -------------------------------------------------------" << endl;
        cout << "|\t\tHOSPITAL MANAGEMENT SYSTEM\t\t|" << endl;
        cout << " -------------------------------------------------------" << endl;
        cout << "|\t\t  PATIENT REGISTERATION\t\t\t|" << endl;
        cout << " -------------------------------------------------------" << endl;
        Patient *pa = new Patient();
        fstream myFile;
        cout << "  Enter Paitent ID             : ";
        pa->setid();
        if (this->searchPatient(pa->getid()))
        {
            cout << "Patient Already Exists!!" << endl;
            this->registerPatient();
        }
        cout << " -------------------------------------------------------" << endl;
        cout << "  Enter Paitent Name           : ";
        pa->setname();
        cout << " -------------------------------------------------------" << endl;
        cout << "  Enter Paitent Phone Number   : ";
        pa->setPhoneNumber();
        cout << " -------------------------------------------------------" << endl;
        // cout << "Enter Patient Blood Group    : ";
        pa->setBloodGroup();
        cout << " -------------------------------------------------------" << endl;
        cout << "  Enter Patient Age            : ";
        pa->setAge();
        cout << " -------------------------------------------------------" << endl;
        cout << "  Enter Patient Gender(M/F)    : ";
        pa->setGender();
        cout << " -------------------------------------------------------" << endl;
        cout << "  Enter Patient Email          : ";
        pa->setEmail();
        cout << " -------------------------------------------------------" << endl;
        
        totalData[Data_Size] = to_string(pa->getid()) + "|" + pa->getname() + "|" + to_string(pa->getAge()) + "|" + pa->getPhoneNumber() + "|" + pa->getBloodGroup() + "|" + pa->getGender() + "|" + pa->getEmail() + "|";
        
        Data_Size++;
        
        sortit();
        cout << "Message : Patient  has successfully Registered." << endl;
        return true;
    }

    void displayAllPatientData()
    {
        system("cls");
        fstream myFile;
        myFile.open("Patientdata.txt", ios::in);
        if (myFile.is_open())
        {
            string lines;
            string *data;
            int i = 1;
            cout << " -----------------------------------------------------------------------------------------------" << endl;
            cout << "|\t\t\t\tHOSPITAL'S ALL PATIENT DATA\t\t\t\t\t|" << endl;
            cout << " -----------------------------------------------------------------------------------------------" << endl;
            cout << "|  ID\t Name\t\tAGE\t  Phone No\tBG   Gender\t    Email\t\t\t|" << endl;
            cout << " -----------------------------------------------------------------------------------------------" << endl;
            while (getline(myFile, lines))
            {
                data = slice(lines, '|');
                cout << "  " << data[0] << "\t" << data[1] << "\t" << data[2] << "\t" << data[3] << "\t" << data[4] << "\t" << data[5] << "\t" << data[6] << endl;
                i++;
            }
        }
        myFile.close();
    }
    
    bool searchPatient(int id)
    {
        string key = to_string(id);
        string *data;
        int left = 0;
        int right = sortit();
        while (left <= right)
        {
            int mid = (left + right) / 2;
            data = slice(totalData[mid], '|');
            // if (stoi(data[0]) == id)
            if (data[0] == key)
            {
                return true;
            }
            else if (data[0] < key)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return false;
    }
    void getPatientInfo(int id)
    {
        system("cls");
        cout << " -----------------------------------------------------------------------------------------------" << endl;
        cout << "|\t\t\t\tHOSPITAL'S ALL PATIENT DATA\t\t\t\t\t|" << endl;
        cout << " -----------------------------------------------------------------------------------------------" << endl;
        cout << "   ID\tName\t\tAGE\t  Phone No\tBG   Gender\t    Email" << endl;
        if (this->searchPatient(id))
        {
            fstream myFile;
            myFile.open("Patientdata.txt", ios::in);
            if (myFile.is_open())
            {
                string lines;
                string *data;
                while (getline(myFile, lines))
                {
                    data = slice(lines, '|');
                    if (stoi(data[0]) == id)
                    {
                        cout << "  " << data[0] << "\t" << data[1] << "\t" << data[2] << "\t" << data[3] << "\t" << data[4] << "\t" << data[5] << "\t" << data[6] << endl;
                    }
                }
            }
            myFile.close();
        }
        cout << "Message : Patient record has been Found!." << endl;
    }
    void deletePatientRecord(int id)
    {

        string *data;
        int j = this->loadAllData();
        fstream myFile;
        myFile.open("Patientdata.txt", ios::out);
        for (int i = 0; i < j; i++)
        {
            data = slice(totalData[i], '|');
            if (stoi(data[0]) == id)
            {
                continue;
            }
            myFile << totalData[i] << endl;
        }

        myFile.close();
        cout << "Message : This Patient data has been removed succesfully." << endl;
    }
    void editPatientRecord(int id)
    {

        this->deletePatientRecord(id);
        system("cls");
        cout << " -------------------------------------------------------" << endl;
        cout << "|\t\tHOSPITAL MANAGEMENT SYSTEM\t\t|" << endl;
        cout << " -------------------------------------------------------" << endl;
        cout << "|\t\t  UPDATE PATIENT'S RECORD\t\t|" << endl;
        cout << " -------------------------------------------------------" << endl;
        Patient *pa = new Patient();
        fstream myFile;
        cout << "  Enter Paitent Name           : ";
        pa->setname();
        cout << " -------------------------------------------------------" << endl;
        cout << "  Enter Paitent Phone Number   : ";
        pa->setPhoneNumber();
        cout << " -------------------------------------------------------" << endl;
        // cout << "Enter Patient Blood Group    : ";
        pa->setBloodGroup();
        cout << " -------------------------------------------------------" << endl;
        cout << "  Enter Patient Age            : ";
        pa->setAge();
        cout << " -------------------------------------------------------" << endl;
        cout << "  Enter Patient Gender(M/F)    : ";
        pa->setGender();
        cout << " -------------------------------------------------------" << endl;
        cout << "  Enter Patient Email          : ";
        pa->setEmail();
        cout << " -------------------------------------------------------" << endl;

        string totaldata = to_string(id) + "|" + pa->getname() + "|" + to_string(pa->getAge()) + "|" + pa->getPhoneNumber() + "|" + pa->getBloodGroup() + "|" + pa->getGender() + "|" + pa->getEmail() + "|\n";
        myFile.open("Patientdata.txt", ios::app);
        if (myFile.is_open())
        {
            myFile << totaldata;
        }
        myFile.close();
        cout << "Message : Patient record has successfully updated." << endl;
    }

    int sortit()
    {
        string temp, *temp1, *key, *data1;
        int n = Data_Size;

        for (int i = 1; i < n; i++)
        {
            key = slice(totalData[i], '|');
            int j = i;
            // data1 = slice(totalData[j - 1], '|');
            temp = totalData[i];
            temp1 = slice(totalData[i], '|');
            while (j > 0 && temp1[0] <= (slice(totalData[j - 1], '|')[0]))
            {
                totalData[j] = totalData[j - 1];
                j = j - 1;
            }
            totalData[j] = temp;
        }

        
        // for (int i = 0; i < n; i++)
        // {
        //     cout << totalData[i] << endl;
        // }

        savePatientData();

        return n;
    }
};

bool loginFunc(string userName, string userPass)
{
    if (userName == "Admin" && userPass == "ADMIN")
    {
        return true;
    }
    return false;
}
void loadingFunc()
{
    system("color A");
    cout << "\n\n\n\t\t\t\t\t\t    loading......\n\n";
    char a = 124, b = 219;
    cout << "\t\t\t\t";
    for (int i = 0; i <= 50; i++)
        cout << a;
    cout << "\r";
    cout << "\t\t\t\t";
    for (int i = 0; i <= 50; i++)
    {
        cout << b;
        for (int j = 0; j <= 1e7; j++);
            
    }
    system("cls");
}
int main()
{
    cout << setw(25);
    loadingFunc();
    Hospital *hos = new Hospital();
Login:
    system("cls");
    cout << " -------------------------------------------------------" << endl;
    cout << "|\t\tHOSPITAL MANAGEMENT SYSTEM\t\t|" << endl;
    cout << " -------------------------------------------------------" << endl;
    cout << "|\t\t\tLOGIN\t\t\t\t|" << endl;
    cout << " -------------------------------------------------------" << endl;
    string userName, userPass;
    int option = 0, id = 0;
    cout << "  Enter User Name : ";
    cin >> userName;
    cout << "  Enter Password  : ";
    cin >> userPass;

    if (loginFunc(userName, userPass))
    {
    options:
        system("cls");
        cout << " -------------------------------------------------------" << endl;
        cout << "|\t\tHOSPITAL MANAGEMENT SYSTEM\t\t|" << endl;
        cout << " -------------------------------------------------------" << endl;
        cout << "| (1) Register a patient\t\t\t\t|" << endl;
        cout << " -------------------------------------------------------" << endl;
        cout << "| (2) Edit Patient's Record\t\t\t\t|" << endl;
        cout << " -------------------------------------------------------" << endl;
        cout << "| (3) Remove Patient's Record\t\t\t\t|" << endl;
        cout << " -------------------------------------------------------" << endl;
        cout << "| (4) Search Patient's Record\t\t\t\t|" << endl;
        cout << " -------------------------------------------------------" << endl;
        cout << "| (5) Display all Patient's Record\t\t\t|" << endl;
        cout << " -------------------------------------------------------" << endl;
        cout << "| (6) Appointment for a Paitent\t\t\t\t|" << endl;
        cout << " -------------------------------------------------------" << endl;
        cout << "| (7) Remove Patient's Appointment\t\t\t|" << endl;
        cout << " -------------------------------------------------------" << endl;
        cout << "| (8) Display all Appointment Record\t\t\t|" << endl;
        cout << " -------------------------------------------------------" << endl;
        cout << "| (0) Exit\t\t\t\t\t\t|" << endl;
        cout << " -------------------------------------------------------\n\n" << endl;

        cout << "Please select your options : ";
        cin >> option;
        if (option == 1)
        {
            hos->registerPatient();
            system("pause");
            goto options;
        }
        else if (option == 2)
        {
            cout << "Enter Patient's ID : ";
            cin >> id;
            if (!hos->searchPatient(id))
            {
                cout << "Message : This Patient does not exist" << endl;
                system("pause");
                goto options;
            }
            else
            {
                hos->editPatientRecord(id);
            }
            goto options;
        }
        else if (option == 3)
        {
            system("cls");
            cout << " -------------------------------------------------------" << endl;
            cout << "|\t\tHOSPITAL MANAGEMENT SYSTEM\t\t|" << endl;
            cout << " -------------------------------------------------------" << endl;
            cout << "|\t\t  REMOVE PATIENT DATA\t\t\t|" << endl;
            cout << " -------------------------------------------------------" << endl;
            cout << "Enter Patient's ID : ";
            cin >> id;
            hos->deletePatientRecord(id);
            system("pause");
            goto options;
        }
        else if (option == 4)
        {

            system("cls");
            cout << " -------------------------------------------------------" << endl;
            cout << "|\t\tHOSPITAL MANAGEMENT SYSTEM\t\t|" << endl;
            cout << " -------------------------------------------------------" << endl;
            cout << "|\t\t     SEARCH PATIENT\t\t\t|" << endl;
            cout << " -------------------------------------------------------" << endl;

            cout << "  Enter Patient's ID : ";
            cin >> id;
            if (hos->searchPatient(id))
            {

                hos->getPatientInfo(id);
            }
            else
            {
                cout << "Error : This Patient does not Exits." << endl;
            }
            system("pause");
            goto options;
        }
        else if (option == 5)
        {
            hos->displayAllPatientData();
            system("pause");
            goto options;
        }
        else if (option == 6)
        {
            
            system("cls");
            cout << " -------------------------------------------------------" << endl;
            cout << "|\t\tHOSPITAL MANAGEMENT SYSTEM\t\t|" << endl;
            cout << " -------------------------------------------------------" << endl;
            cout << "|\t\t     PATIENT APPOINTMENT\t\t|" << endl;
            cout << " -------------------------------------------------------" << endl;

            cout << "  Enter Patient's ID : ";
            cin >> id;
            if (hos->searchPatient(id))
            {
                hos->beforeMakeAppointment(id);
            }
            else
            {
                cout << "Error : This Patient does not Exits." << endl;
            }
            system("pause");

            goto options;

        }
        else if (option == 7)
        {
            system("cls");
            cout << " -------------------------------------------------------" << endl;
            cout << "|\t\tHOSPITAL MANAGEMENT SYSTEM\t\t|" << endl;
            cout << " -------------------------------------------------------" << endl;
            cout << "|\t\tREMOVE PATIENT'S APPOINTMENT\t\t|" << endl;
            cout << " -------------------------------------------------------" << endl;


            int patientId;
            cout << "Enter Patient Id to remove Appointment: ";
            cin >> patientId;
            
            hos->deletePatientAppointment(patientId);
            system("pause");
            goto options;
        }
        else if(option == 8)
        {
            hos->displayAllAppointment();
            system("pause");
            goto options;
        }

        // else if(option == 9)
        // {
        //     hos->sortit();
        //     system("pause");
        //     goto options;
        // }

        else if (option == 0)
        {
            system("cls");
            system("exit");
            // goto Login;
        }
    }
    else
    {
        cout << "incorrent User-name & Password" << endl;
        system("pause");
        system("cls");
        goto Login;
    }

    return 0;
}
