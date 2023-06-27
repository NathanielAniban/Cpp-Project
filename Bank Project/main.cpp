#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;
string Database1 = "Accounts.csv";
string Database2 = "PersonalInfo.csv";
string Database3 = "HistoryTransaction.csv";
string Database3Path = "C:\\Users\\TECH\\OneDrive\\Desktop\\C++ Projects\\Bank Project\\output\\Transaction\\";
class BankInfo{
    public:
    string name, age, gender, email, phone, id, birthday, address;
    double amount;
    string MyUsername, MyPassword;
    void Settings(){
        char Choice;
        cout << "===========================" << endl;
        cout << "|     S E T T I N G S     |" << endl;
        cout << "===========================" << endl;
        cout << "|  [T] View Transaction   |" << endl;
        cout << "|  [D] Delete Transaction |" << endl;
        cout << "|  [I] View Information   |" << endl;
        cout << "|  [E] Edit Information   |" << endl;
        cout << "|  [Q] Go Back to Menu    |" << endl;
        cout << "===========================" << endl;
        cout << "Select: "; cin >> Choice;
        switch(Choice){
            case 'T': case 't':
            SeeTransaction();
            break;
            case 'D': case 'd':
            DeleteTransaction();
            break;
            case 'I': case 'i':
            SeeInfo();
            break;
            case 'E': case 'e':
            EditInfo();
            break;
            default:
            case 'Q': case 'q':
            break;
            system("cls");
            cout << "Invalid. Please Try Again!\n";
            Settings();
            break;
        }
    }
    //Settings
    void SeeTransaction(){
        fstream file;
        string line;
        int counter, spacecounter;
        vector <string> ShowLine, Showline2;
        file.open(Database3Path + id + name + Database3);
        if(file.is_open()){
            file.close();
            file.open(Database3Path + id + name + Database3, ios::in);
            if(file.is_open()){
                while(!file.eof()){
                    getline(file, line, ',');
                    ShowLine.push_back(line);
                    getline(file, line);
                    Showline2.push_back(line);
                }
            }
            file.close();
            counter = ShowLine.size()-1;
            for(int x = 0; x < counter; x++){
                
                line = ShowLine[x];
                spacecounter = line.size();
                for(int y = 0; y < 20; y++){
                    if(y < spacecounter){
                        cout << line[y];
                    }else{
                        cout << " ";
                    }
                }
                cout << Showline2[x] << endl;
            }

        }else{
            cout << "No Records of Transaction!\n";
        }
        system("pause");
        system("cls");
    }
    void DeleteTransaction(){
        char choice;
        string Getter = Database3Path + id + Database3;
        char *filegetter = &Getter[0];
        cout << "Are You Sure?:\n";
        cout << "[Y] Yes\n";
        cout << "[N] No\n";
        cout << "Select: "; cin >> choice;
        switch(choice){
            case 'Y': case 'y':
            if(remove(filegetter) == 0){
                cout << "Transaction Deletion Successfully!\n";
            }
            else{
                cout << "Transaction Deletion Failed!\n";
            }
            break;
            case 'N': case 'n':
            system("cls");
            break;
            default:
            cout << "Invalid. Please Try Again!\n";
            DeleteTransaction();
            break;

        }
    }
    void SeeInfo(){
        cout << "===========================" << endl;
        cout << "|  I N F O R M A T I O N  |" << endl;
        cout << "===========================" << endl;
        cout << "Email: " << email << endl;
        cout << "Phone No.: " << phone << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Birthday: " << birthday << endl;
        cout << "Address: " << address << endl;
        cout << "===========================" << endl;
        system("pause");
        system("cls");
    }
    void EditInfo(){
        system("cls");
        cin.get();
        string Name, Address, PhoneNumber, gender, Email;
        char selection;
        int thisage;
        cout << "==============================" << endl;
        cout << "Editing Information Form:\n";
        cout << "==============================" << endl;
        cout << "Enter Your Name: "; getline(cin, Name);
        cin.get();
        string Birthday = BirthdayGetter();
        string Days = DaysOld();
        string Year = YearOld();
        Birthday += Days + " " + Year;
        int AgeGetter = stoi(Year);
        time_t now = time(0);
        tm *ltm = localtime(&now);
        thisage = (1900 + ltm->tm_year) - AgeGetter;
        cout << "Enter Your Email: "; cin >> Email;
        again:
        cout << "Select Gender:\n";
        cout << "[M] Male\n";
        cout << "[F] Female\n";
        cout << "[O] Others\n";
        cout << "Select: "; cin >> selection;
        switch(selection){
            case 'M': case 'm':
            gender = "Male";
            break;
            case 'F': case 'f':
            gender = "Female";
            break;
            case 'O': case 'o':
            cin.get();
            cout << "Specify Your Gender: "; getline(cin ,gender);
            break;
            default:
            cout << "Invalid. Please Try Again!\n";
            goto again;
            break;
        }
        cout << "Enter Your Phone Number: "; cin >> PhoneNumber;
        cin.get();
        cout << "Enter Your Address: "; getline(cin, Address);

        fstream file;
        string line;
        int counter;
        vector <string> ID_Getter, MyName, MyAge, MyGender, MyEmail;
        vector <string> MyAddress, MyPhone, MyBalance, MyBirthday;
        file.open(Database2, ios::in);
        while(!file.eof()){
            getline(file, line, ',');
            ID_Getter.push_back(line);

            getline(file, line, ',');
            MyName.push_back(line);

            getline(file, line, ',');
            MyAge.push_back(line);

            getline(file, line, ',');
            MyBirthday.push_back(line);

            getline(file, line, ',');
            MyGender.push_back(line);

            getline(file, line, ',');
            MyEmail.push_back(line);

            getline(file, line, ',');
            MyAddress.push_back(line);

            getline(file, line, ',');
            MyPhone.push_back(line);

            getline(file, line);
            MyBalance.push_back(line);
        }
        file.close();
        counter = ID_Getter.size()-1;

        file.open(Database2, ios::out);
        for(int x = 0; x < counter; x++){
            if(id == ID_Getter[x]){
                file << ID_Getter[x] << "," << Name << "," << thisage << "," <<  Birthday << "," << gender << "," << Email << "," << Address << "," << PhoneNumber << "," << MyBalance[x] << endl;
                name = Name;
                cout << "Changing Information Success!\n";
            }
            else{
                file << ID_Getter[x] << "," << MyName[x] << "," << MyAge[x] << "," << MyBirthday[x] << "," << MyGender[x] << "," << MyEmail[x] << "," << MyAddress[x] << "," << MyPhone[x] << "," << MyBalance[x] << endl;
            }
        }
        file.close();

    }
    void ChangeUsername(){
        fstream file;
        string ThisPassword;
        string line, UserChanger;
        vector <string> ThisID, ThisPass, ThisUser;
        cout << "================================" << endl;
        cout << "| C H A N G E  U S E R N A M E |" << endl;
        cout << "================================" << endl;
        cout << "Enter Password: "; cin >> ThisPassword;
        if(ThisPassword != MyPassword){
            cout << "Invalid Password.\n";
        }
        else{
            file.open(Database1, ios::in);
            while(!file.eof()){
                getline(file, line, ',');
                ThisID.push_back(line);
                getline(file, line ,',');
                ThisUser.push_back(line);
                getline(file,line);
                ThisPass.push_back(line);
            }
            file.close();
            cout << "Enter New Username: "; cin >> UserChanger;
            int counter = ThisID.size()-1;
            file.open(Database1, ios::out);
            for(int x = 0; x < counter; x++){
                if(MyUsername == ThisUser[x]){
                file << ThisID[x] << "," << UserChanger << "," << ThisPass[x] << endl;
                cout << "Changing Username Successfully!\n";
                }
                else{
                file << ThisID[x] << "," << ThisUser[x] << "," << ThisPass[x] << endl;
                }
            }
            file.close();
            system("pause");
        }
    }
    void ChangePassword(){
        fstream file;
        string line;
        vector <string> ThisID, ThisPass, ThisUser;
        string OldPassword, NewPassword;
        cout << "================================" << endl;
        cout << "| C H A N G E  U S E R N A M E |" << endl;
        cout << "================================" << endl;
        cout << "Enter Old Password: "; cin >> OldPassword;
        cout << "Enter New Password: "; cin >> NewPassword;
        if(MyPassword != OldPassword){
            cout << "Incorrect Password!\n";
        }
        else{
            file.open(Database1, ios::in);
            while(!file.eof()){
                getline(file, line, ',');
                ThisID.push_back(line);
                getline(file, line ,',');
                ThisUser.push_back(line);
                getline(file,line);
                ThisPass.push_back(line);
            }
            file.close();
            int counter = ThisID.size()-1;
            file.open(Database1, ios::out);
            for(int x = 0; x < counter; x++){
                if(OldPassword == ThisPass[x]){
                file << ThisID[x] << "," << ThisUser[x] << "," << NewPassword << endl;
                cout << "Changing Username Successfully!\n";
                }
                else{
                file << ThisID[x] << "," << ThisUser[x] << "," << ThisPass[x] << endl;
                }
            }
            file.close();
            system("pause");
        }
    }
   // Withdraw/Deposit Process
    void Withdraw_Process(double withdraw){
        if(withdraw < 0){
                cout << "Invalid Amount to Withdraw!\n";
                system("pause");
                system("cls");
            }
            else if(amount < withdraw){
                cout << "Insufficient Balance!\n";
                system("pause");
                system("cls");
            }
            else{
                cout << "Balance Before: " << amount << endl;
                cout << "Withdrawal Amount: " << withdraw << endl;
                amount = amount - withdraw;
                cout << "Balance Now: " << amount << endl;
                FileUpdating(amount, withdraw, "-");
            }
    }
    void Deposit_Process(double deposit){
        if(deposit < 0){
                cout << "Invalid Amount to Add Balance!\n";
                system("pause");
                system("cls");
            }
            else{
                cout << "Balance Before: " << amount << endl;
                cout << "Deposit Amount: " << deposit << endl;
                amount = amount + deposit;
                cout << "Balance Now: " << amount << endl;
                FileUpdating(amount, deposit, "+");
            }
    }
    void FileUpdating(double myAmount, double BalanceBefore, string sign){
        fstream file;
        string line, convert;
        vector <string> MyName, Age, Gender, Email, Phone, Balance, ID, Birthday, Address;
        time_t now = time(0);
        char* dt = ctime(&now);
       
        file.open(Database2, ios::in);
            while (!file.eof())
            {
                getline(file, line , ','); // ID
                ID.push_back(line);
                getline(file, line , ','); //Name
                MyName.push_back(line);
                getline(file, line , ','); //Age
                Age.push_back(line);
                getline(file, line , ',');//Birthday
                Birthday.push_back(line);
                getline(file, line , ',');//Gender
                Gender.push_back(line);
                getline(file, line , ',');//Email
                Email.push_back(line);
                getline(file, line , ',');//Address
                Address.push_back(line);
                getline(file, line , ',');//Phone
                Phone.push_back(line);
                getline(file, line);//Balance
                Balance.push_back(line);
            }
        
        file.close();
        int size = Balance.size()-1;
        file.open(Database2, ios::out);
            for(int length = 0; length < size; length++){
            if(id == ID[length]){
            convert = to_string(myAmount);
            file << ID[length] << "," << MyName[length] << "," << Age[length] << "," << Birthday[length] << "," << Gender[length] << "," << Email[length] << "," << Address[length] << "," << Phone[length] << "," << convert << endl;
            }
            else{
            file << ID[length] << "," << MyName[length] << "," << Age[length]  << "," << Birthday[length] << "," << Gender[length] << "," << Email[length] << "," << Address[length] << "," << Phone[length] << "," << Balance[length] << endl;
            }
            }
        ifstream thisfile;
        thisfile.open(Database3Path + id + name + Database3);
        if(thisfile){
            cout << "Database Find!\n";
            fstream myfile;
            myfile.open(Database3Path + id + name + Database3, ios::app);
            myfile << sign << BalanceBefore << "," << dt;
            myfile.close();
        }
        else{
            cout << "Creating Database for Transactions!\n";
            fstream myfile;
            myfile.open(Database3Path + id + name + Database3, ios::out);
            myfile << "Amount,Date of Transaction" << endl;
            myfile << sign << BalanceBefore << "," << dt;
            myfile.close();
        }
        thisfile.close();

        system("pause");
        system("cls");
    }
    // Registration Center
    void UserRegistration(){
        string Username, Password, Confirmation;
        cout << "User Registration Form:\n";
        cout << "NOTE: For Creating An Account. You're Obliged to Follow the Rules and Regulation.\n";
        cout << "Enter Your Username: "; cin >> Username;
        cout << "Enter Your Password: "; cin >> Password;
        cout << "Confirm Your Password: "; cin >> Confirmation;

        if(Confirmation == Password){
            cin.get();
            InformationRegistration(Username, Password);
        }
        else{
            cout << "Password Does not Match!\n";
        }

    }
    void InformationRegistration(string Username, string Password){
        string Name, Address, PhoneNumber, gender, Email;
        char selection;
        int thisage;
        cout << "==============================" << endl;
        cout << "Information Registration Form:\n";
        cout << "==============================" << endl;
        cout << "Enter Your Name: "; getline(cin, Name);
        string Birthday = BirthdayGetter();
        string Days = DaysOld();
        string Year = YearOld();
        Birthday += Days + " " + Year;
        int AgeGetter = stoi(Year);
        time_t now = time(0);
        tm *ltm = localtime(&now);
        thisage = (1900 + ltm->tm_year) - AgeGetter;
        cout << "Enter Your Email: "; cin >> Email;
        again:
        cout << "Select Gender:\n";
        cout << "[M] Male\n";
        cout << "[F] Female\n";
        cout << "[O] Others\n";
        cout << "Select: "; cin >> selection;
        switch(selection){
            case 'M': case 'm':
            gender = "Male";
            break;
            case 'F': case 'f':
            gender = "Female";
            break;
            case 'O': case 'o':
            cin.get();
            cout << "Specify Your Gender: "; getline(cin ,gender);
            break;
            default:
            cout << "Invalid. Please Try Again!\n";
            goto again;
            break;
        }
       
        cout << "Enter Your Phone Number: "; cin >> PhoneNumber;
        cin.get();
        cout << "Enter Your Address: "; getline(cin, Address);
        Registration_Getter(Username, Password, Name, thisage, Birthday, gender, Email,PhoneNumber, Address);
    }
    string BirthdayGetter(){
        Again:
        string BirthDate;
        char Months;
        cout << "BirthDate:\n";
        cout << "Enter Year:\n";
        cout << "[1] January    [2] February\n";
        cout << "[3] March      [4] April\n";
        cout << "[5] May        [6] June\n";
        cout << "[7] July       [8] August\n";
        cout << "[9] September  [0]October\n";
        cout << "[N]November   [D]December\n";
        cout << "Select: "; cin >> Months;
        switch(Months){
            case '1':BirthDate = "January ";break;
            case '2':BirthDate = "February ";break;
            case '3':BirthDate = "March ";break;
            case '4':BirthDate = "April ";break;
            case '5':BirthDate = "May ";break;
            case '6':BirthDate = "June ";break;
            case '7':BirthDate = "July ";break;
            case '8':BirthDate = "August ";break;
            case '9':BirthDate = "September ";break;
            case '0':BirthDate = "October ";break;
            case 'N':BirthDate = "November ";break;
            case 'D':BirthDate = "December ";break;
            default:
            system("cls");
            cout << "Invalid. Please Try Again!\n";
            goto Again;
            break;
        }
        return BirthDate;
    }
    string DaysOld(){
        string Day;
        cout << "Enter Day (1 - 31): "; cin >> Day;
        return Day;
    }
    string YearOld(){
        string Year;
        cout << "Enter Year (ex. 2003): "; cin >> Year;
        return Year;
    }
    void Registration_Getter(string Username, string Password, string Name, int age,string Birthday, string gender, string Email, string PhoneNumber, string Address){
        int ID = 0;
        vector <string> counter;
        string line;
        double value;
        cout << "Enter Amount to Deposit: "; cin >> value;
        if(value < 0){
            cout << "Enter Valid Amount!\n";
            Registration_Getter(Username, Password, Name, age,Birthday, gender, Email, PhoneNumber, Address);
        }
        else if(value == 0){
            cout << "Please Enter Amount Other than 0.\n";
            Registration_Getter(Username, Password, Name, age, Birthday,gender, Email, PhoneNumber, Address);
        }
        else{
        fstream file;
        //Database 1 for Login
        file.open(Database1);
        if(file.is_open()){
            file.close();
            file.open(Database1, ios::in);
            while(!file.eof()){
                getline(file, line);
                counter.push_back(line);
            }
            file.close();
            ID += counter.size()-1;
            file.open(Database1, ios::app);
            file << ID << "," << Username << "," << Password << endl;
            file.close();
        }
        else{
            file.close();
            file.open(Database1, ios::out);
            file << "ID" << "," <<  "Username" << "," << "Password" << endl;
            file.close();
            file.open(Database2, ios::out);
            file << "ID" << "," << "Name" << "," << "Age" << ",Birthday,Gender" << "," << "Email" << ",Address," << "Phone No." << "," << "Balance" << endl;
            file.close();

            file.open(Database1, ios::in);
            while(!file.eof()){
                getline(file, line);
                counter.push_back(line);
            }
            file.close();
            ID += counter.size()-1;

            file.open(Database1, ios::app);
            file << ID << "," << Username << "," << Password << endl;
            file.close();
            
        }
        for(int x = 0; x < ID+1; x++){
            counter.pop_back();
        }
        ID = 0;
        //Database 2 for Information
        file.open(Database2);
        if(file.is_open()){
            file.close();

            file.open(Database2, ios::in);
            while(!file.eof()){
                getline(file, line);
                counter.push_back(line);
            }
            file.close();
            ID += counter.size()-1;

            file.open(Database2, ios::app);
            file << ID << "," << Name << "," << age << ","<< Birthday <<"," << gender << "," << Email  << "," << Address << "," << PhoneNumber <<  "," << to_string(value) << endl;
            file.close();
            cout << "Your Information Is Successfully Added to Database!\n";
        }
        else{
            file.close();
            file.open(Database1, ios::in);
            while(!file.eof()){
                getline(file, line);
                counter.push_back(line);
            }
            file.close();
            ID += counter.size()-1;

            file.open(Database2, ios::app);
            file << ID << "," << Name << "," << age << ","<< Birthday <<"," << gender << "," << Email  << "," << Address <<  "," << PhoneNumber << "," << to_string(value) << endl;
            file.close();
            cout << "Your Information Is Successfully Added to Database!\n";
        }
         
        }

    }
    //Login Center
    void UserLogin(){
        fstream file;
        string Username, Password, line;
        vector <string> User, Pass, Balance, Name, ID, Birthday, Address;
        vector <string> getAge, getEmail, getPhoneNo, getGender;
        int length;
        bool setter = false;
        cout << "===========================" << endl;
        cout << "|   L O G I N  F O R M    |" << endl;
        cout << "===========================" << endl;
        cout << "Enter Username: "; cin >> Username;
        cout << "Enter Password: "; cin >> Password;

        file.open(Database1);
        if(file.is_open()){
            file.close();
            file.open(Database1, ios::in);
            while(!file.eof()){
            getline(file,line,',');
            ID.push_back(line);

            getline(file, line, ',');
            User.push_back(line);

            getline(file, line);
            Pass.push_back(line);

            
        }
        file.close();

        file.open(Database2);
        if(file.is_open()){
            file.close();
            file.open(Database2, ios::in);
            while(!file.eof()){

            getline(file,line,',');
            ID.push_back(line);

            getline(file, line, ',');
            Name.push_back(line);

            getline(file, line, ',');
            getAge.push_back(line);

            getline(file, line, ',');
            Birthday.push_back(line);

            getline(file, line, ',');
            getGender.push_back(line);

            getline(file, line, ',');
            getEmail.push_back(line);

            getline(file, line, ',');
            Address.push_back(line);

            getline(file, line, ',');
            getPhoneNo.push_back(line);

            getline(file, line);
            Balance.push_back(line);
            }
        }

        length = User.size();

        for(int x = 0; x < length; x++){
            if(Username == User[x] && Password == Pass[x]){
                name = Name[x];
                amount = stod(Balance[x]);
                MyUsername = User[x];
                age = getAge[x];
                gender = getGender[x];
                email = getEmail[x];
                phone = getPhoneNo[x];
                id = ID[x];
                birthday = Birthday[x];
                address = Address[x];
                setter = true;
                MyPassword = Pass[x];
            }
        }

        if(setter == true){
            cout << "Login Successfully!\n";
            Main_Menu();
        }
        else{
            cout << "Wrong Username or Password!\n";
        }

        }
        else{
        cout << "No Database Recorded. Need to Register First!\n";
        system("pause");
        file.close();
        }

    }
    //Forgot Password System
    void ForgotPassword(){
        system("cls");
        string Email,PhoneNumber;
        vector<string> thisID,thisName,thisAge,thisBirthday,thisGender,thisEmail;
        vector<string> thisAddress,thisPhone,thisBalance;
        cout << "============================" << endl;
        cout << "|  F I N D  A C C O U N T  |" << endl;
        cout << "============================" << endl;
        cout << "Enter Email: "; cin >> Email;
        cout << "Enter Phone No.: "; cin >> PhoneNumber;

        string line;
        fstream file;
        file.open(Database2, ios::in);
        while(!file.eof()){
            getline(file, line, ',');
            thisID.push_back(line);

            getline(file, line, ',');
            thisName.push_back(line);

            getline(file, line, ',');
            thisAge.push_back(line);

            getline(file, line, ',');
            thisBirthday.push_back(line);

            getline(file, line, ',');
            thisGender.push_back(line);

            getline(file, line, ',');
            thisEmail.push_back(line);

            getline(file, line, ',');
            thisAddress.push_back(line);

            getline(file, line, ',');
            thisPhone.push_back(line);

            getline(file, line);
             thisBalance.push_back(line);
        }
        file.close();
        
        vector <string> User,Pass,ID;
        file.open(Database1, ios::in);
        while(!file.eof()){
            getline(file, line, ',');
            ID.push_back(line);
            getline(file, line, ',');
            User.push_back(line);
            getline(file, line);
            Pass.push_back(line);
        }
        file.close();
        int setcounter = 0;
        int counter = thisID.size()-1;
        for(int x = 0; x < counter; x++){
            if(Email == thisEmail[x] && PhoneNumber == thisPhone[x]){
                cout << "Account Found!\n";
                cout << "Your Username: " << User[x] << endl;
                cout << "Your Password: " << Pass[x] << endl;
            setcounter++;
            }
            setcounter++;
        }
        if(setcounter == counter){
            cout << "Account Not Found!\n";
        }
        system("pause");

    }
    //Account Deletion Process
    void FirstStepDeletion(){
        char choice;
        cout << "===========================" << endl;
        cout << "|      1 S T  S T E P     |" << endl;
        cout << "===========================" << endl;
        cout << "Are You Sure?\n";
        cout << "[Y] Yes    [N] No\n";
        cout << "Select: "; cin >> choice;
        switch(choice){
            case 'Y': case 'y':
            SecondStepDeletion();
            break;
            case 'N': case 'n':
            Main_Menu();
            break;
            default:
            cout << "Invalid. Please Try Again!\n";
            FirstStepDeletion();
            break;
        }
    }
    void SecondStepDeletion(){
        vector<string> thisID,thisName,thisAge,thisBirthday,thisGender,thisEmail;
        vector<string> thisAddress,thisPhone,thisBalance;
        bool setter = false;
        string Email, Password;
            cout << "===========================" << endl;
            cout << "|      2 N D  S T E P     |" << endl;
            cout << "===========================" << endl;
            cout << "Enter Email: "; cin >> Email;
            cout << "Enter Password: "; cin >> Password;

        fstream file;
        string line;
        file.open(Database2, ios::in);
        while(!file.eof()){
            getline(file, line, ',');
            thisID.push_back(line);

            getline(file, line, ',');
            thisName.push_back(line);

            getline(file, line, ',');
            thisAge.push_back(line);

            getline(file, line, ',');
            thisBirthday.push_back(line);

            getline(file, line, ',');
            thisGender.push_back(line);

            getline(file, line, ',');
            thisEmail.push_back(line);

            getline(file, line, ',');
            thisAddress.push_back(line);

            getline(file, line, ',');
            thisPhone.push_back(line);

            getline(file, line);
            thisBalance.push_back(line);
        }
        file.close();

        int size = thisID.size()-1;

        vector <string> User,Pass,ID;
        file.open(Database1, ios::in);
        while(!file.eof()){
            getline(file, line, ',');
            ID.push_back(line);
            getline(file, line, ',');
            User.push_back(line);
            getline(file, line);
            Pass.push_back(line);
        }
        file.close();

        for(int x = 0; x < size; x++){
            if(Email == thisEmail[x] && Password == Pass[x]){
                cout << "Email and Password Match!\n";
                setter = true;
            }
        }
        if(setter == true){
            ThirdStepDeletion();
        }else{
            cout << "Email or Password is Incorrect!\n";
            system("pause");
            Main_Menu();
        }
    }
    void ThirdStepDeletion(){
        system("cls");
        char choice;
        cout << "=============================================" << endl;
        cout << "|             F I N A L   S T E P           |" << endl;
        cout << "=============================================" << endl;
        cout << "NOTE: Clicking 'Yes' means that you Agree to\n";
        cout << "Delete Your Account Completely. And There's No\n";
        cout << "Account Recovery!\n";
        cout << "=============================================" << endl;
        cout << "Are You Sure?\n";
        cout << "[Y] Yes    [N] No\n";
        cout << "Select: "; cin >> choice;
        switch (choice)
        {
        case 'Y': case 'y':
            system("cls");
            AccountDeletion();
            break;
        case 'N': case 'n':
            cout << "Account Deletion Failed!\n";
            system("pause");
            Main_Menu();
            break;
        default:
            cout << "Invalid. Please Try Again!\n";
            ThirdStepDeletion();
            break;
        }
    }
    void AccountDeletion(){
        string line;
        vector<string> thisID,thisName,thisAge,thisBirthday,thisGender,thisEmail;
        vector<string> thisAddress,thisPhone,thisBalance;
        fstream file;
        file.open(Database2, ios::in);
        while(!file.eof()){
            getline(file, line, ',');
            thisID.push_back(line);

            getline(file, line, ',');
            thisName.push_back(line);

            getline(file, line, ',');
            thisAge.push_back(line);

            getline(file, line, ',');
            thisBirthday.push_back(line);

            getline(file, line, ',');
            thisGender.push_back(line);

            getline(file, line, ',');
            thisEmail.push_back(line);

            getline(file, line, ',');
            thisAddress.push_back(line);

            getline(file, line, ',');
            thisPhone.push_back(line);

            getline(file, line);
            thisBalance.push_back(line);
        }
        file.close();

        vector <string> User,Pass,ID;
        file.open(Database1, ios::in);
        while(!file.eof()){
            getline(file, line, ',');
            ID.push_back(line);
            getline(file, line, ',');
            User.push_back(line);
            getline(file, line);
            Pass.push_back(line);
        }
        file.close();

        int counter = ID.size()-1;
        file.open(Database2, ios::out);
        for(int x = 0; x < counter; x++){
            if(name == thisName[x]){
                cout << "Information Deleted!\n";
            }
            else{
                file << ID[x] << "," << thisName[x] << "," << thisAge[x] << "," << thisBirthday[x] << "," << thisGender[x] << "," << thisEmail[x] << "," << thisAddress[x] << "," << thisPhone[x] << "," << thisBalance[x] << endl;
            }
        }
        file.close();
        
        string Getter = Database3Path + id + name + Database3;
        char *filegetter = &Getter[0];
        if(remove(filegetter) == 0){
            cout << "Transaction Deleted Successfully!\n";
        }else{
            cout << "Transaction not Found\n";
        }

        file.open(Database1, ios::out);
        for(int x = 0; x < counter; x++){
            if(MyUsername == User[x]){
                cout << "Account Deleted!\n";
            }
            else{
                file << ID[x] << "," << User[x] << "," << Pass[x] << endl;
            }
        }
    }
    //MENU TEMPLATE
    void Main_Menu(){
        Main:
        system("cls");
        char choice;
        double withdraw, deposit;
        cout << "Welcome to C++ Bank Account" << endl;
        cout << "Name: " << name << "\n";
        cout << "Balance: "<< setprecision(10) << amount << "\n";
        cout << "===========================" << endl;
        cout << "|    S E L E C T I O N    |" << endl;
        cout << "===========================" << endl;
        cout << "|  [W] Withdraw           |" << endl;
        cout << "|  [D] Deposit            |" << endl;
        cout << "|  [S] Settings           |" << endl;
        cout << "|  [U] Change Username    |" << endl;
        cout << "|  [P] Change Password    |" << endl;
        cout << "|  [A] Account Deletion   |" << endl;
        cout << "|  [Q] Log out            |" << endl;
        cout << "===========================" << endl;
        cout << "Select: "; cin >> choice;
        switch(choice){
            case 'W': case 'w':
            cout << "Enter Amount to Withdraw: "; cin >> withdraw;
            Withdraw_Process(withdraw);
            goto Main;
            break;

            case 'D': case 'd':
            cout << "Enter Amount to Deposit: "; cin >> deposit;
            Deposit_Process(deposit);
            goto Main;
            break;

            case 'Q': case 'q':
            cout << "Logout Successfully!\n";
            system("pause");
            break;

            case 'S': case 's':
            system("cls");
            Settings();
            goto Main;
            break;

            case 'U': case 'u':
            system("cls");
            ChangeUsername();
            goto Main;
            break;

            case 'P': case 'p':
            system("cls");
            ChangePassword();
            goto Main;
            break;

            case 'A': case 'a':
            FirstStepDeletion();
            break;

            default:
            cout << "Invalid. Please try Again!\n";
            goto Main;
            break;
        }
    }
    void Menu(){
        system("cls");
        char choice;
        cout << "===========================" << endl;
        cout << "   Welcome to C++ Bank!\n";
        cout << "===========================" << endl;
        cout << "|    S E L E C T I O N    |" << endl;
        cout << "===========================" << endl;
        cout << "[L] Login\n";
        cout << "[R] Register\n";
        cout << "[F] Forgot Password\n";
        cout << "[Q] Quit\n";
        cout << "===========================" << endl;
        cout << "Select: "; cin >> choice;
        switch(choice){
            case 'R': case 'r':
            system("cls");
            UserRegistration();
            Menu();
            break;
            case 'L': case 'l':
            system("cls");
            UserLogin();
            Menu();
            break;
            case 'F': case 'f':
            ForgotPassword();
            Menu();
            break;
            case 'Q': case 'q':
            cout << "Thank You. Have a Nice Day!\n";
            system("pause");
            break;
            default:
            cout << "Invalid. Please Try Again!\n";
            system("pause");
            Menu();
            break;

        }
        
    }
};
int main(){
    BankInfo MyBank;
    MyBank.Menu();
    return 0;    
}