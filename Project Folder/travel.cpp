# include "iGraphics.h"
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int x = 300, y = 300, r = 20;
int page=3;
int booking_text=0;
// int booking_text=18;
// int page=15;
int user = 1;
int prev_page = 0;
//auth
int auth = 0;
char auth_file[50]="data/auth.csv";

int initialize = 0;
void initializing(){
	remove("bot_response.txt");
	FILE *file = fopen("bot_response.txt", "w");
	fprintf(file, "Hi! I am Salem Here to Assist you !\n Lets Plan a Trip and Discover Bangladesh.\n Where do you want to go?");
	fclose(file);

}


//place image

//user == 1 >> trip planner
//user == 2 >> hotel owner
//user == 3 >> car owner

//text input 
// char usr_name[50]="salem";
char usr_name[50]="";

char pass[50]="";
char security[50]="";
int usr_len;
int pass_len;
int sec_len;
int mode =0;
int usr_in=0;
int pass_in=0;
int sec_in=0;

// starting the app
char intro_image[40][21] = { "intro/intro (1).bmp", "intro/intro (2).bmp", "intro/intro (3).bmp", "intro/intro (4).bmp", "intro/intro (5).bmp", "intro/intro (6).bmp", "intro/intro (7).bmp", "intro/intro (8).bmp", "intro/intro (9).bmp", "intro/intro (10).bmp", "intro/intro (11).bmp", "intro/intro (12).bmp", "intro/intro (13).bmp", "intro/intro (14).bmp", "intro/intro (15).bmp", "intro/intro (16).bmp", "intro/intro (17).bmp", "intro/intro (18).bmp", "intro/intro (19).bmp", "intro/intro (20).bmp", "intro/intro (21).bmp", "intro/intro (22).bmp", "intro/intro (23).bmp", "intro/intro (24).bmp", "intro/intro (25).bmp", "intro/intro (26).bmp", "intro/intro (27).bmp", "intro/intro (28).bmp", "intro/intro (29).bmp", "intro/intro (30).bmp", "intro/intro (31).bmp", "intro/intro (32).bmp", "intro/intro (33).bmp", "intro/intro (34).bmp", "intro/intro (35).bmp", "intro/intro (36).bmp", "intro/intro (37).bmp", "intro/intro (38).bmp", "intro/intro (39).bmp", "intro/intro (40).bmp" };
int intro_index = 0;

//places
char palce_image[6][25]= {"places/places (1).bmp","places/places (2).bmp","places/places (3).bmp","places/places (4).bmp","places/places (5).bmp","places/places (6).bmp"};
int place_index = 2;

//discover type
char discover_type[5][30]={"discover_sel/discover1.bmp","discover_sel/discover2.bmp","discover_sel/discover3.bmp","discover_sel/discover4.bmp","discover_sel/discover5.bmp"};
int discover_type_index=0;
//landing page variables
int plan_a_trip_x=200, plan_a_trip_y=350,col=200,row=80;

//login page variables
int id_x=200, id_y=300;

//budget page variables
int place_budget = 0;
int transport_budget = 0;
int hotel_budget = 0;
int days_budget = 0;
int guide_budget = 0;



//landing page
void landing_page(){
	//iShowBMP(0, 0, "assets/home.bmp");

}


//discover page
void discover_page(){
	//iShowBMP(0, 0, "assets/discover.bmp");

}

//plan a trip page
void plan_a_trip_page(){
	//iShowBMP(0, 0, "assets/plan.bmp");

}


//login signup page                                               
void login_signup_page(){
	//iShowBMP(0, 0, "assets/signin-up.bmp");

}



//login page
void login_page(){
	
	//iShowBMP(0, 0, "assets/login.bmp");
	
	
	iSetColor(0, 0, 0);
	iText(245, 395, pass, GLUT_BITMAP_TIMES_ROMAN_24);	

	iSetColor(0, 0, 0);
	iText(245, 480, usr_name, GLUT_BITMAP_TIMES_ROMAN_24);

}


//signup page
void signup_page(){
	
	//iShowBMP(0, 0, "assets/signup.bmp");
	
	// Sign_in button

	iSetColor(0, 0, 0);
	iText(250, 485, usr_name, GLUT_BITMAP_TIMES_ROMAN_24);	

	//Sign_up button
	iSetColor(0, 0, 0);
	iText(250, 400, pass, GLUT_BITMAP_TIMES_ROMAN_24);

	// Password
	
	iSetColor(0, 0, 0);
	iText(250, 315, security, GLUT_BITMAP_TIMES_ROMAN_24);	

}


//type of user 
void user_type(){
	
	//iShowBMP(0, 0, intro_image[20]);
	
	// Sign_in button
	
	iSetColor(255, 255, 255);
	iFilledRectangle(id_x+col*0-10, id_y+row*0-20, 270, 50);
	iSetColor(0, 0, 0);
	iText(id_x+col*0, id_y+row*0, "Transport Owner", GLUT_BITMAP_TIMES_ROMAN_24);	

	//Sign_up button
	iSetColor(255, 255, 255);
	iFilledRectangle(id_x+col*0-10,id_y+row*1-20, 270, 50);
	iSetColor(0, 0, 0);
	iText(id_x+col*0, id_y+row*1, "Hotel/Resturant Owner", GLUT_BITMAP_TIMES_ROMAN_24);

	// Password
	iSetColor(255, 255, 255);
	iFilledRectangle(id_x+col*0-10, id_y+row*2-20, 270, 50);
	iSetColor(0, 0, 0);
	iText(id_x+col*0, id_y+row*2, "Tour Guide", GLUT_BITMAP_TIMES_ROMAN_24);	


}

