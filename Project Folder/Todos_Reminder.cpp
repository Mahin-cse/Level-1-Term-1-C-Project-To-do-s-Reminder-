#include "iGraphics.h"
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include <unistd.h>

#define sw 1024
#define sh 600

// variables to store the input values
char username[1000000];
char password[1000000];
char yourname[1000000];
char yourpass[1000000];
char yournewpass[1000000];

int capt_1, capt_2, capt_3, capt_4, capt_5, capt_6, capt_7, capt_8, capt_9;
bool truth_value = false;
bool hurry = false;
int len1 = 0;
int len2 = 0;
int len3 = 0;
int len4 = 0;
int len5 = 0;
// variables to store the cursor position
int cursor_x1 = 512;
int cursor_x2 = 512;
int cursor_y1 = 300;
int cursor_y2 = 250;
int cursor_x3 = 375;
int cursor_x4 = 375;
int cursor_x5 = 375;
int cursor_y3 = 250;
int cursor_y4 = 190;
int cursor_y5 = 130;

// variables to store the focus state
bool focus1 = false;
bool focus2 = false;
bool focus3 = false;
bool focus4 = false;
bool focus5 = false;
// variable to store the current page number

int chng_ind;
int del_ind = -1;
int taskcount = 0;
int x = 255, y = 255, z = 255;
int bgi = 1;
int ringingtaskindex = 0;
bool musicstate = false;
typedef struct
{
    int dd;
    int mm;
    int yy;
    int h;
    int mi;
    int sec;
} systime;
systime pc;
FILE *fp;
FILE *fp2;

typedef struct
{
    char taskname[1000000];
    int year;
    int day;
    int month;
    int hour;
    int minute;
    int taskstate; // 0: Not Done, 1: Done
    int completed; // 0: Incomplete, 1: Completed
} task;

task tasklist[10];
typedef struct
{
    int oldbgi;
    int oldmsi;
    int oldst;
    int oldx, oldy, oldz;
} restoreold;
restoreold restore;

int i = 0, j = 0;
int st = 100;
char tempdate[50];
char temptime[50];
char tempo[10];
char *tmp = tempdate;
char *tmt = temptime;
int counterfordate = 0;
int counterfortime = 0;

char music[10][100] = {"music\\Allweknow.wav", "music\\thousand_years.wav", "music\\unity.wav", "music\\agar_tum_sath_ho.wav", "music\\click.wav", "music\\thousand_years.wav", "music\\unity.wav", "music\\agar_tum_sath_ho.wav"};
int musici = 0;

void saveUserCredentials();
void checkUserCredentials();
void registerForm();
void drawLoginForm();
void frontpage();
void AddRemoveTask();
void ChangeRingtone();
void ChangeBackground();
void Settings();
void Credits();
void inputTask();
void saveToFile();
void getFileSize();
void removeTask();
void tasknamelist();
void remindtimelist();
void biostimefetch();
void ringtone();
void taskshow();
void alarm();
void Alarmoff();
void statusshow();
void savesettings();
void fetchsettings();
void push();
void delete_everything();
void saveandquit();
void biostimeprint();
void changeschedule();

void iDraw()
{
    iClear();
    if (st == 100)
    {
        drawLoginForm();
    }
    if (st == 101)
    {
        registerForm();
    }
    if (st == 0)
    {
        frontpage();
    }
    if (st == 1)
    {
        inputTask();
    }
    if (st == 2)
    {
        removeTask();
    }
    if (st == 3)
    {
        ChangeRingtone();
    }
    if (st == 4)
    {
        ChangeBackground();
    }
    if (st == 5)
    {
        Credits();
    }
    if (st == 6)
    {
        inputTask();
    }
    if (st == 7)
    {
        taskshow();
    }
    if (st == 8)
    {
        inputTask();
    }
    if (st == 9)
    {
        Alarmoff();
    }
    if (st == 10 || st == 11 || st == 12)
    {
        changeschedule();
    }
}

// Function to save user credentials to a file
void saveUserCredentials(char *username, char *password)
{
    FILE *file = fopen("user_credentials.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%s %s\n", username, password);
        fclose(file);
    }
}

// Function to check if user credentials exist in the file
int checkUserCredentials(char *username, char *password)
{
    FILE *file = fopen("user_credentials.txt", "r");
    if (file != NULL)
    {
        char storedUsername[1000000];
        char storedPassword[1000000];

        while (fscanf(file, "%s %s", storedUsername, storedPassword) == 2)
        {
            if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0)
            {
                fclose(file);
                return 1; // Credentials match
            }
        }

        fclose(file);
    }
    return 0; // Credentials do not match
}

void drawLoginForm()
{
    // draw the background image
    iShowBMP(0, 0, "photos\\credits.bmp");
    // draw the container
    iSetColor(250,110,80);
    iFilledRectangle(390,480,350,40);
    iSetColor(200, 25, 50);
    iText(400,490,"Welcome To Mahin's To-Dos Reminder",GLUT_BITMAP_HELVETICA_18);
    iSetColor(255, 255, 255);
    iFilledRectangle(270, 290, 420, 90);
    iSetColor(237, 66, 112);
    iFilledRectangle(270, 200, 420, 90);
    iSetColor(245, 185, 95);
    iFilledRectangle(270, 380, 295, 40);
    iSetColor(180, 115, 235);
    iText(305, 390, "Please Solve The Captcha :", GLUT_BITMAP_HELVETICA_18);
    iSetColor(180, 115, 235);
    iFilledRectangle(270 + 295, 380, 295, 40);
    iSetColor(245, 185, 95);
    iText(590, 390, "Select All Images With A Cat", GLUT_BITMAP_HELVETICA_18);
    if (truth_value == false)
    {
        iSetColor(255, 0, 0);
        iFilledRectangle(690, 170, 170, 40);
        iSetColor(255, 255, 0);
        iText(715, 183, "Am I A Robot?", GLUT_BITMAP_HELVETICA_18);
    }
    if (truth_value == true)
    {
        iSetColor(0, 255, 0);
        iFilledRectangle(690, 170, 170, 40);
        iSetColor(255, 0, 255);
        iText(710, 183, "I'm Not A Robot", GLUT_BITMAP_HELVETICA_18);
    }

    // draw the labels
    iSetColor(237, 66, 112);
    iText(315, 310, "Username:", GLUT_BITMAP_HELVETICA_18);
    iRectangle(412, 300, 200, 30);
    iSetColor(255, 255, 255);
    iText(315, 260, "Password:", GLUT_BITMAP_HELVETICA_18);
    iRectangle(412, 250, 200, 30);

    iShowBMP(690, 210, "photos\\captcha.bmp");

    if (capt_1 == 1)
    {
        iSetColor(255, 127, 0); // orange
        iFilledRectangle(690, 210, 56.67, 56.67);
    }
    if (capt_2 == 2)
    {
        iSetColor(0, 0, 255); // blue
        iFilledRectangle(690 + 56.67, 210, 56.67, 56.67);
    }
    if (capt_3 == 3)
    {
        iSetColor(196, 164, 132); // ash+chocolate
        iFilledRectangle(690 + 56.67 + 56.67, 210, 56.67, 56.67);
    }
    if (capt_4 == 4)
    {
        iSetColor(0, 255, 0); // green
        iFilledRectangle(690, 210 + 56.67, 56.67, 56.67);
    }
    if (capt_5 == 5)
    {
        iSetColor(135, 206, 250); // indigo
        iFilledRectangle(690 + 56.67, 210 + 56.67, 56.67, 56.67);
    }
    if (capt_6 == 6)
    {
        iSetColor(148, 0, 211); // violet
        iFilledRectangle(690 + 56.67 + 56.67, 210 + 56.67, 56.67, 56.67);
    }
    if (capt_7 == 7)
    {
        iSetColor(247, 75, 190); // pink
        iFilledRectangle(690, 210 + 56.67 * 2, 56.67, 56.67);
    }
    if (capt_8 == 8)
    {
        iSetColor(255, 255, 0); // yellow
        iFilledRectangle(690 + 56.67, 210 + 56.67 * 2, 56.67, 56.67);
    }
    if (capt_9 == 9)
    {
        iSetColor(255, 0, 0); // red
        iFilledRectangle(690 + 56.67 + 56.67, 210 + 56.67 * 2, 56.67, 56.67);
    }

    // draw the input values
    iSetColor(237, 66, 112);
    iText(422, 310, username, GLUT_BITMAP_HELVETICA_18);
    iSetColor(255, 255, 255);
    iText(422, 260, password, GLUT_BITMAP_HELVETICA_18);

    // draw the cursor
    iSetColor(0, 0, 255);
    if (focus1)
    {
        iLine(cursor_x1, cursor_y1, cursor_x1, cursor_y1 + 20);
    }
    if (focus2)
    {
        iLine(cursor_x2, cursor_y2, cursor_x2, cursor_y2 + 20);
    }

    // draw the button
    iSetColor(152, 255, 152);
    iFilledRectangle(270, 170, 210, 40);
    iSetColor(2, 48, 32);
    iText(353, 185, "Login", GLUT_BITMAP_HELVETICA_18);
    iSetColor(135, 200, 255);
    iFilledRectangle(270 + 210, 170, 210, 40);
    iSetColor(2, 48, 32);
    iText(355 + 165, 185, "Create Account", GLUT_BITMAP_HELVETICA_18);
}

