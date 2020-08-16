/* 
COPYRIGHT 2010, ALL RIGHT RESERVED 
AUTHOR BADDE LIYANAGE DON DILANGA. bld@dilanga.com


*/


#include <iostream.h>//include the iostream header file where all necessary objects included which manipulate IO(input/output) operations
#include <conio.h> //include conio header file which uses to manipulate screen affairs 
#include <fstream.h> //fstream standards for file stream and a derived class of iostream class and used to file handling 
#include <process.h> //process class is for handling processes related to processor.
#include <iomanip.h>//input /output manipulator which is an extended class where mentions fewer of io handling objects.
#include <string.h> //string class to manipulate strings and as a replacer for char arrays.

//functions and procedures prototypes
void mainmenu();
void doctors();
void patients();
void about();

void addnewpatient();
void admissionform();
void showallpatients();                               
void modifypatient();

void searchpatientMenu();
void searchpatient(char* searchParam);
void searchSubForum(char*param,char*query);
void searchRetrieve(fstream &fileIO); //parameter is declared as a reference so variable assign to this can be indrecitly modified

void searchdoc(char* searchParam);
void searchdocMenu();
void searchdocSubForum(char* param,char* query);
void searchdocRetrieve(fstream &fileIO); //parameter is declared as a reference so variable assign to this can be indrecitly modified

void addnewdoc();
void modifydoc();
void showalldoc();

void newRegAdmin();
void auth(); // use authonication prototype

const char* dataBaseName ="Data01.dat";
const char* dataBaseNameP ="Data02.dat";
const char* dataBaseNameA = "Data03.dat";
const int sideMsg_x = 50;
const int sideMsg_y = 12;
const int maxValue=50;
int flag;//flag will determine the authrization

//patient structers 
struct patient{
  char pid[maxValue],pfirstname[maxValue],
  psecondname[maxValue],paddress[maxValue],
  ptele[maxValue],pbirthday[maxValue],
  pdoctreated[maxValue],
  page[maxValue],
  pdiagnosis[maxValue],pdoctorname[maxValue],
  pspecification[maxValue],
  padmissiondate[maxValue],pward[maxValue],
  ptotalfee[maxValue],pdocfee[maxValue],paddnum[maxValue],
  phospitalfee[maxValue],ptotal[maxValue];
};
//doctor structers 
struct doctor{
  char did[maxValue],dname[maxValue],dspecialfield[maxValue],daddress[maxValue],dtele[maxValue],demail[maxValue],dweb[maxValue];
};
//new registration struct
struct newRegistration{
  char userName[maxValue],passWord[maxValue],authority[maxValue];
};

//main function where program begins from
int main()
{
   textcolor(WHITE);//change the text colour to white
   textbackground(BLUE);//change the back ground colour of the console 
    clrscr();//clear the screen

    auth();
 //mainmenu();

 getch();//wait till user type an input from the keyword then if it doesn't return to somewhere extract and discard
 return 0;//return 0 to the main function by telling program is done.
}
//----------------------------------------AUTHORIZATION WIZARD-------------------------
void auth()
{
  textcolor(WHITE);
   textbackground(BLUE);
    clrscr();

  //check the database
  ifstream fileRead; //declared an object from the ifstream class to manipulate the files
  fileRead.open(dataBaseNameA,ios::in|ios::binary);//open the the file in binary mode and load data into the input stream
  if(fileRead.fail())//fail will return false if program couldn't open the file
  {

   textcolor(RED);
   textbackground(WHITE);
   clrscr();

    gotoxy(10,12);//go to the 10,12 position on the screen
    textattr(RED+(WHITE<<4));
    cprintf("%s","No Database is found ");
    cout << "\n";
    gotoxy(10,14);
    textattr(RED+(WHITE<<4));
    cprintf("%s","so it will create then you neeed to register as an admin frist ");
    cout << "\n";
    gotoxy(10,16);
    textattr(RED+(WHITE<<4));
    cprintf("%s","in order to proceed");
    getch();
    flag=1;
    newRegAdmin();
  }else
  {

   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();
   //check is there any values in the database
   if(fileRead.peek() == -1)//-1 will return if the stream is empty ,well the open() function loads data into the stream and those values will represnet as either binary or text if non of characters found in the stream peek() will return -1  if found it will return corresponding value
   {
      textcolor(BLACK);
   	textbackground(WHITE);
   	clrscr();
      gotoxy(2,15);
   	cout << "Database is filled with empty shades please register as an admin to proceed" << endl;
      getch();
      newRegAdmin();
   }


  char userName[maxValue],passWord[maxValue];
  newRegistration newReg;


  gotoxy(15,10);
  textattr(YELLOW+(BLUE<<4));
  cprintf("%s","WELCOME.! PLEASE CONFIRM YOUR AUTHORITY TO PROCEED");

  gotoxy(15,12);
  textattr(GREEN+(BLUE<<4));
  cprintf("%s","What is your User Name.?");
  cin.getline(userName,maxValue);


  gotoxy(15,16);
  textattr(GREEN+(BLUE<<4));
  cprintf("%s","What is your password.?");
  cin.getline(passWord,maxValue);


    while(fileRead.read((char*)&newReg,sizeof newReg))
    {
  	    if(!strcmp(userName,newReg.userName) && !strcmp(passWord,newReg.passWord)) //check the password and user name and both should be matched in order to proceed
       {
        textcolor(WHITE);
   	  textbackground(BLUE);
    	  clrscr();
        gotoxy(10,12);
  		  textattr(GREEN+(BLUE<<4));
  		  cprintf("%s","Welcome User is Found!"); //admin ,office,docviewr -> Three user types available
        cout << "\n";
        gotoxy(10,14);
        cout << "User Name is " << newReg.userName << endl;
        gotoxy(10,16);
        cout << "User Type is " << newReg.authority<< endl;
        cout << "\n";
        getch();

      	if(!strcmp(newReg.authority,"admin"))
      	{
           flag = 1;
           mainmenu();
           break;
      	}

         else if(!strcmp(newReg.authority,"office"))
         {
           flag = 2;
           mainmenu();
           break;
         }

         else if(!strcmp(newReg.authority,"docviewer"))
         {
           flag = 3;
           doctors();
           break;
         }
         else
         {
          cout << "Strange Something wrong has happened and program will close" << endl;
          exit(0);
         }


       }

    }
    if(fileRead.eof())
    {
      textcolor(WHITE);
      textbackground(WHITE);
      clrscr();

      gotoxy(10,12);   //change the location on the dos window
      textattr(RED+(WHITE<<4));  //text color change see it was described well on somewhere within the codes
      cprintf("%s","No User name has found ");
      cout << "\n";
      gotoxy(10,14);
      textattr(RED+(WHITE<<4));
      cprintf("%s","or may be you have typed the password incorrectly ");
      cout << "\n";
      gotoxy(10,16);
      textattr(RED+(WHITE<<4));
      cprintf("%s","so please enter your details and try again");
      cout << "\n";
      getch();
      auth();
    }

  }

}