//authentication
// validate user credentials
int authenticateUser(int userType, const char *username, const char *password) {
    FILE *file = fopen(auth_file, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 0;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        int storedUserType;
        char storedUsername[50];
        char storedPassword[50];
        char storedSecurityq[50];

        sscanf(line, "%d,%[^,],%[^,],%s", &storedUserType, storedUsername, storedPassword, storedSecurityq);

        if (userType == storedUserType && strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            fclose(file);
            return 1; // Authentication successful
        }
    }

    fclose(file);

    return 0; // Authentication failed
}


//add user

void addUser(int userType, const char *username, const char *password, const char *securityq) {
	FILE *file = fopen(auth_file, "a");
	if (file == NULL) {
		printf("Error opening the file.\n");
		return;
	}

	fprintf(file, "%d,%s,%s,%s\n", userType, username, password, securityq);
	fclose(file);
}


// forgot password

int recover_pass(int userType, const char *username, const char *password, const char *securityq){
	FILE *file = fopen(auth_file, "r");
	FILE *file2 = fopen("data/temp.csv", "w+");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 0;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        int storedUserType;
        char storedUsername[50];
        char storedPassword[50];
        char storedSecurityq[50];

        sscanf(line, "%d,%[^,],%[^,],%s", &storedUserType, storedUsername, storedPassword, storedSecurityq);

        if (userType == storedUserType && strcmp(username, storedUsername) == 0 && strcmp(securityq, storedSecurityq) == 0) {
			fprintf(file2, "%d,%s,%s,%s\n", userType, username, password, securityq);
        }

		else{
			fputs(line, file2);
		}
    }

    fclose(file);
	fclose(file2);
	remove(auth_file);
	rename("data/temp.csv", auth_file);
    return 0; // Authentication failed
}


//change password

void forgot_pass(){
	//iShowBMP(0, 0, "assets/recover.bmp");
	
	// Sign_in button

	iSetColor(0, 0, 0);
	iText(250, 485, usr_name, GLUT_BITMAP_TIMES_ROMAN_24);	

	//Sign_up button
	iSetColor(0, 0, 0);
	iText(250, 400, pass, GLUT_BITMAP_TIMES_ROMAN_24);

	// Password
	
	iSetColor(0, 0, 0);
	iText(250, 315, security, GLUT_BITMAP_TIMES_ROMAN_24);	

}





//start function
void intro(){
		if (intro_index==39){
			// intro_index=0;
			//iShowBMP(0, 0, intro_image[30]);
			// login_page();
			// landing_page();
		}
		else{
			intro_index++;
			Sleep(100);
			//iShowBMP(0, 0, intro_image[intro_index]);
		}
}

//place image

void place(){
	//iShowBMP(0, 0, palce_image[place_index]);
}

//discover type
void discover_type_loop(){
	//iShowBMP(0, 0, discover_type[discover_type_index]);
}

//choose destination
void destination(){
	//iShowBMP(0, 0, "assets/destination.bmp");
}

//choose transport
void transport(){
	//iShowBMP(0, 0, "assets/transport.bmp");
}

//choose hotel
void hotel(){
	//iShowBMP(0, 0, "assets/hotel.bmp");
}

//choose days
void days(){
	//iShowBMP(0, 0, "assets/days.bmp");
}

//choose guide
void guide(){
	//iShowBMP(0, 0, "assets/guide.bmp");
}

//budget

void budget(){
	//iShowBMP(0, 0, "assets/budget.bmp");
	iSetColor(0, 0, 0);

	int total = place_budget*transport_budget + hotel_budget*days_budget + guide_budget;
	char total_budget[50];
	sprintf(total_budget, "%d", total);
	iText(360, 300, total_budget, GLUT_BITMAP_TIMES_ROMAN_24);	
}

//display text
void display_text(char *file_name, int x, int y){
	iSetColor(0, 100, 1000);
	FILE *file = fopen(file_name, "r");
	if (file == NULL) {
		printf("Error opening the file.: display\n");
		return;
	}
	char line[50];
	while (fgets(line, sizeof(line), file)) {
		iText(x, y, line ,GLUT_BITMAP_HELVETICA_12);
		y -= 20;
	}
	fclose(file);
}

int user_text_x=0;
int user_text_y=0;
int ai_text_x=0;
int ai_text_y=0;

char user_text_destination[100];
char user_text_transport[100];
char user_text_hotel[100];
char user_text_days[100];
char user_text_guide[100];
char user_text_budget[100];
char user_text_input[100];
char user_text_input_show[100];
int user_text_len=0;

//booking

