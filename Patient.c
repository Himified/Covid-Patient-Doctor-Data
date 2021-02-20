#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
struct date{
	int dd;
	int mm;
	int yy;
};
struct patient{
	int id;
	char fname[30];
	char lname[30];
	char area[30];
	int age;
	char gender[20];
	struct date adate;
	struct date ddate;
};
int count=0;
void countt()  //Keeps Record of Total Count of Patients
{
	struct patient p;
	FILE *fp;
	fp= fopen("Suratcovid.txt", "r+"); //File Name
	if(fp==NULL)
	{
		printf("No data In Record!");
	}
	else
	{
		while(fread(&p,sizeof(struct patient),1,fp))
		{
			count++;	
		}
	}
	fclose(fp);
}
void add()
{
	struct patient p;
	FILE *fp;
	fp= fopen("Suratcovid.txt", "a+");
	if(fp==NULL)
	{
		printf("\nFailed to open File!");
	}
	else
	{
	printf("Enter New Patient's ID: ");
	fflush(stdin);
	scanf("%d", &p.id);
	printf("Enter New Patient's First Name: ");
	fflush(stdin);
	scanf("%s", &p.fname);
	printf("Enter New Patient's Last Name: ");
	fflush(stdin);
	scanf("%s", &p.lname);
	printf("Enter New Patient's age: ");
	fflush(stdin);
	scanf("%d", &p.age);
	printf("Enter New Patient's gender: ");
	fflush(stdin);
	scanf("%s", &p.gender);
	printf("Enter New Patient's Address: ");
	fflush(stdin);
	scanf("%s", p.area);
	printf("Enter New Admission Date: ");
	fflush(stdin);
	scanf("%d/%d/%d", &p.adate.dd, &p.adate.mm, &p.adate.yy);
	printf("Enter New Discharge Date: ");
	fflush(stdin);
	scanf("%d/%d/%d", &p.ddate.dd, &p.ddate.mm, &p.ddate.yy);
	fflush(stdin);
	fwrite(&p, sizeof(struct patient), 1, fp); //Writing Details to Text File
	count++;
	}
	fclose(fp);
}

void display()  //Shows the Details
{ 
	struct patient p;
	FILE *fp;
	fp= fopen("Suratcovid.txt", "r+");
	if(fp==NULL)
	{
		printf("No data In Record!");
	}
	else
	{
		while(fread(&p,sizeof(struct patient),1,fp))
		{
			printf("\n");
			printf("\nPatient ID: %d", p.id);
			printf("\nPatient First Name: %s", p.fname);
			printf("\nPatient Last Name: %s", p.lname);
			printf("\nPatient Gender: %s", p.gender);
			printf("\nPatient Age: %d", p.age);
			printf("\nPatient Address: %s", p.area);
			printf("\nPatient Appointment Date: %d / %d / %d", p.adate.dd, p.adate.mm, p.adate.yy);
			printf("\nPatient Discharge Date: %d / %d / %d", p.ddate.dd, p.ddate.mm, p.ddate.yy);	
		}
	}
	fclose(fp);
}
void deletef()
{
	struct patient p1;
	FILE *fp;
	FILE *fp1;
	fp=fopen("Suratcovid.txt","r+");
	if(fp==NULL)
	{
		printf("Records empty!");
		fclose(fp);
		return;
	}
	else
	{
		fp1=fopen("copy.txt","a+");
		int n,flag=0;
		printf("\nEnter the Patient's ID to be Deleted/Updated : ");
		scanf("%d",&n);
		while(fread(&p1,sizeof(struct patient),1,fp))
		{
			if(p1.id!=n)  
			{
				fwrite(&p1,sizeof(struct patient),1,fp1); //Writing Details in Copy Text File
			}
			else
			{
				flag=1;  /*The deleted Item is Ignored and all the remaing text is written in Copy text file*/
			}
		}
	fclose(fp);
	fclose(fp1);
	remove("Suratcovid.txt"); /*Deleting previous text file with all details */
	rename("copy.txt","Suratcovid.txt"); /*The final text file "copy" is being renamed as Suratcovid as it has all the required details*/
	if(flag==1)
	{
		printf("\nRecord has been Deleted!");
		count--;
	}
	else
	{
		printf("Record Not Found!");
	}
	}
}

