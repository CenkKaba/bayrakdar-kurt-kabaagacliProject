//============================================================================
// Name        : bayrakdar-kurt-kabaagacliProject.cpp
// Author      : ErkinKurt-H.MelihBayrakdar-CenkKabaagacli
// Description : SE311 2018 Project
//============================================================================
#include <iostream>
#include <vector>
using namespace std;
//Forward declaration
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
	virtual void setDrugName(string dName){}
	virtual string getDrugName(){}
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
	void setDrugName(string dName){drugName = dName;}
	string getDrugName(){return drugName;}
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
        cout << "Sent e-mail to "<< email << endl;
        cout << sub.getDrugName() <<" side effects has been changed. Current side effects are as follows:" << endl;
        for(int i = 0; i < changedSideEffects.size(); i++){
            cout << changedSideEffects[i] << endl;
        }
        cout << endl;
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
    /*vector<LabTest*> getLabTest(){return this->labTests;}
    void AddLabTest(LabTest *labTest){
        labTests.push_back(labTest);
    }*/
    void printTestResults(){
        cout << "This is the test results for the patient : " << name << endl;
        for(int i = 0; i < testResults.size(); i++){
            cout << i+1 << ": " << testResults[i] << endl;
        }
    }
    void AddNewTestResults(string newTestResults){
		testResults.push_back(newTestResults);
	}