void free_user_text_input(char *user_text_free){
	// while(user_text_len>=0){
	// 	user_text_free[user_text_len]='\0';
	// 	user_text_len--;
	// }
	int len = strlen(user_text_free);
	while(len>=0){
		user_text_free[len]='\0';
		len--;
	}
	// memset(user_text_free, '\0', sizeof(user_text_free));
	user_text_len=0;
}


char order_file[50]="data/order.csv";

//find previous order
int findorder() {
	printf("finding order - start\n");
	FILE *file = fopen(order_file, "r");
	if (file == NULL) {
		printf("Error opening the file.\n");
		return 0;
	}
	char line[200];
	char storedUsername[50];
	char storeddestination[50];
	char storedtransport[50];
	char storedhotel[50];
	char storeddays[50];
	char storedguide[50];
	char storedbudget[50];

	while (fgets(line, sizeof(line), file)) {
		long order_ref;
		sscanf(line, "%d,%ld,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", &user, &order_ref, storedUsername, storeddestination,storedtransport, storedhotel, storeddays, storedguide, storedbudget);
		if (strcmp(usr_name, storedUsername) == 0) {
			fclose(file);
			return 1;
		}
	}
	printf("finding order - done\n");
	fclose(file);
	return 0;
}

void addorder() {
	if(findorder()){
		printf("order already exists\n");
		booking_text=16;
		return;
	}
	printf("adding order - start\n");
	FILE *file = fopen(order_file, "a");
	if (file == NULL) {
		printf("Error opening the file.\n");
		return;
	}
	time_t order_ref = time(NULL);
	strcat(user_text_budget,"\0");
	fprintf(file, "%d,%ld,%s,%s,%s,%s,%s,%s,%s\n", user,order_ref, usr_name, user_text_destination,user_text_transport, user_text_hotel, user_text_days, user_text_guide, user_text_budget);
	printf("adding order - done\n");
	fclose(file);
}
//cancel order
void cancelorder() {
	printf("cancelling order - start\n");
	FILE *file = fopen(order_file, "r");
	FILE *temp = fopen("data/temp.csv", "w+");
	if(file == NULL){
		printf("Error opening the file.\n");
		return;
	}
	char line[200];
	while(fgets(line, sizeof(line), file)){
		long order_ref;
		char temp_usr_name[50];
		char temp_user_text_destination[50];
		char temp_user_text_transport[50];
		char temp_user_text_hotel[50];
		char temp_user_text_days[50];
		char temp_user_text_guide[50];
		char temp_user_text_budget[50];
		sscanf(line, "%d,%ld,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", &user, &order_ref, temp_usr_name, temp_user_text_destination,temp_user_text_transport, temp_user_text_hotel, temp_user_text_days, temp_user_text_guide, temp_user_text_budget);
		// sscanf(line, "%d,%ld,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", &user, &order_ref, usr_name, user_text_destination,user_text_transport, user_text_hotel, user_text_days, user_text_guide, user_text_budget);
		if(strcmp(usr_name, temp_usr_name) != 0){
			fprintf(temp, "%d,%ld,%s,%s,%s,%s,%s,%s,%s\n", user,order_ref, usr_name, user_text_destination,user_text_transport, user_text_hotel, user_text_days, user_text_guide, user_text_budget);
		}
	}

	fclose(file);
	fclose(temp);
	remove(order_file);
	rename("data/temp.csv", order_file);

}
//show order
int showorder() {
	// printf("showing order - start\n");
	FILE *file = fopen(order_file, "r");
	if(file == NULL){
		printf("Error opening the file.\n");
		return 0;
	}
	char line[200];
	char storedUsername[50];
	while(fgets(line, sizeof(line), file)){
		long order_ref;
		sscanf(line, "%d,%ld,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", &user, &order_ref, storedUsername, user_text_destination,user_text_transport, user_text_hotel, user_text_days, user_text_guide, user_text_budget);
		// printf("%d,%ld,%s,%s,%s,%s,%s,%s,%s\n", storedUsername,order_ref, usr_name, user_text_destination,user_text_transport, user_text_hotel, user_text_days, user_text_guide, user_text_budget);
		// printf("%s , %s\n",usr_name, storedUsername);
		if(strcmp(usr_name, storedUsername) == 0){
			fclose(file);
			return 0;
		}
	}
	// printf("showing order - done\n");
	fclose(file);
	return 1;
}

//ai chat bot

void ai_chat_bot(){
	//iShowBMP(0, 0, "assets/chat_ai.bmp");
	display_text("bot_response.txt",230,580);
	//text box
	// display_text("data/destination.csv", 190, 256);
	iText(190, 256, user_text_input ,GLUT_BITMAP_HELVETICA_12);
}