//------------------------------DOCTOR MENU---------------------
void doctors()
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();

 gotoxy(15,8);
 textattr(YELLOW+(BLUE<<4));
 cprintf("%s","Doctors Menu");

 //creating a console menu
 const int max = 6;
 int yloc[max] = {10,13,15,18,21,24};
 int i=0;
 char* words[max] = {"Add New Doctor","Modify Doctor","Search","Show All Doctors","Back","EXIT"};

  //make the dash lines which devide the description and the menu options
  for(int gotoxy_y=6;gotoxy_y<24;gotoxy_y++)
  {
   	gotoxy(40,gotoxy_y);
      textattr(YELLOW+(BLUE<<4));
      cprintf("%s","|");
  }

 while(i<max)
 {
   if(i==0)
   {
    gotoxy(15,yloc[i]);
    textattr(BLUE + (YELLOW<<4));
    cprintf("%s",words[i]);
   }else
   {
    gotoxy(15,yloc[i]);
    textattr(WHITE + (BLUE<<4));
    cprintf("%s",words[i]);
   }
   i++;
 }
 i=0;
 //initial message
 gotoxy(sideMsg_x,sideMsg_y);
 cprintf("%s","You can add new doctors     ");

 while(1)
 {
  //fill the color of each line
  if(i>max-1 || i<0)i=0; //reset the i if it exceed the 2(max value)
  gotoxy(15,yloc[i]);
  textattr(BLUE + (YELLOW<<4));
  cprintf("%s",words[i]);

  switch(getch())
  {
   case 113:
   exit(0);//exit when press the q
   break;

   case 80: if(max-1>i){   //when press the down arrow (ASCII value for down arrow is 80)
    //recolour
    gotoxy(15,yloc[i]);
    textattr(WHITE + (BLUE<<4));
    cprintf("%s",words[i]);
    i++;
          switch(i){ //details show in here!!
         	case 1:
            	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can Modify Doctors     "); break; //modify
            case 2:
            	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can search Doctors     "); break;   //search
            case 3:
            	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can view all doctors   "); break;   //showall
            case 4:
             	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","Go back to mainmenu        "); break;  ///go to back
            case 5:
             	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","Directly Exit from System  "); break;  //exit
            default:
                gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","                           "); break;
            }

    }break;

   case 72: if(i>0){  //shwn press the up aroow (ASCII value for down arrow is 72)
    //recolor
    gotoxy(15,yloc[i]);
    textattr(WHITE + (BLUE<<4));
    cprintf("%s",words[i]);
    i--;
         switch(i){ //details show in here!!
         	case 0:
            	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can Add Doctors        "); break; //add doctors
            case 1:
            	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can Modify Doctors     "); break;   //modify
            case 2:
            	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can Search doctors     "); break;   //Search
            case 3:
             	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can show all           "); break;  ///show all
            case 4:
             	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","Go back to mainmenu        "); break;  //exit
            default:
                gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","                           "); break;
            }


    }break;

   case 27: //when press ESC
   	mainmenu();
      break;

   case 13: //call to appropriate procedures
   if(i==0){//add new doctor
    if(flag == 3)
    {
     textcolor(RED);
     textbackground(WHITE);
     clrscr();
     gotoxy(1,12);
     cout << "OF COURSE YOU CAN'T ADD DOCTORS DUE TO YOUR USER LEVEL SO PLEASE CONTACT SYSTEM ADMINISTRATOR ,KEEP TRYING WILL CAUSE TO KEEP ASKING THE SAME QUESTION AGAIN - \nTHANKS" << endl;
     getch();
     doctors();
    }
    addnewdoc();
   }

   else if(i==1){  //modify doctors
   if(flag == 3)
    {
     textcolor(RED);
     textbackground(WHITE);
     clrscr();
     gotoxy(1,12);
     cout << "OF COURSE YOU CAN'T ADD DOCTORS DUE TO YOUR USER LEVEL SO PLEASE CONTACT SYSTEM ADMINISTRATOR ,KEEP TRYING WILL CAUSE TO KEEP ASKING THE SAME QUESTION AGAIN - \nTHANKS" << endl;
     getch();
     doctors();
    }
    modifydoc();
   }

   else if(i==2){ //search
    searchdocMenu();
   }

   else if(i==3){ //show all doctors
    showalldoc();
   }

   else if(i==4){ //back button
   if(flag == 3)
    {
     textcolor(RED);
     textbackground(WHITE);
     clrscr();
     gotoxy(1,12);
     cout << "OF COURSE YOU CAN'T GO TO MAIN MENU DUE TO YOUR USER LEVEL SO PLEASE CONTACT SYSTEM ADMINISTRATOR ,KEEP TRYING WILL CAUSE TO KEEP ASKING THE SAME QUESTION AGAIN - \nTHANKS" << endl;
     getch();
     doctors();
    }
   mainmenu();
   }

   else if(i==5){ //show all doctors
    exit(0);
   }

   break;
  }
 }

}
 //---------------------------------------PATIENT MENU--------------------------
void patients()
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();

 gotoxy(15,6);
 textattr(YELLOW+(BLUE<<4));
 cprintf("%s","Patient Menu");

 //creating a console menu
 const int max = 6;
 int yloc[max] = {9,12,14,18,20,23};
 int i=0;
 char* words[max] = {"Add New Patient","Search Patient","Modify Patient","Admission Details","Show All Patients","Back"};

  //make the dash lines which devide the description and the menu options
  for(int gotoxy_y=6;gotoxy_y<24;gotoxy_y++)
  {
   	gotoxy(40,gotoxy_y);
      textattr(YELLOW+(BLUE<<4));
      cprintf("%s","|");
  }

 while(i<max)//0,1,2,3,4,5,<6  //initializer
 {
   if(i==0)
   {
    gotoxy(15,yloc[i]);
    textattr(BLUE + (YELLOW<<4));
    cprintf("%s",words[i]);
   }else
   {
    gotoxy(15,yloc[i]);
    textattr(WHITE + (BLUE<<4));
    cprintf("%s",words[i]);
   }
   i++;
 }
 i=0;
 //initial message
 gotoxy(sideMsg_x,sideMsg_y);
 cprintf("%s","You can add new patients    ");

 while(1)
 {
  //fill the color of each line
  gotoxy(15,yloc[i]);
  textattr(BLUE + (YELLOW<<4));
  cprintf("%s",words[i]);

  switch(getch())
  {
   case 113:
   exit(0);//exit when press the q
   break;

   case 80: if(max-1>i){
    //recolour
    gotoxy(15,yloc[i]);
    textattr(WHITE + (BLUE<<4));
    cprintf("%s",words[i]);
    i++;
    		switch(i){ //details show in here!!
         	case 1:
            	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can search patients    "); break;  //search
            case 2:
            	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can modify patients    "); break;   //modify
            case 3:
            	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can print admissions   "); break;   //admission
            case 4:
             	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can show all patients  "); break;  //show all
            case 5:
             	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","Go back to mainmenu        "); break;  //back
            default:
                gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","                           "); break;
            }
    }break;

   case 72: if(i>0){
    //recolor
    gotoxy(15,yloc[i]);
    textattr(WHITE + (BLUE<<4));
    cprintf("%s",words[i]);
    i--;

           switch(i){ //details show in here!!
         	case 0:
            	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can add patients       "); break;   //add
            case 1:
            	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can search patients    "); break;  //search
            case 2:
            	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can modify patients    "); break;   //modify
            case 3:
             	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can print admission    "); break;   //admission
            case 4:
             	 gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","You can show all patients  "); break;  //show all
            default:
                gotoxy(sideMsg_x,sideMsg_y);
                cprintf("%s","                           "); break;
            }

    }break;
  /*
    void addnewpatient(void);
    void searchpatientMenu(void);
    void modifypatient(void);
	 void admissionform(void);
    void showallpatients(void);

  */
  case 27: //if user pressed the ESC go back to the mainmenu
  		mainmenu();
      break;

   case 13: //call to appropriate procedures
   if(i==0){  //patients
   	addnewpatient();
   }

   else if(i==1){
   	searchpatientMenu();
   }

   else if(i==2){
    	modifypatient();
   }

   else if(i==3){
   	admissionform();//to create the admission form
   }

   else if(i==4){
   	showallpatients();
   }

   else if(i==5){//back to main menu
   mainmenu();
   }

   break;
  }
 }



}
 //-----------------------------------------ABOUT MENU-------------------------------
void about()
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();

 gotoxy(15,10);
 textattr(YELLOW+(BLUE<<4));
 cprintf("%s","ABOUT HEART BEAT SYSTEM");

 gotoxy(15,12);
 textattr(WHITE+(BLUE<<4));
 cprintf("%s","Developed by BLD Dilanga for ICBT /2010,11,21");
 cout << "\n";
 gotoxy(15,14);
 cprintf("%s","ICBT Assignment HND/Batch/04/ Computing");
 cout << "\n";
 gotoxy(15,16);
 cprintf("%s","Email : bld@dilanga.com");
 cout << "\n";

 gotoxy(15,24);
 textattr(BLUE + (YELLOW<<4));
 cprintf("%s","BACK");

 while(1)
 {
  //fill the color of each line
  gotoxy(15,24);
  textattr(BLUE + (YELLOW<<4));
  cprintf("%s","BACK");

  switch(getch())
  {
   case 13://about back when enter cause there is only one option
   mainmenu();
   	break;
   case 27: //patient back when press ESC
   mainmenu();
   	break;
  }
 }

}
//------------------------------------------------MAIN MENU---------------------------------
void mainmenu()
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();

 gotoxy(15,10);
 textattr(YELLOW+(BLUE<<4));
 cprintf("%s","Welcome to ");
 textattr(RED+(WHITE<<4));
 cprintf("%s","Heart Beat");
 textattr(YELLOW+(BLUE<<4));
 cprintf("%s"," Hospital Computer System");

 //creating a console menu
 const int max = 5;
 int yloc[max] = {13,16,18,21,24};
 int i=0;
 char* words[max] = {"Patients","Doctors","About","New Registration","Exit"};

 while(i<max)//initialized the menu items
 {
   if(i==0)
   {
    gotoxy(15,yloc[i]);
    textattr(BLUE + (YELLOW<<4));
    cprintf("%s",words[i]);
   }else
   {
    gotoxy(15,yloc[i]);
    textattr(WHITE + (BLUE<<4));
    cprintf("%s",words[i]);
   }
   i++;
 }
 i=0;

 while(1)//loop contiue untill user press appropriate command
 {
  //fill the color of each line
  if(i>4 || i<0)i=0; //reset the i if it exceed the 2(max value)
  gotoxy(15,yloc[i]);
  textattr(BLUE + (YELLOW<<4));
  cprintf("%s",words[i]);

  switch(getch())//capture the which button was user pressed
  {
   case 113: //means q (simple q)
   exit(0);//exit when press the q
   break;

   case 80: if(max-1>i){//80 means down arrow in ASCII
    //recolour
    gotoxy(15,yloc[i]);
    textattr(WHITE + (BLUE<<4));
    cprintf("%s",words[i]);
    i++;
    }break;

   case 72: if(i>0){ //means up arrow in ASCII
    //recolor
    gotoxy(15,yloc[i]);
    textattr(WHITE + (BLUE<<4));
    cprintf("%s",words[i]);
    i--;
    }break;

   case 27: //means Escape button (NOT back!)
   exit(0);//if user pressed the return while staying in the menu which will cause to exit the program

   case 13: //call to appropriate procedures //13 means Return Carrige button
   if(i==0){  //patients
   patients();
   }

   else if(i==1){ //doctors
   doctors();
   }

   else if(i==2){
   about();
   }

   else if(i==3){
   if(flag != 1)
   {
    textcolor(RED);
    textbackground(WHITE);
    clrscr();
    gotoxy(2,10);
    cout << "YOU ARE NO AUTHORIZED TO REGISTER NEW USERS INTO THE SYSTEM PLEASE CONTACT THE SYSTEM ADMINISTRATOR" << endl;
    getch();
    mainmenu();
   }
   newRegAdmin();
   }

   else if(i==4){
   gotoxy(15,30);
   textattr(YELLOW + (BLUE<<4));
   cprintf("%s ","your are about to exit press any key to exit proceed");
   getch();
   exit(0);
   }

   break;
  }
 }

}
 //----------------------------------------NEW Registration/--------------------------------------