private:
    string name;
    string phoneNumber;
    string email;
    string insurance;
    string signature;
    vector<RadioTest*> radioTests;
    //vector<LabTest*> labTests;
    //Drug list.
    vector<Drug*> drugs;
    //ObserverState
    vector<string> changedSideEffects;
    //This is the vector to store the test result of the patient.
    vector<string> testResults;
};
//Using Command Pattern
//Command Pattern --> Receiver(1).
class Radiology{
public:
    void ActionEndocrinologyTest(Patient *p){
        string testResult = "Endocrinology test has been done ";
        p->AddNewTestResults(testResult);
        cout << testResult  << " for the patient: " << p->getName() << endl;
    }
    void ActionXrayTest(Patient *p){
        string testResult = "Xray test has been done ";
        p->AddNewTestResults(testResult);
        cout << testResult<<  " for the patient: " << p->getName() << endl;
    }
    void ActionEKGTest(Patient *p){
        string testResult = "EKG test has been done";
        p->AddNewTestResults(testResult);
        cout << testResult <<  " for the patient: "<< p->getName() << endl;
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
        string testResult = "Endocrinology blood test has been done";
        p->AddNewTestResults(testResult);
        cout << testResult<< " for the patient: " << p->getName() << endl;
    }
    void ActionOrthopedicsBloodTest(Patient *p){
        string testResult = "Orthopedics blood test has been done ";
        p->AddNewTestResults(testResult);
        cout << testResult << " for the patient: "<< p->getName() << endl;
    }
    void ActionCardiologyBloodTest(Patient *p){
        string testResult = "Cardiology blood test has been done ";
        p->AddNewTestResults(testResult);
        cout << testResult<< " for the patient: " << p->getName() << endl;
    }
};
//Using Command Pattern. Using Abstract Factory Pattern.
//Command Pattern --> Abstract Command(1). Abstract Factory Pattern --> Abstract Product(1).
class RadioTest {
public:
    virtual void ExecuteRadioTest(Patient *p) = 0;
    virtual void setRadiology(Radiology *_r){
        r = _r;
    }
protected:
    Radiology *r;
};
//Using Command Pattern. Using Abstract Factory Pattern.
//Command Pattern --> Concrete Command(1). Abstract Factory Pattern --> Concrete Product(1).
class EndocrinologyTest : public RadioTest{
public:
    void ExecuteRadioTest(Patient *p){
        r->ActionEndocrinologyTest(p);
    }
};
//Using Command Pattern. Using Abstract Factory Pattern.
//Command Pattern --> Concrete Command(1). Abstract Factory Pattern --> Concrete Product(1).
class XRAY : public RadioTest{
public:
    void ExecuteRadioTest(Patient *p){
        r->ActionXrayTest(p);
    }
};
//Using Command Pattern. Using Abstract Factory Pattern.
//Command Pattern --> Concrete Command(1). Abstract Factory Pattern --> Concrete Product(1).
class EKG : public RadioTest{
public:
    void ExecuteRadioTest(Patient *p){
        r->ActionEKGTest(p);
    }
};
//Using Command Pattern. Using Abstract Factory Pattern.
//Command Pattern --> Abstract Command(2). Abstract Factory Pattern --> Abstract Product(2).
class LabTest {
public:
    virtual void ExecuteLabTest(Patient *p) = 0;
    virtual void setLaboratory(Laboratory *_lab){
        lab = _lab;
    }
protected:
    Laboratory *lab;
};
//Using Command Pattern. Using Abstract Factory Pattern.
//Command Pattern --> Concrete Command(2). Abstract Factory Pattern --> Concrete Product(2).
class EndocrinologyBloodTest : public LabTest {
public:
    void ExecuteLabTest(Patient *p){
        lab->ActionEndocrinologyBloodTest(p);
    }
};
//Using Command Pattern. Using Abstract Factory Pattern.
//Command Pattern --> Concrete Command(2). Abstract Factory Pattern --> Concrete Product(2).
class OrthopedicsBloodTest : public LabTest {
public:
    void ExecuteLabTest(Patient *p){
        lab->ActionOrthopedicsBloodTest(p);
    }
};
//Using Command Pattern. Using Abstract Factory Pattern.
//Command Pattern --> Concrete Command(2). Abstract Factory Pattern --> Concrete Product(2).
class CardiologyBloodTest : public LabTest{
public:
    void ExecuteLabTest(Patient *p){
        lab->ActionCardiologyBloodTest(p);
    }
};
//Using Abstract Factory, Template Pattern
//Abstract Factory Pattern ---> Abstract Factory. Template Pattern ----> Abstract Class
class Department {
public:
    virtual RadioTest* CreateRadioTest(Radiology *r) = 0;
    virtual LabTest* CreateLabTest(Laboratory *lab) = 0;
    //Template method
    virtual void RecordPatient(Patient *p){
        bool status = CheckPersonalDemographicInformation(p) && CheckInsuranceInformation(p)
                        && CheckPastMedicalHistory(p) && CheckConsentForm(p);
        //cout << "Status : " << CheckPersonalDemgoraficInformation(p) << CheckInsuranceInformation(p) << CheckPastMedicalHistory(p) << CheckConsentForm(p) <<endl;
        if(status){
            cout << "Patient record has successfully registered to the "<< name <<"."<< endl;
            patients.push_back(p);
        }
        else
            cout << "Patient has been failed to record to the "<< name <<"." << endl;
    }
    //primitive operation 1.
    bool CheckPersonalDemographicInformation(Patient *p){
        if(p->getEmail().empty() || p->getPhoneNumber().empty()){
            return false;
        }
        else
            return true;
    }
    //Assumption: If patient is already in the departments record, don't register the patient again, else register the patient.
    //We did not assume that it would differ for each department...
    //primitive operation 2.
    bool CheckPastMedicalHistory(Patient *p){
        for(int i = 0; i < patients.size(); i++){
            if(p->getEmail() == patients[i]->getEmail()){

                return false;
            }
        }
        return true;
    }
    //primitive operation 3.
    virtual bool CheckInsuranceInformation(Patient *p) = 0;
    //primitive operation 4.
    virtual bool CheckConsentForm(Patient *p) = 0;

