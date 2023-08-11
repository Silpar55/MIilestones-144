/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Alejandro Silva Juarez
Student ID#: 142655224
Email      : asilva-juarez@myseneca.ca
Section    : NFF

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"
#include <string.h>


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;
    int records = 0;

    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
            records = 1;
        }
    }

    if (!records)
    {
        printf("*** No records found ***");
    }


    printf("\n");

}


// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;
    do
    {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"

            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");

        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;

        }
    } while (selection);
}


// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int i;
    int patients = 0, spaceAvailable = 0;


    for (i = 0; i < max; i++)
    {
        // To know how many patients are there
        if (patient[i].patientNumber != 0)
        {
            patients++;
        }
        else
        {
            if (spaceAvailable == 0)
            {
                spaceAvailable = i;
            }
        }
    }

    // Input patient if there is space
    if (max > patients)
    {
        patient[spaceAvailable].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[spaceAvailable]);
        printf("*** New patient record added ***\n\n");
    }
    else
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}


// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int patientNum, index;

    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNum, patient, max);
    putchar('\n');

    // Need to find if exist this Patient Number given

    if (index != -1)
    {
        menuPatientEdit(&patient[index]);
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int patientNum, index;
    char decision;

    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNum, patient, max);
    putchar('\n');
    // Need to find if exist this Patient Number given

    if (index != -1)
    {
        displayPatientData(&patient[index], FMT_FORM);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        decision = inputCharOption("yn");

        if (decision == 'y' || decision == 'Y')
        {
            // Because we cannot delete a struct what we can do is not display this patient and overwrite when the user wants to create a new patient
            patient[index].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }

    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }

}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData *data)
{        
    int i, patientAp;

    // Display header
    displayScheduleTableHeader(NULL, 1);

    // Get every single appointment and show it respective patient
    for ( i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientNumber != 0)
        {
            patientAp = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);

            displayScheduleData(&data->patients[patientAp], &data->appointments[i], 1);
        }
    }
    
    printf("\n");
   
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData *data)
{    
    int i, patientAp;
    struct Date date = { 0 };

    date = inputDate();

    displayScheduleTableHeader(&date, 0);

    // Get every single appointment and show it respective patient

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].date.year == date.year && data->appointments[i].date.month == date.month && data->appointments[i].date.day == date.day)
        {
            patientAp = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);

            displayScheduleData(&data->patients[patientAp], &data->appointments[i], 0);
        }
    }

    printf("\n");
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment *appointments, int maxAppointments,
    struct Patient *patients, int maxPatient)
{
    int patientIndex, isAvailable, i, added = 0;
    struct Appointment appointment = { 0 };
   

    printf("Enter the patient number: ");
    appointment.patientNumber = inputIntPositive();
    patientIndex = findPatientIndexByPatientNum(appointment.patientNumber, patients, maxPatient);
    putchar('\n');

    if (patientIndex != -1)
    {
    
        // Check if there is the timeslot is available
        do
        {
            appointment.date = inputDate();

            appointment.time = inputTime();

            
            // isAvailable = -1 Means that timeslot doesn't exist, therefore it can be added
            isAvailable = findAppointmentIndexByDate(appointments, &appointment, maxAppointments, 0);


            if (isAvailable != -1)
            {
                printf("ERROR: Appointment timeslot is not available!\n\n");
            }
            else
            {
                for ( i = 0; i < maxAppointments && added == 0; i++)
                {
                    if (appointments[i].patientNumber == 0)
                    {
                        appointments[i] = appointment;
                        added = 1;
                    }
                    
                }

                sortAppointments(appointments, maxAppointments);
                
                printf("*** Appointment scheduled! ***\n\n");
                
            }

        } while (added == 0 ); // Repeat until find an available timeslot
     

    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
 
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointments, int maxAppointments,
    struct Patient* patients, int maxPatient)
{
    int patientIndex, isTimeslot, decision;
    struct Appointment appointment = { 0 };


    printf("Enter the patient number: ");
    appointment.patientNumber = inputIntPositive();
    patientIndex = findPatientIndexByPatientNum(appointment.patientNumber, patients, maxPatient);
    putchar('\n');

