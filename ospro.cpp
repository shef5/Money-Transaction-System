#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
int mutex=1;
int balance=100,balancee[15],accNo,owner;


void *credit( void *ptr )
{
     /*char *message;
     //message = (char *) ptr;

     int x=0,i=0;
     while(message[i]!='\0'){
        x=x*10+message[i]-'0';
        i++;
     }*/

        int money;
     while(mutex==0)
        ;

    mutex=0;

    //cs start;
    while(1){
            printf("Enter account Number\n");
            scanf("%d",&accNo);
            if(accNo<0){printf("Wait... Someone is crediting money from the account\n");}
                else
                    break;
        }
    printf("\nYour present balance is: %d\n",balancee[accNo]);
          while(1){
        printf("Enter Money To Credit\n");
        scanf("%d",&money);
        if(money<0){
            printf("Wait... Someone is crediting money from the account\n");
            continue;
        }
        break;
    }
    //printf("\nCredit\nYour previous balance was: %d\n",balance);
    balancee[accNo] = balancee[accNo] + money;
    //printf("Your updated balance is: %d\n\n",balance);

    //cs ends

     mutex=1;
}

void *debit( void *ptr )
{
     /*char *message;
     message = (char *) ptr;
     int x=0,i=0;
     while(message[i]!='\0'){
        x=x*10+message[i]-'0';
        i++;
     }*/

     while(mutex==0)
        ;

    mutex=0;
    int money;
    //cs start;
    while(1){
        printf("Enter account Number\n");
        scanf("%d",&accNo);
        if(accNo<0){printf("Wait... Someone is debiting money from the account\n");}
                else
                    break;

        }
    printf("\nYour present balance is: %d\n",balancee[accNo]);
      while(1){
        printf("Enter Money To Debit\n");
        scanf("%d",&money);
        if(money<0){
            printf("Wait... Someone is debiting money from the account\n");
            continue;
        }
        break;
    }
    if(money>balancee[accNo]){
        printf("Insufficient balance\n");
        mutex=1;
        return (void*)0;
    }
    //printf("\nDebit\nYour previous balance was: %d\n",balance);
    balancee[accNo] = balancee[accNo] - money;
       // printf("Your updated balance is: %d\n\n",balance);
    //cs ends

     mutex=1;
}

int atoi(string& s){
    int ans=0,i;
    for(i=0;i<s.length();i++){
        ans=ans*10+s[i]-'0';
    }
    return ans;
}


main()
{
    int i;
    string password="dhruv";
    string userPass;
    string line;
    ifstream myfile;
    myfile.open ("os_dbFile.txt");

    for(i=0;i<10;i++){
        getline (myfile,line);
        balancee[i]=atoi(line);
        //cout<<i<<" "<<balancee[i]<<"\n";
    }
    myfile.close();



    while(1){
            cout<<"Enter Admin's Password\n";
            cin>>userPass;
            if(userPass==password){
                cout<<"Welcome\n";
                break;
            }
            else
                cout<<"Wrong Password\n";
        }


    while(1){

        printf("Press -1 to see Balance\nPress -2 to credit\nPress -3 to debit\n");
        int option ;
        scanf("%d",&option);
        if(option==-1){
            while(1){
            printf("Enter account Number\n");
            scanf("%d",&accNo);
            if(accNo<0){printf("Wait... Someone is viewing money from the account\n");}
                else
                    break;
            }
            printf("\nYour present balance is: %d\n",balancee[accNo]);
            continue;
        }
        else if(option==-2){
            pthread_t thread_credit;
            const char message1[] = "0";
            int  iret1, iret2;

             iret1 = pthread_create( &thread_credit, NULL, credit, (void*) message1);
             if(iret1)
             {
                 fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
                 exit(EXIT_FAILURE);
             }

             pthread_join( thread_credit, NULL);
        }
        else{
            pthread_t thread_debit;
            const char message2[] = "0";
            int  iret1, iret2;

             iret2 = pthread_create( &thread_debit, NULL, debit, (void*) message2);
             if(iret2)
             {
                 fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
                 exit(EXIT_FAILURE);
             }

             pthread_join( thread_debit, NULL);
        }

    ofstream myfilewrite;
    myfilewrite.open ("os_dbFile.txt");

    for(i=0;i<10;i++){
        myfilewrite << balancee[i] <<"\n";
    }
    myfilewrite.close();

    }

}