void newRegAdmin()
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();

   newRegistration newRegOne;
   ofstream fileWrite;
   fileWrite.open(dataBaseNameA,ios::out|ios::app|ios::binary);
   if(fileWrite.fail()){ cout << "Error Occured in the Database " << endl;getch();mainmenu();}

   gotoxy(5,12);
   textattr(WHITE + (BLUE<<4));
   cprintf("%s ","Welcome to New Registration Wizard Press any Key to proceed or ESC to back");
   if(getch()==27)mainmenu();

   clrscr();
   cout << "What is your user name" << endl;
   cin.getline(newRegOne.userName,maxValue);
   cout << "What is your password" << endl;
   cin.getline(newRegOne.passWord,maxValue);
   cout << "\n";
   textattr(WHITE + (BLUE<<4));
   cprintf("%s ","Select the Authority of the user from following menu");


   //creating a console menu
 const int max = 3;
 int yloc[max] = {13,16,18};
 int i=0;
 char* words[max] = {"Admin","Doc Viewer","Office"};

 while(i<max)
 {
   if(i==0)
   {
    gotoxy(max,yloc[i]);
    textattr(BLUE + (YELLOW<<4));
    cprintf("%s",words[i]);
   }else
   {
    gotoxy(max,yloc[i]);
    textattr(WHITE + (BLUE<<4));
    cprintf("%s",words[i]);
   }
   i++;
 }
 i=0;

 while(1)
 {
  //fill the color of each line
  if(i>2 || i<0)i=0; //reset the i if it exceed the 2(max value)
  gotoxy(max,yloc[i]);
  textattr(BLUE + (YELLOW<<4));
  cprintf("%s",words[i]);

  switch(getch())
  {
   case 113:
   exit(0);//exit when press the q
   break;

   case 80: if(max-1>i){
    //recolour
    gotoxy(max,yloc[i]);
    textattr(WHITE + (BLUE<<4));
    cprintf("%s",words[i]);
    i++;
    }break;

   case 72: if(i>0){
    //recolor
    gotoxy(max,yloc[i]);
    textattr(WHITE + (BLUE<<4));
    cprintf("%s",words[i]);
    i--;
    }break;

   case 13: //call to appropriate procedures
   if(i==0){//admins
    strcpy(newRegOne.authority,"admin");
    cout << "\n";
    gotoxy(17,20);
    cout << "\n";gotoxy(17,20);
    cout << "Confirm your details \n " << endl;gotoxy(17,21);
    cout << "User Name is            :" << newRegOne.userName << endl;gotoxy(17,22);
    cout << "User Password is        :" << newRegOne.passWord << endl;gotoxy(17,23);
    cout << "User Authority is       :" << newRegOne.authority << endl;gotoxy(17,24);
    cout << "\nPress any key to go to menu" << endl;
    getch();
    //update the database
    fileWrite.write((char*)&newRegOne,sizeof newRegOne);//write details at end of the final record
    fileWrite.clear();
    fileWrite.close();
    mainmenu();
   }

   else if(i==1){  //docviewer
    strcpy(newRegOne.authority,"docviewer");
    cout << "\n";gotoxy(17,20);
    cout << "Confirm your details \n " << endl;gotoxy(17,21);
    cout << "User Name is            :" << newRegOne.userName << endl;gotoxy(17,22);
    cout << "User Password is        :" << newRegOne.passWord << endl;gotoxy(17,23);
    cout << "User Authority is       :" << newRegOne.authority << endl;gotoxy(17,24);
    cout << "\nPress any key to go to menu" << endl;
    getch();
    //update the database
    fileWrite.write((char*)&newRegOne,sizeof newRegOne);//write details at end of the final record
    fileWrite.clear();
    fileWrite.close();
    mainmenu();
   }

   else if(i==2){  //office
    strcpy(newRegOne.authority,"office");
    cout << "\n";gotoxy(17,20);
    cout << "Confirm your details \n " << endl;gotoxy(17,21);
    cout << "User Name is            :" << newRegOne.userName << endl;gotoxy(17,22);
    cout << "User Password is        :" << newRegOne.passWord << endl;gotoxy(17,23);
    cout << "User Authority is       :" << newRegOne.authority << endl;gotoxy(17,24);
    cout << "\nPress any key to go to menu" << endl;
    getch();
    //update the database
    fileWrite.write((char*)&newRegOne,sizeof newRegOne);//write details at end of the final record
    fileWrite.clear();
    fileWrite.close();
    mainmenu();
   }

  }

 }


}
//-------------------------PATIENT--------------------------------
//---------------------ADD NEW PATIENT------------------------
void addnewpatient()
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();        //clear the screen for DOS

 patient patientOne;

 cout<<"ADD NEW PATIENT WIZARD"<<endl;
 cout<<"press any key to continue or ESC to back"<<endl;

 if(getch() == 27)patients();

 //ask the details to enter from the users and write to the struct
 cout << "What is the patient ID.?"<<endl;
 cin.getline(patientOne.pid,maxValue);

 cout << "What is the patient first name.?"<<endl;
 cin.getline(patientOne.pfirstname,maxValue);

 cout << "What is the patient second name.?"<<endl;
 cin.getline(patientOne.psecondname,maxValue);

 cout << "What is the patient address.?"<<endl;
 cin.getline(patientOne.paddress,maxValue);

 cout << "What is the patient telephone number.?"<<endl;
 cin.getline(patientOne.ptele,maxValue);

 cout << "What is the patient birthday.?"<<endl;
 cin.getline(patientOne.pbirthday,maxValue);

 cout << "What is the patient's doctor treated.?"<<endl;
 cin.getline(patientOne.pdoctreated,maxValue);
                                                       //------>
 cout << "What is the patient age.?"<<endl;
 cin.getline(patientOne.page,maxValue);

 cout << "What is the patient diagnosis.?"<<endl;
 cin.getline(patientOne.pdiagnosis,maxValue);

 cout << "What is the name of the doctor.?"<<endl;
 cin.getline(patientOne.pdoctorname,maxValue);

 cout << "What is the Specification.?"<<endl;
 cin.getline(patientOne.pspecification,maxValue);

 cout << "What is the Admission Date.?"<<endl;
 cin.getline(patientOne.padmissiondate,maxValue);

 cout << "What is the hospital fee.?"<<endl;
 cin.getline(patientOne.phospitalfee,maxValue);

 cout << "What is the doctor fee.?"<<endl;
 cin.getline(patientOne.pdocfee,maxValue);

 cout << "What is the total fee.?"<<endl;
 cin.getline(patientOne.ptotalfee,maxValue);

 cout << "What is the admission number"<<endl;
 cin.getline(patientOne.paddnum,maxValue);

 cout << "What is the ward number.?"<<endl;
 cin.getline(patientOne.pward,maxValue);

 //validation
 if(!strcmp(patientOne.pid,"\0") || !strcmp(patientOne.pfirstname,"\0") || !strcmp(patientOne.psecondname,"\0")|| !strcmp(patientOne.paddress,"\0")|| !strcmp(patientOne.ptele,"\0")|| !strcmp(patientOne.pbirthday,"\0")|| !strcmp(patientOne.pdoctreated,"\0") || !strcmp(patientOne.page,"\0") || !strcmp(patientOne.pdiagnosis,"\0")|| !strcmp(patientOne.pdoctorname,"\0")|| !strcmp(patientOne.pspecification,"\0")|| !strcmp(patientOne.padmissiondate,"\0")|| !strcmp(patientOne.pward,"\0")|| !strcmp(patientOne.phospitalfee,"\0")|| !strcmp(patientOne.ptotalfee,"\0")|| !strcmp(patientOne.pdocfee,"\0")|| !strcmp(patientOne.paddnum,"\0"))
 {
  //if anyof field set to null then ask to type again those values
  cout << "You missed some of fields to fill so back to fill those and press any key to proceed or ESC to patient menu"<<endl;
  if(getch() == 27)patients();
  addnewpatient();
 }
 textcolor(WHITE);
 textbackground(BLUE);
 clrscr();        //clear the screen for DOS
 //verify typed details
 clrscr();
 cout << "Entered Patient's Details\n" << endl;
 cout << "\n";
 cout << "patient ID is....................." << patientOne.pid << endl;
 cout << "patient first name is............." << patientOne.pfirstname << endl;
 cout << "patient second name is............" << patientOne.psecondname << endl;
 cout << "patient address is................" << patientOne.paddress << endl;
 cout << "patient telephone number is......." << patientOne.ptele << endl;
 cout << "patient birthday is..............." << patientOne.pbirthday << endl;
 cout << "patient's treated doctors are....." << patientOne.pdoctreated << endl;
 cout << "patient age......................." << patientOne.page << endl;
 cout << "patient diagnosis................." << patientOne.pdiagnosis << endl;
 cout << "patient's doctor name............." << patientOne.pdoctorname << endl;
 cout << "patient specification............." << patientOne.pspecification << endl;
 cout << "patient admission date............" << patientOne.padmissiondate << endl;
 cout << "patient ward number..............." << patientOne.pward << endl;
 cout << "patient hospital fee.............." << patientOne.phospitalfee << endl;
 cout << "patient total fee................." << patientOne.ptotalfee << endl;
 cout << "patient doctor fee................" << patientOne.pdocfee << endl;
 cout << "patient admission number.........." << patientOne.paddnum << endl;
 cout << "\n";

 cout << "You have done typing press Enter to Proceed or ESC to back"<<endl; //13 ->Return ESC->27 in ASCII
 if(getch() == 13)  //pressed enter now proceed
 {
 	//open the database
 	ofstream fileWrite;//declare an object from the ofstream class so can manipulate bytes receive and go out through the stream
 	fileWrite.open(dataBaseNameP,ios::out|ios::app|ios::binary);  //data will add at end of the database

  	if(!fileWrite.fail()) //if there is no stream corruption or IO error failbit will keep in 0
 	{
      //update the database
      fileWrite.write((char*)&patientOne,sizeof patientOne);
      /*assign the address of the patientOne struct and convert to pointer char since function will only accept as in this type so write() function will
      identify that location in the stream buffer and begin to write as bytes and second parameter will determine number of bytes that need to write to buffer
      once the process is done by flusing buffer will update the real file or C++ automatically updates the database when process is done.
      flusing will flush the buffer to source that connected with the program
      */
 	}
   //close the connection
   fileWrite.close();
   //reset the stream
   fileWrite.clear();

   //ask another record to proceed
   cout << "Do you want to add another record press Enter to proceed or ESC patient menu"<<endl;
   int command = getch();
   if(command == 13) //carrige return
   {
    addnewpatient();// recursion function will call to "this" function again
   }
   else if(command == 27) //ESC
   {
    patients();
   }else
   {
    patients();
   }

 }
 else if(getch() == 27) //press ESC now proceed
 {
   patients();
 }

}