    if (patientIndex != -1)
    {

        // Check if the appointment exist
        do
        {
            appointment.date = inputDate();
            putchar('\n');


            //Find the appointmentIndex by date

            isTimeslot = findAppointmentIndexByDate(appointments, &appointment, maxAppointments, 1);
            
            // If timeslot is -1 means there is not timeslot, therefore cannot be removed

            printf("%d", isTimeslot);
            if (isTimeslot == -1)
            {
                
                printf("ERROR: Appointment timeslot is not available!\n\n");
            }
            else
            {


                displayPatientData(&patients[patientIndex], FMT_FORM);
                putchar('\n');
                printf("Are you sure you want to remove this appointment record? (y,n): ");
                decision = inputCharOption("yn");

                if (decision == 'y' || decision == 'Y')
                {
                    // Because we cannot delete a struct what we can do is not display this appointment
                    appointments[isTimeslot].patientNumber = 0;
                    printf("Appointment record has been removed!\n\n");

                }
                else
                {
                    printf("Operation aborted.\n\n");
                }
                

            }

        } while (isTimeslot == -1); // reapeat until find a timeslot is found


    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }

}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNumber, index;


    printf("Search by patient number: ");
    patientNumber = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNumber, patient, max);
    putchar('\n');


    if (index != -1)
    {
        displayPatientData(&patient[index], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }

    printf("\n");

}


// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i;
    int records = 0;
    char phoneNumber[PHONE_LEN + 1];

    printf("Search by phone number: ");
    inputCString(phoneNumber, PHONE_LEN, PHONE_LEN);
    printf("\n");

    displayPatientTableHeader();
    // For every patient we compare the phone number given
    for (i = 0; i < max; i++)
    {
        if (strcmp(phoneNumber, patient[i].phone.number) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);

            records = 1;
        }
    }

    if (!records)
    {
        printf("\n*** No records found ***\n");


    }

    printf("\n");
}


// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int maxNum = patient[0].patientNumber;


    for (i = 0; i < max; i++)
    {
        // IF there is a number largest than the current largest number, the maxNum will be the new number
        if (patient[i].patientNumber > maxNum)
        {
            maxNum = patient[i].patientNumber;
        }
    }

    // The next patient should be: Higher largest number + 1
    return maxNum + 1;
}


// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            return i;
        }
    }

    //In case there is no match
    return -1;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{

    printf("Patient Data Input\n"
        "------------------\n");

    printf("Number: %05d\n", patient->patientNumber);

    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);

    putchar('\n');
    inputPhoneData(&patient->phone);

}


// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone)
{

    int selection;

    printf("Phone Information\n"
        "-----------------\n");

    printf("How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");
    selection = inputIntRange(1, 4);

    switch (selection)
    {
    case 1:
        putchar('\n');
        strncpy(phone->description, "CELL", PHONE_DESC_LEN);
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        break;
    case 2:
        putchar('\n');
        strncpy(phone->description, "HOME", PHONE_DESC_LEN);
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        break;
    case 3:
        putchar('\n');
        strncpy(phone->description, "WORK", PHONE_DESC_LEN);
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        break;
    case 4:
        strncpy(phone->description, "TBD", PHONE_DESC_LEN);
        strncpy(phone->number, "", PHONE_DESC_LEN);
        break;
    }

    putchar('\n');
}



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0;
    FILE* file;

    file = fopen(datafile, "r");

    if (file != NULL)
    {
        while (fscanf(file, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number) != EOF)
        {
            if (i < max)
            {
                i++;
            }
        }
            
        fclose(file);
    }
    else
    {
        printf("ERROR: file cannot open");
    }


    return i;
}


// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0;
    FILE* file;

    file = fopen(datafile, "r");

    if (file != NULL)
    {
        while (fscanf(file, "%d,%d,%d,%d,%d,%d", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min) != EOF)
        {
            if (i < max)
            {
                i++;
            }
        }


        fclose(file);

        sortAppointments(appoints, max);
    }
    else
    {
        printf("ERROR: file cannot open");
    }


    return i;
}

