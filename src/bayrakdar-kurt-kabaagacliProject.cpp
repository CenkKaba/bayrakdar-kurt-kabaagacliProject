//============================================================================
// Name        : bayrakdar-kurt-kabaagacliProject.cpp
// Author      : ErkinKurt-H.MelihBayrakdar-CenkKabaagacli
// Version     :
// Copyright   :
// Description : SE311 2018 Project
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
//Forward declarations...
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

    void setPhoneNumber(string phoneNumber){this->phoneNumber = phoneNumber;}
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

//Using Command Pattern
//Command Pattern --> Receiver(1).
class Radiology{
public:
    void ActionEndocrinologyTest(Patient *p){
        cout << "Endocrinology test has been done for the patient: " << p->getName() << endl;
    }
    void ActionXrayTest(Patient *p){
        cout << "Xray test has been done for the patient: " << p->getName() << endl;
    }
    void ActionEKGTest(Patient *p){
        cout << "EKG test has been done for the patient: " << p->getName() << endl;
    }
    static Radiology* getInstance(){
        if(instance == NULL){
            instance = new Radiology();
        }
        return instance;
    }
private:
    static Radiology* instance;
    Radiology(){};
};

//Using Command Pattern
//Command Pattern ----> Receiver (2)
class Laboratory {
public:
    void ActionEndocrinologyBloodTest(Patient *p){
        cout << "Endocrinology blood test has been done for the patient" << p->getName() << endl;
    }
    void ActionOrthologyBloodTest(Patient *p){
        cout << "Orthology blood test has been done for the patient." << p->getName() << endl;
    }
    void ActionCardiologyBloodTest(Patient *p){
        cout << "Cardiology blood test has been done for the patient" << p->getName() << endl;
    }
};

//Using Command Pattern.
//Command Pattern --> Abstract Command(1).
class RadioTest {
public:
    virtual void ExecuteRadioTest(Patient *p) = 0;
    virtual void setRadiology(Radiology *_r){
        r = _r;
    }
protected:
    Radiology *r;
};

//Using Command Pattern
//Command Pattern --> Concrete Command(1).
class EndocrinologyTest : public RadioTest{
public:
    void ExecuteRadioTest(Patient *p){
        r->ActionEndocrinologyTest(p);
    }
};

//Using Command Pattern
//Command Pattern --> Concrete Command(1)
class XRAY : public RadioTest{
public:
    void ExecuteRadioTest(Patient *p){
        r->ActionXrayTest(p);
    }
};

//Using Command Pattern
//Command Pattern --> Concrete Command(1).
class EKG : public RadioTest{
public:
    void ExecuteRadioTest(Patient *p){
        r->ActionEndocrinologyTest(p);
    }
};



//Using Command Pattern.
//Command Pattern --> Abstract Command(2).
class LabTest {
public:
    virtual void ExecuteLabTest(Patient *p) = 0;
    virtual void setLabratory(Laboratory *_lab){
        lab = _lab;
    }
protected:
    Laboratory *lab;
};

//Using Command Pattern
//Command Pattern --> Concrete Command(2).
class EndocrinologyBloodTest : public LabTest {
public:
    void ExecuteLabTest(Patient *p){
        lab->ActionEndocrinologyBloodTest(p);
    }
};

//Using Command Pattern
//Command Pattern --> Concrete Command(2).
class OrthologyBloodTest : public LabTest {
public:
    void ExecuteLabTest(Patient *p){
        lab->ActionOrthologyBloodTest(p);
    }
};

//Using Command Pattern
//Command Pattern --> Concrete Command(2).
class CardiologyBloodTest : public LabTest{
public:
    void ExecuteLabTest(Patient *p){
        lab->ActionCardiologyBloodTest(p);
    }
};


//Using Abstract Factory, Template Pattern
//Abstract Factory Pattern ---> Abstract Factory
//Template method ----> Record Patient.
class Department {
public:
    virtual RadioTest* CreateRadioTest(Radiology *r) = 0;
    virtual LabTest* CreateLabTest(Laboratory *lab) = 0;
    virtual void RecordPatient(Patient *p){
        bool status = CheckPersonalDemgoraficInformation(p) && CheckInsuranceInformation(p)
                        && CheckPastMedicalHistory(p) && CheckConsentForm(p);
        cout << "Status : " << CheckPersonalDemgoraficInformation(p) << CheckInsuranceInformation(p) << CheckPastMedicalHistory(p) << CheckConsentForm(p) <<endl;
        if(status){
            cout << "Patient record has successfully registered." << endl;
            patients.push_back(p);
        }
        else
            cout << "Patient record has failed." << endl;
    }

    bool CheckPersonalDemgoraficInformation(Patient *p){
        if(p->getEmail().empty() || p->getPhoneNumber().empty()){
            return false;
        }
        else
            return true;
    }

    //Assumption: If patient is already in the departments record, don't register the patient again, else register the patient.
    //We did not assume that it would differ for each department...
    bool CheckPastMedicalHistory(Patient *p){
        for(int i = 0; i < patients.size(); i++){
            if(p->getEmail() == patients[i]->getEmail()){

                return false;
            }
        }
        return true;
    }
    virtual bool CheckInsuranceInformation(Patient *p) = 0;