//-----------------------------------ADMISSION FORM-------------------------------
void admissionform()
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();

  //in here can create the admission form
  ofstream fileIO;
  ifstream fileRead;
  fileIO.open("blankForm.txt",ios::out);
  fileRead.open(dataBaseNameP,ios::in|ios::binary);

  ofstream fileWrite;
  fileWrite.open("admission.dat",ios::out);

  patient patientOne;
  int command;
  char query[maxValue];

  cout << "press any key to proceed or ESC to back" << endl;
  command = getch();

  if(command == 27)//the ESC
  {
  	patients();
  }

  cout << "Type the Patient ID to print the Admission Form " << endl;
  cin.getline(query,maxValue);

  while(fileRead.read((char*)&patientOne,sizeof patientOne))//read one record and put that into the the struct    ¯¯¯¯¯¯¯¯¯¯
  {
   if(!strcmp(query,patientOne.pid))
   {


      cout.setf(ios::right,ios::adjustfield);
      cout << "|" << setw(70) << setfill('-') << "|" << "\n";
      cout << "|" << setw(70) << setfill(' ') << "|" << "\n";
      cout << "|" << "Patient Name  " << setw(1) << setfill(' ') << ":" << patientOne.pfirstname << " " << patientOne.psecondname << setw(3) << setfill(' ') << "|" << "Age " << setw(3) << setfill(' ') << ":" << patientOne.page << setw(2) << setfill(' ') << "\n";
      cout << "|" << setw(70) << setfill('-') << "|" << "\n";
      cout << "|" << setw(70) << setfill(' ') << "|" << "\n";
      cout << "|" << "Address       " << setw(1) << setfill(' ') << ":" << patientOne.paddress << setw(3) << "\n";
      cout << "|" << setw(70) << setfill('-') << "|" << "\n";
      cout << "|" << setw(70) << setfill(' ') << "|" << "\n";
      cout << "|" << "Diagnosis     " << setw(1) << setfill(' ') << ":" << patientOne.pdiagnosis << setw(8) << "\n";
      cout << "|" << setw(70) << setfill('-') << "|" << "\n";
      cout << "|" << "Doctor Name   " << setw(1) << setfill(' ') << ":" << patientOne.pdoctorname << setw(3) << setfill(' ') << "|" << "Specification " << setw(3) << setfill(' ') << ":" << patientOne.pspecification << setw(2) << setfill(' ') << "\n";
      cout << "|" << setw(70) << setfill('-') << "|" << "\n";
      cout << "|" << "Admission Date" << setw(1) << setfill(' ') << ":" << patientOne.padmissiondate << setw(3) << setfill(' ') << "|" << "Ward No " << setw(3) << setfill(' ') << ":" << patientOne.pward << setw(3) << setfill(' ') << "|" << "Admission No " << setw(3) << setfill(' ') << ":" << patientOne.paddnum << setw(2) << setfill(' ') << "\n";
      cout << "|" << setw(70) << setfill('-') << "|" << "\n";
      cout << "|" << "Doctor Fees   " << setw(1) << setfill(' ') << ":" << patientOne.pdocfee << setw(3) << setfill(' ') << "|" << "Hospital Fee " << setw(3) << setfill(' ') << ":" << patientOne.phospitalfee << setw(3) << setfill(' ') << "|" << "Total Fee " << setw(3) << setfill(' ') << ":" << patientOne.ptotalfee << setw(2) << setfill(' ') << "\n";
      cout << "|" << setw(70) << setfill(' ') << "|" << "\n";
      cout << "|" << setw(70) << setfill('-') << "|" << "\n" << endl;

      cout << "WRITE TO THE FILE " << endl;
      getch();

  fileWrite.setf(ios::right,ios::adjustfield);
  fileWrite<< "|" << setw(70) << setfill('-') << "|" << "\n";
  fileWrite<< "|" << setw(70) << setfill(' ') << "|" << "\n";
  fileWrite<< "|" << "Patient Name  " << setw(1) << setfill(' ') << ":" << patientOne.pfirstname << " " << patientOne.psecondname << setw(3) << setfill(' ') << "|" << "Age " << setw(3) << setfill(' ') << ":" << patientOne.page << setw(2) << setfill(' ') << "\n";
  fileWrite<< "|" << setw(70) << setfill('-') << "|" << "\n";
  fileWrite<< "|" << setw(70) << setfill(' ') << "|" << "\n";
  fileWrite<< "|" << "Address       " << setw(1) << setfill(' ') << ":" << patientOne.paddress << setw(3) << "\n";
  fileWrite<< "|" << setw(70) << setfill('-') << "|" << "\n";
  fileWrite<< "|" << setw(70) << setfill(' ') << "|" << "\n";
  fileWrite<< "|" << "Diagnosis     " << setw(1) << setfill(' ') << ":" << patientOne.pdiagnosis << setw(8) << "\n";
  fileWrite<< "|" << setw(70) << setfill('-') << "|" << "\n";
  fileWrite<< "|" << "Doctor Name   " << setw(1) << setfill(' ') << ":" << patientOne.pdoctorname << setw(3) << setfill(' ') << "|" << "Specification " << setw(3) << setfill(' ') << ":" << patientOne.pspecification << setw(2) << setfill(' ') << "\n";
  fileWrite<< "|" << setw(70) << setfill('-') << "|" << "\n";
  fileWrite<< "|" << "Admission Date" << setw(1) << setfill(' ') << ":" << patientOne.padmissiondate << setw(3) << setfill(' ') << "|" << "Ward No " << setw(3) << setfill(' ') << ":" << patientOne.pward << setw(3) << setfill(' ') << "|" << "Admission No " << setw(3) << setfill(' ') << ":" << patientOne.paddnum << setw(2) << setfill(' ') << "\n";
  fileWrite<< "|" << setw(70) << setfill('-') << "|" << "\n";
  fileWrite<< "|" << "Doctor Fees   " << setw(1) << setfill(' ') << ":" << patientOne.pdocfee << setw(3) << setfill(' ') << "|" << "Hospital Fee " << setw(3) << setfill(' ') << ":" << patientOne.phospitalfee << setw(3) << setfill(' ') << "|" << "Total Fee " << setw(3) << setfill(' ') << ":" << patientOne.ptotalfee << setw(2) << setfill(' ') << "\n";
  fileWrite<< "|" << setw(70) << setfill(' ') << "|" << "\n";
  fileWrite<< "|" << setw(70) << setfill('-') << "|" << "\n" << endl;



     break;
   }

  }

   if(fileRead.eof())
   {
    cout << "couldn't find the record so can't proceed" << endl;
    getch();
    patients();
   }


  fileIO.close();
  fileIO.clear();
  patients();

}