void booking(){
	mode = 1;
	iSetColor(0, 0, 0);

	switch(booking_text){
		case 0:
			//iShowBMP(0, 0, "assets/chat0.bmp");
			iText(210, 420, "Hi! I am Salem Here to Assist you !", GLUT_BITMAP_HELVETICA_12);
			iText(210, 400, "Where do you want to go?", GLUT_BITMAP_HELVETICA_12);

			//text box
			iText(190, 256, user_text_input ,GLUT_BITMAP_HELVETICA_12);
			break;

			
		case 1:
			//iShowBMP(0, 0, "assets/chat1.bmp");
			//ai text
			iText(210, 550, "Hi! I am Salem Here to Assist you !", GLUT_BITMAP_HELVETICA_12);
			iText(210, 530, "Where do you want to go?", GLUT_BITMAP_HELVETICA_12);
			//user text
			strcpy(user_text_destination,user_text_input);
			free_user_text_input(user_text_input);
			iText(300, 410, user_text_destination, GLUT_BITMAP_HELVETICA_12);
			iText(300, 390, "", GLUT_BITMAP_HELVETICA_12);
			//text box
			iText(190, 256, user_text_input ,GLUT_BITMAP_HELVETICA_12);
			
			break;
		case 2:
			//iShowBMP(0, 0, "assets/chat2.bmp");
			//ai text
			iText(210, 420, "Great! Which hotel do you want to stay?", GLUT_BITMAP_HELVETICA_12);
			iText(210, 400, "5 star, 4 star, 4 Star, Regular", GLUT_BITMAP_HELVETICA_12);
			// display_text("data/hotel.csv", 210, 380);
			//user text
		
			iText(300, 540, user_text_destination, GLUT_BITMAP_HELVETICA_12);
			iText(300, 520, "", GLUT_BITMAP_HELVETICA_12);
			//text box
			iText(190, 256, user_text_input ,GLUT_BITMAP_HELVETICA_12);
			break;

		case 4:			
			//iShowBMP(0, 0, "assets/chat2.bmp");
			//ai text
			iText(210, 420, "Okay how many days would you", GLUT_BITMAP_HELVETICA_12);
			iText(210, 400, " like to stay?", GLUT_BITMAP_HELVETICA_12);
			//user text
			iText(300, 540, user_text_hotel, GLUT_BITMAP_HELVETICA_12);
			iText(300, 540, "", GLUT_BITMAP_HELVETICA_12);
			//text box
			iText(190, 256, user_text_input ,GLUT_BITMAP_HELVETICA_12);
			break;
		
		case 6:
			//iShowBMP(0, 0, "assets/chat2.bmp");
			//ai text
			iText(210, 420, "Which transport would you prefer", GLUT_BITMAP_HELVETICA_12);
			iText(210, 400, " to use? ", GLUT_BITMAP_HELVETICA_12);
			iText(210, 380, " bus, car, train, air or boat. ", GLUT_BITMAP_HELVETICA_12);
			// display_text("data/transport.csv", 210, 360);
			//user text
			iText(300, 540, user_text_days, GLUT_BITMAP_HELVETICA_12);
			iText(300, 540, "", GLUT_BITMAP_HELVETICA_12);
			//text box
			iText(190, 256, user_text_input ,GLUT_BITMAP_HELVETICA_12);
			break;



		case 8:
			//iShowBMP(0, 0, "assets/chat2.bmp");
			//ai text
			iText(210, 420, " Excellent choice!", GLUT_BITMAP_HELVETICA_12);
			iText(210, 400, "Do you need a tour guide? ", GLUT_BITMAP_HELVETICA_12);
			iText(210, 380, "", GLUT_BITMAP_HELVETICA_12);
			// display_text("data/guide.csv", 210, 360);
			//user text
			iText(300, 540, user_text_transport, GLUT_BITMAP_HELVETICA_12);
			iText(300, 540, "", GLUT_BITMAP_HELVETICA_12);
			//text box
			iText(190, 256, user_text_input ,GLUT_BITMAP_HELVETICA_12);
			break;

		case 10:
			//iShowBMP(0, 0, "assets/chat2.bmp");
			//ai text
			iText(210, 420, " Excellent !!", GLUT_BITMAP_HELVETICA_12);
			iText(210, 400, "What is your budget? ", GLUT_BITMAP_HELVETICA_12);
			iText(210, 380, "", GLUT_BITMAP_HELVETICA_12);
			//user text
			iText(300, 540, user_text_guide, GLUT_BITMAP_HELVETICA_12);
			iText(300, 540, "", GLUT_BITMAP_HELVETICA_12);
			//text box
			iText(190, 256, user_text_input ,GLUT_BITMAP_HELVETICA_12);
			break;
		case 12:
			//iShowBMP(0, 0, "assets/chat2.bmp");
			//ai text
			iText(210, 420, " You have successfully created", GLUT_BITMAP_HELVETICA_12);
			iText(210, 400, "an order. Do you want to confirm? ", GLUT_BITMAP_HELVETICA_12);
			iText(210, 380, "Type yes to confirm", GLUT_BITMAP_HELVETICA_12);
			//user text
			iText(300, 540, user_text_budget, GLUT_BITMAP_HELVETICA_12);
			iText(300, 540, "", GLUT_BITMAP_HELVETICA_12);
			//text box
			iText(190, 256, user_text_input ,GLUT_BITMAP_HELVETICA_12);
			break;		
		case 14:
			//iShowBMP(0, 0, "assets/chat2.bmp");
			//ai text
			iText(210, 420, "Thank you for being with us", GLUT_BITMAP_HELVETICA_12);
			iText(210, 400, "Your order has been confirmed ", GLUT_BITMAP_HELVETICA_12);
			iText(210, 380, "Enjoy travelling with us.", GLUT_BITMAP_HELVETICA_12);
			//user text
			iText(300, 540, user_text_input_show, GLUT_BITMAP_HELVETICA_12);
			iText(300, 540, "", GLUT_BITMAP_HELVETICA_12);
			//text box
			iText(190, 256, user_text_input ,GLUT_BITMAP_HELVETICA_12);
			break;

		case 16:
			//iShowBMP(0, 0, "assets/chat2.bmp");
			//ai text
			iText(210, 420, "You already have an order", GLUT_BITMAP_HELVETICA_12);
			iText(210, 400, "Do you want to cancel it and ", GLUT_BITMAP_HELVETICA_12);
			iText(210, 380, "create a new order? Type yes to continue", GLUT_BITMAP_HELVETICA_12);
			//user text
			iText(300, 540, user_text_input_show, GLUT_BITMAP_HELVETICA_12);
			iText(300, 540, "", GLUT_BITMAP_HELVETICA_12);
			//text box
			iText(190, 256, user_text_input ,GLUT_BITMAP_HELVETICA_12);
			break;

		//show order summary
		case 18:
			//iShowBMP(0, 0, "assets/manage.bmp");
			if(showorder()){
				iText(210, 420, "You don't have any order", GLUT_BITMAP_HELVETICA_12);
				iText(210, 400, "Do you want to create a new order?", GLUT_BITMAP_HELVETICA_12);
				iText(210, 380, "Click home and go to \"plan\"", GLUT_BITMAP_HELVETICA_12);
			}
			else{
				//ai text
				iText(210, 480, "Your Order Summary:", GLUT_BITMAP_HELVETICA_12);
				iText(210, 460, "Destination: ", GLUT_BITMAP_HELVETICA_12);
				iText(210, 440, "Hotel: ", GLUT_BITMAP_HELVETICA_12);
				iText(210, 420, "Days: ", GLUT_BITMAP_HELVETICA_12);
				iText(210, 400, "Transport: ", GLUT_BITMAP_HELVETICA_12);
				iText(210, 380, "Guide: ", GLUT_BITMAP_HELVETICA_12);
				iText(210, 360, "Budget: ", GLUT_BITMAP_HELVETICA_12);
				iText(210, 340, "Do you want to cancel the order?", GLUT_BITMAP_HELVETICA_12);
				iText(210, 320, "Type yes to continue", GLUT_BITMAP_HELVETICA_12);
				//user text
				iText(300, 460, user_text_destination, GLUT_BITMAP_HELVETICA_12);
				iText(300, 440, user_text_hotel, GLUT_BITMAP_HELVETICA_12);
				iText(300, 420, user_text_days, GLUT_BITMAP_HELVETICA_12);
				iText(300, 400, user_text_transport, GLUT_BITMAP_HELVETICA_12);
				iText(300, 380, user_text_guide, GLUT_BITMAP_HELVETICA_12);
				iText(300, 360, user_text_budget, GLUT_BITMAP_HELVETICA_12);
				//text box	
				iText(190, 256, user_text_input ,GLUT_BITMAP_HELVETICA_12);
			}
			break;
		case 20:
			ai_chat_bot();

		}
		
}



