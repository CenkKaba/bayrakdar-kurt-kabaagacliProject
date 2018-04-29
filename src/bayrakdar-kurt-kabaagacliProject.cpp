//============================================================================
// Name        : bayrakdar-kurt-kabaagacliProject.cpp
// Author      : ErkinKurt-H.MelihBayrakdar-CenkKabaagacli
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;


class Subject;
//Using observer pattern.
//Observer Interface
class Observer{
public:
	virtual void Update(Subject& subject) = 0;
};

//Using observer pattern.
//Subject Interface
class Subject {
public:
	virtual void Attach(Observer* observer){
		observers.push_back(observer);
	};
	//virtual void Detach(Observer* o){} //TODO Implement Detach later (Erkin)
	virtual void Notify(){
		for(unsigned int i = 0; i < observers.size() ; i++){
			observers[i]->Update(*this);
		}
	}

	virtual vector<string> GetSideEffects(){};

	virtual void AddSideEffects(vector<string> newSideEffects){};
	void setDrugName(string dName){}
	string getDrugName(){}

private:
	 vector<Observer*> observers;
};

//Using observer pattern.ExecuteRadioTest
//Subject of Prescription
class Drug : public Subject{
public:
    //GetState
	vector<string> GetSideEffects(){
		return sideEffects;
	}
	//SetState
	void AddSideEffects(vector<string> newSideEffects){
		sideEffects.insert(sideEffects.end(), newSideEffects.begin(), newSideEffects.end());
		//Notify observers...
		Notify();
	}
	void setDrugName(string dName){this->drugName = dName;}
	string getDrugName(){return this->drugName;}
private:
    string drugName;
    //State
	vector<string> sideEffects;
};
class RadioTest;
class LabTest;
//Using observer pattern.
//Observer of Prescription.
class Patient: public Observer{
public:
    Patient(){}
    Patient(string name, string email,string insurance, string signature): name(name), email(email),
        insurance(insurance), signature(signature){}

    //Add a drug to the prescription.
    void AddDrug(Drug *newDrug){
        drugs.push_back(newDrug);
    }
    void Update(Subject& sub){

        changedSideEffects = sub.GetSideEffects();
        cout << "Sent e-mail to this address." << endl;
        cout << "This drug's side effects has been changed. Current side effects are as follows:" << endl;

        for(int i = 0; i < changedSideEffects.size(); i++){

            cout << changedSideEffects[i] << endl;
        }
    }

    void setName(string name){this->name = name;}
    string getName(){return this->name;}

    void setEmail(string email){this->email = email;}
    string getEmail(){return this->email;}

    void setInsurance(string insurance){this->insurance = insurance;}
    string getInsurance(){return this->insurance;}

    void setSignature(string signature){this->signature = signature;}
    string getSignature(){return this->signature;}

    void setPhone(string phoneNumber){this->phoneNumber = phoneNumber;}
    string getPhoneNumber(){return this->phoneNumber;}

    vector<RadioTest*> getRadioTest(){return this->radioTests;}
    void AddRadioTest(RadioTest *radioTest){
        radioTests.push_back(radioTest);
    }

    vector<LabTest*> getLabTest(){return this->labTests;}
    void AddLabTest(LabTest *labTest){
        labTests.push_back(labTest);
    }

private:
    string name;
    string phoneNumber;
    string email;
    string insurance;
    string signature;
    vector<RadioTest*> radioTests;
    vector<LabTest*> labTests;
    //Drug list.
    vector<Drug*> drugs;
    //ObserverState
    vector<string> changedSideEffects;
};


//Using Command Pattern.
//Command Pattern --> Abstract receiver(1).
class RadioTest {
public:
    virtual void ActionRadioTest(Patient *p) = 0;
};

// Using Command Pattern
//Command Pattern --> Concrete receiver
class EndocrinologyTest : public RadioTest{
public:
    void ActionRadioTest(Patient *p){
        cout << "Endocrinology test has been done for the patient" << p->getName() << endl;
        //TODO Do we need to send the test result to the patient?
    }
};

//Using Command Pattern
//Command Pattern --> Concrete receiver.
class XRAY : public RadioTest{
public:
    void ActionRadioTest(Patient *p){
        cout << "XRAY test has been done for the patient." << p->getName() << endl;
    }
};

//Using Command Pattern
//Command Pattern --> Concrete receiver.
class EKG : public RadioTest{
public:
    void ActionRadioTest(Patient *p){
        cout << "EKG test has been done for the patient." << p->getName() << endl;
    }
};