//---------------------------------------MODIFY THE PATIENT------------------------------
void modifypatient()
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();

 char pID[maxValue];
 int command=0;

 patient patientOne;

 cout << "Patient Modify Wizard" << endl;
 cout << "to Proceed you need the ID if don't know back to search Wizard and found the ID" << endl;
 cout << "\n";
 cout << "Press Enter to Proceed or ESC to back" <<endl;
 command = getch();
 if(command == 13)//return carrige
 {
  cout << "Type the Patient ID" << endl;
  cin.getline(pID,maxValue);

  //open the database
   /*
   by creating an object from the fstream class can manipulate both I/O operations similately
   it means both have a same stream and same buffer
  */
  fstream fileIO;
  fileIO.open(dataBaseNameP,ios::out|ios::in|ios::binary);//load the file to the buffer

  if(fileIO.good()) //good function will return true if goodbit keeps in 0 which is a member of ios class new one is ios_base
  {
     while(fileIO.read((char*)&patientOne,sizeof patientOne)) //iterate till found the relevant record
     {
       if(!strcmp(patientOne.pid,pID))//if found proceed
       {
         streampos getPosition = fileIO.tellg(); //get the current position of the stream which return integer type value NOT size_t
         getPosition = getPosition - sizeof patientOne;// go to begin of the current record
         fileIO.seekg(getPosition);//seekg will move the stream to begin of the current record which is a function of fstream class

         //read the current record begin to end
         fileIO.read((char*)&patientOne,sizeof patientOne);//this will change the position of the stream to end of the current record


           //ask the details to enter from the users and write to the struct
//ask the details to enter from the users and write to the struct
 cout << "What is the patient ID.?"<<endl;
 cin.getline(patientOne.pid,maxValue);

 cout << "What is the patient first name.?"<<endl;
 cin.getline(patientOne.pfirstname,maxValue);

 cout << "What is the patient second name.?"<<endl;
 cin.getline(patientOne.psecondname,maxValue);

 cout << "What is the patient address.?"<<endl;
 cin.getline(patientOne.paddress,maxValue);

 cout << "What is the patient telephone number.?"<<endl;
 cin.getline(patientOne.ptele,maxValue);

 cout << "What is the patient birthday.?"<<endl;
 cin.getline(patientOne.pbirthday,maxValue);

 cout << "What is the patient's doctor treated.?"<<endl;
 cin.getline(patientOne.pdoctreated,maxValue);
                                                       //------>
 cout << "What is the patient age.?"<<endl;
 cin.getline(patientOne.page,maxValue);

 cout << "What is the patient diagnosis.?"<<endl;
 cin.getline(patientOne.pdiagnosis,maxValue);

 cout << "What is the name of the doctor.?"<<endl;
 cin.getline(patientOne.pdoctorname,maxValue);

 cout << "What is the Specification.?"<<endl;
 cin.getline(patientOne.pspecification,maxValue);

 cout << "What is the Admission Date.?"<<endl;
 cin.getline(patientOne.padmissiondate,maxValue);

 cout << "What is the hospital fee.?"<<endl;
 cin.getline(patientOne.phospitalfee,maxValue);

 cout << "What is the doctor fee.?"<<endl;
 cin.getline(patientOne.pdocfee,maxValue);

 cout << "What is the total fee.?"<<endl;
 cin.getline(patientOne.ptotalfee,maxValue);

 cout << "What is the admission number"<<endl;
 cin.getline(patientOne.paddnum,maxValue);

 cout << "What is the ward number.?"<<endl;
 cin.getline(patientOne.pward,maxValue);

 //validation
 if(!strcmp(patientOne.pid,"\0") || !strcmp(patientOne.pfirstname,"\0") || !strcmp(patientOne.psecondname,"\0")|| !strcmp(patientOne.paddress,"\0")|| !strcmp(patientOne.ptele,"\0")|| !strcmp(patientOne.pbirthday,"\0")|| !strcmp(patientOne.pdoctreated,"\0") || !strcmp(patientOne.page,"\0") || !strcmp(patientOne.pdiagnosis,"\0")|| !strcmp(patientOne.pdoctorname,"\0")|| !strcmp(patientOne.pspecification,"\0")|| !strcmp(patientOne.padmissiondate,"\0")|| !strcmp(patientOne.pward,"\0")|| !strcmp(patientOne.phospitalfee,"\0")|| !strcmp(patientOne.ptotalfee,"\0")|| !strcmp(patientOne.pdocfee,"\0")|| !strcmp(patientOne.paddnum,"\0"))
 {
  //if anyof field set to null then ask to type again those values
  cout << "You missed some of fields to fill so back to fill those and press any key to proceed or ESC to patient menu"<<endl;
  if(getch() == 27)patients(); //ESC
  modifypatient();
 }
    textcolor(WHITE);
    textbackground(BLUE);
    clrscr();        //clear the screen for DOS
    //verify typed details
 cout << "\n";
 cout << "patient ID is....................." << patientOne.pid << endl;
 cout << "patient first name is............." << patientOne.pfirstname << endl;
 cout << "patient second name is............" << patientOne.psecondname << endl;
 cout << "patient address is................" << patientOne.paddress << endl;
 cout << "patient telephone number is......." << patientOne.ptele << endl;
 cout << "patient birthday is..............." << patientOne.pbirthday << endl;
 cout << "patient's treated doctors are....." << patientOne.pdoctreated << endl;
 cout << "patient age......................." << patientOne.page << endl;
 cout << "patient diagnosis................." << patientOne.pdiagnosis << endl;
 cout << "patient's doctor name............." << patientOne.pdoctorname << endl;
 cout << "patient specification............." << patientOne.pspecification << endl;
 cout << "patient admission date............" << patientOne.padmissiondate << endl;
 cout << "patient ward number..............." << patientOne.pward << endl;
 cout << "patient hospital fee.............." << patientOne.phospitalfee << endl;
 cout << "patient total fee................." << patientOne.ptotalfee << endl;
 cout << "patient doctor fee................" << patientOne.pdocfee << endl;
 cout << "patient admission number.........." << patientOne.paddnum << endl;
 cout << "\n";



 			cout << "You have done typing press Enter to print values to database or ESC to back"<<endl; //13 ->Return ESC->27 in ASCII
         int command =getch();
 			if(command == 13)  //pressed enter now proceed
 			{

          //go to the begin of the record
          fileIO.seekp(getPosition);//seekp is an ofstream function and will move the stream to the begin of the current record so ONLY this record can be updated
          fileIO.write((char*)&patientOne,sizeof patientOne) << flush;  //flush bytes into the source(in here the file)
          fileIO.close();
          fileIO.clear();
          patients();//back to patient menu

         }else if(command == 27)
         {
         	fileIO.close();
          	fileIO.clear();
          	patients();//back to patient menu
         }else
         {
            fileIO.close();
          	fileIO.clear();
          	patients();//back to patient menu
         }
       }

     }  //end of while loop
     if(fileIO.eof())   //if the eofbit set to 1 this function will return true ,eofbit set 1(bitwise operators) when the stream reaches the end of the file(NOT keyboard but a file)
       {
         fileIO.close();
         fileIO.clear();

         cout << "This id Associated record can't find press enter to search again ESC to back to menu" << endl;
         command = getch();
         if(command == 13)//return carrige
         {
           modifypatient();

         }else if(command == 27)//ESC
         {
          patients();
         }

       }

    }

 }
 else if(command == 27)//ESC
 {
   patients();

 }else
 {
  modifypatient();//if any key press other than return or ESC back to place
 }

}

//------------------------------------SEARCH PATIENTS-----------------------------