void registerForm()
{
    iShowBMP(0, 0, "photos\\login.bmp");
    iSetColor(74, 187, 235);
    iFilledRectangle(140, 40, 730, 310);
    int b = 0, rd = 70, gr = 255, bl = 220;

    // draw the form
    for (int i = 0; i < 3; i++)
    {
        iSetColor(rd, gr, bl);
        iFilledRectangle(180, 110 + b, 830 - 180, 60);
        iSetColor(100, 80, 250);
        iRectangle(180, 110 + b, 830 - 180, 60);
        rd += 50;
        gr += 50;
        bl += 50;
        b += 60;
    }

    iSetColor(0, 0, 0);
    iText(258, 250, "Your Name: ", GLUT_BITMAP_HELVETICA_18);
    iText(222, 190, "Your Password: ", GLUT_BITMAP_HELVETICA_18);
    iText(199, 130, "Confirm Password: ", GLUT_BITMAP_HELVETICA_18);

    iSetColor(160, 255, 200);
    iFilledRectangle(20, 540, 220 - 20, 590 - 540);
    iSetColor(0, 0, 0);
    iText(37, 557, "Back To Login Page", GLUT_BITMAP_HELVETICA_18);

    int k = 0, rd1 = 50, gr1 = 170, bl1 = 250;

    for (int i = 0; i < 3; i++)
    {
        iSetColor(rd1, gr1, bl1);
        iFilledRectangle(370, 123 + k, 430, 35);
        iSetColor(100, 80, 250);
        iRectangle(370, 123 + k, 430, 35);
        rd1 += 0;
        gr1 += 50;
        bl1 += 50;
        k += 60;
    }

    iSetColor(160, 255, 200);
    iFilledRectangle(470, 70, 100, 40);
    iSetColor(100, 80, 250);
    iRectangle(470, 70, 100, 40);

    iSetColor(0, 0, 0);
    // input values
    iText(487, 85, "Sign Up", GLUT_BITMAP_HELVETICA_18);
    iText(375, 130 + 120, yourname, GLUT_BITMAP_HELVETICA_18);
    iText(375, 130 + 60, yourpass, GLUT_BITMAP_HELVETICA_18);
    iText(375, 130, yournewpass, GLUT_BITMAP_HELVETICA_18);

    // draw cursor
    iSetColor(0, 0, 255);
    if (focus3)
    {
        iLine(cursor_x3, cursor_y3, cursor_x3, cursor_y3 + 20);
    }
    if (focus4)
    {
        iLine(cursor_x4, cursor_y4, cursor_x4, cursor_y4 + 20);
    }
    if (focus5)
    {
        iLine(cursor_x5, cursor_y5, cursor_x5, cursor_y5 + 20);
    }
}

void changeschedule()
{
    if (bgi)
    {
        iShowBMP(0, 0, "photos\\ready.bmp");
        iSetColor(90, 235, 100);
        // iSetColor(103, 68, 207);
        iFilledRectangle(20, 550, 70, 40);
        // iSetColor();
        int j = 0, k = 100, l = 240, m = 187;
        for (int i = 0; i < 3; i++)
        {
            iSetColor(k, l, m);
            iFilledRectangle(190, 240 + j, 410, 40);
            iSetColor(k + 50, l + 50, m + 50);
            iFilledRectangle(190, 280 + j, 410, 40);
            j += 100;
            k += 50;
            l += 50;
            m += 50;
        }
        iSetColor(0, 0, 0);
    }
    else
        iSetColor(x, y, z);
    iText(30, 560, "Back", GLUT_BITMAP_HELVETICA_18);
    iText(200, 500, "Choose Task (1-10): ", GLUT_BITMAP_HELVETICA_18);
    iText(200, 450, tempo, GLUT_BITMAP_HELVETICA_18);
    iText(200, 400, "Set Date: (DD / MM / YYYY)", GLUT_BITMAP_HELVETICA_18);
    iText(200, 350, tmp, GLUT_BITMAP_HELVETICA_18);
    iText(200, 300, "Set Time: (24 Hour Clock - HH : MM)", GLUT_BITMAP_HELVETICA_18);
    iText(200, 250, temptime, GLUT_BITMAP_HELVETICA_18);
}

void delete_everything()
{
    remove("tasks.bin");
    remove("oldset.bin");
    exit(0);
}

void statusshow()
{
    int k = 0;
    for (int f = 0; f < taskcount; f++)
    {
        iFilledCircle(120, 463 - 50 * (f + 1), 2);
        if (tasklist[f].taskstate == 0)
        {
            if (bgi)
            {
                iSetColor(255, 0, 0);
                iFilledRectangle(690, 400 - k, 100, 30);
                iSetColor(217, 249, 113);
            }
            else
                iSetColor(x, y, z);
            iText(700, 460 - 50 * (f + 1), "Not Done", GLUT_BITMAP_HELVETICA_18);
            k += 50;
        }
        else
        {
            if (bgi)
            {
                iSetColor(0, 255, 0);
                iFilledRectangle(690, 400 - k, 100, 30);
                iSetColor(230, 60, 160);
            }
            else
                iSetColor(x, y, z);
            iText(700, 460 - 50 * (f + 1), "Done", GLUT_BITMAP_HELVETICA_18);
            k += 50;
        }
    }
}

