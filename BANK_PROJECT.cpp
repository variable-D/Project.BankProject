#include <stdio.h>
#include <string.h>
#include <mysql.h>
#pragma warning(disable : 4996)
#pragma comment(lib, "libmysql.lib")

#define LOCALHOST "localhost"
#define USER    "root"
#define PASSWORD "1234"
#define DATABASENAME "bankam"
#define PORTNUMBER 3306



void menu();
int account_opening();
int input();
int output();
int all_check_page();
int money_check_page();
int end_part();
int Check_your_account();
int delete_user();

int main() {
    int choice;
    while (1) {
        menu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            account_opening();
            break;
        case 2:
            input();
            break;
        case 3:
            output();
            break;
        case 4:
            money_check_page();
            break;
        case 5:
            all_check_page();
            break;
        case 6:
            Check_your_account();
            break;
        case 7:
            delete_user();
            break;
        case 8:
            return 0;
            break;
        default:
            break;
        }
    }

}
void finish_with_error(MYSQL* con)

{

    fprintf(stderr, "%s \n", mysql_error(con));

    mysql_close(con);

    exit(1);

}

void menu() {
    printf("\n");
    printf("\t\t\t        HIMEDIA BANK \n");
    printf("\n");
    printf("\t\t-----------------------------------------------------\n");
    printf("\n");
    printf("\t\t\t\t   Menu       \n");
    printf("\n");
    printf("\t\t-----------------------------------------------------\n");
    printf("\n");
    printf("\t\t      1.     계 좌      개 설    \n");
    printf("\n");
    printf("\t\t      2.        입   금    \n");
    printf("\n");
    printf("\t\t      3.        출   금    \n");
    printf("\n");
    printf("\t\t      4.     잔 액      조 회    \n");
    printf("\n");
    printf("\t\t      5.     모든    회 원      조 회    \n");
    printf("\n");
    printf("\t\t      6.     본 인   정 보      조 회    \n");
    printf("\n");
    printf("\t\t      7.     회 원      삭 제    \n");
    printf("\n");
    printf("\t\t      8.     프로그램  종료     \n");
    printf("\n");
    printf("\t\t-----------------------------------------------------\n");
    printf("\n");
    printf("\t\t\t    메뉴 선택 : ");
}
int account_opening() {
   


    MYSQL_RES* res;
    MYSQL_ROW row;

    MYSQL* con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(con, LOCALHOST, USER, PASSWORD, DATABASENAME, PORTNUMBER, NULL, 0) == NULL)

    {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(con);
        return 1;
    }
    mysql_set_character_set(con, "euckr");

    char query[1000];
    int useraccnum;
    char username[100];
    char userssn[100];
    char userphone[100];
    char userpass[100];
    int userage;


    printf("\n\n");
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t원하는 계좌 번호  *5자리 (- 하이픈) 빼고 입력해주세요 : ");
    scanf("%d", &useraccnum);
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t이름 입력해주세요 : ");
    scanf("%s", username);
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t주민등록번호 *14자리 (- 하이픈) 넣고 입력해주세요 : ");
    scanf("%s", userssn);
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t핸드폰 번호 *11자리 (- 하이픈) 빼고 입력해주세요 : ");
    scanf("%s", userphone);
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t사용하실 비밀번호  *4자리 입력해주세요 : ");
    scanf("%s", userpass);
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t사용자의 나이를 입력해주세요 : ");
    scanf("%d", &userage);



    snprintf(query, sizeof(query), "INSERT INTO membertbl(useraccnum,username,userssn,userphone,userpass,userage) VALUES (%d,'%s','%s','%s','%s',%d)", useraccnum, username, userssn, userphone, userpass, userage);

    if (mysql_query(con, query)) {
        printf("\t\t-----------------------------------------------------\n");
        fprintf(stderr, "\t\t개설이 실패 하였습니다. %s\n", mysql_error(con));
    }
    else {
        printf("\t\t-----------------------------------------------------\n");
        printf("\t\t개설이 완료 되었습니다.\n");
    }

    mysql_close(con);

     

    }