void iDraw() {
	//place your drawing codes here
	iClear();// intro();
	if(intro_index!=39){
		intro();
	}
	else{		
		switch (page){
			case 0:
				user_type();
				break;
			case 1:
				login_page();
				break;
			case 2:
				signup_page();
				break;
			case 3:
				login_signup_page();
				break;
			case 4:
				forgot_pass();
				break;
			case 10:
				landing_page();
				break;
			case 11:
			
				discover_page();
				break;
			case 111:
				discover_type_loop();
				break;
			case 12:
				plan_a_trip_page();
				break;
			case 13:
				place();
				break;
			case 121:
				destination();
				break;
			case 122:
				transport();
				break;
			case 123:
				hotel();
				break;
			case 124:
				days();
				break;
			case 125:
				guide();
				break;
			case 126:
				budget();
				break;
			case 14:
				booking();
				break;
			case 15:
				mode = 1;
				if(initialize==0){
					initializing();
					initialize=1;
				}
			 	ai_chat_bot();
				break;
		}
	}
	// landing_page();
	
	iSetColor(0,0,0);
	if(auth)iText(10,10,"Press <F1> to Sign Out (Developed by Salem)",GLUT_BITMAP_HELVETICA_18);
	
}

//run python script
void run_python(){
	// Command to be executed
    char command[] = "python ai.py";

    // Execute the command
    int result = system(command);

    if (result == -1) {
        perror("Error executing command");
    }
	else{
		FILE *file = fopen("bot_response.txt", "r");
		while (file == NULL) {
			printf("Error opening the file.: run_python\n");
		}
		printf("python executed\n");
	}

}



/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		printf("%d,%d\n",mx,my);

// home button for user 1
		if(mx>=430&&mx<=616&&my>=31&&my<=100&&auth==1&&user==1){
			prev_page = page;
			page = 10;
		}