void alarm()
{
    biostimefetch();
    for (int i = 0; i < taskcount; i++)
    {
        if (pc.h == tasklist[i].hour && pc.mi == tasklist[i].minute && pc.dd == tasklist[i].day && pc.mm == tasklist[i].month && pc.yy == tasklist[i].year && pc.sec == 0 && tasklist[i].taskstate == 0)
        {
            musicstate = true;
            tasklist[i].taskstate = 1;
            ringingtaskindex = i;
            st = 9;
            hurry = true;
            ringtone();
            break;
        }
    }
}
void Alarmoff()
{
    if (bgi)
    {
        iShowBMP(0, 0, "photos\\temic.bmp");
        iSetColor(65, 235, 125);
        iFilledRectangle(20, 550, 70, 40);
        iSetColor(245, 160, 80);
        iFilledRectangle(140, 200, 350, 50);
        iSetColor(128, 243, 255); // sky blue
        iFilledRectangle(350, 200, 140, 50);
        iSetColor(200, 235, 90);
        iFilledRectangle(340 + 140, 200, 650 - 350, 50);
        iSetColor(225, 80, 180);
        iFilledRectangle(310, 285, 210, 50);
        iSetColor(225 + 30, 80 + 30, 180 + 30);
        iFilledRectangle(310, 285 + 50, 210, 50);
        iSetColor(225 + 30 * 2, 80 + 30 * 2, 180 + 30 * 2);
        iFilledRectangle(310, 285 + 100, 210, 50);
        iSetColor(225 + 30 * 3, 80 + 30 * 3, 180 + 30 * 3);
        iFilledRectangle(310, 285 + 150, 210, 50);
        iSetColor(0, 0, 0);
    }

    else
        iSetColor(x, y, z);

    iText(370, 450, "Snooze For:", GLUT_BITMAP_HELVETICA_18);
    iText(370, 400, "+5 minutes", GLUT_BITMAP_HELVETICA_18);
    iText(370, 350, "+10 minutes", GLUT_BITMAP_HELVETICA_18);
    iText(380, 300, "Turn Off", GLUT_BITMAP_HELVETICA_18);
    iText(145, 220, "Hurry up! Time to shine!      Your task: ", GLUT_BITMAP_HELVETICA_18);
    iText(520, 220, tasklist[ringingtaskindex].taskname, GLUT_BITMAP_HELVETICA_18);
    iText(30, 560, "Back", GLUT_BITMAP_HELVETICA_18);
}

void taskshow()
{
    if (bgi)
    {
        iShowBMP(0, 0, "photos\\light.bmp");
        iSetColor(50, 220, 150);
        iFilledRectangle(90, 435, 870, 45);
        iSetColor(255, 67, 100);
        iFilledRectangle(20, 550, 70, 40); // back
        iSetColor(245, 245, 180);
        iFilledRectangle(400, 480, 250, 45);
        iSetColor(150, 10, 100);
    }
    else
        iSetColor(x, y, z);
    iText(30, 560, "Back", GLUT_BITMAP_HELVETICA_18);
    iText(440, 500, "Your Added Tasks: ", GLUT_BITMAP_HELVETICA_18);
    iText(195, 450, "Title", GLUT_BITMAP_HELVETICA_18);
    iLine(193, 445, 245, 445);
    iText(400, 450, "Remind Me At", GLUT_BITMAP_HELVETICA_18);
    iLine(400, 440, 500, 440);
    iText(700, 450, "Status", GLUT_BITMAP_HELVETICA_18);
    iLine(700, 440, 760, 440);
    iLine(380, 480, 380, 0);
    iLine(680, 480, 680, 0);

    tasknamelist();
    remindtimelist();
    statusshow();
}

void frontpage()
{
    // drawLoginForm();
    if (bgi)
    {
        iShowBMP(0, 0, "photos\\front.bmp");
        iSetColor(255, 87, 51);
        iFilledRectangle(20, 540, 200, 50); // mx>=30 && mx<=80 && my>=560 && my<=581 && st==0
        iSetColor(240, 110, 240);
        iFilledRectangle(380, 450, 255, 40);
        // iSetColor(144,238,144);

        iSetColor(100, 90, 228); // violet
        iFilledRectangle(380, 40, 255, 50);
        iSetColor(41, 91, 230); // blue
        iFilledRectangle(380, 40 + 50, 255, 50);
        iSetColor(80, 224, 253); // indigo
        iFilledRectangle(380, 40 + 50 * 2, 255, 50);
        iSetColor(144, 238, 144); // green
        iFilledRectangle(380, 40 + 50 * 3, 255, 50);
        iSetColor(255, 255, 0); // yellow
        iFilledRectangle(380, 40 + 50 * 4, 255, 50);
        iSetColor(250, 165, 80); // orange
        iFilledRectangle(380, 40 + 50 * 5, 255, 50);
        iSetColor(230, 20, 90); // red
        iFilledRectangle(380, 40 + 50 * 6, 255, 50);

        iSetColor(133, 1, 1); // red
        iFilledRectangle(740, 5, 270, 50);
        iSetColor(255, 223, 0); // golden yellow
        iFilledRectangle(20, 5, 270, 50);
        iSetColor(0, 0, 0);
        iText(460, 465, "To-Do Alert", GLUT_BITMAP_HELVETICA_18);
    }
    else
    {
        iSetColor(x, y, z);
        iText(440, 465, "To-Do Alert", GLUT_BITMAP_HELVETICA_18);
    }
    if (hurry == true)
    {
        if (bgi)
            iSetColor(200, 210, 50);
        else
            iSetColor(0, 0, 0);
        iFilledCircle(850, 305, 93);
        iSetColor(0, 0, 0);
        iText(812, 300, "My Alarm", GLUT_BITMAP_HELVETICA_18);
        if (!bgi)
        {
            iSetColor(x, y, z);
            iText(812, 300, "My Alarm", GLUT_BITMAP_HELVETICA_18);
        }
    }
    iText(37, 557, "Back To Login Page", GLUT_BITMAP_HELVETICA_18);
    iText(390, 360, "I. Create New Task", GLUT_BITMAP_HELVETICA_18);
    iText(390, 310, "II. Delete Task", GLUT_BITMAP_HELVETICA_18);
    iText(390, 260, "III. View Task List", GLUT_BITMAP_HELVETICA_18);
    iText(390, 210, "IV. Customize Ringtone", GLUT_BITMAP_HELVETICA_18);
    iText(390, 160, "V. Personalize Background", GLUT_BITMAP_HELVETICA_18);
    iText(390, 110, "VI. Acknowledgements", GLUT_BITMAP_HELVETICA_18);
    iText(390, 60, "VII. Adjust Task Schedule", GLUT_BITMAP_HELVETICA_18);
    if (bgi)
        iSetColor(255, 223, 0);
    else
        iSetColor(x, y, z); // golden yellow
    iText(770, 20, "Delete Everything & Exit!!", GLUT_BITMAP_HELVETICA_18);
    if (bgi)
        iSetColor(133, 1, 1); // red
    else
        iSetColor(x, y, z);
    iText(40, 20, "Press End to Save & Exit", GLUT_BITMAP_HELVETICA_18);
    biostimeprint();
}

void Credits()
{
    if (bgi)
    {
        iShowBMP(0, 0, "photos\\heart.bmp");
        iSetColor(70, 253, 241);
        iFilledRectangle(20, 550, 70, 40); // back
        iSetColor(188, 200, 235);
        iFilledRectangle(290, 250 - 50, 430, 130 + 50);
        iSetColor(255, 92, 47);
    }
    else
        iSetColor(x, y, z);
    iText(30, 560, "Back", GLUT_BITMAP_HELVETICA_18);
    iText(300, 360, "1. Myself (Mahin, BUET CSE'22, Ex-Cadet CCC)", GLUT_BITMAP_HELVETICA_18);
    iText(300, 310, "2. My Laptop", GLUT_BITMAP_HELVETICA_18);
    iText(300, 260, "3. My Project Supervisor (Mushtari Sadia Ma'am)", GLUT_BITMAP_HELVETICA_18);
    iText(300, 210, "4. Tanvir Uday Vaia", GLUT_BITMAP_HELVETICA_18);
}