//////////////////////////////////////
// MY FUNCTIONS
//////////////////////////////////////

// Sort the appointment by date
void sortAppointments(struct Appointment appoints[], int max)
{
    int i = 0, j = 0, needSwap = 0;
    struct Appointment appointTmp = { 0 };

    // sort by year first
    for ( i = 0; i < max; i++)
    {
        
        for (j = 0; j < max; j++)
        {
            needSwap = 0;
            if (appoints[i].date.year < appoints[j].date.year)
                needSwap = 1;

            if (appoints[i].date.year == appoints[j].date.year && appoints[i].date.month < appoints[j].date.month)
                needSwap = 1;

            if (appoints[i].date.year == appoints[j].date.year && appoints[i].date.month == appoints[j].date.month && appoints[i].date.day < appoints[j].date.day)
                needSwap = 1;

            if (appoints[i].date.year == appoints[j].date.year && appoints[i].date.month == appoints[j].date.month && appoints[i].date.day == appoints[j].date.day && appoints[i].time.hour < appoints[j].time.hour)
                needSwap = 1;
            
            if (appoints[i].date.year == appoints[j].date.year && appoints[i].date.month == appoints[j].date.month && appoints[i].date.day == appoints[j].date.day && appoints[i].time.hour == appoints[j].time.hour && appoints[i].time.min < appoints[j].time.min)
                needSwap = 1;

            if(needSwap)
            {
                appointTmp = appoints[i];
                appoints[i] = appoints[j];
                appoints[j] = appointTmp;
            }

        }

    }



}

// Display the format of date and fill what is required
struct Date inputDate()
{
    struct Date date = { 0 };
    int maxDays;

    printf("Year        : ");
    date.year = inputIntPositive();
    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);
    maxDays = getDaysMonths(date.year, date.month);
    printf("Day (1-%d)  : ", maxDays);
    date.day = inputIntRange(1, maxDays);
    
    return date;
}

// Display the format of time, with validation and fill what is required
struct Time inputTime()
{
    int isCorrect = 0;
    struct Time time = { 0 };


    do
    {

        printf("Hour (0-23)  : ");
        time.hour = inputIntRange(0, 23);
        printf("Minute (0-59): ");
        time.min = inputIntRange(0, 59);
        putchar('\n');





        if ((time.hour >= MIN_INTERVAL && time.hour <= MAX_INTERVAL) && (time.min == 0 || time.min == HALF_HOUR) && !(time.hour == MAX_INTERVAL && time.min == HALF_HOUR))
        {
            isCorrect = 1;
        }
        else
        {
            isCorrect = 0;
            printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", MIN_INTERVAL, MAX_INTERVAL, HALF_HOUR);

        }

    } while (!isCorrect);
    

    return time;
}

// Get days format depending on the month
int getDaysMonths(int year, int month)
{
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
        break;
    case 2:
        if (year % 4 == 0)
        {
            return 29;
        }
        else
        {
            return 28;
        }
    default:
        return 0;
        break;
    }

}


// Find appointment index by date and program requirement
int findAppointmentIndexByDate(const struct Appointment* appointments, const struct Appointment* appointment, int maxAppointments, int isRemoveMode)
{
    int i;

    // check every single apppointment and find the appointment
    for (i = 0; i < maxAppointments; i++)
    {
        if (isRemoveMode == 1)
        {
            // If isRemoveMode equal 1, means that this calling belongs to remove Appointment (because is not required time)
            if (appointments[i].date.year == appointment->date.year && appointments[i].date.month == appointment->date.month && appointments[i].date.day == appointment->date.day && appointments[i].patientNumber == appointment->patientNumber)
            {
                return i;
            }
        }
        else
        {
            // else it belongs to add appointment 
            if (appointments[i].date.year == appointment->date.year && appointments[i].date.month == appointment->date.month && appointments[i].date.day == appointment->date.day && appointments[i].time.hour == appointment->time.hour && appointments[i].time.min == appointment->time.min)
            {
                return i;
            }
        }


    }

    // if doesnt found
    return -1;

}