//back button
		if(mx>=100&&mx<=290&&my>=31&&my<=100){
			page = prev_page;
		}

	//for user selection
		if(mx >= 190 && mx <= (190+270) && page == 0)
		{
			if(my>=280 && my <= 330){
				prev_page = page;
				page = 1;
				user = 2;	
				mx=0;
				my=0;
			}
			
			if(my>=440 && my <= 490){
				prev_page = page;
				page = 1;
				user = 1;	
				mx=0;
				my=0;
			}
			
			if(my>=365 && my <= 412){
				prev_page = page;
				page = 1;
				user = 0;	
				mx=0;
				my=0;
			}
			printf("%d,%d\n",user,page);
		}

	//for login
		if(mx >= 231 && mx <= 409 && page == 1)
		{

			if(my>=468 && my <=520 ){
				mode=1;
				pass_in=0;
				usr_in = 1;
				mx=0;
				my=0;
				printf("usrin\n");

			}
			if(my>=380 && my <= 427){
				mode = 1;
				usr_in=0;
				pass_in=1;	
				mx=0;
				my=0;

				printf("passin\n");

			}

			if(my>=305 && my <= 349){

				mx=0;
				my=0;
				printf("%s,%s\n",usr_name,pass);
				auth = authenticateUser(user, usr_name, pass);
				if(auth==1){
					prev_page = page;
					page=10;
				}
				else{
					prev_page = page;
					free_user_text_input(usr_name);
					free_user_text_input(pass);
					free_user_text_input(security);
					pass_len=0;
					usr_len=0;
					page=4;
				}
			}
			
			
			if(my>=235 && my <= 285){
				prev_page = page;
				page=4;
				mx=0;
				my=0;
			}
			// else printf("%d,%d\n",mx,my);
		}

	//for signup and recover
		if(mx >= 231 && mx <= 409 && (page == 2||page==4))
		{

			if(my>=470 && my <=513 ){
				mode=1;
				pass_in=0;
				sec_in=0;
				usr_in = 1;
				mx=0;
				my=0;
				printf("usrin\n");

			}
			if(my>=380 && my <= 430){
				mode = 1;
				usr_in=0;
				sec_in=0;
				pass_in=1;	
				mx=0;
				my=0;

				printf("passin\n");

			}
			
			if(my>=300 && my <= 345){
				mode = 1;
				usr_in=0;
				pass_in=0;
				sec_in=1;	
				mx=0;
				my=0;

				printf("secin\n");

			}

			if(my>=232 && my <= 280 &&(page==2||page==4)){

				mx=0;
				my=0;

				if(page == 2)addUser(user, usr_name, pass, security);
				if(page == 4)recover_pass(user, usr_name, pass, security);
				page=1;
			}
			
			
			if(my>=235 && my <= 285){
				
				mx=0;
				my=0;
			}
			// else printf("%d,%d\n",mx,my);
		}


//discover type page
if(mx>11&&mx<90&&my>360&&my<435&&page==111){
	mx=0;
	my=0;
	if(discover_type_index==0){
		discover_type_index=4;
	}
	else{
		discover_type_index--;
	}
}

if(mx>600&&mx<700&&my>330&&my<435&&page==111){
	mx=0;
	my=0;
	if(discover_type_index==4){
		discover_type_index=0;
	}
	else{
		discover_type_index++;
	}
}

if(mx>151&&mx<600&&my>206&&my<600&&page==111){
	mx=0;
	my=0;
	page = 13;
}


//send message button
	if(mx>470&&mx<550&&my>225&&my<270&&page==14){
		mx=0;
		my=0;
		if(booking_text==0) strcpy(user_text_destination,user_text_input);
		if(booking_text==2) strcpy(user_text_hotel,user_text_input);
		if(booking_text==4) strcpy(user_text_days,user_text_input);
		if(booking_text==6) strcpy(user_text_transport,user_text_input);
		if(booking_text==8) strcpy(user_text_guide,user_text_input);
		if(booking_text==10) strcpy(user_text_budget,user_text_input);
		if(booking_text==12) strcpy(user_text_input_show,user_text_input);
		// if(booking_text==14) strcpy(user_text_days,user_text_input);
		if(booking_text==16) {
			strcpy(user_text_input_show,user_text_input);
			if(user_text_input_show[0]=='y'||user_text_input[0]=='Y'){
			cancelorder();
			addorder();
				
			}
		}
		if(booking_text==18) {
			strcpy(user_text_input_show,user_text_input);
			if((user_text_input_show[0]=='y'||user_text_input[0]=='Y'))cancelorder();
			free_user_text_input(user_text_input);
			free_user_text_input(user_text_input_show);
			free_user_text_input(user_text_destination);
			free_user_text_input(user_text_transport);
			free_user_text_input(user_text_hotel);
			free_user_text_input(user_text_days);
			free_user_text_input(user_text_guide);
			free_user_text_input(user_text_budget);
		}
		if(booking_text<=12)booking_text=booking_text+2;
		if(booking_text==14&&(user_text_input_show[0]=='y'||user_text_input[0]=='Y'))addorder();
		free_user_text_input(user_text_input);
	}