void ChangeRingtone()
{
    if (bgi)
    {
        int m = 0, n = 0, o = 0, k = 0;
        iShowBMP(0, 0, "photos\\Ring_tone.bmp");
        iSetColor(82, 247, 143);
        iFilledRectangle(20, 550, 70, 40); // back
        iSetColor(255, 255, 192);
        iFilledRectangle(380, 240, 230, 150);
        for (int i = 0; i < 3; i++)
        {
            iSetColor(237 + m, 165 + n, 110 + o);
            iFilledRectangle(610, 240 + k, 100, 50);
            iSetColor(206 + m, 224 + n, 67 + o);
            iFilledRectangle(710, 240 + k, 100, 50);
            m += 30;
            n += 30;
            o += 30;
            k += 50;
        }
        iSetColor(80, 80, 226);
    }

    else
        iSetColor(x, y, z);
    iSetColor(0, 0, 255);
    iText(625, 210 + 50, "Turn On", GLUT_BITMAP_HELVETICA_18);
    iText(625, 210 + 50 * 2, "Turn On", GLUT_BITMAP_HELVETICA_18);
    iText(625, 210 + 50 * 3, "Turn On", GLUT_BITMAP_HELVETICA_18);
    if (musici == 3)
    {
        iSetColor(206, 224, 67);
        iFilledRectangle(610, 240, 100, 50);
        iSetColor(233, 30, 42);
        iRectangle(610, 240, 100, 50);
        iSetColor(237, 165, 110);
        iFilledRectangle(710, 240, 100, 50);
        iSetColor(30, 246, 232);
        iRectangle(710, 240, 100, 50);
        iSetColor(0, 0, 255);
        iText(725, 210 + 50, "Turn Off", GLUT_BITMAP_HELVETICA_18);
    }
    if (musici == 2)
    {
        iSetColor(206 + 30, 224 + 30, 67 + 30);
        iFilledRectangle(610, 290, 100, 50);
        iSetColor(233, 30, 42);
        iRectangle(610, 290, 100, 50);
        iSetColor(237 + 30, 165 + 30, 110 + 30);
        iFilledRectangle(710, 290, 100, 50);
        iSetColor(30, 246, 232);
        iRectangle(710, 290, 100, 50);
        iSetColor(0, 0, 255);
        iText(725, 210 + 50 * 2, "Turn Off", GLUT_BITMAP_HELVETICA_18);
    }
    if (musici == 1)
    {
        iSetColor(206 + 60, 224 + 60, 67 + 60);
        iFilledRectangle(610, 340, 100, 50);
        iSetColor(233, 30, 42);
        iRectangle(610, 340, 100, 50);
        iSetColor(237 + 60, 165 + 60, 110 + 60);
        iFilledRectangle(710, 340, 100, 50);
        iSetColor(30, 246, 232);
        iRectangle(710, 340, 100, 50);
        iSetColor(0, 0, 255);
        iText(725, 210 + 50 * 3, "Turn Off", GLUT_BITMAP_HELVETICA_18);
    }

    iText(30, 560, "Back", GLUT_BITMAP_HELVETICA_18);
    iText(400, 360, "1. Thousand Years", GLUT_BITMAP_HELVETICA_18);
    iText(400, 310, "2. Unity", GLUT_BITMAP_HELVETICA_18);
    iText(400, 260, "3. Agar Tum Sath Ho", GLUT_BITMAP_HELVETICA_18);
}
void ChangeBackground()
{
    if (bgi)
    {
        iShowBMP(0, 0, "photos\\back.bmp");
        iSetColor(237, 66, 112);
        iFilledRectangle(380, 320, 130, 70);
        iSetColor(255, 255, 255);
        iFilledRectangle(380, 250, 130, 70);
        iSetColor(255, 87, 51);
        iFilledRectangle(20, 550, 70, 40);
        iSetColor(237, 66, 112);
        iText(400, 270, "2. Dark", GLUT_BITMAP_HELVETICA_18);
        iSetColor(255, 255, 255);
    }
    else
    {
        iSetColor(x, y, z);
        iText(400, 270, "2. Dark", GLUT_BITMAP_HELVETICA_18);
    }
    iText(30, 560, "Back", GLUT_BITMAP_HELVETICA_18);
    iText(400, 350, "1. Pixel UI ", GLUT_BITMAP_HELVETICA_18);
}

void saveToFile()
{
    fp = fopen("tasks.bin", "w");
    for (int p = 0; p < taskcount; p++)
    {
        fwrite(&tasklist[p], sizeof(task), 1, fp);
    }
    fclose(fp);
}
void getFileSize()
{
    fseek(fp, 0L, SEEK_END);
    unsigned int long size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    i = size / sizeof(task);
    taskcount = i;
}

void fetchtask()
{
    fp = fopen("tasks.bin", "r");
    if (fp)
    {
        getFileSize();
        for (int p = 0; p < i; p++)
        {
            fread(&tasklist[p], sizeof(task), 1, fp);
        }
        fclose(fp);
    }
}
void savesettings()
{
    fp2 = fopen("oldset.bin", "w");
    fwrite(&restore, sizeof(restoreold), 1, fp2);
    fclose(fp2);
}
void fetchsettings()
{
    fp2 = fopen("oldset.bin", "r");
    if (fp2)
    {
        fread(&restore, sizeof(restoreold), 1, fp2);
        bgi = restore.oldbgi;
        musici = restore.oldmsi;
        st = restore.oldst;
        x = restore.oldx;
        y = restore.oldy;
        z = restore.oldz;
        fclose(fp2);
    }
}

