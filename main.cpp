#include<bits/stdc++.h>
using namespace std;

#define MIN_BALANCE 500

class InsufficientFunds{};
class account
{
private:
    long accountNumber;
    string firstName;
    string lastName;
    float balance;
    static long NextAccountNumber;
public:
    account(){}
    account(string fname,string lname, float balance);
    long accNO(){
        return accountNumber;
    }
    string getfirstName(){
        return firstName;
    }
    string getlastName(){
        return lastName;
    }
    float bal(){
        return balance;
    }

    void deposite(float amount);
    void withdraw(float amount);
    static void setLastAccNO(long accNumber);
    static long getlastAccNO();
    friend ofstream & operator<<(ofstream &ofs,account &acc);
    friend ifstream & operator >>(ifstream &ifs,account &acc);
    friend ostream & operator<<(ostream &os, account &acc);

};
long account :: NextAccountNumber=0;

class Bank{
    private:
    map<long, account> accounts;
    public:
    Bank();
    account openAccount(string fname, string lname,float balance);
    account BalanceEnq(long accountNumber);
    account Deposite(long accountNumber ,float amount);
    account Withdraw(long accountNumber, float amount);
    void CloseAcc(long accountNumber);
    void showALLaccounts();
    ~Bank();
};
account::account(string fname,string lname, float balance){
    NextAccountNumber++;
    accountNumber=NextAccountNumber;
    firstName=fname;
    lastName=lname;
    this->balance=balance;
}
void account::deposite(float amount){
    balance+=amount;
}
void account:: withdraw(float amount){
   if(balance-amount<MIN_BALANCE)
 throw InsufficientFunds();
 balance-=amount;
}

void account::setLastAccNO(long accountNumber){
    NextAccountNumber=accountNumber;
}
long account:: getlastAccNO(){
    return NextAccountNumber;
}

ofstream & operator<<(ofstream &ofs,account &Acc){
    ofs<<Acc.accountNumber<<endl;
    ofs<<Acc.firstName<<endl;
    ofs<<Acc.lastName<<endl;
    ofs<<Acc.balance<<endl;
    return ofs;
}
ifstream & operator>>(ifstream &ifs,account &Acc){
    ifs>>Acc.accountNumber;
    ifs>>Acc.firstName;
    ifs>>Acc.lastName;
    ifs>>Acc.balance;
    return ifs;    
}

ostream & operator<<(ostream &os,account &Acc){
    os<<"First Name: "<<Acc.getfirstName()<<endl;
    os<<"Last Name: "<<Acc.getlastName()<<endl;
    os<<"Account Number: "<<Acc.accNO()<<endl;
    os<<"Balance: "<<Acc.bal()<<endl;
    return os;
}

Bank :: Bank(){
    account acc1;
    ifstream infile;
    infile.open("Bank.data");
    if(!infile){
        return; 
    }
   while(!infile.eof())
 {
 infile>>acc1;
 accounts.insert(pair<long, account>(acc1.accNO(),acc1));
 }
 account::setLastAccNO(acc1.accNO());
 
 infile.close();
}

account Bank :: openAccount(string fname,string lname,float balance){
    ofstream outfile;
    account acc1(fname,lname,balance);
    accounts.insert(pair<long,account>(acc1.accNO(),acc1));
    outfile.open("Bank.data", ios::trunc);
    // map<long,account>::iterator itr;
    for(auto it=accounts.begin();it !=accounts.end();it++){
        outfile<<it->second;
    }
    outfile.close();
    return acc1;
}

account Bank:: BalanceEnq(long accountNumber){
    map<long ,account>::iterator it=accounts.find(accountNumber);
    return it->second;
}
account Bank:: Deposite(long accountNumber, float amount){
     map<long ,account>::iterator it=accounts.find(accountNumber);
     it->second.deposite(amount);
}
account Bank:: Withdraw(long accountNumber, float amount){
     map<long ,account>::iterator it=accounts.find(accountNumber);
     it-> second.withdraw(amount);
     return it->second;
}
void Bank::CloseAcc(long accountNumber){
     map<long ,account>::iterator it=accounts.find(accountNumber);
     cout<<"Account Deleted"<<it->second;
     accounts.erase(accountNumber);
}
void Bank::showALLaccounts(){
    map<long ,account>::iterator it;
    for(it=accounts.begin();it!=accounts.end();it++){
        cout<<"Account"<<it->first<<endl<<it->second<<endl;
    }
}
Bank::~Bank(){
    ofstream outfile;
    outfile.open("Bank.data",ios:: trunc);

    for(auto it=accounts.begin(); it!=accounts.end();it++){
        outfile<<it->second;
    }
    outfile.close();
}
    int main(){
        Bank b;
        account Acc;

        int choice;
        string fname,lname;
        long accountNumber;
        float balance;
        float amount;
        cout<<"***Banking System*** \n";
        do{
            cout<<"\n\tselect one option below";
            cout<<"\n\t1 Open an Account ";
            cout<<"\n\t2 Balance Enquiry";
            cout<<"\n\t3 Deposite";
            cout<<"\n\t4 Withdreawal";
            cout<<"\n\t5 close an Account ";
            cout<<"\n\t6 Show all Accounts";
            cout<<"\n\t7 Quit";
            cout<<"\nEnter your choice: ";
            cin>>choice;
            switch(choice){
                case 1:
                    cout<<"Enter First Name: ";
                    cin>>fname;
                    cout<<"Enter last Name: ";
                    cin>>lname;
                    cout<<"Enter initial Balance: ";
                    cin>>balance;
                    Acc=b.openAccount(fname,lname,balance);
                    cout<<endl<<"Congradulation Account is created"<<endl;
                    cout<<Acc;
                    break;

                case 2:
                    cout<<"Enter Account Number: ";
                    cin>>accountNumber;
                    Acc=b.BalanceEnq(accountNumber);
                    cout<<endl<<"Your Account Details "<<endl; 
                    cout<<Acc;
                    break;

                case 3:
                    cout<<"Enter Account Number: ";
                    cin>>accountNumber;
                    cout<<"Enter Balance: ";
                    cin>>amount;
                    Acc=b.Deposite(accountNumber,amount);
                    cout<<endl<<"Amount is Deposited"<<endl;
                    cout<<Acc;
                    break;

                case 4:
                    cout<<"Enter Account Number: ";
                    cin>>accountNumber;
                    cout<<"Enter Balance";
                    cin>>amount;
                    Acc=b.Withdraw(accountNumber,amount);
                    cout<<endl<<"Amount Withdrawn\n ";
                    cout<<Acc;
                    break;

                case 5: 
                    cout<<"Enter Account Number: ";
                    cin>>accountNumber;
                    b.CloseAcc(accountNumber);
                    cout<<endl<<"Account is Closed \n";
                    cout<<Acc;
                    break;

                case 6:
                    b.showALLaccounts();
                    break;

                case 7: break;
                default: cout<<"\n Enter correct choice";
                exit(0);        
            }

        }while(choice!=7);
    return 0;
}

