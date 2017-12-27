/***********************************************************MarksDatabaseSystem************************************************************/
//Author: Shadow Saint ( KEERTHAN BHAT )

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define MAX 50

void add(void);
void modify(void);
void _delete(void);
void list(void);

 struct attend
  { 
    float ca,ct;
  }a;
 
 struct course
  { 
    char name[MAX];
    float q1,q2,q3,t1,t2;
    float l,ss;
    struct attend a;
  }s;

 void main()
 { 
  system("clear");
  int n,o=1;
  printf("\t\t\tWELCOME TO THE MARKS DATABASE\n\n");
  while(o==1)
  { 
   printf("Enter\n1 : Enter marks of a course\n2 : Modify marks of a course\n3 : Delete marks of a course\n4 : Print report card\n");
   scanf("%d",&n);
        switch(n)
        {
            case 1 : add();
                     break;
            case 2 : modify();
                     break;
            case 3 : _delete();
                     break;
            case 4 : list();
                     break;
            default : printf("Invalid choice\n");
                      

        }
        printf("\nEnter 1 to continue, 0 to abort\n");
        scanf("%d",&o);
   }
 }

 void add()
 { 
    FILE *fp;
    fp=fopen("Marks.dat","rb+");
    if(fp==NULL)
    {
        fp=fopen("Marks.dat","wb+");
        if(fp==NULL)
        {
            puts("Cannot open the file\n");
            exit(1);
        }
    }
    
     fseek(fp,0,SEEK_END);
     printf("\nEnter the name of the course:\n");
     scanf("%s",s.name);
     printf("\nEnter the quiz marks in order:\n");
     scanf("%f %f %f",&s.q1,&s.q2,&s.q3);
     printf("\nEnter the test marks in order:\n");
     scanf("%f %f",&s.t1,&s.t2);
     printf("\nEnter the self study marks:\n");
     scanf("%f",&s.ss);
     printf("\nEnter the internal practical lab exam marks:\n");
     scanf("%f",&s.l);
     printf("\nEnter the total and attended number of classes\n");
     scanf("%f %f",&s.a.ct,&s.a.ca);     
     fwrite(&s,sizeof(s),1,fp);
     fclose(fp);
 }
 void modify()
 {
   char name[MAX];
   int flag=0;
   FILE *fp;
    fp=fopen("Marks.dat","rb+");
    if(fp==NULL)
    {
        fp=fopen("Marks.dat","wb+");
        if(fp==NULL)
        {
            puts("Cannot open the file\n");
            exit(1);
        }
    }   
   printf("\nThe coursename whose marks you want to modify:\n");
   scanf("%s",name);
   rewind(fp);
   while(fread(&s,sizeof(s),1,fp)==1)
   { 
     if(strcmp(s.name,name)==0)
     { 
      printf("\nEnter the new name of the course:\n");
      scanf("%s",s.name);
      printf("\nEnter the new quiz marks in order:\n");
      scanf("%f %f %f",&s.q1,&s.q2,&s.q3);
      printf("\nEnter the new test marks in order:\n");
      scanf("%f %f",&s.t1,&s.t2);
      printf("\nEnter the new self study marks:\n");
      scanf("%f",&s.ss);
      printf("\nEnter the new internal practical lab exam marks:\n");
      scanf("%f",&s.l);
      printf("\nEnter the new total and attended number of classes\n");
      scanf("%f %f",&s.a.ct,&s.a.ca);   
      fseek(fp,-sizeof(s),SEEK_CUR);
      fwrite(&s,sizeof(s),1,fp);
      flag=1;
      break;     
     }
   }
  if(flag==0)
  printf("\nNot found, please check your spelling.\n");
  fclose(fp);
 }

 void _delete()
  {        
   char name[MAX];
   int flag=0;
   FILE *fp,*ft;
   fp=fopen("Marks.dat","rb+");
    if(fp==NULL)
    {
        fp=fopen("Marks.dat","wb+");
        if(fp==NULL)
        {
            puts("Cannot open the file\n");
            exit(1);
        }
    }   
   printf("\nThe coursename which you want to delete:\n");
   scanf("%s",name);
   ft=fopen("Tmarks.dat","wb");
   rewind(fp);
   while(fread(&s,sizeof(s),1,fp)==1)
   { 
     if(strcmp(s.name,name)!=0)
     { 
      fwrite(&s,sizeof(s),1,ft);
       }
     if(strcmp(s.name,name)==0)
     flag=1;
   }
   fclose(fp);
   fclose(ft);
   if(flag==0)
   { printf("\nNot found, please check your spelling.\n");
     return;
   }
   remove("Marks.dat");
   rename("Tmarks.dat","Marks.dat");
  }

 void list()
 { 
   FILE *fp;
   fp=fopen("Marks.dat","rb+");
   if(fp==NULL)
    {
        fp=fopen("Marks.dat","wb+");
        if(fp==NULL)
        {
            puts("Cannot open the file\n");
            exit(1);
        }
    }     
   rewind(fp);
   while(fread(&s,sizeof(s),1,fp)==1)
   { 
     printf("\n\n\n\nThe name of the course is: %s\n",s.name);
     printf("\nThe quiz marks in order is: %f %f %f\n",s.q1,s.q2,s.q3);
     printf("\nThe test marks in order is: %f %f\n",s.t1,s.t2);
     printf("\nThe self study marks is: %f\n",s.ss);
     printf("\nThe internal practical lab exam marks is: %f\n",s.l);
     printf("\nThe total and attended number of classes is: %f %f\n",s.a.ct,s.a.ca);
     float t=0;
     float at=s.a.ca/s.a.ct*100;
     if(at<75)
     { printf("\nYou have got NSAR ( Not Satisfied Attendance Requirements )\n");      
       continue;
     }
     if(s.l!=0)
     { 
       t=s.q1+s.q2+s.q3+s.t1/50*30+s.t2/50*30+s.ss+s.l;
       printf("\nYour total in internals in this course is: %f/150\n",t);
       if(t<60)
       printf("\nYou have got NSSR ( Not Satisfied Sessions Requirements )\n");
       else
           { if(t<150&&t>135)
             printf("\nYou have got S grade in this course and have to get %f in end exam to maintain the grade.\n",135-(t-135));
             if(t<135&&t>120)
             printf("\nYou have got A grade in this course and have to get %f in end exam to maintain the grade.\n",120-(t-120));
             if(t<120&&t>105)
             printf("\nYou have got B grade in this course and have to get %f in end exam to maintain the grade.\n",105-(t-105));
             if(t<105&&t>90)
             printf("\nYou have got C grade in this course and have to get %f in end exam to maintain the grade.\n",90-(t-90));
             if(t<90&&t>75)
             printf("\nYou have got D grade in this course and have to get %f in end exam to maintain the grade.\n",75-(t-75));
             if(t<75&&t>60)
             printf("\nYou have got E grade in this course and have to get %f in end exam to maintain the grade.\n",60-(t-60));
           }
     }
     else
     { 
       if(s.ss<=10)
       t=s.q1+s.q2+s.q3+s.t1/50*30+s.t2/50*30+s.ss+s.l;
       else
       t=s.q1+s.q2+s.q3+s.t1/50*25+s.t2/50*25+s.ss+s.l;
       printf("\nYour total in internals in this course is: %f/100\n",t);
       if(t<40)
       printf("\nYou have got NSSR ( Not Satisfied Sessions Requirements )\n");
       else
           { if(t<100&&t>90)
             printf("\nYou have got S grade in this course and have to get %f in end exam to maintain the grade.\n",90-(t-90));
             if(t<90&&t>80)
             printf("\nYou have got A grade in this course and have to get %f in end exam to maintain the grade.\n",80-(t-80));
             if(t<80&&t>70)
             printf("\nYou have got B grade in this course and have to get %f in end exam to maintain the grade.\n",70-(t-70));
             if(t<70&&t>60)
             printf("\nYou have got C grade in this course and have to get %f in end exam to maintain the grade.\n",60-(t-60));
             if(t<60&&t>50)
             printf("\nYou have got D grade in this course and have to get %f in end exam to maintain the grade.\n",50-(t-50));
             if(t<50&&t>40)
             printf("\nYou have got E grade in this course and have to get %f in end exam to maintain the grade.\n",40-(t-40));
           }
     }
   }
 }



    