void inputTask()
{
    if (bgi)
    {
        iShowBMP(0, 0, "photos\\dream.bmp");
        iSetColor(103, 68, 207);
        iFilledRectangle(20, 550, 70, 40);
        // iSetColor();
        int j = 0, k = 245, l = 185, m = 90;
        for (int i = 0; i < 3; i++)
        {
            iSetColor(k, l, m);
            iFilledRectangle(190, 240 + j, 370, 40);
            iSetColor(k + 50, l + 50, m + 50);
            iFilledRectangle(190, 280 + j, 370, 40);
            j += 100;
            k += 30;
            l -= 10;
            m += 30;
        }

        iSetColor(255, 50, 40);
    }

    else
        iSetColor(x, y, z);
    if (i != -1)
    {
        iText(200, 450, tasklist[i].taskname, GLUT_BITMAP_HELVETICA_18);
    }
    iText(30, 560, "Back", GLUT_BITMAP_HELVETICA_18);
    iText(200, 500, "Name Your Task: ", GLUT_BITMAP_HELVETICA_18);
    iText(200, 400, "Date: (DD / MM / YYYY)", GLUT_BITMAP_HELVETICA_18);
    iText(200, 350, tempdate, GLUT_BITMAP_HELVETICA_18);
    iText(200, 300, "Time: (24 Hour Clock - HH : MM)", GLUT_BITMAP_HELVETICA_18);
    iText(200, 250, temptime, GLUT_BITMAP_HELVETICA_18);
}
void removeTask()
{
    if (bgi)
    {
        iShowBMP(0, 0, "photos\\remove.bmp");
        iSetColor(50, 220, 150);
        iFilledRectangle(90, 435, 870, 45);
        iSetColor(245, 245, 180);
        iFilledRectangle(370, 480, 320, 45);
        iSetColor(255, 135, 208);
        iFilledRectangle(20, 550, 70, 40); // back
        iSetColor(205, 10, 150);
    }
    else
        iSetColor(x, y, z);
    iText(30, 560, "Back", GLUT_BITMAP_HELVETICA_18);
    iText(380, 500, "Click The Task You Want To Delete: ", GLUT_BITMAP_HELVETICA_18);
    iText(195, 450, "Title", GLUT_BITMAP_HELVETICA_18);
    iLine(193, 440, 243, 440);
    iText(400, 450, "Remind at", GLUT_BITMAP_HELVETICA_18);
    iLine(400, 440, 500, 440);
    iText(700, 450, "Status", GLUT_BITMAP_HELVETICA_18);
    iLine(700, 440, 760, 440);
    iLine(380, 480, 380, 0);
    iLine(680, 480, 680, 0);

    tasknamelist();
    remindtimelist();
    statusshow();
}
void tasknamelist()
{
    int k = 0;
    for (int f = 0; f < taskcount; f++)
    {
        if (bgi)
        {
            iSetColor(128, 243, 255);
            iFilledRectangle(90, 400 + k, 280, 30);
            iSetColor(150, 10, 100);
            k -= 50;
        }
        else
            iSetColor(x, y, z);
        char bruh[3];
        itoa(f + 1, bruh, 10);
        iText(100, 460 - 50 * (f + 1), bruh, GLUT_BITMAP_HELVETICA_18);
        iFilledCircle(120, 463 - 50 * (f + 1), 2);
        iText(130, 460 - 50 * (f + 1), tasklist[f].taskname, GLUT_BITMAP_HELVETICA_18);
    }
}
void remindtimelist()
{
    int k = 0;
    for (int f = 0; f < taskcount; f++)
    {
        if (bgi)
        {
            iSetColor(240, 175, 245);
            iFilledRectangle(390, 400 + k, 280, 30);
            iSetColor(150, 10, 100);
            k -= 50;
        }
        else
            iSetColor(x, y, z);
        char lol[11][5][5];
        itoa(tasklist[f].day, lol[f][0], 10);
        itoa(tasklist[f].month, lol[f][1], 10);
        itoa(tasklist[f].year, lol[f][2], 10);
        itoa(tasklist[f].hour, lol[f][3], 10);
        itoa(tasklist[f].minute, lol[f][4], 10);
        for (int s = 3; s < 5; s++)
        {
            if (lol[f][s][1] == '\0')
            {
                char tmp2 = lol[f][s][0];
                lol[f][s][0] = '0';
                lol[f][s][1] = tmp2;
                lol[f][s][2] = '\0';
            }
        }
        for (int s = 0; s < 2; s++)
        {
            if (lol[f][s][1] == '\0')
            {
                char tmp2 = lol[f][s][0];
                lol[f][s][0] = '0';
                lol[f][s][1] = tmp2;
                lol[f][s][2] = '\0';
            }
        }

        iText(405, 460 - (f + 1) * 50, lol[f][0], GLUT_BITMAP_HELVETICA_18);
        iText(435, 460 - (f + 1) * 50, "/", GLUT_BITMAP_HELVETICA_18);
        iText(445, 460 - (f + 1) * 50, lol[f][1], GLUT_BITMAP_HELVETICA_18);
        iText(470, 460 - (f + 1) * 50, "/", GLUT_BITMAP_HELVETICA_18);
        iText(480, 460 - (f + 1) * 50, lol[f][2], GLUT_BITMAP_HELVETICA_18);
        iText(530, 460 - (f + 1) * 50, ",", GLUT_BITMAP_HELVETICA_18);
        iText(540, 460 - (f + 1) * 50, lol[f][3], GLUT_BITMAP_HELVETICA_18);
        iText(565, 460 - (f + 1) * 50, ":", GLUT_BITMAP_HELVETICA_18);
        iText(575, 460 - (f + 1) * 50, lol[f][4], GLUT_BITMAP_HELVETICA_18);
    }
}
void push()
{
    for (int s = 0; s < (taskcount); s++)
    {
        if (del_ind != -1)
        {
            tasklist[del_ind + s] = tasklist[del_ind + s + 1];
            tasklist[del_ind + s + 1].taskname[0] = '\0';
        }
    }
}
void saveandquit()
{
    saveToFile();
    restore.oldbgi = bgi;
    restore.oldmsi = musici;
    restore.oldst = st;
    restore.oldx = x;
    restore.oldy = y;
    restore.oldz = z;
    savesettings();
    exit(0);
}
void biostimeprint()
{
    char c[10];
    if (bgi)
    {
        iSetColor(208, 65, 126);
        iFilledRectangle(830, 530, 180, 65);
        iSetColor(128, 240, 100);
    }
    else
        iSetColor(x, y, z);
    itoa(pc.dd, c, 10);
    iText(850, 570, c, GLUT_BITMAP_HELVETICA_18);
    iText(880, 570, "/", GLUT_BITMAP_HELVETICA_18);
    itoa(pc.mm, c, 10);
    iText(890, 570, c, GLUT_BITMAP_HELVETICA_18);
    itoa(pc.dd, c, 10);
    iText(920, 570, "/", GLUT_BITMAP_HELVETICA_18);
    itoa(pc.yy, c, 10);
    iText(930, 570, c, GLUT_BITMAP_HELVETICA_18);
    itoa(pc.h, c, 10);
    iText(880, 540, c, GLUT_BITMAP_HELVETICA_18);
    iText(905, 540, ":", GLUT_BITMAP_HELVETICA_18);
    itoa(pc.mi, c, 10);
    iText(910, 540, c, GLUT_BITMAP_HELVETICA_18);
    iText(935, 540, ":", GLUT_BITMAP_HELVETICA_18);
    itoa(pc.sec, c, 10);
    iText(940, 540, c, GLUT_BITMAP_HELVETICA_18);
}