//Using Command Pattern.
//Command Pattern --> Abstract receiver(2).
class LabTest {
public:
    virtual void ActionLabTest(Patient *p) = 0;
};

//Using Command Pattern
//Command Pattern --> Concrete receiver(2).
class EndocrinologyBloodTest : public LabTest {
public:
    void ActionLabTest(Patient *p){
        cout << "Endocrinology blood test has been done for the patient." << p->getName() << endl;
    }
};

//Using Command Pattern
//Command Pattern --> Concrete receiver(2).
class OrthopedicsBloodTest : public LabTest {
public:
    void ActionLabTest(Patient *p){
        cout << "Orthopedics blood test has been done for the patient." << p->getName() <<  endl;
    }
};

//Using Command Pattern
//Command Pattern --> Concrete receiver(2).
class CardiologyBloodTest : public LabTest{
public:
    void ActionLabTest(Patient *p){
        cout << "Cardiology blood test has been done for the patient." << p->getName() << endl;
    }
};

//Using Template Pattern, Abstract Factory and Command Pattern.
//Template pattern --> Abstract Template. Command Pattern ---> Abstract Command
class Clinic {
public:
    virtual void ExecuteRadioTest(Patient *p) = 0;
    virtual void ExecuteLabTest(Patient *p) = 0;

private:
    vector<Patient> patients;
};

//Using Command Pattern.
//Command Pattern --> Concrete Command.
class CardiologyClinic : public Clinic{
public:
    void ExecuteRadioTest(Patient *p){
        ekgTest->ActionRadioTest(p);
    }
    void ExecuteLabTest(Patient *p){
        cardiologyBloodTest->ActionLabTest(p);
    }
    CardiologyClinic(){}
    CardiologyClinic(RadioTest *ekgTest, LabTest *cardiologyBloodTest): ekgTest(ekgTest), cardiologyBloodTest(cardiologyBloodTest){}
private:
    RadioTest *ekgTest;
    LabTest *cardiologyBloodTest;
};

//Using Command Pattern.
//Command Pattern --> Concrete Command.
class OrthopedicsClinic : public Clinic {
public:
    void ExecuteRadioTest(Patient *p){
        xrayTest->ActionRadioTest(p);
    }
    void ExecuteLabTest(Patient *p){
        orthopedicsBloodTest->ActionLabTest(p);
    }
    OrthopedicsClinic(){}
    OrthopedicsClinic(RadioTest *xrayTest, LabTest* orthoBloodTest): xrayTest(xrayTest), orthopedicsBloodTest(orthoBloodTest){}
private:
    RadioTest *xrayTest;
    LabTest *orthopedicsBloodTest;
};

//Using Command Pattern.
//Command Pattern --> Concrete Command.
class EndocrinologyClinic : public Clinic{
public:
    void ExecuteRadioTest(Patient *p){
        endocrinologyTest->ActionRadioTest(p);
    }
    void ExecuteLabTest(Patient *p){
        endocrinologyBloodTest->ActionLabTest(p);
    }
    EndocrinologyClinic(){}
    EndocrinologyClinic(RadioTest *endocrinologyTest, LabTest *endocrinologyBloodTest) : endocrinologyTest(endocrinologyTest), endocrinologyBloodTest(endocrinologyBloodTest){}
private:
    RadioTest *endocrinologyTest;
    LabTest *endocrinologyBloodTest;
};

//Using Command Pattern.
//Command -----> Invoker.
class Doctor {
public:
    void PlaceRadioTest(Clinic *c){
        c->ExecuteRadioTest(patient);
    }
    void PlaceLabTest(Clinic *c){
        c->ExecuteLabTest(patient);
    }
    void setPatient(Patient *p){
        this->patient = p;
    }
private:
    Patient *patient;
};


int main() {
    Doctor *dc = new Doctor();
    Patient *motherPatient = new Patient();
    motherPatient->setName("Erkin Russia");
    Subject *drug = new Drug();
    Observer *patient = new Patient();
    drug->Attach(patient);
    dc->setPatient(motherPatient);
    LabTest *orto = new OrthopedicsBloodTest();
    RadioTest *ortoo = new XRAY();
    Clinic *mother = new OrthopedicsClinic(ortoo,orto);


    drug->setDrugName("Lefkosaa ORTAM");
    vector<string> side;
    side.push_back("Circir");   side.push_back("Bok bocegi"); side.push_back("Aglama hamza");
    drug->AddSideEffects(side);
    dc->PlaceLabTest(mother);

	return 0;
}