    virtual bool CheckConsentForm(Patient *p) = 0;



private:
    vector<Patient*> patients;
};

//Using Abstract Factory Pattern
//Abstract Factory Pattern ---> Concrete Factory
class CardiologyClinic : public Department{
public:
    RadioTest* CreateRadioTest(Radiology *r){
        EKG *e = new EKG();
        e->setRadiology(r);
        return e;
    }
    LabTest* CreateLabTest(Laboratory *lab){
        CardiologyBloodTest *c = new CardiologyBloodTest();
        c->setLabratory(lab);
        return c;
    }
    //Assumption: Cardiology accepts Government insurance and all the other insurance.
    bool CheckInsuranceInformation(Patient *p){
        if(p->getInsurance().empty())
            return false;
        else{
         return true;
        }
    }

    bool CheckConsentForm(Patient *p){
        cout << "This is Cardiology Consent Form : " << endl << "Your signature please." << endl;
        if(p->getSignature().empty())
            return false;
        else
            return true;
    }

    CardiologyClinic(){}
};

//Using Abstract Factory Pattern
//Abstract Factory Pattern ---> Concrete Factory
class OrthopedicsClinic : public Department {
public:
    RadioTest* CreateRadioTest(Radiology *r){
        XRAY *x = new XRAY();
        x->setRadiology(r);
        return x;
    }
    LabTest* CreateLabTest(Laboratory *lab){
        OrthologyBloodTest *ort = new OrthologyBloodTest();
        ort->setLabratory(lab);
        return ort;
    }

    //Assumption: Orthopedics does not accept Government insurance but, it accepts all the other insurance.
    bool CheckInsuranceInformation(Patient *p){
        if(p->getInsurance() == "Goverment" || p->getInsurance().empty())
            return false;
        else{
         return true;
        }
    }

    bool CheckConsentForm(Patient *p){
        cout << "This is Orthopedics Consent Form : " << endl << "Your signature please." << endl;
        if(p->getSignature().empty())
            return false;
        else
            return true;
    }

    OrthopedicsClinic(){}

};

//Using Abstract Factory Pattern
//Abstract Factory Pattern ---> Concrete Factory
class EndocrinologyClinic : public Department{
public:
    RadioTest* CreateRadioTest(Radiology *r){
        EndocrinologyTest *e = new EndocrinologyTest();
        e->setRadiology(r);
        return e;
    }
    LabTest* CreateLabTest(Laboratory *lab){
        EndocrinologyBloodTest *endo = new EndocrinologyBloodTest();
        endo->setLabratory(lab);
        return endo;
    }
    //Assumption: Endocrinology does not accept Government insurance excepts all the other insurance.
    bool CheckInsuranceInformation(Patient *p){
        if(p->getInsurance() == "Goverment" || p->getInsurance().empty())
            return false;
        else{
         return true;
        }
    }

    bool CheckConsentForm(Patient *p){
        cout << "This is Endocrinology Consent Form : " << endl << "Your signature please." << endl;
        if(p->getSignature().empty())
            return false;
        else
            return true;
    }
    EndocrinologyClinic(){}
};

//Using Command Pattern, AbstractFactory
//Command -----> Invoker. //AbstractFactory ----> Client
class Doctor {
public:
    void OrderRadioTest(){
        radioTest->ExecuteRadioTest(patient);
    }
    void OrderLabTest(){
        labTest->ExecuteLabTest(patient);
    }
    void setPatient(Patient *p){
        this->patient = p;
    }
    void createRadiologyTest(Department *d, Radiology *r){
        radioTest = d->CreateRadioTest(r);
    }
    void createLaboratoryTest(Department *d, Laboratory *lab){
        labTest = d->CreateLabTest(lab);
    }
private:
    Patient *patient;
    RadioTest *radioTest;
    LabTest *labTest;
};
Radiology *Radiology::instance = NULL;

int main() {
    Doctor *dc = new Doctor();
    Patient *motherPatient = new Patient();
    motherPatient->setName("Erkin Russia");
    motherPatient->setEmail("ErkinKurt@gmail.com");
    motherPatient->setPhoneNumber("0505050550");
    motherPatient->setSignature("BabaSignature");
    motherPatient->setInsurance("OtherInsurance");
    Subject *drug = new Drug();
    Observer *patient = new Patient();
    drug->Attach(patient);

    drug->setDrugName("Lefkosaa ORTAM");
    vector<string> side;
    side.push_back("Circir");   side.push_back("Bok bocegi"); side.push_back("Aglama hamza");
    drug->AddSideEffects(side);
    Department *orthopedicsClinic = new OrthopedicsClinic();
    orthopedicsClinic->RecordPatient(motherPatient);
    dc->setPatient(motherPatient);
    Laboratory *lab = new Laboratory();

    Radiology *r = Radiology::getInstance();
    dc->createLaboratoryTest(orthopedicsClinic, lab);
    dc->createRadiologyTest(orthopedicsClinic, r);
    dc->OrderRadioTest();

	return 0;
}