void iMouseMove(int mx, int my)
{
    printf("x = %d, y= %d\n", mx, my);
}

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
       PlaySoundA(music[4], NULL, SND_ASYNC);
        if (st == 0)
        {
            if (mx >= 380 && mx <= 635 && my >= 340 && my <= 390)
            {
                st = 1;
                iFilledRectangle(380, 40, 255, 50);
            }
            if (mx >= 380 && mx <= 635 && my >= 290 && my <= 340)
            {
                st = 2;
                iFilledRectangle(380, 40, 255, 50);
            }
            if (mx >= 380 && mx <= 635 && my >= 240 && my <= 290)
            {
                st = 7;
            }
            if (mx >= 380 && mx <= 635 && my >= 190 && my <= 240)
            {
                st = 3;
            }
            if (mx >= 380 && mx <= 635 && my >= 140 && my <= 190)
            {
                st = 4;
            }
            if (mx >= 380 && mx <= 635 && my >= 90 && my <= 140)
            {
                st = 5;
            }
            if (mx >= 740 && mx <= 1000 && my >= 20 && my <= 43)
            {
                delete_everything();
            }
            if (mx >= 0 && mx <= 300 && my >= 20 && my <= 43)
            {
                saveandquit();
            }
            if (mx > 380 && mx <= 635 && my >= 40 && my <= 90)
            {
                st = 10;
            }
            if (hurry == true && mx >= 750 && mx <= 930 && my >= 210 && my <= 390)
            {
                st = 9;
            }
        }
        // place your codes here

        if (st == 101)
        {
            if (mx >= 370 && mx <= 370 + 430 && my >= 123 + 120 && my <= 123 + 180)
            {
                // set the focus to true
                focus3 = true;
                focus4 = false;
                focus5 = false;

                // set the cursor position
                cursor_x3 = 375 + len3 * 12;
                cursor_y3 = 250;
            }

            if (mx >= 370 && mx <= 370 + 430 && my >= 123 + 60 && my <= 123 + 120)
            {
                // set the focus to true
                focus3 = false;
                focus4 = true;
                focus5 = false;

                // set the cursor position
                cursor_x4 = 375 + len4 * 12;
                cursor_y4 = 190;
            }

            if (mx >= 370 && mx <= 370 + 430 && my >= 123 && my <= 123 + 60)
            {
                // set the focus to true
                focus3 = false;
                focus4 = false;
                focus5 = true;

                // set the cursor position
                cursor_x5 = 375 + len5 * 12;
                cursor_y5 = 130;
            }

            if (mx >= 470 && mx <= 470 + 100 && my >= 70 && my <= 70 + 40)
            {
                // process the registration form
                printf("Your Name: %s\n", yourname);
                printf("Your Password: %s\n", yourpass);
                printf("Confirm Password: %s\n", yournewpass);

                // check if the passwords match
                if (strcmp(yourpass, yournewpass) == 0)
                {
                    // save user credentials to file
                    saveUserCredentials(yourname, yourpass);
                    // switch to login page
                    st = 100;
                }
                else
                {
                    // handle password mismatch
                    printf("Passwords do not match.\n");
                }
            }
        }
        // check if the username input is clicked
        if (mx >= 412 && mx <= 612 && my >= 300 && my <= 330)
        {
            // set the focus to true
            focus1 = true;
            focus2 = false;

            // set the cursor position
            cursor_x1 = 412 + len1 * 12;
            cursor_y1 = 300;
        }

        // check if the password input is clicked
        if (mx >= 412 && mx <= 612 && my >= 250 && my <= 280)
        {
            // set the focus to true
            focus1 = false;
            focus2 = true;

            // set the cursor position
            cursor_x2 = 412 + len2 * 12;
            cursor_y2 = 250;
        }

        if (mx >= 690 && mx <= 690 + 56.67 && my >= 210 && my <= 210 + 56.67)
        {
            capt_1 = 1;
        }
        if (mx >= 690 + 56.67 && mx <= 690 + 56.67 * 2 && my >= 210 && my <= 210 + 56.67)
        {
            capt_2 = 2;
        }
        if (mx >= 690 + 56.6 * 2 && mx <= 690 + 56.67 * 3 && my >= 210 && my <= 210 + 56.67)
        {
            capt_3 = 3;
        }
        if (mx >= 690 && mx <= 690 + 56.67 && my >= 210 + 56.67 && my <= 210 + 56.67 * 2)
        {
            capt_4 = 4;
        }
        if (mx >= 690 + 56.67 && mx <= 690 + 56.67 * 2 && my >= 210 + 56.67 && my <= 210 + 56.67 * 2)
        {
            capt_5 = 5;
        }
        if (mx >= 690 + 56.67 * 2 && mx <= 690 + 56.67 * 3 && my >= 210 + 56.67 && my <= 210 + 56.67 * 2)
        {
            capt_6 = 6;
        }
        if (mx >= 690 && mx <= 690 + 56.67 && my >= 210 + 56.67 * 2 && my <= 210 + 56.67 * 3)
        {
            capt_7 = 7;
        }
        if (mx >= 690 + 56.67 && mx <= 690 + 56.67 * 2 && my >= 210 + 56.67 * 2 && my <= 210 + 56.67 * 3)
        {
            capt_8 = 8;
        }
        if (mx >= 690 + 56.67 * 2 && mx <= 690 + 56.67 * 3 && my >= 210 + 56.67 * 2 && my <= 210 + 56.67 * 3)
        {
            capt_9 = 9;
        }
        if (capt_1 == 1 && capt_2 != 2 && capt_3 != 3 && capt_4 != 4 && capt_5 != 5 && capt_6 != 6 && capt_7 == 7 && capt_8 == 8 && capt_9 != 9)
        {
            truth_value = true;
        }
        if (capt_1 == 1 && capt_7 == 7 && capt_8 == 8 && (capt_2 == 2 || capt_3 == 3 || capt_4 == 4 || capt_5 == 5 || capt_6 == 6 || capt_9 == 9))
        {
            truth_value = false;
        }

        // check if the button is clicked
        if (mx >= 270 && mx <= 270 + 210 && my >= 170 && my <= 210)
        {
            // process the login form
            printf("Username: %s\n", username);
            printf("Password: %s\n", password);

            // check if the username and password are valid
            if (checkUserCredentials(username, password) && capt_1 == 1 && capt_2 != 2 && capt_3 != 3 && capt_4 != 4 && capt_5 != 5 && capt_6 != 6 && capt_7 == 7 && capt_8 == 8 && capt_9 != 9)
            {
                // change the page to frontpage
                st = 0;
            }
            else
            {
                // handle invalid credentials
                printf("Invalid username or password.\n");
            }
        }

        if (mx >= 270 + 210 && mx <= 270 + 210 + 210 && my >= 170 && my <= 210 && st == 100)
        {
            st = 101;
        }

        if (mx >= 20 && mx <= 220 && my >= 540 && my <= 590 && (st == 0 || st == 101))
        {
            st = 100; // Back to login page
        }

        if (mx >= 20 && mx <= 90 && my >= 550 && my <= 590 && st != 0 && st != 100 && st != 101)
        {
            st = 0; // Back
        }

        if (st == 4)
        {
            if (mx >= 380 && mx <= 380 + 130 && my >= 320 && my <= 320 + 70)
            {
                x = 0;
                y = 0;
                z = 0;
                bgi = 1;
            }
            if (mx >= 380 && mx <= 380 + 130 && my >= 250 && my <= 320)
            {
                x = 255;
                y = 255;
                z = 255;
                bgi = 0;
            }
        }

        if (st == 3)
        {
            // iFilledRectangle(610,240+k,100,50);
            if (mx >= 610 && mx <= 710 && my >= 340 && my <= 390)
            {
                musicstate = true;
                musici = 1;
                ringtone();
            }
            if (mx >= 610 && mx <= 710 && my >= 290 && my <= 340)
            {
                musicstate = true;
                musici = 2;
                ringtone();
            }
            if (mx >= 610 && mx <= 710 && my >= 240 && my <= 290)
            {
                musicstate = true;
                musici = 3;
                ringtone();
            }
            if (mx >= 710 && mx <= 810 && my >= 340 && my <= 390)
            {
                musicstate = true;
                musici = 4;
                ringtone();
                musici = 5;
            }
            if (mx >= 710 && mx <= 810 && my >= 290 && my <= 340)
            {
                musicstate = true;
                musici = 4;
                ringtone();
                musici = 6;
            }
            if (mx >= 710 && mx <= 810 && my >= 240 && my <= 290)
            {
                musicstate = true;
                musici = 4;
                ringtone();
                musici = 7;
            }
        }
        if (st == 9)
        {
            if (mx >= 360 && mx <= 465 && my >= 399 && my <= 424)
            {
                tasklist[ringingtaskindex].minute += 5;
                if (tasklist[ringingtaskindex].minute >= 60)
                {
                    tasklist[ringingtaskindex].hour += 1;
                    tasklist[ringingtaskindex].minute %= 60;
                }
                PlaySoundA(music[4], NULL, SND_ASYNC);
                tasklist[ringingtaskindex].taskstate = 0;
                st = 0;
            }
            if (mx >= 310 && mx <= 465 && my >= 349 && my <= 374)
            {
                tasklist[ringingtaskindex].minute += 10;
                if (tasklist[ringingtaskindex].minute >= 60)
                {
                    tasklist[ringingtaskindex].hour += 1;
                    tasklist[ringingtaskindex].minute %= 60;
                }
                PlaySoundA(music[4], NULL, SND_ASYNC);
                tasklist[ringingtaskindex].taskstate = 0;
                st = 0;
            }
            if (mx >= 310 && mx <= 465 && my >= 299 && my <= 324)
            {
                PlaySoundA(music[4], NULL, SND_ASYNC);
                tasklist[ringingtaskindex].taskstate = 1;
                hurry = false;
                st = 0;
            }
        }
        if (st == 2)
        {

            if (mx >= 125 && mx <= 370 && my >= 410 && my <= 431)
            {
                del_ind = 0;
                push();
                taskcount--;
                i--;
            }
            if (mx >= 125 && mx <= 370 && my >= 360 && my <= 381)
            {
                del_ind = 1;
                push();
                taskcount--;
                i--;
            }
            if (mx >= 125 && mx <= 370 && my >= 310 && my <= 331)
            {
                del_ind = 2;
                taskcount--;
                i--;
                push();
            }
            if (mx >= 125 && mx <= 370 && my >= 260 && my <= 281)
            {
                del_ind = 3;
                taskcount--;
                i--;
                push();
            }
            if (mx >= 125 && mx <= 370 && my >= 210 && my <= 231)
            {
                del_ind = 4;
                taskcount--;
                i--;
                push();
            }
            if (mx >= 125 && mx <= 370 && my >= 160 && my <= 181)
            {
                del_ind = 5;
                taskcount--;
                i--;
                push();
            }
            if (mx >= 125 && mx <= 370 && my >= 110 && my <= 131)
            {
                del_ind = 6;
                taskcount--;
                i--;
                push();
            }
            if (mx >= 125 && mx <= 370 && my >= 60 && my <= 81)
            {
                del_ind = 7;
                taskcount--;
                i--;
                push();
            }
            if (mx >= 125 && mx <= 370 && my >= 10 && my <= 31)
            {
                del_ind = 8;
                taskcount--;
                i--;
                push();
            }
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        PlaySoundA(music[4], NULL, SND_ASYNC);
        if (mx >= 690 && mx <= 690 + 56.67 && my >= 210 && my <= 210 + 56.67)
        {
            capt_1 = 0;
            truth_value = false;
        }
        if (mx >= 690 + 56.67 && mx <= 690 + 56.67 * 2 && my >= 210 && my <= 210 + 56.67)
        {
            capt_2 = 0;
        }
        if (mx >= 690 + 56.6 * 2 && mx <= 690 + 56.67 * 3 && my >= 210 && my <= 210 + 56.67)
        {
            capt_3 = 0;
        }
        if (mx >= 690 && mx <= 690 + 56.67 && my >= 210 + 56.67 && my <= 210 + 56.67 * 2)
        {
            capt_4 = 0;
        }
        if (mx >= 690 + 56.67 && mx <= 690 + 56.67 * 2 && my >= 210 + 56.67 && my <= 210 + 56.67 * 2)
        {
            capt_5 = 0;
        }
        if (mx >= 690 + 56.67 * 2 && mx <= 690 + 56.67 * 3 && my >= 210 + 56.67 && my <= 210 + 56.67 * 2)
        {
            capt_6 = 0;
        }
        if (mx >= 690 && mx <= 690 + 56.67 && my >= 210 + 56.67 * 2 && my <= 210 + 56.67 * 3)
        {
            capt_7 = 0;
            truth_value = false;
        }
        if (mx >= 690 + 56.67 && mx <= 690 + 56.67 * 2 && my >= 210 + 56.67 * 2 && my <= 210 + 56.67 * 3)
        {
            capt_8 = 0;
            truth_value = false;
        }
        if (mx >= 690 + 56.67 * 2 && mx <= 690 + 56.67 * 3 && my >= 210 + 56.67 * 2 && my <= 210 + 56.67 * 3)
        {
            capt_9 = 0;
        }
        if ((capt_2 == 0 && capt_3 == 0 && capt_4 == 0 && capt_5 == 0 && capt_6 == 0 && capt_9 == 0) && (capt_1 == 1 && capt_7 == 7 && capt_8 == 8))
        {
            truth_value = true;
        }
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        static int countclick = 0;
        for (int f = 0; f < taskcount; f++)
        {
            if (mx >= 700 && mx <= 850 && my >= 460 - 50 * (f + 1) && my <= 483 - 50 * (f + 1))
            {
                countclick = (countclick + 1) % 2;
            }
        }

        if (st == 7 && countclick == 0)
        {
            for (int f = 0; f < taskcount; f++)
            {
                if (mx >= 700 && mx <= 850 && my >= 460 - 50 * (f + 1) && my <= 483 - 50 * (f + 1))
                {
                    tasklist[f].taskstate = !tasklist[f].taskstate;
                }
            }
        }
    }
}

