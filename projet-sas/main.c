#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_RESERVATION 100
#define NAME_LENGTH 50
#define PHONE_LENGTH 11
#define STATUS_LENGTH 30

#define ID_WIDTH 4
#define NAME_WIDTH 15
#define LASTNAME_WIDTH 15
#define NUMBER_WIDTH 15
#define EMAIL_WIDTH 25
#define AGE_WIDTH 4
#define STATUS_WIDTH 15
#define DATE_WIDTH 15

void print_line() {
    printf("+");
    for(int i = 0; i < ID_WIDTH; i++) printf("-");
    printf("+");
    for(int i = 0; i < NAME_WIDTH; i++) printf("-");
    printf("+");
    for(int i = 0; i < LASTNAME_WIDTH; i++) printf("-");
    printf("+");
    for(int i = 0; i < NUMBER_WIDTH; i++) printf("-");
    printf("+");
    for(int i = 0; i < EMAIL_WIDTH; i++) printf("-");
    printf("+");
    for(int i = 0; i < AGE_WIDTH; i++) printf("-");
    printf("+");
    for(int i = 0; i < STATUS_WIDTH; i++) printf("-");
    printf("+");
    for(int i = 0; i < DATE_WIDTH; i++) printf("-");
    printf("+\n");

}

void menu() {
    printf("\n---------------------------------------------");
    printf("\n ********** MENU ********** \n");
    printf("1. Add the reservation \n");
    printf("2. Edit the reservation \n");
    printf("3. Delete the reservation \n");
    printf("4. Display all reservation \n");
    printf("5. Display Details reservation \n");
    printf("6. Search the reservation \n");
    printf("7. Display statistics patients who have booking \n");
    printf("8. Sort The reservations \n");
    printf("9. Exit");
}

struct reservations {
    int id;
    char firstName[NAME_LENGTH];
    char lastName[NAME_LENGTH];
    char numberPhone[PHONE_LENGTH];
    char emails[NAME_LENGTH];
    char status[STATUS_LENGTH];
    int age;
    int days;
    int months;
    int years;
};

//function calculate average patients by age
void averagePatients(struct reservations reserves[], int size) {

    int result = 0;
    for(int i = 0; i < size; i++) {
        result = result + reserves[i].age;
    }

    int average = result / size;

    printf("\n Average age: %d \n", average);
}
// end function calculate average patients by age

void groupAge(struct reservations reserves[], int size) {

    int count_1 = 0;
    int count_2 = 0;
    int count_3 = 0;

    for(int i = 0; i < size; i++) {
        if(reserves[i].age >= 0 && reserves[i].age <= 18) {
            count_1++;
        } else if(reserves[i].age >= 19 && reserves[i].age <= 35) {
            count_2++;
        }  else {
            count_3++;
        }
    }

        printf("Number age between 0 - 18 %d \n", count_1);
        printf("Number age between 19 - 35 %d \n", count_2);
        printf("Number age +36 %d \n", count_3);
}

// sort reservation by name
int comparatorByName(const void *a, const void *b) {

    return strcmp(((struct reservations*)a)->firstName, ((struct reservations*)b)->firstName);

}

void sortByStatus(struct reservations *reserves, int size, const char *statu) {

    int i, j;
    struct reservations tmp;

    for(i = 0; i < size - 1; i++) {
        for(j = 0; j < size - i - 1; j++) {
            if(strcmp(reserves[j].status, reserves[j + 1].status) > 0) {
                tmp = reserves[j];
                reserves[j] = reserves[j + 1];
                reserves[j + 1] = tmp;
            }
        }
    }
}

