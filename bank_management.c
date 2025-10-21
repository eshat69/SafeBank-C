#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

void create_account() ;
void deposit_money() ;
void withdraw_money() ;
void check_balance() ;
void delete_account() ;
void list_account() ;
void transaction_log() ;
void transaction_history() ;

const char *ACCOUNTs_File = "account.dat" ;
const char *TRANSACTION_File = "transaction.txt" ;

typedef struct {
    char name[50] ;
    int acc_no ;
    float balance ;
} Account ;

int main() {
    while (1) {
        printf("\n\n ~ Bank Management system ~ \n") ;
        printf("\n 1. Create Account \n") ;
        printf("\n 2. Deposit Money \n") ;
        printf("\n 3. Withdraw money \n") ;
        printf("\n 4. Check Balance \n") ;
        printf("\n 5. Delete Account \n") ;
        printf("\n 6. List of all Account \n") ;
        printf("\n 7. Show transaction history \n") ;
        printf("\n 8. Exit \n") ;
        printf("\n Enter your choice : ") ;

        int choice ;
        scanf("%d", &choice) ;

        switch (choice) {
            case 1 :
                create_account() ;

                break ;
            case 2 :
                deposit_money() ;

                break ;
            case 3 :
                withdraw_money() ;

                break ;
            case 4 :
                check_balance() ;

                break ;
            case 5 :
                delete_account() ;

                break ;
            case 6 :
                list_account() ;

                break ;
            case 7 :
                transaction_history() ;

                break ;
            case 8 :
                printf("\n Closing the bank . Thank you for visiting \n") ;
                return 0 ;

            default :
                printf("\n Invalid choice \n ") ;
        }
    }
    return 0 ;
}

void create_account() {
    Account acc ;
    FILE *file = fopen(ACCOUNTs_File , "ab+") ;
    if (file == NULL){
        printf("\n Unable to open file !") ;
        return ;
    }
    char c ;
    do {
        c = getchar() ;
    } while (c != '\n' && c != EOF) ;      //take input until new line and end of file

    printf("\n Enter your name : ") ;
    fgets(acc.name, sizeof(acc.name), stdin) ;
    int idx = strcspn(acc.name, "\n") ;
    acc.name[idx] = '\0' ;
    printf("Enter your account number :") ;
    scanf("%d", &acc.acc_no) ;
    acc.balance = 0.0 ;
    fwrite(&acc , sizeof(acc) , 1 , file ) ;
    fclose(file) ;
    printf("\n Account created successfully ! \n") ;
}
void deposit_money() {
    FILE *file = fopen(ACCOUNTs_File , "rb+") ;
    if (file == NULL) {
        printf("\n Unable to open account file !") ;
        return ;
    }
    FILE *tfile = fopen(TRANSACTION_File, "r") ;
    if(tfile == NULL) {
        printf("\n No transaction history found ! ") ;
        return ;
    }
    int acc_no ;
    float money ;
    Account acc_r ;
    printf("\n Enter your account number :") ;
    scanf("%d", &acc_no) ;
    printf("\n Enter amount to deposit : ") ;
    scanf("%f", &money) ;
    while (fread(&acc_r , sizeof(acc_r) , 1 , file)) {
        if(acc_r.acc_no == acc_no){
            acc_r.balance += money ;
            //fseek(file , -sizeof(acc_r).SEEK_CUR ) ;
            fseek(file , -sizeof(acc_r), SEEK_CUR);
            fwrite(&acc_r , sizeof(acc_r) , 1 , file) ;
            transaction_log(acc_no, "Deposit" , money , acc_r.balance) ;
            fclose(file) ;
            printf("\n Successfully deposited %.2f Tk . New balance is %.2f Tk", money , acc_r.balance) ;
            return ;
        }
    }
    fclose(file) ;
    fclose(tfile) ;
    printf("\n Money could not be deposit as the account no %d was not found in record." , acc_no ) ;
}

void withdraw_money() {
    FILE *tfile = fopen(TRANSACTION_File, "r") ;
    if(tfile == NULL) {
        printf("\n No transaction history found ! ") ;
        return ;
    }
    FILE *file = fopen(ACCOUNTs_File , "rb+") ;
    if(file == NULL){
        printf("\n Unable to open the account file !") ;
        return ;
    }
    int acc_no ;
    float money ;
    Account acc_r ;
    printf("\n Enter your account number : ") ;
    scanf("%d",&acc_no) ;
    printf("\n Enter the amount you want to withdraw : ") ;
    scanf("%f" , &money) ;
    while (fread(&acc_r , sizeof(acc_r) , 1 , file)) {
    if (acc_r.acc_no == acc_no) {
        if (acc_r.balance >= money) {
            acc_r.balance -= money;
            fseek(file , - sizeof(acc_r), SEEK_CUR) ;
            fwrite(&acc_r, sizeof(acc_r), 1, file) ;
            transaction_log(acc_no, "Withdraw" , money , acc_r.balance) ;
            printf("\n Successfully withdrew %.2f Tk. Remaining balance is %.2f Tk\n",
                   money, acc_r.balance);
        } else {
            printf("\n Insufficient balance !");
        }
        fclose(file);
        return;
    }
}
fclose(file) ;
fclose(tfile) ;
printf("\n Account number %d not found.\n", acc_no) ;
}