//for ai chat bot
	if(mx>470&&mx<550&&my>225&&my<270&&page==15){
		mode = 1;
		mx=0;
		my=0;
		remove("user_input.txt");
		FILE *file = fopen("user_input.txt", "w+");
		if(file == NULL){
			printf("Error opening the file.: user_input\n");
			return;
		}
		fprintf(file, "%s\n", user_text_input);
		fclose(file);
		run_python();
		free_user_text_input(user_text_input);
		
	}

//Home page buttons
	//plan page
		if(mx>180&&mx<350&&my>415&&my<585&&page==10&&auth==1){
				mx=0;
				my=0;
			prev_page = page;
			booking_text=0;
			page=14;
			
		}
	//discover page
		if(mx>385&&mx<560&&my>415&&my<585&&page==10&&auth==1){
				mx=0;
				my=0;
			prev_page = page;
			page=15;
		}
	//budget page
		if(mx>180&&mx<350&&my>215&&my<370&&page==10&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				page=121;
			}
	//manage page
		if(mx>385&&mx<560&&my>215&&my<370&&page==10&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				page=14;
				booking_text=18;
			}


//discover page buttons
	//plan page
		if(mx>180&&mx<350&&my>415&&my<585&&page==11&&auth==1){
				mx=0;
				my=0;
			prev_page = page;
			page=13;
		}
	//discover page
		if(mx>385&&mx<560&&my>415&&my<585&&page==11&&auth==1){
				mx=0;
				my=0;
			prev_page = page;
			page=13;
		}
	//budget page
		if(mx>180&&mx<350&&my>215&&my<370&&page==11&&auth==1){
				mx=0;
				my=0;
			prev_page = page;
			page=13;
		}
	//manage page
		if(mx>385&&mx<560&&my>215&&my<370&&page==11&&auth==1){
				mx=0;
				my=0;
			prev_page = page;
			page=13;
		}
	//places button
		//previous
		if(mx>180&&mx<350&&my>215&&my<249&&page==13&&auth==1){
				mx=0;
				my=0;
			if(place_index==0){
				place_index=5;
			}
			else{
				place_index--;
			}
		}
		//next
		if(mx>385&&mx<560&&my>215&&my<250&&page==13&&auth==1){
				mx=0;
				my=0;
			// printf("%s\n",place_image[place_index]);
			if(place_index==6){
				place_index=1;
			}
			else{
				place_index++;
			}
		}

		//select button
		if(mx>287&&mx<450&&my>270&&my<300&&page==13&&auth==1){
				mx=0;
				my=0;
			prev_page = page;
			page=121;
		}


//budget page buttons
	//select destination
		//dhaka
		if(mx>150&&mx<330&&my>430&&my<481&&page==121&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				place_budget=10;
				page=122;
			}
		//coxs bazar
		if(mx>150&&mx<330&&my>340&&my<390&&page==121&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				place_budget = 50;
				page=122;
			}
		//barishal
		if(mx>150&&mx<330&&my>250&&my<290&&page==121&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				place_budget=30;
				page=122;
			}
		//sylhet
		if(mx>390&&mx<571&&my>430&&my<481&&page==121&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				place_budget=18;
				page=122;
			}
		//khulna
		if(mx>390&&mx<565&&my>340&&my<390&&page==121&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				place_budget=10;
				page=122;
			}
		//Ctg
		if(mx>390&&mx<570&&my>250&&my<290&&page==121&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				place_budget=12;
				page=122;
			}
	

	//select transport
		//car
		if(mx>150&&mx<330&&my>430&&my<481&&page==122&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				transport_budget=300;
				page=123;
			}
		//plane
		if(mx>150&&mx<330&&my>340&&my<390&&page==122&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				transport_budget=400;
				page=123;
			}
		//air
		if(mx>150&&mx<330&&my>250&&my<290&&page==122&&auth==1){
				mx=0;
				my=0;
				// prev_page = page;
				// page=123;
			}
		//bus
		if(mx>390&&mx<571&&my>430&&my<481&&page==122&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				transport_budget=200;
				page=123;
			}
		//boat
		if(mx>390&&mx<565&&my>340&&my<390&&page==122&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				transport_budget=100;
				page=123;
			}
		//bike
		if(mx>390&&mx<570&&my>250&&my<290&&page==122&&auth==1){
				mx=0;
				my=0;
				// prev_page = page;
				// page=123;
			}


	//select hotel
		//5 star
		if(mx>150&&mx<330&&my>430&&my<481&&page==123&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				hotel_budget=2000;
				page=124;
			}
		//3 star
		if(mx>150&&mx<330&&my>340&&my<390&&page==123&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				hotel_budget=1000;
				page=124;
			}
		//0 star
		if(mx>150&&mx<330&&my>250&&my<290&&page==123&&auth==1){
				mx=0;
				my=0;
				// prev_page = page;
				// page=124;
			}
		//4 star
		if(mx>390&&mx<571&&my>430&&my<481&&page==123&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				hotel_budget=1500;
				page=124;
			}
		//regular
		if(mx>390&&mx<565&&my>340&&my<390&&page==123&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				hotel_budget=500;
				page=124;
			}
		//2 star
		if(mx>390&&mx<570&&my>250&&my<290&&page==123&&auth==1){
				mx=0;
				my=0;
				// prev_page = page;
				// page=124;
			}
	
	//select days
		//1 day
		if(mx>150&&mx<330&&my>430&&my<481&&page==124&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				days_budget=1;
				page=125;
			}
		//3 day
		if(mx>150&&mx<330&&my>340&&my<390&&page==124&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				days_budget=3;
				page=125;
			}
		//5 day
		if(mx>150&&mx<330&&my>250&&my<290&&page==124&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				days_budget=5;
				page=125;
			}
		//2 day
		if(mx>390&&mx<571&&my>430&&my<481&&page==124&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				days_budget=2;
				page=125;
			}
		//4 day
		if(mx>390&&mx<565&&my>340&&my<390&&page==124&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				days_budget=4;
				page=125;
			}
		//6 day
		if(mx>390&&mx<570&&my>250&&my<290&&page==124&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				days_budget=6;
				page=125;
			}

	//select guide
		//12 hour
		if(mx>150&&mx<330&&my>430&&my<481&&page==125&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				guide_budget=1200;
				page=126;
			}
		//6 hour
		if(mx>150&&mx<330&&my>340&&my<390&&page==125&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				guide_budget=600;
				page=126;
			}
		//None
		if(mx>150&&mx<330&&my>250&&my<290&&page==125&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				guide_budget=0;
				page=126;
			}
		//8 hour
		if(mx>390&&mx<571&&my>430&&my<481&&page==125&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				guide_budget=800;
				page=126;
			}
		//4 hour
		if(mx>390&&mx<565&&my>340&&my<390&&page==125&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				guide_budget=400;
				page=126;
			}
		//None
		if(mx>390&&mx<570&&my>250&&my<290&&page==125&&auth==1){
				mx=0;
				my=0;
				prev_page = page;
				guide_budget=0;
				page=126;
			}



