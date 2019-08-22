#include <stdio.h>
#include <stdlib.h>

struct employee{
    int empNumber;
    int score;
};
typedef struct employee employee;

int enterOption(){
    int selection;
    printf("1- Write to another file  2- update 3- add new record 4- delete record 5- traverse 6-exit\n");
    scanf("%d", &selection);
    return selection;
}
void textFile(FILE *ptr){
    FILE *writePtr = fopen("newRecodFile.txt", "w");
    employee mainEmp = {0,0};
    if(writePtr == NULL){
        printf("New record File cannot be created\n");
    }else{
        rewind(ptr);
        fprintf(writePtr, "These are new infos");
        while(!feof(ptr)){
            fread(&mainEmp, sizeof(employee), 1, ptr);
            if(mainEmp.empNumber != 0)
                fprintf(writePtr, "%d-%d\n", mainEmp.empNumber, mainEmp.score);
            fclose(writePtr);
        }
    }
}

void updateRecord(FILE *ptr){
    int updatedRecordNo;
    int newScore;
    employee mainEmp = {0,0};
    printf("Please enter the updated record no : ");
    scanf("%d", &updatedRecordNo);
    fseek(ptr , (updatedRecordNo-1)* sizeof(employee), SEEK_SET);
    fread(&mainEmp, sizeof(employee), 1, ptr);
    if(mainEmp.empNumber > 0 ){
        printf("Old record : %d-%d \n", mainEmp.empNumber, mainEmp.score);
        printf("Enter the new score : ");
        scanf("%d", &newScore);
        mainEmp.score = newScore;
        fseek(ptr , (updatedRecordNo-1)* sizeof(employee), SEEK_SET);
        fread(&mainEmp, sizeof(employee), 1, ptr);
    }
}

void deleteRecord(FILE *ptr){
    employee mainEmp;
    employee emptyEmp = {0,0};
    int empId;
    printf("Enter the deleted record\n");
    scanf("%d", &empId);
    fseek(ptr, (empId-1)*sizeof(employee), SEEK_SET);
    fread(&mainEmp, sizeof(employee), 1,ptr);
    if(mainEmp.empNumber == 0)
        printf("There is no account");
    else{
        fseek(ptr, (empId-1)*sizeof(employee), SEEK_SET);
        fwrite(&emptyEmp, sizeof(employee), 1,ptr);
    }
}

void traverse(FILE *ptr){
    employee mainEmp = {0,0};
    while(!feof(ptr)){
        fread(&mainEmp, sizeof(employee), 1,ptr);
        printf("%d-%d\n", mainEmp.empNumber, mainEmp.score);
    }
    fclose(ptr);
}
int main(){
    FILE *ptr;
    int selection;
    ptr = fopen("employees.txt", "r+");
    if(ptr == NULL){
        printf("File cannot be opened \n");
    }else{
        while((selection = enterOption()) != 6){
            switch (selection) {
                case 1:textFile(ptr);break;
                case 2:updateRecord(ptr);break;
                case 3:deleteRecord(ptr);break;
                case 4:traverse(ptr);break;
            }
        }
        fclose(ptr);
    }
}