int all_check_page() {

    MYSQL* con = mysql_init(NULL);

    if (con == NULL) {

        fprintf(stderr, "mysql_init() failed \n");

        exit(1);

    }



    if (mysql_real_connect(con, LOCALHOST, USER, PASSWORD, DATABASENAME, PORTNUMBER, NULL, 0) == NULL)

    {

        finish_with_error(con);

    }

    mysql_query(con, "set names euckr");



    if (mysql_query(con, "SELECT useraccnum,username,userage,userphone FROM membertbl"))

    {

        finish_with_error(con);

    }



 

    MYSQL_RES* result = mysql_store_result(con);

    if (result == NULL)

    {

        finish_with_error(con);

    }



   

    int num_fields = mysql_num_fields(result);



   

    MYSQL_ROW row;
    
    printf("\n\n\n");
    printf("\t\t\t\t계좌 정보 조회\n\n\n");
    printf("\tㅏ-계좌------------이름-----------나이--------------휴대폰----------┐\n");
    while (row = mysql_fetch_row(result))

    {
        
        for (int i = 0; i < num_fields; i++)

        {
            
            printf("          %s ", row[i]);

        }
        printf("\n\tㅏ------------------------------------------------------------------ㅓ\n");
    }
    printf("\n\n\n\n");

    mysql_free_result(result);

    mysql_close(con);
    
}
int input() {


    MYSQL_RES* res;
    MYSQL_ROW row;

    MYSQL* con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(con, LOCALHOST, USER, PASSWORD, DATABASENAME, PORTNUMBER, NULL, 0) == NULL)

    {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(con);
        return 1;
    }
    mysql_set_character_set(con, "euckr");

    char query[1000];
    int useraccnum;
    int inputmoney;
    int outputmoney = 0;

    
 
    printf("\n\n");
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t본인 계좌 번호  *5자리 (- 하이픈) 빼고 입력해주세요 : ");
    scanf("%d", &useraccnum);
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t입금할 금액을 입력해주세요 : ");
    scanf("%d", &inputmoney);

    if (inputmoney <= 0) {
        printf("\t\t-----------------------------------------------------\n");
        printf("\t\t입금할 금액은 0보다 커야 합니다.\n");
        return 0; // 입력 실패를 나타내는 값 또는 코드를 반환
    }

    snprintf(query, sizeof(query), "INSERT INTO membermoneytbl (num,useraccnum,inputmoney,outputmoney,date)  VALUES (null,%d,%d,%d,now())", useraccnum, inputmoney, outputmoney);

    if (mysql_query(con, query)) {
        printf("\t\t-----------------------------------------------------\n");
        fprintf(stderr, "\t\t입금이 실패 하였습니다. %s\n", mysql_error(con));
    }
    else {
        printf("\t\t-----------------------------------------------------\n");
        printf("\t\t%d원 입금완료 되었습니다.\n", inputmoney);
    }

     
}

int output() {
    MYSQL_RES* res;
    MYSQL_ROW row;

    MYSQL* con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(con, LOCALHOST, USER, PASSWORD, DATABASENAME, PORTNUMBER, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(con);
        return 1;
    }
    mysql_set_character_set(con, "euckr");

    char query[1000];
    int useraccnum;
    int inputmoney = 0;
    int outputmoney;

    printf("\n\n");
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t본인 계좌 번호  *5자리 (- 하이픈) 빼고 입력해주세요 : ");
    scanf("%d", &useraccnum);
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t출금할 금액을 입력해주세요 : ");
    scanf("%d", &outputmoney);

    if (outputmoney <= 0) {
        printf("\t\t-----------------------------------------------------\n");
        printf("\t\t출금할 금액은 0보다 커야 합니다.\n");
        mysql_close(con); // 연결 종료
        return 0; // 입력 실패를 나타내는 값 또는 코드를 반환
    }

    // 출금 가능 여부 확인
    snprintf(query, sizeof(query), "SELECT SUM(inputmoney - outputmoney) AS balance FROM membermoneytbl WHERE useraccnum = %d", useraccnum);

    if (mysql_query(con, query)) {
        printf("\t\t-----------------------------------------------------\n");
        fprintf(stderr, "\t\t잔액 조회 실패: %s\n", mysql_error(con));
        mysql_close(con); // 연결 종료
        return 0; // 입력 실패를 나타내는 값 또는 코드를 반환
    }

    MYSQL_RES* result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "\t\t잔액 조회 결과 가져오기 실패\n");
        mysql_close(con); // 연결 종료
        return 0; // 입력 실패를 나타내는 값 또는 코드를 반환
    }

    row = mysql_fetch_row(result);

    int balance = atoi(row[0]);
    mysql_free_result(result); // 결과 메모리 해제

    if (outputmoney > balance) {
        printf("\t\t-----------------------------------------------------\n");
        printf("\t\t잔액이 부족합니다. 출금할 수 없습니다.\n");
        mysql_close(con); // 연결 종료
        return 0; // 입력 실패를 나타내는 값 또는 코드를 반환
    }

    // 출금 쿼리 실행
    snprintf(query, sizeof(query), "INSERT INTO membermoneytbl (num, useraccnum, inputmoney, outputmoney, date) VALUES (null, %d, 0, %d, now())", useraccnum, outputmoney);

    if (mysql_query(con, query)) {
        printf("\t\t-----------------------------------------------------\n");
        fprintf(stderr, "\t\t출금이 실패 하였습니다. %s\n", mysql_error(con));
        mysql_close(con); // 연결 종료
        return 0; // 입력 실패를 나타내는 값 또는 코드를 반환
    }
    else {
        printf("\t\t-----------------------------------------------------\n");
        printf("\t\t%d원이 출금 완료되었습니다.\n", outputmoney);
        mysql_close(con); // 연결 종료
        return 1; // 입력 성공을 나타내는 값 또는 코드를 반환
    }
    
}