void summary()
{
	struct patient p,p1;
	FILE *fp;
	FILE *fp1;
	fp= fopen("Suratcovid.txt", "r+");
	if(fp==NULL)
	{
		printf("No data In Record!");
	}
	else
	{
		int age[100]={0},f=0;
		while(fread(&p,sizeof(struct patient),1,fp))
		{
			age[p.age]++; /*Storing age group gap using array indexing*/
			if(p.gender =="Female")
			{
				f++;
			}
	}
	fclose(fp);
	printf("\nTotal Number of Patients are %d", count); //Simple count of patients
	int i=0;
	for(i=0; i<100; i++)
	{
		if(age[i]!=0)  /*All the index with value are being considered*/
		{
			printf("\nNumber of Patients of %d Age are %d", i,age[i]);
		}
	}
	printf("\nNumber of Female Patients: %d", count-f);
	printf("\nNumber of Male Patients: %d", f);
	
	int acount,flag=0,v=0;
	fp=fopen("Suratcovid.txt","r+"); 
	char word[20],city[count][20]; //For Area Count
	while(fread(&p1,sizeof(struct patient),1,fp)) 
	{ 
		int flag=0;
		int countarea=0;
		strcpy(word,p1.area); 
		for(i=0;i<v;i++) 
		{ 
			if(strcmp(word,city[i])==0) 
			{
				flag=1; 
			 } 
			/*If City Matches Word it will skip the process and then at the end iterate the count v*/
		} 
		if(flag==1) 
		{ 
			continue; 
		} 
		else 
		{ 
			strcpy(city[v],word); //Passing the area to word
			v++; 
		} 
		FILE *fp1; 
		fp1=fopen("Suratcovid.txt","r+"); 
		while(fread(&p1,sizeof(struct patient),1,fp1)) 
		{ 
			if(strcmp(word,p1.area)==0) //If area found already Countarea increments
			countarea++; 
		} 
		printf("\nNumber of people in area %s : %d",word,countarea); 
		fclose(fp1); 
	} 
	fclose(fp); 
	}
}

void list()
{
	int n; 
	FILE *fp; 
	fp=fopen("Suratcovid.txt","r+"); 
	if(fp==NULL) 
	{
	 printf("Failed to sort! Records Empty "); 
	 fclose(fp); 
	 return; 
	} 
	fclose(fp); 
	printf("\n\n1.Ascending order\n2.Descending order"); 
	printf("\nChoice : "); 
	scanf("%d",&n); 
	if(n==1) //ASCENDING 
	{ 
		printf("\nSort by "); 
		printf("\n1.First Name\n2.Last Name\n3.Age\n4.Discharge Date\nChoose : "); 
		int tch; 
		scanf("%d",&tch); 
		switch(tch) 
		{
		 case 1: 
		 	firstname(n); 
			break; 
		case 2: 
			lastname(n); 
			break; 
		case 3: 
			age(n); 
			break; 
		case 4:
			dates(n); 
			break; 
		default: 
			printf("\n\nInvalid choice!!"); 
			break; 
		} 
	} else if(n==2) //DESCENDING 
	{ 
		printf("\nSort by "); 
		printf("\n1.First Name\n2.Last Name\n3.Age\n4.Discharge Date\nChoose : "); 
		int tch; 
		scanf("%d",&tch); 
		switch(tch) 
		{ 
			case 1: 
				firstname(n); 
				break; 
			case 2: 
				lastname(n); 
				break; 
			case 3: 
				age(n); 
				break; 
			case 4: 
				dates(n); 
				break; 
			default: 
				printf("\n\nInvalid choice!!"); 
				break; 
			} 
		} 
		else 
		{ 
			printf("\n\nInvalid Choice!"); 
		} 
	}


