#include<stdio.h>
#include<string.h>

int exitfunc(char ch[2])
{
  printf("If you want to try again,enter 'Y'\n");
  printf("If you want to exit,enter 'N'\n");
  printf("Your choice: ");
  //ch[2];
  scanf("%s",ch);

  if(strcmp(ch,"Y")==0)
  {
    return 1;
  }
  else
  {
    printf("Good Bye!!!\n");
    return 0;
  }
}

int main()
{
  int nt=0;//number of teachers
  int ns=0;//number of students
  int i;
  int ssd;//starting position of student database
  int std;//starting position of teacher database

  FILE *fp;
  fp=fopen("Main Database.DAT","rb");
  printf("\t\tDatabase Management by 1907115 \n\n");
  struct Admin
  {
    char ause[10];
    char apass[10];
  };

  struct Teach
  {
    char tuse[10];
    char tpass[10];
    char tfname[20];//first name
    char tlname[20];//last name
    char tcourse[10];
  };

  struct Stu
  {
    char suse[10];
    char spass[10];
    char sfname[20];
    char slname[20];
    int sid;//student id
    int smarks[20];
  };
  struct Teach te;
  struct Stu st;
  struct Admin ad;

/*printf("nt: %lu\n",sizeof(nt));
  printf("ns: %lu\n",sizeof(ns));
  printf("te: %lu\n",sizeof(te));
  printf("st: %lu\n",sizeof(st));*/
  char m[1];// If I declare char type data,the programes misbehaves.So,I choice string here.
  int check=1;
  if(fp==NULL)// if file is not creat ever
  {
    fp=fopen("Main Database.DAT","ab+");

    printf("\aThere is no Database or Admin Panel\n");
    printf("\nAdmin's Username: ");
    scanf("%s",ad.ause);
    printf("Admin's Password: ");
    scanf("%s",ad.apass);
    fwrite(&ad,sizeof(ad),1,fp);
    int last=ftell(fp);

    fwrite(&nt,sizeof(nt),1,fp);///////////////////////////////////////////////////////////////////////////////////////////////////
    fwrite(&ns,sizeof(ns),1,fp);//////////////////////////////////////////////////////////////////////////////////////////////////

    printf("ok! You complete it.\n");
    printf("You will be logout now.\n");
    printf("Then login again!\n");
    fclose(fp);
  }
  else
  {
    fp=fopen("Main Database.DAT","rb+");// not uding ab+,ab+ has no ability to modify data
    printf("Please follow the instructions below:\n");
    printf("If you are Admin,enter 'A'\n");
    printf("If you are Teacher,enter 'T'\n");
    printf("If you are Student,enter 'S'\n");


    while(check)
    {
      printf("\nYour mode: ");
      scanf("%s",m);

      /**********************Admin Panel*************************/
      if(strcmp(m,"A")==0)
      {
        char checkuse[10];
        char checkpass[10];
        printf("Username: ");
        scanf("%s",checkuse);
        printf("Password: ");
        scanf("%s",checkpass);

        fread(&ad,sizeof(ad),1,fp);
        if(strcmp(checkuse,ad.ause)==0 && strcmp(checkpass,ad.apass)==0) //admin username and password checked successfully
        {
          printf("Admin login is successful.\n");
          printf("\nPlease follow the instructions below:\n");
          printf("If you want to add Teacher information,enter 'T'\n");
          printf("If you want to add Student information,enter 'S'\n");
          char choice[2];
          printf("\nYour Choice: ");
          scanf("%s",choice);
          fflush(stdin);

          if(strcmp(choice,"T")==0)//Edit teacher information by admin
          {
            printf("\nPlease follow the instructions below to edit teacher information:\n");
            printf("If want to Add,enter 'A'\n");
            printf("If want to Modify,enter 'M'\n");

            char tchoice[2];
            printf("\nYour Choice: ");
            scanf("%s",tchoice);


            if(strcmp(tchoice,"A")==0)//Add information
            {

              std=sizeof(ad)+sizeof(nt)+sizeof(ns);
              rewind(fp);
              fseek(fp,std,SEEK_CUR);
              char op[2]="Y";
              while(strcmp(op,"Y")==0)
              {
                nt++;
                printf("\n%d.Information for teacher:\n",nt);
                printf("Username: ");
                scanf("%s",te.tuse);
                printf("Password: ");
                scanf("%s",te.tpass);
                printf("First Name: ");
                scanf("%s",te.tfname);
                printf("Last Name: ");
                scanf("%s",te.tlname);
                printf("Course Name: ");
                scanf("%s",te.tcourse);
                fwrite(&te,sizeof(te),1,fp);
                printf("Do you want to add another record(Y/N): ");
                scanf("%s",op);
              }
              rewind(fp);
              fseek(fp,sizeof(ad),SEEK_CUR);
              fwrite(&nt,sizeof(nt),1,fp);//write the information of total number of teacher in file
            }
            else if(strcmp(tchoice,"M")==0)//Modification
            {
              rewind(fp);
              fseek(fp,sizeof(ad),SEEK_CUR);
              fread(&nt,sizeof(nt),1,fp);
              std=sizeof(ad)+sizeof(nt)+sizeof(ns);
              printf("\n\tFull Database of Teachers\n");
              printf("\nUsername,Password,First_Name,Last_Name,Course respectively: \n");
              rewind(fp);
              fseek(fp,std,SEEK_CUR);
              for(i=0;i<nt;i++)
              {
                fread(&te,sizeof(te),1,fp);
                printf("%s %s %s %s %s\n",te.tuse,te.tpass,te.tfname,te.tlname,te.tcourse);
              }
              rewind(fp);
              fseek(fp,std,SEEK_CUR);
              char rt[20];//replace to
              printf("\nEnter username you want to modify: ");
              scanf("%s",rt);

              int flag=0;//To check match data found yet or not
              char tmchoice[2];
              strcpy(tmchoice,"Y");
              while(strcmp(tmchoice,"Y")==0)
              {

                while(fread(&te,sizeof(te),1,fp))
                {

                  if(strcmp(te.tuse,rt)==0)
                  {
                    printf("Please enter modify data below: \n\n");
                    printf("Modified Username:");
                    scanf("%s",te.tuse);
                    printf("Modified Password: ");
                    scanf("%s",te.tpass);
                    printf("Modified First_Name: ");
                    scanf("%s",te.tfname);
                    printf("Modified Last_Name: ");
                    scanf("%s",te.tlname);
                    printf("Modified Course_Name: ");
                    scanf("%s",te.tcourse);
                    printf("fp of second data: %ld\n",ftell(fp));
                    fseek(fp,-sizeof(te),SEEK_CUR);

                    fwrite(&te,sizeof(te),1,fp);
                    flag=1;
                    break;
                  }

               }
                if(flag==0)
                {
                    printf("No match found with database!\n");
                }
               printf("\nAfter Modification: \n");
               printf("\nUsername,Password,First_Name,Last_Name,Course\n");
               rewind(fp);
               fseek(fp,std,SEEK_CUR);
               while(fread(&te,sizeof(te),1,fp))
               {
                 printf("%s %s %s %s %s\n",te.tuse,te.tpass,te.tfname,te.tlname,te.tcourse);
               }
               printf("Do you want to modify another record(Y/N): ");
               scanf("%s",tmchoice);
             }
            }

            else//wrong choice
            {
              printf("Something is wrong!\n");
              printf("Follow the instructions and try again!\n");
              //exitfunc(log);
            }
          }
          else if(strcmp(choice,"S")==0)//Edit student information by Admin
          {

            printf("\nPlease follow the instructions below to edit student information:\n");
            printf("If want to Add,enter 'A'\n");
            printf("If want to Modify,enter 'M'\n");

            char schoice[2];
            printf("\nYour Choice: ");
            scanf("%s",schoice);
            if(strcmp(schoice,"A")==0)//Add student information
            {

              rewind(fp);
              fseek(fp,sizeof(ad),SEEK_CUR);
              fread(&nt,sizeof(nt),1,fp);

              ssd=sizeof(ad)+sizeof(te)*nt+sizeof(nt)+sizeof(ns);//student information start from which position
              printf("ssd: %d\n",ssd);
              rewind(fp);
              fseek(fp,ssd,SEEK_CUR);

              char schoice[2];
              strcpy(schoice,"Y");

              while(strcmp(schoice,"Y")==0)
              {
                ns++;
                printf("\n%d. Information for student:\n",ns);
                printf("Username: ");
                scanf("%s",st.suse);
                printf("Password: ");
                scanf("%s",st.spass);
                printf("Roll: ");
                scanf("%d",&st.sid);
                printf("First_Name: ");
                scanf("%s",st.sfname);
                printf("Last_Name: ");
                scanf("%s",st.slname);//mark problem
                for(i=0;i<nt;i++)
                {
                  st.smarks[i]=0;//assign 0 to all marks to avoid garbage value
                }
                fwrite(&st,sizeof(st),1,fp);
                printf("\nDo you want to add another record?(Y/N): ");
                scanf("%s",schoice);
              }
              rewind(fp);
              int size=sizeof(ad)+sizeof(nt);
              fseek(fp,size,SEEK_CUR);
              fwrite(&ns,sizeof(ns),1,fp);//write the total number of students in database
            }
            else if(strcmp(schoice,"M")==0)//Modification of student Information
            {

              printf("Full Database of Students: \n");
              rewind(fp);
              int ss=sizeof(ad)+sizeof(nt);
              fseek(fp,ss,SEEK_CUR);
              fread(&ns,sizeof(ns),1,fp);

              rewind(fp);//find starting position of student database
              fseek(fp,sizeof(ad),SEEK_CUR);
              fread(&nt,sizeof(nt),1,fp);//read the information of nt here
              ssd=sizeof(ad)+sizeof(te)*nt+sizeof(nt)+sizeof(ns);
              //printf("nt: %d\n",nt);////////////////////////////////////////////////////////////////////////////////////

              printf("ssd in modification of admin panel: %d\n",ssd);
              rewind(fp);
              fseek(fp,ssd,SEEK_CUR);
              //printf("fp in modification %d\n",ftell(fp));
              //fread(&ns,sizeof(ns),1,fp);
              //printf("%s",st.suse);
              printf("Username,Password,ID,First_Name,Last_Name,Marks respectively: \n");//print student's full database
              int i,j;
              for(i=0;i<ns;i++)
              {
                //printf("ns: %d\n",ns);
                fread(&st,sizeof(st),1,fp);
                printf("%s %s %d %s %s ",st.suse,st.spass,st.sid,st.sfname,st.slname);
                //printf("i: %d\n",i);
                for(j=0;j<nt;j++)
                {
                  printf("%d ",st.smarks[j]);
                }
                printf("\n");
              }
              //printf("after ns: %d\n",ns);
              //printf("afetr nt: %d\n",nt);
              rewind(fp);
              fseek(fp,ssd,SEEK_CUR);
              char mschoice[2];//choice of modified another record
              strcpy(mschoice,"Y");
              char strt[10];
              printf("Enter username you want to modified: ");
              scanf("%s",strt);

              int flag=0;//check replace data match or not
              while(strcmp(mschoice,"Y")==0)
              {
                while(fread(&st,sizeof(st),1,fp))
                {
                  if(strcmp(strt,st.suse)==0)
                  {
                    printf("Modified Username: ");
                    scanf("%s",st.suse);
                    printf("Modified Password: ");
                    scanf("%s",st.spass);
                    printf("Modified ID: ");
                    scanf("%d",&st.sid);
                    printf("Modified First_Name: ");
                    scanf("%s",st.sfname);
                    printf("Modified Last_Name: ");
                    scanf("%s",st.slname);
                    for(i=0;i<nt;i++)
                    {
                      printf("Modified Marks for Subject no.%d :",i+1);
                      scanf("%d",&st.smarks[i]);
                    }
                    fseek(fp,-sizeof(st),SEEK_CUR);
                    fwrite(&st,sizeof(st),1,fp);
                    flag=1;
                    break;
                }
              }
              if(flag==0)
              {
                printf("Sorry! No match found!\n");
              }
              else
              {
                rewind(fp);//Full modified student database are shown from here
                fseek(fp,ssd,SEEK_CUR);

                printf("Modified Database:\n");
                printf("Username,Password,ID,First_Name,Last_Name,Marks respectively: \n");//print student's full database
                while(fread(&st,sizeof(st),1,fp))
                {
                  printf("%s %s %d %s %s ",st.suse,st.spass,st.sid,st.sfname,st.slname);
                  for(i=0;i<nt;i++)
                  {
                    printf("%d ",st.smarks[i]);
                  }
                printf("\n");
              }
            }

            printf("Do yo want to modify another record?(Y/N): ");
            scanf("%s",mschoice);
          }
         }
        }
          else//If choice is not T or S
          {
            printf("Your choice is not T or S\n");
          }
        }
        else
        {
          printf("Something is wrong!\n");
        }
        check=0;
      }
      /********************Teacher panel*****************************************************/
      else if(strcmp(m,"T")==0)
      {
        printf("\t\tWelcome to Teacher Panel\n\n");
        char tinus[10];//input of username from teacher
        printf("Username: ");
        scanf("%s",tinus);
        char tinp[10];//input of password from teacher
        printf("Password: ");
        scanf("%s",tinp);
        rewind(fp);
        std=sizeof(ad)+sizeof(ns)+sizeof(nt);
        fseek(fp,std,SEEK_CUR);

        int flag=0;
        int temp=0;//teacher number
        while(fread(&te,sizeof(te),1,fp))
        {
          temp++;
          if(strcmp(tinus,te.tuse)==0 && strcmp(tinp,te.tpass)==0)
          {
            printf("\nSuccessful login!\n");
            printf("\nPlease follow the instructions below:\n");
            printf("If you want to Provide/Update class test marks,enter 'P'\n");
            printf("If you want to find student by Roll number,enter,'R'\n");
            printf("If you want to find student by First name,enter 'F'\n");
            printf("If you want to know Total number of students,enter 'T'\n");
            char tchoice[2];
            printf("Your Choice: ");
            scanf("%s",tchoice);

            rewind(fp);
            int ssize=sizeof(ad)+sizeof(nt);
            fseek(fp,ssize,SEEK_CUR);
            fread(&ns,sizeof(ns),1,fp);//read the data of total number of students from database

            int tsize=sizeof(ad);
            rewind(fp);
            fseek(fp,tsize,SEEK_CUR);
            fread(&nt,sizeof(nt),1,fp);//read the data of total number of teachers from database

            ssd=sizeof(ad)+sizeof(te)*nt+sizeof(nt)+sizeof(ns);//starting position of student database

            if(strcmp(tchoice,"P")==0)//Provide/Update class test marks
            {
              rewind(fp);
              fseek(fp,ssd,SEEK_CUR);
              int j;

              for(i=0;i<ns;i++)
              {
                fread(&st,sizeof(st),1,fp);
                printf("Student no.%d:\n",i+1);
                printf("Roll: %d\n",st.sid);

                printf("First_Name: %s\n",st.sfname);

                printf("Last_Name: %s\n",st.slname);

                printf("Class Test Marks: ");
                scanf("%d",&st.smarks[temp-1]);

                fseek(fp,-sizeof(st),SEEK_CUR);
                fwrite(&st,sizeof(st),1,fp);
                //printf("Find fp: %ld\n",ftell(fp));
                printf("\n");

              }
              break;
            }
            else if(strcmp(tchoice,"R")==0)//find student by Roll number
            {
              char op[2]="Y";
              while(strcmp(op,"Y")==0)
              {
                rewind(fp);
                fseek(fp,ssd,SEEK_CUR);
                int froll;//finding roll
                printf("Which roll you want to find?: ");
                scanf("%d",&froll);
                while(fread(&st,sizeof(st),1,fp))
                {
                  if(st.sid == froll)
                  {
                    printf("Roll: %d\n",st.sid);
                    printf("First_Name: %s\n",st.sfname);
                    printf("Last_Name: %s\n",st.slname);
                    printf("Class Test Marks: %d\n",st.smarks[temp-1]);
                  }
                }
                printf("Do you want to find another record?(Y/N): ");
                scanf("%s",op);
              }
              break;
            }
            else if(strcmp(tchoice,"F")==0)//find student by First name
            {
              char op[2]="Y";
              while(strcmp(op,"Y")==0)
              {
                rewind(fp);
                fseek(fp,ssd,SEEK_CUR);
                char fname[20];//finding first_name
                printf("Which first_name you want to find?: ");
                scanf("%s",fname);
                while(fread(&st,sizeof(st),1,fp))
                {
                  if(strcmp(fname,st.sfname)==0)
                  {
                    printf("Roll: %d\n",st.sid);
                    printf("First_Name: %s\n",st.sfname);
                    printf("Last_Name: %s\n",st.slname);
                    printf("Class Test Marks: %d\n",st.smarks[temp-1]);
                  }
                }
                printf("Do you want to find another record?(Y/N): ");
                scanf("%s",op);
              }
              break;
            }
            else if(strcmp(tchoice,"T")==0)//know Total number of students
            {
              printf("Total number of students: %d\n",ns);
            }
            else
            {
              printf("Something is wrong!\n");
              printf("Please,follow the instructions and try again!\n");
            }
          }
        }
        check=0;
      }
      /*********************************************Student panel******************************/
      else if(strcmp(m,"S")==0)
      {
        char sinuse[10];//input from student for username
        char sinpass[10];//input from student for password
        printf("\t\tWelcome to Student Panel\n\n");
        printf("Username: ");
        scanf("%s",sinuse);
        printf("Password: ");
        scanf("%s",sinpass);

        char sub[20][100];//couses of teacher assign here
        rewind(fp);
        fseek(fp,sizeof(ad),SEEK_CUR);
        fread(&nt,sizeof(nt),1,fp);
        printf("nt: %d\n",nt);
        rewind(fp);
        std=sizeof(ad)+sizeof(nt)+sizeof(ns);
        fseek(fp,std,SEEK_CUR);
        int j=0;
        for(j=0;j<nt;j++)
        {
          fread(&te,sizeof(te),1,fp);

          strcpy(sub[j],te.tcourse);
        }

        rewind(fp);//find starting position of student database
        ssd=sizeof(ad)+sizeof(te)*nt+sizeof(nt)+sizeof(ns);
        //printf("ssd: %d\n",ssd);

        rewind(fp);
        fseek(fp,ssd,SEEK_CUR);

        int flag=0;
        while(fread(&st,sizeof(st),1,fp))
        {
          //printf("st.suse: %s and st.spass: %s\n",st.suse,st.spass);
          if(strcmp(st.suse,sinuse)==0 && strcmp(st.spass,sinpass)==0)
          {
            printf("successful login!\n\n");
            printf("Your Information: \n");
            printf("Roll: %d\n",st.sid);
            printf("First_Name: %s\n",st.sfname);
            printf("Last_Name: %s\n",st.slname);

            int sum = 0;
            printf("Your Class Test Marks: \n");
            for(i=0;i<nt;i++)
            {
              sum=st.smarks[i]+sum;
              printf("%s: %d\n",sub[i],st.smarks[i]);
            }
            printf("Your Total Marks: %d\n",sum);
            flag=1;
            break;
          }
        }
        if(flag==0)
        {
          printf("Something is wrong!\n");
        }
        check=0;
      }
      else
      {
        printf("\aSomething is going wrong\n");
        printf("May be your mode is not correct!\n");
        printf("Try again!\n");
        char choice[2];
        check=exitfunc(choice);
      }
    }
    fclose(fp);
  }
}