int money_check_page(){
    char query[1000];
    int useraccnum;
    MYSQL* con = mysql_init(NULL);

    if (con == NULL) {

        fprintf(stderr, "mysql_init() failed \n");

        exit(1);

    }



    if (mysql_real_connect(con, LOCALHOST, USER, PASSWORD, DATABASENAME, PORTNUMBER, NULL, 0) == NULL)

    {

        finish_with_error(con);

    }

    

    mysql_query(con, "set names euckr");

    printf("\n\n");
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t본인 계좌 번호  *5자리 (- 하이픈) 빼고 입력해주세요 : ");
    scanf("%d", &useraccnum);

    snprintf(query, sizeof(query), "select useraccnum,sum(inputmoney-outputmoney) from membermoneytbl where useraccnum = '%d'",useraccnum);

    if (mysql_query(con, query)) {
        printf("\t\t-----------------------------------------------------\n");
        fprintf(stderr, "\t\t잔액 조회 실패 :  %s\n", mysql_error(con));
    }
    else {
        printf("\t\t-----------------------------------------------------\n");
        printf("\t\t잔액 조회 성공\n");
    }



    MYSQL_RES* result = mysql_store_result(con);

    if (result == NULL)

    {

        finish_with_error(con);

    }





    int num_fields = mysql_num_fields(result);





    MYSQL_ROW row;

    printf("\n\n\n");
    printf("\t\t\t\t잔액 정보 조회\n\n\n");
    printf("\t\t\tㅏ-계좌------------------------잔액---┐\n");
    while (row = mysql_fetch_row(result))

    {

        for (int i = 0; i < num_fields; i++)

        {

            printf("\t\t          %s ", row[i]);

        }
        printf("\n\t\t\tㅏ------------------------------------ㅓ\n");
    }
    printf("\n\n\n\n");

    mysql_free_result(result);

    mysql_close(con);
    
}
int Check_your_account() {
    char query[1000];
    int useraccnum;

    MYSQL* con = mysql_init(NULL);

    if (con == NULL) {

        fprintf(stderr, "mysql_init() failed \n");

        exit(1);

    }



    if (mysql_real_connect(con, LOCALHOST, USER, PASSWORD, DATABASENAME, PORTNUMBER, NULL, 0) == NULL)

    {

        finish_with_error(con);

    }

    mysql_query(con, "set names euckr");

    printf("\n\n");
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t본인 계좌 번호  *5자리 (- 하이픈) 빼고 입력해주세요 : ");
    scanf("%d", &useraccnum);

    snprintf(query, sizeof(query), "SELECT useraccnum,username,userage,userphone FROM membertbl where useraccnum = '%d'", useraccnum);

    if (mysql_query(con, query))

    {

        finish_with_error(con);

    }





    MYSQL_RES* result = mysql_store_result(con);

    if (result == NULL)

    {

        finish_with_error(con);

    }





    int num_fields = mysql_num_fields(result);





    MYSQL_ROW row;

    printf("\n\n\n");
    printf("\t\t\t\t본인 정보 조회\n\n\n");
    printf("\tㅏ-계좌------------이름-----------나이--------------휴대폰----------┐\n");
    while (row = mysql_fetch_row(result))

    {

        for (int i = 0; i < num_fields; i++)

        {

            printf("          %s ", row[i]);

        }
        printf("\n\tㅏ------------------------------------------------------------------ㅓ\n");
    }
    printf("\n\n\n\n");

    mysql_free_result(result);

    mysql_close(con);
    
}
int delete_user() {
    char query[1000];
    int useraccnum;
    MYSQL* con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, LOCALHOST, USER, PASSWORD, DATABASENAME, PORTNUMBER, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    mysql_query(con, "set names euckr");

    printf("\n\n");
    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t삭제할 사용자의 계좌 번호  *5자리 (- 하이픈) 빼고 입력해주세요 : ");
    scanf("%d", &useraccnum);

    // 먼저 membermoneytbl 테이블에서 사용자와 관련된 모든 데이터 삭제
    snprintf(query, sizeof(query), "DELETE FROM membermoneytbl WHERE useraccnum = %d", useraccnum);

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    // 이후 membertbl 테이블에서 사용자 삭제
    snprintf(query, sizeof(query), "DELETE FROM membertbl WHERE useraccnum = %d", useraccnum);

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    printf("\t\t-----------------------------------------------------\n");
    printf("\t\t사용자 계정이 삭제되었습니다.\n");

    mysql_close(con);

    
}