//sign -in up page buttons
		if(mx>210&&mx<515&&my>380&&my<450&&page==3){
				mx=0;
				my=0;
			prev_page = page;
			page=2;
		}
		if(mx>215&&mx<520&&my>260&&my<320&&page==3){
				mx=0;
				my=0;
			prev_page = page;
			page=1;
		}


	}
			
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
	mx=0;
	my=0;
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {

	int i;	

	if(mode == 1 && key!=0){

		//text input for chat
		if(page==14||page==15){
			if(key == '\b')
			{
				if(user_text_len > 0)
				{
					user_text_len--;
					user_text_input[user_text_len] = 0;
				}
			}
			else
			{
				user_text_input[user_text_len] = key;
				user_text_len++;
			}
		}




		//user name input login page
		if(usr_in==1 && page==1){
			printf("usrin = 1\n");
			if(key == '\b')
			{
				if(usr_len > 0)
				{
					usr_len--;
					usr_name[usr_len] = 0;
				}
			}
			else
			{
				usr_name[usr_len] = key;
				usr_len++;
			}
		}

		if(pass_in==1 && page==1){
			printf("passin = 1\n");
			if(key == '\b')
			{
				if(pass_len > 0)
				{
					pass_len--;
					pass[pass_len] = 0;
				}
			}
			else
			{
				pass[pass_len] = key;
				pass_len++;
			}
		}


		//user name input signup page
		// //user name input login page
		if(usr_in==1 && (page==2||page==4)){
			printf("usrin = 1\n");
			if(key == '\b')
			{
				if(usr_len > 0)
				{
					usr_len--;
					usr_name[usr_len] = 0;
				}
			}
			else
			{
				usr_name[usr_len] = key;
				usr_len++;
			}
		}
					
		if(pass_in==1 && (page==2||page==4)){
			printf("passin = 1\n");
			if(key == '\b')
			{
				if(pass_len > 0)
				{
					pass_len--;
					pass[pass_len] = 0;
				}
			}
			else
			{
				pass[pass_len] = key;
				pass_len++;
			}
		}


		if(sec_in==1 && (page==2||page==4)){
			printf("secin = 1\n");
			if(key == '\b')
			{
				if(sec_len > 0)
				{
					sec_len--;
					security[sec_len] = 0;
				}
			}
			else
			{
				security[sec_len] = key;
				sec_len++;
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
void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	if(key==GLUT_KEY_F1){
		auth = 0;
		free_user_text_input(user_text_input);
		free_user_text_input(user_text_input_show);
		free_user_text_input(user_text_destination);
		free_user_text_input(user_text_transport);
		free_user_text_input(user_text_hotel);
		free_user_text_input(user_text_days);
		free_user_text_input(user_text_guide);
		free_user_text_input(user_text_budget);
		free_user_text_input(usr_name);
		free_user_text_input(pass);
		free_user_text_input(security);
		auth = 0;
		page = 3;
		usr_len=0;
		pass_len=0;
		sec_len=0;

		// printf("F1\n");
	}
	//place your codes for other keys here
}


int main() {
	//place your own initialization codes here.
	usr_len=0;
	pass_len=0;
	iInitialize(720, 720, "Travel Adviser");
	return 0;
}