void check_balance() {
    FILE *file = fopen(ACCOUNTs_File , "rb") ;
    if(file == NULL) {
        printf("\n Unable to open file !") ;
        return ;
    }
    int acc_no ;
    Account acc_r ;
    printf("\n Enter your account number : ") ;
    scanf("%d" , &acc_no) ;
    while (fread(&acc_r , sizeof(acc_r) , 1 , file)){
        if(acc_r.acc_no == acc_no){
            printf("\n Your current balance is %.2f Tk ", acc_r.balance) ;
            fclose(file) ;
            return ;
        }
    }
    fclose(file);
    printf("\n Account no %d was not found ", acc_no);
}

void delete_account() {
    Account acc ;
    FILE *file = fopen(ACCOUNTs_File , "rb") ;
    if (file == NULL){
        printf("\n Unable to open file !") ;
        return ;
    }
    FILE *temp = fopen("temp.dat", "wb") ;
    if(temp == NULL){
        printf("\n Unable to create temporary file !") ;
        fclose(file) ;
        return ;
    }
    int acc_no ;
    int found = 0 ;
    Account acc_r ;
    printf("\n Enter the account number you want to delete : ") ;
    scanf("%d" , &acc_no) ;
    while (fread(&acc_r , sizeof(acc_r) , 1 , file)){
        if(acc_r.acc_no == acc_no){
            found = 1 ;
            printf("\n Account deleted successfully !") ;
        } else {
            fwrite(&acc_r, sizeof(acc_r), 1 , temp) ;
        }
    }
    fclose(file) ;
    fclose(temp) ;
    if (found){
        remove(ACCOUNTs_File);
        rename("temp.dat", ACCOUNTs_File) ;
    }
    else {
        remove("temp.dat") ;
        printf("\n Account number %d not found !", acc_no) ;
    }
}

void list_account() {
    Account acc_r ;
    int count = 0 ;
    FILE *file = fopen(ACCOUNTs_File , "rb") ;
    if(file == NULL) {
        printf("\n No Account found !") ;
        return ;
    }
    printf("\n ~List of Accounts~\n") ;
    while (fread(&acc_r , sizeof(acc_r) , 1 , file)){
        printf("Account No : %d \n", acc_r.acc_no) ;
        printf("Name       : %s \n", acc_r.name) ;
        printf("Balance    : %.2f Tk \n", acc_r.balance) ;
        count++ ;
    }
    if (count == 0){
        printf("\n No account available !") ;
    }
    fclose(file) ;
}

void transaction_log() {
    int acc_no ;
    const char *type ;
    float amount ;
    float balance ;
    FILE *tfile = fopen(TRANSACTION_File , "a") ;
    if (tfile) {
        printf("\n Unable to open transaction file !") ;
        return ;
    }
    time_t now ;
    time(&now) ;
    char *dt = ctime(&now) ;
    dt[strcspn(dt , "\n")] = '\0' ;
    fprintf(tfile, "%d | %s | %.2f | %.2f | %s \n" , acc_no, type, amount, balance, dt ) ;
    fclose(tfile) ;
}

void transaction_history() {
    FILE *tfile = fopen(TRANSACTION_File, "r") ;
    if(tfile == NULL) {
        printf("\n No transaction history found ! ") ;
        return ;
    }
    int acc_no ;
    printf("\n Enter Account number to view History !") ;
    scanf("%d" , &acc_no) ;

    char line[200] ;
    int found = 0 ;
    printf("\n Transaction history for  Account %d : ", acc_no) ;
    while(fgets(line , sizeof(line) , tfile)) {
        int file_acc_no ;
        if (sscanf(line , "%d" , &file_acc_no) == 1){
            if (file_acc_no == acc_no) {
                printf("%s" , line) ;
                found = 1 ;
            }
        }
    }
    fclose(tfile) ;
    if(!found) {
        printf("\n No history found for account %d !" , acc_no) ;

    }
    fclose(tfile) ;
}