    virtual vector<Patient*> getPatients(){
        return patients;
    }
protected:
    string name;
private:
    vector<Patient*> patients;
};
//Using Abstract Factory Pattern, Template Pattern
//Abstract Factory Pattern ---> Concrete Factory. Template Pattern --> Concrete Class.
class CardiologyClinic : public Department{
public:
    RadioTest* CreateRadioTest(Radiology *r){
        EKG *e = new EKG();
        e->setRadiology(r);
        return e;
    }
    LabTest* CreateLabTest(Laboratory *lab){
        CardiologyBloodTest *c = new CardiologyBloodTest();
        c->setLaboratory(lab);
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
        cout << "This is Cardiology Consent Form : " << endl << "Your signature please: "<< p->getSignature() << endl;
        if(p->getSignature().empty())
            return false;
        else
            return true;
    }
    CardiologyClinic(){
        name = "Cardiology Clinic";
    }
};
//Using Abstract Factory Pattern, Template Pattern
//Abstract Factory Pattern ---> Concrete Factory. Template Pattern --> Concrete Class.
class OrthopedicsClinic : public Department {
public:
    RadioTest* CreateRadioTest(Radiology *r){
        XRAY *x = new XRAY();
        x->setRadiology(r);
        return x;
    }
    LabTest* CreateLabTest(Laboratory *lab){
        OrthopedicsBloodTest *ort = new OrthopedicsBloodTest();
        ort->setLaboratory(lab);
        return ort;
    }
    //Assumption: Orthopedics does not accept Government insurance but, it accepts all the other insurance.
    bool CheckInsuranceInformation(Patient *p){
        if(p->getInsurance() == "Government" || p->getInsurance().empty())
            return false;
        else{
         return true;
        }
    }
    bool CheckConsentForm(Patient *p){
        cout << "This is Orthopedics Consent Form : " << endl << "Your signature please: "<< p->getSignature() << endl;
        if(p->getSignature().empty())
            return false;
        else
            return true;
    }
    OrthopedicsClinic(){
        name = "Orthopedics Clinic";
    }

};
//Using Abstract Factory Pattern, Template Pattern
//Abstract Factory Pattern ---> Concrete Factory. Template Pattern --> Concrete Class.
class EndocrinologyClinic : public Department{
public:
    RadioTest* CreateRadioTest(Radiology *r){
        EndocrinologyTest *e = new EndocrinologyTest();
        e->setRadiology(r);
        return e;
    }
    LabTest* CreateLabTest(Laboratory *lab){
        EndocrinologyBloodTest *endo = new EndocrinologyBloodTest();
        endo->setLaboratory(lab);
        return endo;
    }
    //Assumption: Endocrinology does not accept Government insurance excepts all the other insurance.
    bool CheckInsuranceInformation(Patient *p){
        if(p->getInsurance() == "Government" || p->getInsurance().empty())
            return false;
        else{
         return true;
        }
    }
    bool CheckConsentForm(Patient *p){
        cout << "This is Endocrinology Consent Form : " << endl << "Your signature please: "<< p->getSignature() << endl;
        if(p->getSignature().empty())
            return false;
        else
            return true;
    }
    EndocrinologyClinic(){
        name = "Endocrinology Clinic";
    }
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
    void setDepartment(Department* d){
        this->department = d;
    }
    void createRadiologyTest(Radiology *r){
        if(radioTest!= NULL){
            delete radioTest;
        }
        radioTest = department->CreateRadioTest(r);
    }
    void createLaboratoryTest(Laboratory *lab){
        if(labTest!= NULL){
            delete labTest;
        }
        labTest = department->CreateLabTest(lab);
    }
    //Search patient method.
    void searchPatient(string s){
        vector<Patient*> temp = department->getPatients();
        for(int i = 0 ; i < temp.size(); i++){
            if(s == temp[i]->getEmail()){
                cout << "Patient with the email " << s <<" has been found." << endl;
                patient = temp[i];
                return;
            }
        }
        cout << "Patient with the email " << s << " is not in the department's list. " << endl;
    }
private:
    Patient *patient;
    RadioTest *radioTest;
    LabTest *labTest;
    Department *department;
};

Radiology *Radiology::instance = NULL;

