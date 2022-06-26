//HOSPITAL MANAGEMENT SYSTEM

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct patient
{
	int id;
	char patientName[50];
	char patientAddress[100];
	char disease[50];
	char date[12];
}p;

struct doctor
{
	int id;
	char name[50];
	char address[100];
	char specialize[100];
}d;

FILE *fp;

void admitPatient()
{
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(p.date, myDate);

    fp=fopen("patient.txt","a");

    printf("Enter Patient id : ");
    scanf("%d",&p.id);

    printf("Enter Patient Name : ");
    fflush(stdin);
    gets(p.patientName);

    printf("Enter Patient Address : ");
    fflush(stdin);
    gets(p.patientAddress);

    printf("Enter Patient Disease : ");
    fflush(stdin);

    gets(p.disease);

    printf("\nPATIENT ADDED SUCCESSFULLY");

    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
}

void patientList()
{
    system("cls");
	printf("\t\t\t<===PATIENT LIST===>\n\n");
	printf("----------------------------------------------------------------------------\n");
	printf("%-10s %-20s %-20s %-10s %s\n","ID","PATIENT NAME","ADDRESS","DISEASE","DATE");
	printf("----------------------------------------------------------------------------\n");

	fp=fopen("patient.txt","r");
	while(fread(&p,sizeof(p),1,fp)==1)
	{
		printf("%-10d %-20s %-20s %-10s %s\n",p.id,p.patientName,p.patientAddress,p.disease,p.date);
	}
	printf("----------------------------------------------------------------------------\n");
	fclose(fp);

}

void dischargePatient()
{
	system("cls");
	FILE *ft;
	int id,f=0;
	printf("\t\t\t<===DISCHARGE PATIENT===>\n\n");
	printf("Enter the ID of the Patient to be discharged : ");
	scanf("%d",&id);
    printf("\n\n");
	fp=fopen("patient.txt","r");
	ft=fopen("temp.txt","w");

	while(fread(&p,sizeof(p),1,fp)==1)
	{
		if(id==p.id)
		{
			f=1;
		}
		else
		{
			fwrite(&p,sizeof(p),1,ft);
		}
	}
	
	if(f==1)
	{
		printf("***THE PATIENT IS DISCHARGED SUCCESSFULLY***\n\n");
	}
	else
	{
		printf("***RECORD NOT FOUND***\n\n");
	}

	fclose(fp);
	fclose(ft);

	remove("patient.txt");
	rename("temp.txt","patient.txt");
}


void addDoctor()
{

    printf("\n\n<== ADD DOCTOR ==>\n\n");

	fp = fopen("doc.txt","ab");

	printf("Enter Doctor id : ");
	scanf("%d",&d.id);

	printf("Enter Doctor Name : ");
	fflush(stdin);
	gets(d.name);

	printf("Enter Doctor Address : ");
	fflush(stdin);
	gets(d.address);

	printf("Enter Specialization : ");
	fflush(stdin);
	gets(d.specialize);

    printf("\n\nDOCTOR ADDED SUCCESSFULLY\n\n");

	fwrite (&d,sizeof(d),1,fp);
	fclose (fp);
}

void doctorList()
{
	system("cls");
	printf("\t\t\t<===DOCTOR LIST===>\n\n");
	printf("---------------------------------------------------------------------------\n");
	printf("%-10s %-20s %-20s %-10s\n","ID","DOCTOR NAME","ADDRESS","SPECIALIZATION");
	printf("---------------------------------------------------------------------------\n");

	fp=fopen("doc.txt","rb");
	while(fread(&d,sizeof(d),1,fp))
	{
		printf("%-10d %-20s %-20s %-10s\n",d.id,d.name,d.address,d.specialize);
	}
	
	fclose(fp);
}

int main()
{
    system("cls");
	int ch;
	
	while(1)
	{
		printf("<///HOSPITAL MANAGEMENT SYSTEM///>\n\n");
		printf("1.ADMIT PATIENT\n");
		printf("2.PATIENT LIST\n");
		printf("3.DISCHARGE PATIENT\n");
		printf("4.ADD DOCTOR\n");
		printf("5.DOCTOR's LIST\n");
		printf("0.EXIT\n\n\n");
		printf("ENTER YOUR CHOICE : ");

		scanf("%d",&ch);
		
		switch(ch)
		{
			case 0:
				exit(0);
				
			case 1:
				admitPatient();
				break;
				
			case 2:
				patientList();
				break;
				
			case 3:
				dischargePatient();
				break;
				
			case 4:
				addDoctor();
				break;
				
			case 5:
				doctorList();
				break;
				
			default:
				printf("INVALID CHOICE.....\n\n");
		}
		printf("\n\nPRESS ANY KEY TO CONTINUE....\n\n");
		getchar();
	}
	return 0;
}