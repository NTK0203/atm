#include <iostream>
#include "atm.h"

using namespace std;

int main(){
    ATM atm;
    
    // case1 test: 정상적인 입출금 로직
    cout<<"\n--- case1: tempcard (Normal Operations) ---\n";
    atm.insertCard("tempcard");
    if(atm.setPin("1111")){
        atm.selectAccount("123456789");

        cout<<"balance: "<<atm.showBalance()<<"\n";
        atm.deposit(1000);
        cout<<"after deposit balance: "<<atm.showBalance()<<"\n";
        atm.withdraw(100);
        cout<<"after withdraw balance: "<<atm.showBalance()<<"\n";
    }

    // case2 test: 잔액 부족 시나리오
    cout<<"\n--- case2: mycard (Insufficient Funds) ---\n";
    atm.insertCard("mycard");
    if(atm.setPin("2222")){
        atm.selectAccount("987654321");
        cout<<"balance: "<<atm.showBalance()<<"\n";
        atm.withdraw(10); // 잔액 부족 (잔액 1원인데 10원 출금 시도)
        atm.deposit(10000);
        cout<<"after deposit balance: "<<atm.showBalance()<<"\n";
    }

    // case3 test: 잘못된 비밀번호 입력
    cout<<"\n--- case3: Wrong PIN Attempt ---\n";
    atm.insertCard("tempcard");
    atm.setPin("9999"); // 틀린 비밀번호
    atm.selectAccount("123456789"); // 인증되지 않아 실패해야 함

    // case4 test: 계좌 선택 전 입출금 시도
    cout<<"\n--- case4: Operations without selecting account ---\n";
    atm.insertCard("mycard");
    if(atm.setPin("2222")){
        // 계좌를 선택하지 않고 바로 잔액 조회 및 입금 시도
        atm.showBalance(); 
        atm.deposit(500); 
    }

    // case5 test: 데이터베이스에 없는 유효하지 않은 계좌 선택
    cout<<"\n--- case5: Invalid Account ---\n";
    atm.insertCard("tempcard");
    if(atm.setPin("1111")){
        atm.selectAccount("000000000"); // 등록되지 않은 계좌
        atm.deposit(1000); // 계좌가 유효하지 않아 실패해야 함
    }

    return 0;
}