//----------------------------------SEARCH PATIENT MENU-------------------------------------------------------
void searchpatientMenu()
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();


 cout << "Search Patient Wizard..Press Enter to Proceed and ESC to go back to Patient Menu"<< endl;
 int command = getch();
 if(command == 27)//when user clicks on the ESC
 {
  doctors();

 }else if(command == 13) //when user clicks on the return carrige
 {
  //select the search method
  //creating the search menu
  const int x_axis = 5;
  const int y_axis[x_axis] = {3,5,7,9,11};
  char* searchParam = 0;

   char* menuItems[x_axis] = {"by ID","by First Name ","by Second Name ","by Telephone Number","Admission Number "};
  int i=0;//use to indetify the interation

  //draw the intial menu
  while(1)    //THIS WORKS
  {
    if(i>4)
    {
     break;//if exceed the number of menu items
    }
    //when it selects
    if(i == 0)
    { //in first iteration
    gotoxy(x_axis,y_axis[i]);
    textattr(BLUE+(YELLOW<<4));
    cprintf("%s",menuItems[i]);
    }else
    {
     //rest of items
     gotoxy(x_axis,y_axis[i]);
     textattr(WHITE+(BLUE<<4));
     cprintf("%s",menuItems[i]);
    }
    i++;
  }

  i=0;//set the identifier to 0

  while(1)
  {
   /*next iteration for determining which button user selected
   arrow keys can't be captured due to it's dual values at first time
   which are 224 72 up ,80 down, 75 left ,77 right       by using iterating getch() will return those 72.. since second iteration
   capture which key pressed by the user getch() can be used to directly capture which button was pressed
   in this context cin can NOT be used cause that stream doesn't use which is a member of istream class
   only catch those commands from standard input unless it was redirected.! if it's connected with the relevant stream

   textattr() //textattr() is a function of conio.h class which decribes the texts further like it's colour and got
    //three parameters and hold 8 bit of colour range and 4 bits for foreground and so hold 16 colours and 3 bits for background and so can hold 8 colours
    //final one is for blinking or not.
   gotoxy() //goto xy got two arguments those are x and y axis coordinations then move the cursor to that location
   */
    if(i>x_axis-1 || i<0)i=0; //reset the i if it exceed the 2(max value)
    //highlight the option
    gotoxy(x_axis,y_axis[i]);
    textattr(BLUE+(YELLOW<<4));
    cprintf("%s",menuItems[i]);


   switch(getch())
   {
    case 80: //if user pressed the down key ,color the previous item with default
    gotoxy(x_axis,y_axis[i]);
    textattr(WHITE+(BLUE<<4));
    cprintf("%s",menuItems[i]);
    i++;
    break;

    case 72: //if pressed the up key
    gotoxy(x_axis,y_axis[i]);
    textattr(WHITE+(BLUE<<4));
    cprintf("%s",menuItems[i]);
    i--;
    break;

    case 27:
    patients();

    case 13: //if pressed the Enter
    if(i == 0)
    {
    //if select the first option
    i=0;
    searchpatient("pid");
    }

    else if(i == 1)
    {
    //if select the second option
    i=0;
    searchpatient("pfirstname");
    }

    else if(i == 2)
    {
    //if select the third option
    i=0;
    searchpatient("psecondname");
    }

	else if(i == 3)
    {
    //if select the third option
    i=0;
    searchpatient("ptele");
    }

	else if(i == 4)
    {
    //if select the third option
    i=0;
    searchpatient("paddnumber");
    }

    break;

   }


  }


 }else
 {
  searchpatientMenu();
 }


}

//---------------------------------------SEARCH PATIENT------------------------
/*Associated Functions
void searchpatientMenu(void);
void searchpatient(char* searchParam);
void searchSubForum(char*param,char*query);
void searchRetrieve(fstream &fileIO); //parameter is declared as a reference so variable assign to this can be indrecitly modified
*/

void searchpatient(char* searchParam)
{
  gotoxy(3,15);
  cout << "Search Parameter is : " << searchParam << endl;
  cout << "Type your query to proceed" << endl;
  char query[20];
  cin.getline(query,20);

  if(!strcmp(searchParam,"pid"))
  {
   searchSubForum("pid",query);
  }

  else if(!strcmp(searchParam,"pfirstname"))
  {
   searchSubForum("pfirstname",query);
  }

  else if(!strcmp(searchParam,"psecondname"))
  {
   searchSubForum("psecondname",query);
  }

  else if(!strcmp(searchParam,"ptele"))
  {
   searchSubForum("ptele",query);
  }

  else if(!strcmp(searchParam,"paddnumber"))
  {
   searchSubForum("paddnumber",query);
  }

}
//-------------------------------SEARCH PATIENT SUB FORUM------------------------
void searchSubForum(char*param,char*query)///pid ,pfirstname ,psecondname ,ptele,paddnumber are the search parameters
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();

   fstream fileIO;
   patient patientOne;
   fileIO.open(dataBaseNameP,ios::in|ios::out|ios::binary);

   if(fileIO.good())
   {
   	while(fileIO.read((char*)&patientOne,sizeof patientOne)) //get the first record
      {
          if(!strcmp(patientOne.pid,query)||   !strcmp(patientOne.pfirstname,query)||  !strcmp(patientOne.psecondname,query) ||  !strcmp(patientOne.ptele,query) ||  !strcmp(patientOne.paddnum,query) )
          {
            searchRetrieve(fileIO);
            break;
          }
      }
      	if(fileIO.eof())   //if the eofbit set to 1 this function will return true ,eofbit set 1(bitwise operators) when the stream reaches the end of the file(NOT keyboard but a file)
          {
         	fileIO.close();
         	fileIO.clear();
         	cout << "This id Associated record can't find press enter to search again ESC to back to menu" << endl;
            int command = getch();
         	if(command == 13)//return carrige
         	{
           		searchpatientMenu();

            }
            else if(command == 27)//ESC
         	{
          		patients();
            }
          }

   }
   else
   {
    fileIO.close();
    fileIO.clear();
    doctors();
    cout << "Unable to open the database or it's corrupted" << endl;
   }

   fileIO.close();
   fileIO.clear();

}


//------------------------------------SEARCH PATIENT RETRIEVE DATA--------------------

void searchRetrieve(fstream &fileIO)
{
  patient patientOne;
  //reset to the begin of the record
  int currentPosition = fileIO.tellg();
  streampos beginPosition = currentPosition - sizeof patientOne;
  fileIO.seekg(beginPosition); //stream move to the new location in buffer

  //put those values into the struct for displaying
  fileIO.read((char*)&patientOne,sizeof patientOne);

   //verify typed details
 clrscr();
 cout << "Patient's Details\n" << endl;
 cout << "\n";
 cout << "patient ID is....................." << patientOne.pid << endl;
 cout << "patient first name is............." << patientOne.pfirstname << endl;
 cout << "patient second name is............" << patientOne.psecondname << endl;
 cout << "patient address is................" << patientOne.paddress << endl;
 cout << "patient telephone number is......." << patientOne.ptele << endl;
 cout << "patient birthday is..............." << patientOne.pbirthday << endl;
 cout << "patient treated doctors are......." << patientOne.pdoctreated << endl;
 cout << "patient age......................." << patientOne.page << endl;
 cout << "patient diagnosis................." << patientOne.pdiagnosis << endl;
 cout << "patient's doctor name............." << patientOne.pdoctorname << endl;
 cout << "patient specification............." << patientOne.pspecification << endl;
 cout << "patient admission date............" << patientOne.padmissiondate << endl;
 cout << "patient ward number..............." << patientOne.pward << endl;
 cout << "patient hospital fee.............." << patientOne.phospitalfee << endl;
 cout << "patient total fee................." << patientOne.ptotalfee << endl;
 cout << "patient doctor fee................" << patientOne.pdocfee << endl;
 cout << "patient admission number.........." << patientOne.paddnum << endl;
 cout << "\n";


 			cout << "You have done typing press Enter to print values to textfile or ESC to back press"<<endl; //13 ->Return ESC->27 in ASCII
 			if(getch() == 13)  //pressed enter now proceed
 			{
          fileIO.close();
          fileIO.clear();

          //update the buffer
          fileIO.open("fileDOC.txt",ios::out);

          fileIO.setf(ios::right,ios::adjustfield);
           cout << "Patient's Details\n" << endl;
 fileIO << "\n";
 fileIO << "patient ID is....................." << patientOne.pid << endl;
 fileIO << "patient first name is............." << patientOne.pfirstname << endl;
 fileIO << "patient second name is............" << patientOne.psecondname << endl;
 fileIO << "patient address is................" << patientOne.paddress << endl;
 fileIO << "patient telephone number is......." << patientOne.ptele << endl;
 fileIO << "patient birthday is..............." << patientOne.pbirthday << endl;
 fileIO << "patient treated doctors are......." << patientOne.pdoctreated << endl;
 fileIO << "patient age......................." << patientOne.page << endl;
 fileIO << "patient diagnosis................." << patientOne.pdiagnosis << endl;
 fileIO << "patient's doctor name............." << patientOne.pdoctorname << endl;
 fileIO << "patient specification............." << patientOne.pspecification << endl;
 fileIO << "patient admission date............" << patientOne.padmissiondate << endl;
 fileIO << "patient ward number..............." << patientOne.pward << endl;
 fileIO << "patient hospital fee.............." << patientOne.phospitalfee << endl;
 fileIO << "patient total fee................." << patientOne.ptotalfee << endl;
 fileIO << "patient doctor fee................" << patientOne.pdocfee << endl;
 fileIO << "patient admission number.........." << patientOne.paddnum << endl;
 fileIO << "\n";

          fileIO.close();
          fileIO.clear();
          patients();

         }

         else if(getch() == 27)
         {
         	fileIO.close();
          	fileIO.clear();
          	patients();//back to patient menu
         }

         else if(getch() == 13)
         {
            fileIO.close();
          	fileIO.clear();
          	patients();//back to patient menu
         }


}


//-----------------------------------SHOW ALL PATIENTS------------------------------