int firstname(int n)
{
	struct patient p[count],p1,temp; 
	int i=0,j; 
	FILE *fp; 
	fp=fopen("Suratcovid.txt","r+"); 
	while(fread(&p1,sizeof(struct patient),1,fp)) 
	{
		p[i]=p1; 
		i++; 
	} 
	if(n==1) //For Ascending  
	{ 
		for(i=1;i<count;i++)
		{ 
			for(j=0;j<count-i;j++) 
			{ 
				if(strcmp(p[j+1].fname,p[j].fname)<0) 
					{ 
						temp=p[j]; 
						p[j]=p[j+1]; 
						p[j+1]=temp; 
					} 
			} 
		} 
}
		else //FOR Descending 
		{ 
			for(i=1;i<count;i++) {
				for(j=0;j<count-i;j++)
				{ 
					if(strcmp(p[j+1].fname,p[j].fname)>0) 
						{ temp=p[j]; 
						  p[j]=p[j+1]; 
						  p[j+1]=temp;
						 } 
				} 
		}
			}  
		FILE *fp1; 
		fp1=fopen("sorted.txt","a+"); 
		for(i=0;i<count;i++) 
		{
		 fwrite(&p[i],sizeof(struct patient),1,fp1); 
		} 
		fclose(fp); 
		fclose(fp1); 
		remove("Suratcovid.txt"); 
		rename("sorted.txt","Suratcovid.txt"); 
		printf("\nSorted Record is : \n"); 
		display();
}

int lastname(int n)
{
	struct patient p[count],p1,temp; 
	int i=0,j; 
	FILE *fp; 
	fp=fopen("Suratcovid.txt","r+"); 
	while(fread(&p1,sizeof(struct patient),1,fp)) 
	{
		p[i]=p1; 
		i++; 
	} 
	if(n==1) //For Ascending order 
	{ 
		for(i=1;i<count;i++)
		{ 
			for(j=0;j<count-i;j++) 
			{ 
				if(strcmp(p[j+1].lname,p[j].lname)<0) 
					{ 
						temp=p[j]; 
						p[j]=p[j+1]; 
						p[j+1]=temp; 
					} 
			} 
		} 
}
		else //FOR descending 
		{ 
			for(i=1;i<count;i++) {
				for(j=0;j<count-i;j++)
				{ 
					if(strcmp(p[j+1].lname,p[j].lname)>0) 
						{ temp=p[j]; 
						  p[j]=p[j+1]; 
						  p[j+1]=temp;
						 } 
				} 
		}
			}  
		FILE *fp1; 
		fp1=fopen("sorted.txt","a+"); 
		for(i=0;i<count;i++) 
		{
		 fwrite(&p[i],sizeof(struct patient),1,fp1); 
		} 
		fclose(fp); 
		fclose(fp1); 
		remove("Suratcovid.txt"); 
		rename("sorted.txt","Suratcovid.txt"); 
		printf("\nSorted Record is : \n"); 
		display();
}

int age(int n)
{
	struct patient p[count],p1,temp; 
	int i=0,j; 
	FILE *fp; 
	fp=fopen("Suratcovid.txt","r+"); 
	while(fread(&p1,sizeof(struct patient),1,fp)) 
	{
		p[i]=p1; 
		i++; 
	} 
	if(n==1) //For Ascending  
	{ 
		for(i=1;i<count;i++)
		{ 
			for(j=0;j<count-i;j++) 
			{ 
				if(p[j+1].age<p[j].age) 
					{ 
						temp=p[j]; 
						p[j]=p[j+1]; 
						p[j+1]=temp; 
					} 
			} 
		} 
}
		else //FOR descending 
		{ 
			for(i=1;i<count;i++) {
				for(j=0;j<count-i;j++)
				{ 
					if(p[j+1].age>p[j].age) 
						{ temp=p[j]; 
						  p[j]=p[j+1]; 
						  p[j+1]=temp;
						 } 
				} 
		}
			}  
		FILE *fp1; 
		fp1=fopen("sorted.txt","a+"); 
		for(i=0;i<count;i++) 
		{
		 fwrite(&p[i],sizeof(struct patient),1,fp1); 
		} 
		fclose(fp); 
		fclose(fp1); 
		remove("Suratcovid.txt"); 
		rename("sorted.txt","Suratcovid.txt"); 
		printf("\nSorted Record is : \n"); 
		display();
}

