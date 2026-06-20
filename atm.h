#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class ATM{
    private:
        string cur_card;
        bool isPinVerified;
        string cur_account;

        unordered_map<string, string> card_pin;
        unordered_map<string, int> account_balance;

        bool checkPin(const string& card, const string& pin){
            if(card_pin.count(card))
                if(card_pin[card] == pin)
                    return true;
            return false;
        }

        int getBalance(const string& account){
            if(account_balance.count(account))
                return account_balance[account];
            return -1;
        }

        bool deposit(const string& account, int amount){
            if(account_balance.count(account)){
                account_balance[account] += amount;
                return true;
            }
            return false;
        }
        bool withdraw(const string& account, int amount){
            if(account_balance.count(account))
                if(account_balance[account]>=amount){
                    account_balance[account]-=amount;
                    return true;
                }
            return false;
        }
    public:
        //temp data set
        ATM() : cur_card(""), isPinVerified(false), cur_account(""){
            card_pin["tempcard"]="1111";
            account_balance["123456789"]=10000;

            card_pin["mycard"]="2222";
            account_balance["987654321"]=1;
        }

        void insertCard(const string& card){
            cur_card = card;
            isPinVerified = false;
            cur_account = "";
            cout<<"card inserted success! \n card: "<<card<<"\n";
        }

        bool setPin(const string& pin){
            if(cur_card.empty()){
                cout<<"there is no card. first make your card\n";
                return false;
            }
            if(checkPin(cur_card, pin)){
                isPinVerified=true;
                cout<<"Pin verified.\n";
                return true;
            }
            else{
                cout<<"Pin invalid\n";
                return false;
            }
        }

        bool selectAccount(const string& account){
            if(!isPinVerified){
                cout<<"Pin invalid\n";
                return false;
            }
            cur_account=account;
            cout<<"account is selected.\n account: "<<account<<"\n";
            return true;
        }

        int showBalance(){
            if(cur_account.empty()){
                cout<<"First you have to select account.\n";
                return -1;
            }
            return getBalance(cur_account);
        }
        bool deposit(int amount){
            if(cur_account.empty()){
                cout<<"First you have to select account.\n";
                return false;
            }

            if(deposit(cur_account,amount)){
                cout<<"deposit success. \n amount: "<<amount<<"\n";
                return true;
            }
            else{
                cout<<"account invalid\n";
                return false;
            }
        }

        bool withdraw(int amount){
            if(cur_account.empty()){
                cout<<"First you have to select account.\n";
                return false;
            }
            if(withdraw(cur_account,amount)){
                cout<<"withdraw success. \n amount: "<<amount<<"\n";
                return true;
            }
            else{
                cout<<"account invalid or amount over\n";
                return false;
            }
        }
};