void showallpatients()
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();


   patient patientOne;

 //show all doc information
 ifstream fileRead;
 fileRead.open(dataBaseNameP,ios::in|ios::binary);

 if(!fileRead.fail())
 {
   //if able to read
  while(fileRead.read((char*)&patientOne,sizeof patientOne))  //get the first record for displaying  and put into the struct
  {
    //verify typed details
 cout << "\n";
 cout << "patient ID is....................." << patientOne.pid << endl;
 cout << "patient first name is............." << patientOne.pfirstname << endl;
 cout << "patient second name is............" << patientOne.psecondname << endl;
 cout << "patient address is................" << patientOne.paddress << endl;
 cout << "patient telephone number is......." << patientOne.ptele << endl;
 cout << "patient birthday is..............." << patientOne.pbirthday << endl;
 cout << "patient treated doctors are......." << patientOne.pdoctreated << endl;
 cout << "patient age......................." << patientOne.page << endl;
 cout << "patient diagnosis................." << patientOne.pdiagnosis << endl;
 cout << "patient's doctor name............." << patientOne.pdoctorname << endl;
 cout << "patient specification............." << patientOne.pspecification << endl;
 cout << "patient admission date............" << patientOne.padmissiondate << endl;
 cout << "patient ward number..............." << patientOne.pward << endl;
 cout << "patient hospital fee.............." << patientOne.phospitalfee << endl;
 cout << "patient total fee................." << patientOne.ptotalfee << endl;
 cout << "patient doctor fee................" << patientOne.pdocfee << endl;
 cout << "patient admission number.........." << patientOne.paddnum << endl;
 cout << "\n";
 cout << "Press any key to proceed" << endl;
 getch();
 clrscr();

  }
 }else
 {
   cerr << "Unable to open the database maybe it doesn't exist? or unable to read? or corrupted?? check it out"<<endl;
   getch();
   fileRead.close();
   fileRead.clear();
   patients();//back to doctor menu
 }

 while(1)
 {
 cout << "You reached the end of the database press ESC to go back" << endl;
  if(getch() == 27)  //if user press the ESC
  {
   fileRead.close();
   fileRead.clear();
   patients();//back to doctor menu
   break;
  }
 }




}


//--------------------------------------ADD NEW DOC-------------------------------------
void addnewdoc()
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();

 doctor doctorOne;
 cout <<"Add New Doctor Wizard.."<<endl;
 gotoxy(1,4);

 if(getch() == 27)doctors();//press ESC to go back

 cout <<"What is the doctar name"<<endl;
 cin.getline(doctorOne.dname,maxValue);

 cout <<"What is the doctar id"<<endl;
 cin.getline(doctorOne.did,maxValue);

 cout <<"What is the specialized field"<<endl;
 cin.getline(doctorOne.dspecialfield,maxValue);

 cout <<"What is the doctar address"<<endl;
 cin.getline(doctorOne.daddress,maxValue);

 cout <<"What is the doctar telephone number"<<endl;
 cin.getline(doctorOne.dtele,maxValue);

 cout <<"What is the doctar email"<<endl;
 cin.getline(doctorOne.demail,maxValue);

 cout <<"What is the doctar web address"<<endl;
 cin.getline(doctorOne.dweb,maxValue);

 if(!strcmp(doctorOne.dname,"\0") || !strcmp(doctorOne.did,"\0") || !strcmp(doctorOne.dspecialfield,"\0")  || !strcmp(doctorOne.daddress,"\0") || !strcmp(doctorOne.dtele,"\0") || !strcmp(doctorOne.demail,"\0") || !strcmp(doctorOne.dweb,"\0") )
 {
 //since array chars add \0 null char at end this is suitable for checking the nothing/null
   cout << "You need to fill every asking fields in order to proceed press any key to go back or ESC to doctors menu" <<endl;
   if(getch() == 27)doctors();//press ESC to go back
   addnewdoc();
 }


 cout <<"You have entered all details now please check to proceed"<<endl;
 cout.setf(ios::right,ios::adjustfield);
 cout <<"Doctar Name is........................" << doctorOne.dname << endl;
 cout <<"Doctar ID is.........................." << doctorOne.did << endl;
 cout <<"Doctar Specialized field is..........." << doctorOne.dspecialfield << endl;
 cout <<"Doctar Address is....................." << doctorOne.daddress << endl;
 cout <<"Doctar Telephone number is............" << doctorOne.dtele << endl;
 cout <<"Doctar Email is......................." << doctorOne.demail << endl;
 cout <<"Doctar Web is........................." << doctorOne.dweb << endl;
 cin.ignore(1,'\n');

 //update the database
 ofstream fileWrite;
 fileWrite.open(dataBaseName,ios::binary|ios::out|ios::app);

 if(!fileWrite.fail())
 {
    //then write to the file
    fileWrite.write((char*)&doctorOne,sizeof doctorOne);
    fileWrite.close();
    fileWrite.clear();
 }

 cout << "Do you want to add another record Enter or ESC/anykey"<<endl;
 int commandTyped;
 commandTyped = getch();

 if(commandTyped == 13)  //Enter
 {
    addnewdoc();
 }else if(commandTyped == 27)//ESC
 {
    doctors();
 }else
 {
    doctors();
 }

}
//------------------------------------------------MODIFY DOC----------------------------------------------
void modifydoc()
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();

 doctor doctorOne;

 char docid[maxValue];
 int position;

 cout <<"Doctor Modify Wizard.."<<endl;

 if(getch() == 27)doctors();

 cout <<"What is the Doctor ID .."<<endl;
 cin.getline(docid,maxValue);

 if(!strcmp(docid,"\0")){ cout << "No Parameter Found Please Type any Parameter to proceed" << endl;getch();modifydoc();}

 fstream fileIO;
 fileIO.open(dataBaseName,ios::in|ios::binary|ios::out);

 if(!fileIO.fail()) //if open sucessfully
 {
   while(fileIO.read((char*)&doctorOne,sizeof doctorOne))
   {
     //searching for a correct doctorID
     if(!strcmp(doctorOne.did,docid))   //if matched
     {
      //find the position where the record is
      position = fileIO.tellg();
      position = position-sizeof doctorOne;
      streampos foundPosition = position;

      fileIO.seekg(foundPosition);//move to that location in the buffer
      fileIO.read((char*)&doctorOne,sizeof doctorOne);  //get all values to the struct
      //prepare to modify

      cout << "\n";
      cout <<"What is the doctar name"<<endl;
 		cin.getline(doctorOne.dname,maxValue);

 		cout <<"What is the doctar id"<<endl;
 		cin.getline(doctorOne.did,maxValue);

 		cout <<"What is the specialized field"<<endl;
 		cin.getline(doctorOne.dspecialfield,maxValue);

 		cout <<"What is the doctar address"<<endl;
 		cin.getline(doctorOne.daddress,maxValue);

 		cout <<"What is the doctar telephone number"<<endl;
 		cin.getline(doctorOne.dtele,maxValue);

 		cout <<"What is the doctar email"<<endl;
 		cin.getline(doctorOne.demail,maxValue);

 		cout <<"What is the doctar web address"<<endl;
 		cin.getline(doctorOne.dweb,maxValue);

      if(!strcmp(doctorOne.dname,"\0") || !strcmp(doctorOne.did,"\0") || !strcmp(doctorOne.dspecialfield,"\0")  || !strcmp(doctorOne.daddress,"\0") || !strcmp(doctorOne.dtele,"\0") || !strcmp(doctorOne.demail,"\0") || !strcmp(doctorOne.dweb,"\0") )
      {
 			//since array chars add \0 null char at end this is suitable for checking the nothing/null
      	cout << "You need to fill every asking fields in order to proceed press any key to go back" <<endl;
   		getch();
   		modifydoc();
      }

 		cout <<"You have entered all details now please check to proceed"<<endl;
 		cout.setf(ios::right,ios::adjustfield);
 		cout <<"Doctar Name is........................" << doctorOne.dname << endl;
 		cout <<"Doctar ID is.........................." << doctorOne.did << endl;
 		cout <<"Doctar Specialized field is..........." << doctorOne.dspecialfield << endl;
 		cout <<"Doctar Address is....................." << doctorOne.daddress << endl;
 		cout <<"Doctar Telephone number is............" << doctorOne.dtele << endl;
 		cout <<"Doctar Email is......................." << doctorOne.demail << endl;
 		cout <<"Doctar Web is........................." << doctorOne.dweb << endl;

      //update the database
      //go to the record position in the buffer
      fileIO.seekp(foundPosition);
      //begin to write till that location
      fileIO.write((char*)&doctorOne,sizeof doctorOne);
      //close the connection
      fileIO.close();
      //reset the stream
      fileIO.clear();
      cout << "Press any key to contiue.." <<endl;
      getch();
      doctors();//redirect to doctors menu
     }else if(fileIO.eof())
     {
      cout << "Couldn't find any Details associate with this ID"<<endl;
      doctors();//redirect to doctors menu
     }
   }

 }

}