int dates(int n)
{
	struct patient p[count],p1,temp; 
	int i=0,j; 
	FILE *fp; 
	fp=fopen("Suratcovid.txt","r+"); 
	while(fread(&p1,sizeof(struct patient),1,fp)) 
	{
		p[i]=p1; 
		i++; 
	} 
	if(n==1) //For Ascending  
	{ 
		for(i=1;i<count;i++)
		{ 
			for(j=0;j<count-i;j++) 
			{ 
				if(compare(p[j+1].adate,p[j].adate)<0) 
					{ 
						temp=p[j]; 
						p[j]=p[j+1]; 
						p[j+1]=temp; 
					} 
			} 
		} 
}
		else //FOR descending 
		{ 
			for(i=1;i<count;i++) 
			{
				for(j=0;j<count-i;j++)
				{ 
					if(compare(p[j+1].ddate,p[j].ddate)>0) 
						{ 
						  temp=p[j]; 
						  p[j]=p[j+1]; 
						  p[j+1]=temp;
						} 
				} 
		}
			}  
		FILE *fp1; 
		fp1=fopen("sorted.txt","a+"); 
		for(i=0;i<count;i++) 
		{
		 fwrite(&p[i],sizeof(struct patient),1,fp1); 
		} 
		fclose(fp); 
		fclose(fp1); 
		remove("Suratcovid.txt"); 
		rename("sorted.txt","Suratcovid.txt"); 
		printf("\nSorted Record is : \n"); 
		display();
}

void range()
{
	struct patient p;
	struct date d;
		int mon,year;
	FILE *fp;
	fp= fopen("Suratcovid.txt", "r+");
	if(fp==NULL)
	{
		printf("No data In Record!");
	}
	else
	{   
		int cho,flag=0;
		printf("\n1.Display Next 10 Records From H\n2.Admission date from user given date to next 10 dates");
		printf("\n3.Admission month from user given month to next 5 months\n4. Return");
		while(1)
		{
			printf("\nEnter your choice: ");
			scanf("%d", &cho);
			switch(cho)
			{
				case 1:
					while(fread(&p,sizeof(struct patient),1,fp)) 
					{ 
						if((p.fname[0]>='H'&&p.fname[0]<='Q')||(p.fname[0]>='h'&&p.fname[0]<='q')) 
							{  
								printf("\nPatient Number : %d",p.id); 
								printf("\nFirst Name : %s",p.fname); 
								printf("\nLast Name : %s",p.lname); 
								printf("\nAge : %d",p.age); 
								printf("\nGender : %c",p.gender); 
								printf("\nArea : %s",p.area); 
								printf("\nAdmission Date : %d / %d / %d",p.adate.dd,p.adate.mm,p.adate.yy); 
								printf("\nDischarge Date : %d / %d / %d",p.ddate.dd,p.ddate.mm,p.ddate.yy);
								flag=1; 
							} 
					} 
					fclose(fp);
					if(flag==0) 
					{ 
						printf("\n\nNo Record found!"); 
					} 
					break;
				case 2:
					printf("Enter date to get next 10 dates data (dd mm yy): ");
					scanf("%d %d %d",&d.dd,&d.mm,&d.yy);
					int year=d.yy,month=d.mm,date=d.dd,i;
					int m[2]={month,(month+1)%12},dy[10];
					for(i=0;i<10;i++) dy[i]=(date+i+1)%monthType(month,year); //Calculate the next 10 days from the given date
					struct patient p1;
					FILE *fp;
					fp=fopen("Suratcovid.txt","r+");
					if(fp==NULL) {
						printf("Failed to load!!!");
						fclose(fp);
						return;
						}
					else
					{
						while(fread(&p1,sizeof(struct patient),1,fp))
	 					{	
							if(ispresent(dy,p1.adate.dd,10))
							{
								if((p1.adate.dd>date&&p1.adate.mm==month&&p1.adate.yy==year)||(p1.adate.dd<date&&p1.adate.mm==m[1]&&p1.adate.yy==year&&m[1]!=1)||(p1.adate.dd<date&&p1.adate.mm==m[1]&&p1.adate.yy==year+1&&m[1]==1))
									show(p1);
							}
	   					}
					}
					fclose(fp);
					break;
				case 3:
					printf("Enter date to get next 5 months data (dd mm yy): ");
					scanf("%d %d %d",&d.dd,&d.mm,&d.yy);
					int y[5];
					for(i=1;i<6;i++) y[i]=(month+i)%12;
					fp=fopen("Suratcovid.txt","r+");
					if(fp==NULL) {
						printf("Failed to load!!!");
						fclose(fp);
						return;
						}
					else
					{
						while(fread(&p1,sizeof(struct patient),1,fp))
	 					{	
							if((p1.adate.yy==year&&ispresent(y,p1.adate.mm,5)&&p1.adate.mm>month)||(p1.adate.yy==year+1&&ispresent(y,p1.adate.mm,5)&&p1.adate.mm<month)){
							show(p1);
						}
	   					}
					}
					fclose(fp);
					break;
				case 4:
					return;
				default:
					printf("Invalid Choice!");
					break;
			}
		}
	}
}