int main()
{
    struct reservations reserve[MAX_RESERVATION] = {

        {1, "Othmane", "Rhazlani", "0612345678", "othmane@gmail.com", "validated", 21, 21, 12, 2024},
        {2, "Mostafa", "Rhazlani", "0787654321", "mostafa@gmail.Com", "cancelled", 25, 22, 04, 2024},
        {3, "Adil", "taarabt", "0623890212", "adil@gmail.com", "postponed", 66, 22, 04, 2024},
        {4, "Anas", "Koram", "0678124522", "anas@gmail.com", "processed", 10, 22, 04, 2024},
        {5, "Jalal", "Benlhsan", "0590387655", "jalal@gmail.com", "cancelled", 25, 22, 04, 2024},
        {6, "Imran", "hosni", "0712673254", "imran@gmail.com", "validated", 18, 22, 04, 2024}
    };

    int choose, total = 6, i, uniqueId = 7;
    char fName[NAME_LENGTH], lName[NAME_LENGTH], phone[PHONE_LENGTH], email[NAME_LENGTH];
    int userAge, day, month, year;
    int existing = 0;

    char searchByName[NAME_LENGTH];
    int searchById;
    int searchByDate;

    while(true) {

        if(total >= MAX_RESERVATION) {
            printf("\n No more space for add reservation\n");
            break;
        }

        menu(); // menu
        printf("\n\n");

        // choose number
        printf("Enter number between (1 and 9) : ");

        while(scanf("%d", &choose) != 1 || choose < 1 || choose > 9) {
            printf("\n This Number Not Exist In Menu \n");
            printf(" Choose another number: ");

            while(getchar() != '\n');

        }
        // end choose number

        // switch to display any case choose user
        switch(choose) {
            case 1:
                printf("\n----------Add Reservation----------\n");

                printf("Enter first name : ");
                scanf("%s", fName);

                printf("Enter last name : ");
                scanf("%s", lName);

                rtnNumber:
                printf("Enter your number phone : ");
                scanf("%s",phone);

                if(strlen(phone) != PHONE_LENGTH - 1) {
                    printf("\n Please enter 10 number!\n");
                    goto rtnNumber;
                }

                for (i = 0; i < total; i++) {
                    if(strcmp(reserve[i].numberPhone, phone) == 0) {
                        printf("\n Number Phone already exist!\n");
                        existing = 1;
                        sleep(1);
                        goto rtnNumber;
                        break;
                    }
                }

                rtnEmail:
                printf("Enter your email : ");
                scanf("%s",email);

                for (i = 0; i < total; i++) {
                    if(strcmp(reserve[i].emails, email) == 0) {
                        printf("\nEmail already exist!\n");
                        existing = 1;
                        sleep(1);
                        goto rtnEmail;
                        break;
                    }
                }


                printf("Enter your age : ");
                scanf("%d", &userAge);

                printf("\nChoose booking date \n");

                printf("Choose day: ");
                while(scanf("%d", &day) != 1 || day > 31) {
                    printf("\n Choose number between 1 and 31: ");
                    while(getchar() != '\n');
                    sleep(1);
                }

                printf("Choose month: ");
                while(scanf("%d", &month) != 1 || month > 12) {
                    printf("\n Choose number between 1 and 12: ");
                    while(getchar() != '\n');
                    sleep(1);
                }

                printf("Choose year: ");
                while(scanf("%d", &year) != 1 || year < 2024) {
                    printf("\n Choose year above 2023: ");
                    while(getchar() != '\n');
                    sleep(1);
                }

                if (!existing) {
                    reserve[total].id = uniqueId++;
                    strcpy(reserve[total].firstName, fName);
                    strcpy(reserve[total].lastName, lName);
                    strcpy(reserve[total].numberPhone, phone);
                    strcpy(reserve[total].emails, email);
                    strcpy(reserve[total].status, "validated");
                    reserve[total].age = userAge;
                    reserve[total].days = day;
                    reserve[total].months = month;
                    reserve[total].years = year;
                    printf("\n Reservation add successfully\n");
                    sleep(2);
                    total++;
                    break;
                }
                break;

            case 2:
                printf("\n----------Edit The Reservation----------\n");

                if(total == 0) {
                    printf("No reservation to edit");
                }

                printf("1. Edit Information \n");
                printf("2. Edit Status \n");


                // choose number
                printf("\nChoose option: ");

                while(scanf("%d", &choose) != 1 || choose < 1 || choose > 2) {
                    printf("\n This Option Not Exist In Menu \n");
                    printf(" Choose another option: ");

                    while(getchar() != '\n');

                }
                // end choose number

                switch(choose) {
                    case 1:


                        // choose number
                        printf("\nEnter ID reservation: ");

                        while(scanf("%d", &searchById) != 1) {
                            printf("\n This ID Not Exist \n");
                            printf(" Choose another ID: ");

                            while(getchar() != '\n');

                        }
                        // end choose number

                        for(i = 0; i < total; i++) {
                            if(reserve[i].id == searchById) {
                                printf("Change your first name: ");
                                scanf("%s", reserve[i].firstName);

                                printf("Change your last name: ");
                                scanf("%s", reserve[i].lastName);

                                rtnChangeNumber:
                                printf("Change your number phone : ");
                                scanf("%s",phone);

                                if(strlen(phone) != PHONE_LENGTH - 1) {
                                    printf("\n Please enter 10 number!\n");
                                    goto rtnChangeNumber;
                                }

                                for (i = 0; i < total; i++) {
                                    if(strcmp(reserve[i].numberPhone, phone) == 0) {
                                        printf("\n Number Phone already exist!\n");
                                        existing = 1;
                                        sleep(1);
                                        goto rtnChangeNumber;
                                        break;
                                    }
                                }

                                rtnChangeEmail:
                                printf("Change your email : ");
                                scanf("%s",email);

                                for (i = 0; i < total; i++) {
                                    if(strcmp(reserve[i].emails, email) == 0) {
                                        printf("\nEmail already exist!\n");
                                        existing = 1;
                                        sleep(1);
                                        goto rtnChangeEmail;
                                        break;
                                    }
                                }

                                printf("Change your age: ");
                                scanf("%d", &reserve[i].age);

                                printf("Change day reservation: ");
                                scanf("%d", &reserve[i].days);

                                printf("Change month reservation: ");
                                scanf("%d", &reserve[i].months);

                                printf("Change year reservation: ");
                                scanf("%d", &reserve[i].years);
                            }
                        }

                        printf("\n Reservation Changed successfully\n");
                        sleep(2);

                        break;
                    case 2:

                        // choose number
                        printf("\nEnter ID reservation: ");

                        while(scanf("%d", &searchById) != 1) {
                            printf("\n This ID Not Exist \n");
                            printf(" Choose another ID: ");

                            while(getchar() != '\n');

                        }
                        // end choose number

                        for(i = 0; i < total; i++) {
                            if(reserve[i].id == searchById) {

                                printf("1. validated \n");
                                printf("2. postponed \n");
                                printf("3. cancelled \n");
                                printf("4. processed \n");

                                printf("Choose option: ");
                                scanf("%d", &choose);

                                if(choose == 1) {
                                    strcpy(reserve[i].status, "validated");
                                } else if(choose == 2) {
                                    strcpy(reserve[i].status, "postponed");
                                } else if(choose == 3) {
                                    strcpy(reserve[i].status, "cancelled");
                                } else if(choose == 4) {
                                    strcpy(reserve[i].status, "processed");
                                } else {
                                    printf("Not found this option");
                                }
                            }
                        }

                        printf("\n Status changed successfully!\n");
                        sleep(2);
                        break;
                }

                break;

            case 3:
                printf("\n----------Delete The Reservation----------\n");

                if(total == 0) {
                    printf("No reservation to Delete");
                }

                // choose number
                printf("\nEnter ID reservation: ");

                while(scanf("%d", &searchById) != 1) {
                    printf("\n This ID Not Exist \n");
                    printf(" Choose another ID: ");

                    while(getchar() != '\n');

                }
                // end choose number

                for(i = 0; i < total; i++) {
                    if(reserve[i].id == searchById) {
                        for(int j = i; j < total; j++) {
                            reserve[j] = reserve[j+1];
                        }
                        total--;
                        printf("\n Reservation deleted successfully\n");
                        sleep(2);
                    }
                }
                break;

            case 4:
                printf("\n----------Display All Reservations----------\n");

                if(total != 0) {
                    printf("\nTotal Reservations: %d \n", total);

                    print_line();

                    printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|\n",
                        ID_WIDTH, "ID",
                        NAME_WIDTH, "First Name",
                        LASTNAME_WIDTH, "Last Name",
                        NUMBER_WIDTH, "Number",
                        EMAIL_WIDTH, "Email",
                        AGE_WIDTH, "Age",
                        STATUS_WIDTH, "Status",
                        DATE_WIDTH, "Date");

                    print_line();

                    for(i = 0; i < total; i++) {

                        printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*d|%-*s|%-*d|\n",
                        ID_WIDTH, reserve[i].id,
                        NAME_WIDTH, reserve[i].firstName,
                        LASTNAME_WIDTH, reserve[i].lastName,
                        NUMBER_WIDTH, reserve[i].numberPhone,
                        EMAIL_WIDTH, reserve[i].emails,
                        AGE_WIDTH, reserve[i].age,
                        STATUS_WIDTH, reserve[i].status,
                        DATE_WIDTH, reserve[i].days, reserve[i].months, reserve[i].years);
                    }
                    print_line();
                } else {
                    printf("Reservations empty");
                }
                break;

            case 5:
                printf("\n----------Display Details Reservations----------\n");

                existing = 0;

                if(total == 0) {
                    printf("Reservations Empty");
                }

                rtnIdDetail:
                // choose number
                printf("\nEnter ID reservation: ");

                while(scanf("%d", &searchById) != 1) {
                    printf("\n This ID Not Exist \n");
                    printf(" Choose another ID: ");

                    while(getchar() != '\n');

                }
                // end choose number

                    print_line();

                    printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|\n",
                        ID_WIDTH, "ID",
                        NAME_WIDTH, "First Name",
                        LASTNAME_WIDTH, "Last Name",
                        NUMBER_WIDTH, "Number",
                        EMAIL_WIDTH, "Email",
                        AGE_WIDTH, "Age",
                        STATUS_WIDTH, "Status",
                        DATE_WIDTH, "Date");

                    print_line();

                    for(i = 0; i < total; i++) {
                        if(reserve[i].id == searchById) {
                            printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*d|%-*s|%-*d %-*d %-*d|\n",
                            ID_WIDTH, reserve[i].id,
                            NAME_WIDTH, reserve[i].firstName,
                            LASTNAME_WIDTH, reserve[i].lastName,
                            NUMBER_WIDTH, reserve[i].numberPhone,
                            EMAIL_WIDTH, reserve[i].emails,
                            AGE_WIDTH, reserve[i].age,
                            STATUS_WIDTH, reserve[i].status,
                            DATE_WIDTH, reserve[i].days,
                            DATE_WIDTH, reserve[i].months,
                            DATE_WIDTH, reserve[i].years);
                            existing = 1;
                        }
                    }
                    print_line();

                    if(!existing) {
                        printf("\n --this ID not exist\n");
                        goto rtnIdDetail;
                    }
                break;
            case 6:
                printf("\n----------Search The Reservation----------\n");

                if(total == 0) {
                    printf("Reservations Empty");
                }

                printf("1. Search by ID \n");
                printf("2. Search by name \n");

                // choose number
                printf("\nChoose option: ");

                while(scanf("%d", &choose) != 1) {
                    printf("\n This Choose Not Exist In Menu \n");
                    printf(" Choose another option: ");

                    while(getchar() != '\n');

                }
                // end choose number

                switch(choose) {
                    case 1:
                        existing = 0;
                        rtnId:
                        // choose number
                        printf("\nEnter ID reservation: ");

                        while(scanf("%d", &searchById) != 1) {
                            printf("\n This ID Not Exist \n");
                            printf(" Choose another ID: ");

                            while(getchar() != '\n');

                        }
                        // end choose number

                        print_line();

                        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|\n",
                            ID_WIDTH, "ID",
                            NAME_WIDTH, "First Name",
                            LASTNAME_WIDTH, "Last Name",
                            NUMBER_WIDTH, "Number",
                            EMAIL_WIDTH, "Email",
                            AGE_WIDTH, "Age",
                            STATUS_WIDTH, "Status",
                            DATE_WIDTH, "Date");

                        print_line();

                        for(i = 0; i < total; i++) {
                            if(reserve[i].id == searchById) {
                                printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*d|%-*s|%-*d|\n",
                                ID_WIDTH, reserve[i].id,
                                NAME_WIDTH, reserve[i].firstName,
                                LASTNAME_WIDTH, reserve[i].lastName,
                                NUMBER_WIDTH, reserve[i].numberPhone,
                                EMAIL_WIDTH, reserve[i].emails,
                                AGE_WIDTH, reserve[i].age,
                                STATUS_WIDTH, reserve[i].status,
                                DATE_WIDTH, reserve[i].days, reserve[i].months, reserve[i].years);
                                existing = 1;
                            }
                        }
                        print_line();

                        if(!existing) {
                            printf("\n --this ID not exist\n");
                            goto rtnId;
                        }
                        break;
                    case 2:
                        existing = 0;
                        // choose name
                        rtnName:
                        printf("\nEnter name : ");
                        scanf("%s", searchByName);
                        while(getchar() != '\n');

                        print_line();

                        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|\n",
                            ID_WIDTH, "ID",
                            NAME_WIDTH, "First Name",
                            LASTNAME_WIDTH, "Last Name",
                            NUMBER_WIDTH, "Number",
                            EMAIL_WIDTH, "Email",
                            AGE_WIDTH, "Age",
                            STATUS_WIDTH, "Status",
                            DATE_WIDTH, "Date");

                        print_line();

                        for(i = 0; i < total; i++) {
                            if(strcmp(reserve[i].firstName, searchByName) == 0) {
                                printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*d|%-*s|%-*d|\n",
                                ID_WIDTH, reserve[i].id,
                                NAME_WIDTH, reserve[i].firstName,
                                LASTNAME_WIDTH, reserve[i].lastName,
                                NUMBER_WIDTH, reserve[i].numberPhone,
                                EMAIL_WIDTH, reserve[i].emails,
                                AGE_WIDTH, reserve[i].age,
                                STATUS_WIDTH, reserve[i].status,
                                DATE_WIDTH, reserve[i].days, reserve[i].months, reserve[i].years);
                                existing = 1;
                            }
                        }

                        print_line();
                        if(!existing) {
                            printf("\n --this name not exist\n");
                            goto rtnName;
                        }
                        break;
                }
                sleep(2);

                break;
            case 7:
                printf("\n ------- Display statistics patients who have booking ------- \n");

                printf("1. Display average age patients \n");
                printf("2. Display total of patients reserve by age \n");
                printf("3. Display number of patients reserve by status \n");

                printf("\nChoose option: ");
                scanf("%d", &choose);

                int countValidated = 0;
                int countPostponed = 0;
                int countProcessed = 0;
                int countCancelled = 0;
                switch(choose) {
                    case 1:
                        printf("\n ----- average age patients ----- \n");

                        averagePatients(reserve, total);

                        break;
                    case 2:
                        printf("\n ----- total of patients reserve by age ----- \n");

                        groupAge(reserve, total);

                        break;
                    case 3:
                        printf("\n ----- number of patients reserve by status ----- \n");

                        for(i = 0; i < total; i++) {
                            if(strcmp(reserve[i].status, "validated") == 0) {
                                countValidated++;
                            } else if(strcmp(reserve[i].status, "postponed") == 0) {
                                countPostponed++;
                            } else if(strcmp(reserve[i].status, "cancelled") == 0) {
                                countCancelled++;
                            } else if(strcmp(reserve[i].status, "processed") == 0) {
                                countProcessed++;
                            }
                        }

                        printf("Total reservation validated: %d\n", countValidated);
                        printf("Total reservation postponed: %d\n", countPostponed);
                        printf("Total reservation cancelled: %d\n", countCancelled);
                        printf("Total reservation processed: %d", countProcessed);
                        break;
                }
                break;
            case 8:
                printf("\n ------ Sort The reservations ------ \n");

                printf("1. Sort reservations by name \n");
                printf("2. Sort reservations by statut \n");

                printf("\nChoose option: ");
                scanf("%d", &choose);

                switch(choose) {
                    case 1:
                        printf("\n ----- Sort reservations by name ----- \n");


                        qsort(reserve, total, sizeof(struct reservations), comparatorByName);

                        printf("\n\t Reservations sort successfully! ");

                    break;
                    case 2:
                        printf("\n ----- Sort reservations by status ----- \n");

                        sortByStatus(reserve, total, "validated");

                        printf("\n Reservations sort successfully!\n");
                        sleep(2);
                    break;
                }
            break;
            case 9:
                exit(0);
                break;
        }
        // end switch to display any case choose user

    }

    return 0;
}