void ringtone()
{
    if (musicstate)
    {
        if (musici == 4)
        {
            PlaySoundA(music[musici], NULL, SND_ASYNC);
        }
        else
        {
           PlaySoundA(music[musici], NULL, SND_ASYNC | SND_LOOP);
        }
    }
}

void iKeyboard(unsigned char key)
{
    if (key == 27)
    {
        exit(0);
    }

    if (st == 100)
    {
        // check if the focus is on the username input
        if (focus1)
        {
            // check if the key is backspace
            if (key == '\b')
            {
                // delete the last character
                if (len1 > 0)
                {
                    len1--;
                    username[len1] = 0;
                }
            }
            // check if the key is enter
            else if (key == '\r')
            {
                // switch the focus to the password input
                focus1 = false;
                focus2 = true;
            }
            // otherwise
            else
            {
                // append the key to the input value
                if (len1 < 99)
                {
                    username[len1] = key;
                    len1++;
                    username[len1] = '\0';
                }
            }

            // update the cursor position
            cursor_x1 = 412 + len1 * 12;
        }

        // check if the focus is on the password input
        if (focus2)
        {
            // check if the key is backspace
            if (key == '\b')
            {
                // delete the last character
                if (len2 > 0)
                {
                    len2--;
                    password[len2] = '\0';
                }
            }
            // check if the key is enter
            else if (key == '\r')
            {
                // process the login form
                printf("Username: %s\n", username);
                printf("Password: %s\n", password);

                // check if the username and password are valid
                if (strcmp(username, "m") == 0 && strcmp(password, "1") == 0)
                {
                    // change the page to frontpage
                    st = 0;
                }

                if (checkUserCredentials(username, password) && capt_1 == 1 && capt_2 != 2 && capt_3 != 3 && capt_4 != 4 && capt_5 != 5 && capt_6 != 6 && capt_7 == 7 && capt_8 == 8 && capt_9 != 9)
                {
                    // change the page to frontpage
                    st = 0;
                }
                else
                {
                    // handle invalid credentials
                    printf("Invalid username or password.\n");
                }
            }
            // otherwise
            else
            {
                // append the key to the input value
                if (len2 < 99)
                {
                    password[len2] = key;
                    len2++;
                    password[len2] = '\0';
                }
            }
            // update the cursor position
            cursor_x2 = 412 + len2 * 12;
        }
    }

    if (st == 101)
    {
        if (focus4)
        {
            // check if the key is backspace
            if (key == '\b')
            {
                // delete the last character
                if (len4 > 0)
                {
                    len4--;
                    yourpass[len4] = '\0';
                }
            }
            // check if the key is enter
            else if (key == '\r')
            {
                // switch the focus to the confirm password
                focus3 = false;
                focus4 = false;
                focus5 = true;
            }
            // otherwise
            else
            {
                // append the key to the input value
                if (len4 < 99)
                {
                    yourpass[len4] = key;
                    len4++;
                    yourpass[len4] = '\0';
                }
            }

            // update the cursor position
            cursor_x4 = 375 + len4 * 12;
        }

        if (focus3)
        {
            // check if the key is backspace
            if (key == '\b')
            {
                // delete the last character
                if (len3 > 0)
                {
                    len3--;
                    yourname[len3] = '\0';
                }
            }
            // check if the key is enter
            else if (key == '\r')
            {
                // switch the focus to the password input
                focus3 = false;
                focus4 = true;
                focus5 = false;
            }
            // otherwise
            else
            {
                // append the key to the input value
                if (len3 < 99)
                {
                    yourname[len3] = key;
                    len3++;
                    yourname[len3] = '\0';
                }
            }

            // update the cursor position
            cursor_x3 = 375 + len3 * 12;
        }

        if (focus5)
        {
            // check if the key is backspace
            if (key == '\b')
            {
                // delete the last character
                if (len5 > 0)
                {
                    len5--;
                    yournewpass[len5] = '\0';
                }
            }

            // check if the key is enter
            else if (key == '\r')
            {
                // check if the passwords match
                if (strcmp(yourpass, yournewpass) == 0)
                {
                    // save user credentials to file
                    saveUserCredentials(yourname, yourpass);
                    st = 100;
                }
                else
                {
                    // handle password mismatch
                    printf("Passwords do not match.\n");
                }
            }

            // otherwise
            else
            {
                // append the key to the input value
                if (len5 < 99)
                {
                    yournewpass[len5] = key;
                    len5++;
                    yournewpass[len5] = '\0';
                }
            }

            // update the cursor position
            cursor_x5 = 375 + len5 * 12;
        }
    }
    if (st == 1)
    {
        if (key == '\b')
        {
            j--;
            if (j < 0)
                j = 0;
            tasklist[i].taskname[j] = '\0';
        }
        if (key != '\b')
        {
            tasklist[i].taskname[j] = key;
            tasklist[i].taskname[j + 1] = '\0';
            j++;
        }

        if (key == '\r')
        {
            st = 6;
            j = 0;
            key = ' ';
        }
    }
    if (st == 6 && (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '\r' || key == '\b' || key == '/'))
    {

        if (key == '\b')
        {
            j--;
            if (j < 0)
                j = 0;
            tempdate[j] = '\0';
        }
        if (key != '\b')
        {
            tempdate[j] = key;
            j++;
        }
        if (key == '/' || key == '\r')
        {
            tempdate[j] = '\0';
            tasklist[i].day = atoi(tempdate);
            printf("%d\n", tasklist[i].day);
            tasklist[i].month = atoi(tmp + 3);
            printf("%d\n", tasklist[i].month);
            tasklist[i].year = atoi(tmp + 6);
            printf("%d\n", tasklist[i].year);

            if (key == '\r')
            {
                st = 8;
                j = 0;
                key = ' ';
            }
        }
    }

    if (st == 8 && (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '\r' || key == '\b' || key == ':'))
    {
        if (key == '\b')
        {
            j--;
            if (j < 0)
                j = 0;
            temptime[j] = '\0';
        }
        if (key != '\b')
        {
            temptime[j] = key;
            j++;
        }
        if ((key == ':' || key == '\r'))
        {
            temptime[j] = '\0';
            tasklist[i].hour = atoi(temptime);
            printf("%d\n", tasklist[i].hour);
            tasklist[i].minute = atoi(tmt + 3);
            printf("%d\n", tasklist[i].minute);
            if (key == '\r')
            {
                for (int k = 0; k < 50; k++)
                {
                    tempdate[k] = '\0';
                    temptime[k] = '\0';
                }
                taskcount++;
                i++;
                st = 1;
                j = 0;
            }
        }
    }
    if (st == 10 && (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '\r' || key == '\b'))
    {
        if (key == '\b')
        {
            j--;
            if (j < 0)
                j = 0;
            tempo[j] = '\0';
        }
        if (key != '\b')
        {
            tempo[j] = key;
            j++;
        }
        if (key == '\r')
        {
            tempo[j] = '\0';
            chng_ind = atoi(tempo) - 1;
            printf("%d\n", chng_ind);
            j = 0;
            st = 11;
            key = ' ';
            // tempo[0]='\0';
        }
    }
    if (st == 11 && (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '\r' || key == '\b' || key == '/'))
    {

        if (key == '\b')
        {
            j--;
            if (j < 0)
                j = 0;
            tempdate[j] = '\0';
        }
        if (key != '\b')
        {
            tempdate[j] = key;
            j++;
        }
        if (key == '/' || key == '\r')
        {
            tempdate[j] = '\0';
            tasklist[chng_ind].day = atoi(tempdate);
            tasklist[chng_ind].month = atoi(tmp + 3);
            tasklist[chng_ind].year = atoi(tmp + 6);
            if (key == '\r')
            {
                st = 12;
                j = 0;
                key = ' ';
            }
        }
    }
    if (st == 12 && (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '\r' || key == '\b' || key == ':'))
    {
        if (key == '\b')
        {
            j--;
            if (j < 0)
                j = 0;
            temptime[j] = '\0';
        }
        if (key != '\b')
        {
            temptime[j] = key;
            j++;
        }
        if ((key == ':' || key == '\r'))
        {
            temptime[j] = '\0';
            tasklist[chng_ind].hour = atoi(temptime);
            tasklist[chng_ind].minute = atoi(tmt + 3);

            if (key == '\r')
            {
                for (int k = 0; k < 50; k++)
                {
                    tempdate[k] = '\0';
                    temptime[k] = '\0';
                }
                st = 10;
                j = 0;
                tempo[0] = '\0';
            }
        }
    }
}
/*
    function iSpecialKeyboard() is called whenver user hits special keys like-
    function keys, home, end, pg up, pg down, arraows etc. you have to use
    appropriate constants to detect them. A list is:
    GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
    GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
    GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
    GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
    */
void iSpecialKeyboard(unsigned char key)
{
    if (key == GLUT_KEY_END)
    {
        saveandquit();
    }
    // place your codes for other keys here
}
void biostimefetch()
{
    time_t rawtime;
    tm *t;
    time(&rawtime);
    t = gmtime(&rawtime);
    pc.dd = t->tm_mday;
    pc.mm = t->tm_mon + 1;
    pc.yy = t->tm_year + 1900;
    pc.h = (t->tm_hour + 6) % 24;
    pc.mi = t->tm_min;
    pc.sec = t->tm_sec;
}

int main()
{
    fetchtask();
    fetchsettings();
    iSetTimer(0, alarm);
    // place your own initialization codes here.
    iInitialize(1024, 600, "To-Do Alert");
    return 0;
}