//Auxilary Function
int show(struct patient p){
		printf("\nPatient id : %d",p.id); 
	    printf("\nFirst Name     : %s",p.fname);
	    printf("\nLast Name      : %s",p.lname);
	    printf("\nAge            : %d",p.age);
	    printf("\nGender         : %c",p.gender);
	    printf("\nArea           : %s",p.area);
	    printf("\nAdmission Date : %d / %d / %d",p.adate.dd,p.adate.mm,p.adate.yy);
	    printf("\nDischarge Date : %d / %d / %d",p.ddate.dd,p.ddate.mm,p.ddate.yy);
}
int ispresent(int arr[],int val,int n){
	int i=0;
	for(i=0;i<n;i++){
		if(val==arr[i]) return 1;
	}
	return 0;
}

//Find whether the month has 30 days or 31
int monthType(int m,int y){
	if(m==1||m==3||m==5||m==8||m==10||m==12) return 31;
	else if(m==4||m==6||m==7||m==9||m==11) return 30;
	if(y%4==0&&m==2) return 29;
	return 28;
}

int compare(struct date d1,struct date d2){
	if(d1.yy>d2.yy){
		return 1;
	}else if(d1.yy<d2.yy){
		return -1;
	}else{
		if(d1.mm>d2.mm){
			return 1;
		}else if(d1.mm<d2.mm){
			return -1;
		}else{
			if(d1.dd>d2.dd){
				return 1;
			}else if(d1.dd<d2.dd){
				return -1;
			}else{
				return 0;
			}
		}
	}
}

void separate()
{
	FILE *fp,*fp1,*fp2;
	struct patient p1;
	fp=fopen("Suratcovid.txt","r+");
	fp2=fopen("Male.txt","a+");
	fp1=fopen("Female.txt","a+");
	if(fp==NULL) printf("Failed to load!!!");
	else
	{
		while(fread(&p1,sizeof(struct patient),1,fp))
	 	{	
			if(p1.gender=="Female") fwrite(&p1,sizeof(struct patient),1,fp1);
			else fwrite(&p1,sizeof(struct patient),1,fp2);
	   	}
	}
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	printf("The records have been separated.\n");
}

int main()
{
	int n;
	printf("1. Add a record in the file\n2. Delete a record in the file\n3. Modify the record in the file");
	printf("\n4. Summary Counts\n5. List in Certain Order\n6. List in Specific Range\n7. Display\n8. Separate Male and Female Files\n9.Exit");
	while(1)
	{
		printf("\nEnter your choice: ");
		scanf("%d", &n);
		switch(n)
		{
			case 1:
				add();
				break;
			case 2:
				deletef();
				break;
			case 3:
				deletef();
				add();	
				break;
			case 4:
				summary();
				break;
			case 5:
				list();
				break;
			case 6:
				range();
				break;
			case 7:
				display();
				break;
			case 8:
				separate();
				break;
			case 9:
				exit(0);
			default:
				printf("Invalid Number!");
				break;
		}	
	}
	return 0;
}