int main() {
    //3 different departments 3 different doctors.
    Doctor *endoDoctor = new Doctor();
    Doctor *orthoDoctor = new Doctor();
    Doctor *cardioDoctor = new Doctor();

    Department *endocrinologyClinic = new EndocrinologyClinic();
    Department *orthopedicsClinic = new OrthopedicsClinic();
    Department *cardiologyClinic = new CardiologyClinic();

    //Set the doctor's department's...
    endoDoctor->setDepartment(endocrinologyClinic);
    orthoDoctor->setDepartment(orthopedicsClinic);
    cardioDoctor->setDepartment(cardiologyClinic);

    //2 different patients with different insurances.
    Patient *patient_1 = new Patient();
    patient_1->setName("Erkin Kurt Cobain");
    patient_1->setEmail("kurt.erkin@gmail.com");
    patient_1->setPhoneNumber("8652353819");
    patient_1->setSignature("ErkinKurtDigitalSignature");
    patient_1->setInsurance("Government");

    Patient *patient_2 = new Patient();
    patient_2->setName("Hamza Melih Flagbearer");
    patient_2->setEmail("hamza.melih@gmail.com");
    patient_2->setPhoneNumber("8652353819");
    patient_2->setSignature("HamzaMelihFlagbearerDigitalSignal");
    patient_2->setInsurance("Private");

    //Recording the patients to the departments...Testing template pattern.
    cardiologyClinic->RecordPatient(patient_1);cout << endl;
    orthopedicsClinic->RecordPatient(patient_1);cout << endl;
    endocrinologyClinic->RecordPatient(patient_1);cout << endl;

    cardiologyClinic->RecordPatient(patient_2);cout << endl;
    orthopedicsClinic->RecordPatient(patient_2);cout << endl;
    endocrinologyClinic->RecordPatient(patient_2);cout << endl;

    //Laboratory and Radiology instantiation...
    Laboratory *laboratory = new Laboratory();
    Radiology *radiology = Radiology::getInstance();//Singleton pattern.

    //Ordering the tests for patient_1...
    //Creating tests with abstract factory pattern. Ordering tests with command pattern.
    //First find the patient and order test. //Search Patient finds the patient and sets the patient to the doctor.
    //Since the patient couldn't register to the department because of his/her insurance, doctor cant order tests.
    cout << endl; cout << "Endocrinology department:" << endl;
    endoDoctor->searchPatient("kurt.erkin@gmail.com"); cout << endl;

    //Since the patient couldn't register to the department because of his/her insurance, doctor cant order tests.
    cout << endl; cout << "Orthopedics department:" << endl;
    orthoDoctor->searchPatient("kurt.erkin@gmail.com"); cout << endl;

    //Since the patient has been successfully recorded to the department, doctor can order the tests.
    cout << endl; cout << "Cardiology department:" << endl;
    cardioDoctor->searchPatient("kurt.erkin@gmail.com"); cout << endl;
    cardioDoctor->createLaboratoryTest(laboratory);
    cardioDoctor->createRadiologyTest(radiology);
    cardioDoctor->OrderLabTest();
    cardioDoctor->OrderRadioTest();

    //Ordering the test for the patient_2...
    cout << endl; cout << "Endocrinology department:" << endl;
    endoDoctor->searchPatient("hamza.melih@gmail.com"); cout << endl;
    endoDoctor->createLaboratoryTest(laboratory);
    endoDoctor->createRadiologyTest(radiology);
    endoDoctor->OrderLabTest();
    endoDoctor->OrderRadioTest();

    cout << endl; cout << "Orthopedics department:" << endl;
    orthoDoctor->searchPatient("hamza.melih@gmail.com");cout << endl;
    orthoDoctor->createLaboratoryTest(laboratory);
    orthoDoctor->createRadiologyTest(radiology);
    orthoDoctor->OrderLabTest();
    orthoDoctor->OrderRadioTest();

    cout << endl; cout << "Cardiology department:" << endl;
    cardioDoctor->searchPatient("hamza.melih@gmail.com");cout << endl;
    cardioDoctor->createLaboratoryTest(laboratory);
    cardioDoctor->createRadiologyTest(radiology);
    cardioDoctor->OrderLabTest();
    cardioDoctor->OrderRadioTest();cout << endl;

    //Display the patients' test results.
    patient_1->printTestResults();cout << endl;
    patient_2->printTestResults();cout << endl;

    //Adding drugs to the patients and testing the observer pattern.
    Subject *drug_1 = new Drug();
    drug_1->Attach(patient_1);
    drug_1->Attach(patient_2);
    drug_1->setDrugName("CardioDrug");
    vector<string> side_effect_drug_1;
    side_effect_drug_1.push_back("Headache");   side_effect_drug_1.push_back("Stomachache"); side_effect_drug_1.push_back("Flu");
    drug_1->AddSideEffects(side_effect_drug_1);

    Subject *drug_2 = new Drug();
    drug_2->Attach(patient_2);
    drug_2->setDrugName("EndoDrug");
    vector<string> side_effect_drug_2;
    side_effect_drug_2.push_back("Sweating");   side_effect_drug_2.push_back("Insomnia"); side_effect_drug_2.push_back("Cough");
    drug_2->AddSideEffects(side_effect_drug_2);

	return 0;
}