//-----------------------------------SEARCH DOC MENU---------------------------------
void searchdocMenu()
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();


 cout << "Search Dcotor Wizard..Press Enter to Proceed and ESC to go back to Doctor Menu"<< endl;
 int command = getch();
 if(command == 27)//when user clicks on the ESC
 {
  doctors();

 }else if(command == 13) //when user clicks on the return carrige
 {
  //select the search method
  //creating the search menu
  const int x_axis = 3;
  const int y_axis[x_axis] = {3,5,7};
  char* searchParam = 0;

  char* menuItems[x_axis] = {"by ID","by Name","by Field"};
  int i=0;//use to indetify the interation

  //draw the intial menu
  while(1)    //THIS WORKS
  {
    if(i>2)
    {
     break;//if exceed the number of menu items
    }
    //when it selects
    if(i == 0)
    { //in first iteration
    gotoxy(x_axis,y_axis[i]);
    textattr(BLUE+(YELLOW<<4));
    cprintf("%s",menuItems[i]);
    }else
    {
     //rest of items
     gotoxy(x_axis,y_axis[i]);
     textattr(BLUE+(WHITE<<4));
     cprintf("%s",menuItems[i]);
    }
    i++;
  }

  i=0;//set the identifier to 0

  while(1)
  {
   /*next iteration for determining which button user selected
   arrow keys can't be captured due to it's dual values at first time
   which are 224 72 up ,80 down, 75 left ,77 right       by using iterating getch() will return those 72.. since second iteration
   capture which key pressed by the user getch() can be used to directly capture which button was pressed
   in this context cin can NOT be used cause that stream doesn't use which is a member of istream class
   only catch those commands from standard input unless it was redirected.! if it's connected with the relevant stream

   textattr() //textattr() is a function of conio.h class which decribes the texts further like it's colour and got
    //three parameters and hold 8 bit of colour range and 4 bits for foreground and so hold 16 colours and 3 bits for background and so can hold 8 colours
    //final one is for blinking or not.
   gotoxy() //goto xy got two arguments those are x and y axis coordinations then move the cursor to that location
   */
    if(i>2 || i<0)i=0; //reset the i if it exceed the 2(max value)
    //highlight the option
    gotoxy(x_axis,y_axis[i]);
    textattr(BLUE+(YELLOW<<4));
    cprintf("%s",menuItems[i]);


   switch(getch())
   {
    case 80: //if user pressed the down key ,color the previous item with default
    gotoxy(x_axis,y_axis[i]);
    textattr(WHITE+(BLUE<<4));
    cprintf("%s",menuItems[i]);
    i++;
    break;

    case 72: //if pressed the up key
    gotoxy(x_axis,y_axis[i]);
    textattr(WHITE+(BLUE<<4));
    cprintf("%s",menuItems[i]);
    i--;
    break;

    case 27:
    doctors();

    case 13: //if pressed the Enter
    if(i == 0)
    {
    //if select the first option
    i=0;
    searchdoc("did");

    }

    else if(i == 1)
    {
    //if select the second option
    i=0;
    searchdoc("dname");

    }

    else if(i == 2)
    {
    //if select the third option
    i=0;
    searchdoc("dspecialfield");

    }
    break;

   }


  }


 }else
  {
    searchdocMenu();
  }


}

//-----------------------------------SEARCH DOC SUB MENU--------------------------
//void searchdocSubForum(char* param,char* query);;//did, dname ,dspecialfield
//void searchdocRetrieve(fstream &fileIO);  searchdoc(char* &parameter)
void searchdoc(char* searchParam)
{
  gotoxy(3,15);
  cout << "Search Parameter is : " << searchParam << endl;
  cout << "Type your query to proceed" << endl;
  char query[20];
  cin.getline(query,20);

  if(!strcmp(searchParam,"did"))
  {
   searchdocSubForum("did",query);
  }

  else if(!strcmp(searchParam,"dname"))
  {
   searchdocSubForum("dname",query);
  }

  else if(!strcmp(searchParam,"dspecialfield"))
  {
   searchdocSubForum("dspecialfield",query);
  }

}
//-------------------------------SEARCH DOC SUB FORUM------------------------
void searchdocSubForum(char*param,char*query)///pid ,pfirstname ,psecondname ,ptele,paddnumber are the search parameters
{
   textcolor(WHITE);
   textbackground(BLUE);
    clrscr();

   fstream fileIO;
   doctor doctorOne;
   fileIO.open(dataBaseName,ios::in|ios::out|ios::binary);

   if(fileIO.good())
   {
   	while(fileIO.read((char*)&doctorOne,sizeof doctorOne)) //get the first record
      {
          if(!strcmp(doctorOne.did,query)||   !strcmp(doctorOne.dname,query)||  !strcmp(doctorOne.dspecialfield,query))
          {
            searchdocRetrieve(fileIO);
            break;
          }
      }
      	if(fileIO.eof())   //if the eofbit set to 1 this function will return true ,eofbit set 1(bitwise operators) when the stream reaches the end of the file(NOT keyboard but a file)
          {
         	fileIO.close();
         	fileIO.clear();
         	cout << "This id Associated record can't find press enter to search again ESC to back to menu" << endl;
         	if(getch() == 13)//return carrige
         	{
           		searchdocMenu();

            }
            else if(getch() == 27)//ESC
         	{
          		doctors();
            }
          }

   }
   else
   {
    fileIO.close();
    fileIO.clear();
    doctors();
    cout << "Unable to open the database or it's corrupted" << endl;
   }

   fileIO.close();
   fileIO.clear();

}


//------------------------------------SEARCH DOC RETRIEVE DATA--------------------

void searchdocRetrieve(fstream &fileIO)
{
   doctor doctorOne;
  //reset to the begin of the record
  int currentPosition = fileIO.tellg();
  streampos beginPosition = currentPosition - sizeof doctorOne;
  fileIO.seekg(beginPosition); //stream move to the new location in buffer

  //put those values into the struct for displaying
  fileIO.read((char*)&doctorOne,sizeof doctorOne);

   cout << "Doctor Details \n" << endl;
   //verify typed details
		cout.setf(ios::right,ios::adjustfield);
    	cout <<"Doctar Name is........................" << doctorOne.dname << endl;
 		cout <<"Doctar ID is.........................." << doctorOne.did << endl;
 		cout <<"Doctar Specialized field is..........." << doctorOne.dspecialfield << endl;
 		cout <<"Doctar Address is....................." << doctorOne.daddress << endl;
 		cout <<"Doctar Telephone number is............" << doctorOne.dtele << endl;
 		cout <<"Doctar Email is......................." << doctorOne.demail << endl;
 		cout <<"Doctar Web is........................." << doctorOne.dweb << endl;
      cout << "\n" << endl;


 			cout << "You have done typing press Enter to print values to textfile or ESC to back"<<endl; //13 ->Return ESC->27 in ASCII
 			if(getch() == 13)  //pressed enter now proceed
 			{
          fileIO.close();
          fileIO.clear();

          //update the buffer
          fileIO.open("fileDOC.txt",ios::out);
          fileIO.setf(ios::right,ios::adjustfield);
          fileIO <<"Doctar Name is........................" << doctorOne.dname << endl;
          fileIO <<"Doctar ID is.........................." << doctorOne.did << endl;
          fileIO <<"Doctar Specialized field is..........." << doctorOne.dspecialfield << endl;
          fileIO <<"Doctar Address is....................." << doctorOne.daddress << endl;
          fileIO <<"Doctar Telephone number is............" << doctorOne.dtele << endl;
          fileIO <<"Doctar Email is......................." << doctorOne.demail << endl;
          fileIO <<"Doctar Web is........................." << doctorOne.dweb << endl;
          fileIO << "\n" << endl;
          fileIO.close();
          fileIO.clear();
          doctors();//back to patient menu

         }

         else if(getch() == 27)
         {
         	fileIO.close();
          	fileIO.clear();
          	doctors();//back to patient menu
         }

         else if(getch() == 13)
         {
            fileIO.close();
          	fileIO.clear();
          	doctors();//back to patient menu
         }


}


//---------------------------SHOW ALL DOC--------------------------------
void showalldoc()
{
   textcolor(WHITE);
   textbackground(BLUE);
   clrscr();

 doctor doctorOne;

 //show all doc information
 ifstream fileRead;
 fileRead.open(dataBaseName,ios::in|ios::binary);

 if(!fileRead.fail())
 {
   //if able to read
  while(fileRead.read((char*)&doctorOne,sizeof doctorOne))  //get the first record for displaying  and put into the struct
  {
    cout.setf(ios::right,ios::adjustfield);
    cout <<"Doctar Name is........................" << doctorOne.dname << endl;
    cout <<"Doctar ID is.........................." << doctorOne.did << endl;
    cout <<"Doctar Specialized field is..........." << doctorOne.dspecialfield << endl;
    cout <<"Doctar Address is....................." << doctorOne.daddress << endl;
    cout <<"Doctar Telephone number is............" << doctorOne.dtele << endl;
    cout <<"Doctar Email is......................." << doctorOne.demail << endl;
    cout <<"Doctar Web is........................." << doctorOne.dweb << endl;
    cout << "\n" << endl;
    cout << "press any key to proceed" << endl;
    getch();
    clrscr();
  }
 }else
 {
   cerr << "Unable to open the database maybe it doesn't exist? or unable to read? or corrupted?? check it out"<<endl;
   doctors();//back to doctor menu
 }

 while(1)
 {
 cout << "You reached the end of the database so press ESC to go back" << endl;
  if(getch() == 27)  //if user press the ESC
  {
   doctors();//back to doctor menu
   break;
  }
 }


}



