//Doctor Patient U19CS075
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
struct dp{
	int did;
	int pid;
};
struct date{
	int dd;
	int mm;
	int yy;
};
struct d{
	struct dp did;
	char dfname[30];
	char dlname[30];
	int dage;
	char dgender;
	char darea[30];
};
struct patient{
	struct dp pid;
	char fname[30];
	char lname[30];
	char area[30];
	int age;
	char gender;
	struct date adate;
	struct date ddate;
};
int count=0;
//Add Patient, Doctor and Associate them
void add()
{
	int r,choice;
	struct d d;
	struct dp dp;
	FILE *fp;
	struct patient p,p1;
	FILE *fp1;
	FILE *fp2;
	printf("\n1. First Add Doctor Details in Doctor File\n");
	printf("2. Add Patient Details\n3. Associate Doctor with Patient");
	while(1)
	{
		int id[100]={0},i,idd,idp;
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				fp= fopen("Doctor.txt", "a+");
				if(fp==NULL)
				{
					printf("\nFailed to open File!");
				}
				else
				{
					printf("Enter New Doctor's ID: ");
					fflush(stdin);
					scanf("%d", &d.did.did);
					printf("Enter New Doctor's First Name: ");
					fflush(stdin);
					scanf("%s", &d.dfname);
					printf("Enter New Doctor's Last Name: ");
					fflush(stdin);
					scanf("%s", &d.dlname);
					printf("Enter New Doctor's age: ");
					fflush(stdin);
					scanf("%d", &d.dage);
					printf("Enter New Doctor's gender (M/F): ");
					fflush(stdin);
					scanf("%c", &d.dgender);
					printf("Enter New Doctor's Address: ");
					fflush(stdin);
					scanf("%s", d.darea);
					fflush(stdin);
					fwrite(&d, sizeof(struct d), 1, fp); //Writing Details to Text File
				}
				fclose(fp);
				break;
			case 2:
				fp1= fopen("Patient.txt", "a+");
				if(fp1==NULL)
				{
					printf("\nFailed to open File!");
				}
				else
				{
					printf("Enter New Patient's ID: ");
					fflush(stdin);
					scanf("%d", &p.pid.pid);
					printf("Enter New Patient's First Name: ");
					fflush(stdin);
					scanf("%s", &p.fname);
					printf("Enter New Patient's Last Name: ");
					fflush(stdin);
					scanf("%s", &p.lname);
					printf("Enter New Patient's age: ");
					fflush(stdin);
					scanf("%d", &p.age);
					printf("Enter New Patient's gender (M/F): ");
					fflush(stdin);
					scanf("%c", &p.gender);
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
				break;
			case 3:
				fp1= fopen("Patient-Doctor.txt", "a+");
				if(fp1==NULL)
				{
					printf("\nFailed to open File!");
				}
				else
				{
				printf("\nEnter the Doctor ID: ");
				scanf("%d", &dp.did);
				fflush(stdin);
				printf("\n1. Enter Patient ID\n2. Return\n");
				while(1)
				{
					int n;
					printf("\nEnter choice: ");
					scanf("%d", &n);
					switch(n)
					{
						case 1:
							printf("\nEnter the Patient ID: ");
							scanf("%d", &dp.pid);
							fflush(stdin);
							fwrite(&dp, sizeof(struct dp), 1, fp1);
							break;
						case 2:
							fclose(fp1);
							return;
						default:
							printf("Invalid Choice!");
					}
				}
				break;		
			case 4:
				return;
			default:
				printf("\nInvalid Choice!");
				break;
		}
	}
}
}
//Discount function to count No of Patients Associated with this Doctor
void discount()
{
	struct dp dp;
	struct d d;
	FILE *fp,*fp1;
	fp=fopen("Patient-Doctor.txt","r+");
	if(fp==NULL)
	{
		printf("Unable to open file.\n");
		return;
	}
	else
	{
		int doc[100]={0};
		while(fread(&dp,sizeof(struct dp),1,fp))
 		{
			doc[dp.did]++;
 		}
		int i=0;
		while(i<100)
		{
			if(doc[i]!=0)
			{
				fp1=fopen("Doctor.txt","r+");
 				if(fp1==NULL)
		 		{
					printf("Unable to open doctor file.\n");
					return;
				}
				while(fread(&d,sizeof(struct d),1,fp1))
				{
					if(d.did.did==i)
					{
						printf("\nName of Doctor: %s %s Total patients %d",d.dfname,d.dlname,doc[i]);
					}
				}
				fclose(fp1);
			}
			i++;
		}
	}
	fclose(fp);
	}

//See the Doctor with Least Number of Patients
void least()
{
	struct dp dp;
	struct d d,d1[20];
	int count[20],i=0,min;
	struct patient p;
	FILE *fp,*fp1;
	fp=fopen("Doctor.txt","r+");
	while(fread(&d,sizeof(struct d),1,fp))
	{
		fp1=fopen("Patient-Doctor.txt","r+");
		while(fread(&dp,sizeof(struct dp),1,fp1))
		{
			if(dp.did==d.did.did)
			{
				count[i]++;
			}
		}
		fclose(fp1);
		d1[i]=d;
		i++;
	}
	fclose(fp);
	//Sorting doctor name according to ascending order
	int l,flag,k,t;
	struct d temp;	
	for(k=0;k<i-1;k++)
	{
		flag=0;
		for(l=0;l<i-1-k;l++)
		{
			if(strcmp(d1[l].dfname,d1[l+1].dfname)>0)
			{
				temp=d1[l];
				d1[l]=d1[l+1];
				d1[l+1]=temp;
				t=count[l];
				count[l]=count[l+1];
				count[l+1]=t;
				flag=1;
			}
		}
		if(flag==0) break;
	}
	//Finding doctor with minimum patient count
	min=0;
	for(k=0;k<i;k++)
	{
		if(count[k]<count[min]) 
		{
			min=k;
		}
	}
	printf("\nDoctor with Minimum patients: %s %s and ID %d",d1[min].dfname,d1[min].dlname,d1[min].did);
	printf("\nNow Please Add a Patient Entry to The Doctor With Minimum Patients");
	add();
}
//Count functions
void summary()
{
	int n;
	printf("\n1. Display count of patient\n2. Display the count of patient based on the gender\n");
	printf("3. Display the age wise count of patient\n4. Display the count of patient areawise\n5. Return");
	while(1)
	{
		printf("\nEnter your choice: ");
		scanf("%d", &n);
		struct dp dp;
		struct d d;
		struct patient p;
		FILE *fp,*fp1;
		int acount,flag=0,v=0,i;
		char word[20],city[count][20]; //For Area Count
		switch(n)
		{
			case 1:
				fp=fopen("Patient-Doctor.txt","r+");
				if(fp==NULL)
				{
					printf("Empty!\n");
					return;
				}
				else
				{
					int doc[100]={0};
					while(fread(&dp,sizeof(struct dp),1,fp))
 					{
						doc[dp.did]++; //Patient Count
 					}
					int i=0;
					while(i<100)
					{
						if(doc[i]!=0)
						{
							fp1=fopen("Doctor.txt","r+");
 							if(fp1==NULL)
							{
								printf("Empty!\n");
								return;
							}
							while(fread(&d,sizeof(struct d),1,fp1))
							{
								if(d.did.did==i)
								{
									printf("Name of Doctor: %s %s",d.dfname,d.dlname);
									printf("Patient Count: %d\n",doc[i]);
								}
							}
							fclose(fp1);
						}
						i++;
					}
				}
				fclose(fp);
				break;
			case 2:
				fp=fopen("Doctor.txt","r+");
				while(fread(&d,sizeof(struct d),1,fp))
				{
					int M=0,F=0,r[30]={0},i=0;
					printf("Name of doctor: %s %s ",d.dfname,d.dlname);
					//Reading patients associated with that doctor
					fp1=fopen("Patient-Doctor.txt","r+");
					while(fread(&dp,sizeof(struct dp),1,fp1))
					{
						if(dp.did==d.did.did)
						{
							r[i]=dp.pid;
							i++;
						}
					}
					fclose(fp1);
					//Checking if patient is male or female
					fp1=fopen("Patient.txt","r+");
					while(fread(&p,sizeof(struct patient),1,fp1))
					{
						if(isthere(p.pid,r,i))
						{
							if(p.gender=='M')
							{
								M++;
							 } 
							else 
							{
								F++;	
							}
						}
					}
					fclose(fp1);
					//Printing count
					printf("Male Patients are %d and Female Patients are %d\n",M,F);
				}
				fclose(fp);
				break;
			case 3:
				fp= fopen("Patient.txt", "r+");
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
					}
					fclose(fp);
					int i=0;
					for(i=0; i<100; i++)
					{
						if(age[i]!=0)  /*All the index with value are being considered*/
						{
							printf("\nNumber of Patients of %d Age are %d", i,age[i]);
						}
					}
				}
				break;
			case 4:
				fp=fopen("Patient.txt","r+"); 
				while(fread(&p,sizeof(struct patient),1,fp)) 
				{ 
				 fclose(fp1);
					int flag=0;
					int countarea=0;
					strcpy(word,p.area); 
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
					FILE *fp2; 
					fp2=fopen("Patient.txt","r+"); 
					while(fread(&p,sizeof(struct patient),1,fp2)) 
					{ 
						if(strcmp(word,p.area)==0) //If area found already Countarea increments
						countarea++; 
					} 
					printf("\nNumber of people in area %s : %d",word,countarea); 
					fclose(fp2); 
					}	 
					fclose(fp); 
				break;
			case 5:
				return;
			default:
				printf("Invalid Choice!");
				break;	
		}
	}
}
int isthere(int val,int arr[],int n)
{
	int i=0;
	for(i=0;i<n;i++)
	{
		if(val==arr[i]) return 1;
	}
	return 0;
}
void display(struct patient p)  //Shows the Details
{ 
	printf("\nPatient id : %d",p.pid.pid);
 	printf("\nFirst Name : %s",p.fname);
 	printf("\nLast Name : %s",p.lname);
 	printf("\nAge : %d",p.age);
 	printf("\nGender : %c",p.gender);
 	printf("\nArea : %s",p.area);
 	printf("\nAdmission Date : %d / %d / %d",p.adate.dd,p.adate.mm,p.adate.yy);
 	printf("\nDischarge Date : %d / %d / %d",p.ddate.dd,p.ddate.mm,p.ddate.yy);
 	printf("\n");
 	printf("\n");

}
//Sorting in Ascending Order 
void ascending()
{
	int n;
	struct patient p,p1[50];
	int pat[50]={0};
	struct d d;
	struct dp dp;
	struct date dy;
	FILE *fp;
	FILE *fp1;
	int i=0,l;
	int j,flag,k;
	struct patient temp;
	printf("\n1. Admitted on same date\n2. Discharged on same date\n");
	printf("3. Patients treated under the doctor\n4. Patients treated under the male doctor\n");
	printf("5. Patients treated under the female doctor area wise\n6. Return");
	while(1)
	{
		printf("\nEnter your choice: ");
		scanf("%d", &n);
		switch(n)
		{
			case 1:
				printf("Enter Admission date: ");
				scanf("%d %d %d",&dy.dd,&dy.mm,&dy.yy);
				fp=fopen("Patient.txt","r+");
				if(fp==NULL)
				{
					printf("Empty!\n");
					return;
				}
				while(fread(&p,sizeof(struct patient),1,fp))
				{
					if(p.adate.dd==dy.dd&&p.adate.mm==dy.mm&&p.adate.yy==dy.yy)
					{
						p1[i]=p;
						i++;
					}
				}
				fclose(fp);
				if(i==0)
				{
					printf("No patients Found!.\n");
					return;
				}
				//Sorting on Basis of ID
				for(k=0;k<i-1;k++)
				{
					flag=0;
					for(j=0;j<i-1-k;j++)
					{
						if(p1[j].pid.pid>p1[j+1].pid.pid)
						{
							temp=p1[j];
							p1[j]=p1[j+1];
							p1[j+1]=temp;
							flag=1;
						}
					}
					if(flag==0) break;
				}
				printf("\nAscending Order On basis of ID on the same Day as Input:");
				for(j=0;j<i;j++)
				{
					display(p1[j]);
				}
				break;
			case 2:
				printf("Enter Discharge date: ");
				scanf("%d %d %d",&dy.dd,&dy.mm,&dy.yy);
				fp=fopen("Patient.txt","r+");
				if(fp==NULL)
				{
					printf("Empty!\n");
					return;
				}
				while(fread(&p,sizeof(struct patient),1,fp))
				{
					if(p.ddate.dd==dy.dd&&p.ddate.mm==dy.mm&&p.ddate.yy==dy.yy)
					{
						p1[i]=p;
						i++;
					}
				}
				fclose(fp);
				if(i==0)
				{
					printf("No patients Found!.\n");
					return;
				}
				//Sorting on Basis of ID
				for(k=0;k<i-1;k++)
				{
					flag=0;
					for(j=0;j<i-1-k;j++)
					{
						if(p1[j].pid.pid>p1[j+1].pid.pid)
						{
							temp=p1[j];
							p1[j]=p1[j+1];
							p1[j+1]=temp;
							flag=1;
						}
					}
					if(flag==0) break;
				}
				printf("\nAscending Order On basis of IDs:");
				for(j=0;j<i;j++)
				{
					display(p1[j]);
				}
				break;
			case 3:
				fp=fopen("Doctor.txt","r+");
				while(fread(&d,sizeof(struct d),1,fp))
				{
					i=0,j=0;
					printf("Doctor Name %s %s and ID: %d\n",d.dfname,d.dlname,d.did.did);
					//Reading all patients associated with that doctor
					fp1=fopen("Patient-Doctor.txt","r+");
					while(fread(&dp,sizeof(struct dp),1,fp1))
					{
						if(dp.did==d.did.did)
						{
							pat[i]=dp.pid; //Adding Patient ID In Array
							i++;
						}
					}
					fclose(fp1);
					printf("\nTotal Count of Patient Underview of this Doctor: %d",i);
					printf("\nAscending Order On basis of IDs: ");
					fp1=fopen("Patient.txt","r+");
					while(fread(&p,sizeof(struct patient),1,fp1))
					{
						if(pre(p,pat,i))
						{
							p1[j]=p;
							j++;
						}
					}
					fclose(fp1);
					//Sorting on Basis of ID
					for(k=0;k<j-1;k++)
					{
						flag=0;
						for(l=0;l<j-1-k;l++)
						{
							if(p1[l].pid.pid>p1[l+1].pid.pid)
							{
								temp=p1[l];
								p1[l]=p1[l+1];
								p1[l+1]=temp;
								flag=1;
							}
						}
						if(flag==0) break;
					}
					for(k=0;k<j;k++)
					{
						display(p1[k]);
					}
				}
				fclose(fp);
				break;
			case 4:
				fp=fopen("Doctor.txt","r+");
				while(fread(&d,sizeof(struct d),1,fp))
				{
					if(d.dgender=='M')
					{
						i=0,j=0;
						printf("Doctor Name %s %s and ID: %d\n",d.dfname,d.dlname,d.did.did);
						//Reading patients associated with that doctor
						fp1=fopen("Patient-Doctor.txt","r+");
						while(fread(&dp,sizeof(struct dp),1,fp1))
						{
							if(dp.did==d.did.did)
							{
								pat[i]=dp.pid; //Adding Patient ID In Array
								i++;
							}
						}
						fclose(fp1);
						printf("\nTotal Count of Patient Underview of this Doctor: %d",i);
						printf("\nAscending Order On basis of IDs: ");
						fp1=fopen("Patient.txt","r+");
						while(fread(&p,sizeof(struct patient),1,fp1))
						{
							if(pre(p,pat,i))
							{
								p1[j]=p;
								j++;
							}
						}
						fclose(fp1);
						//Sorting on Basis of ID
						for(k=0;k<j-1;k++)
						{
							flag=0;
							for(l=0;l<j-1-k;l++)
							{
								if(p1[l].pid.pid>p1[l+1].pid.pid)
								{
									temp=p1[l];
									p1[l]=p1[l+1];
									p1[l+1]=temp;
									flag=1;
								}
							}
							if(flag==0) break;
						}
						for(k=0;k<j;k++)
						{
							display(p1[k]);
						}
					}
				}
				fclose(fp);
				break;
			case 5:
				fp=fopen("Doctor.txt","r+");
				while(fread(&d,sizeof(struct d),1,fp))
				{
					if(d.dgender=='F')
					{
						i=0,j=0;
						printf("Doctor Name %s %s and ID: %d\n",d.dfname,d.dlname,d.did.did);
						//Reading patients associated with that doctor
						fp1=fopen("Patient-Doctor.txt","r+");
						while(fread(&dp,sizeof(struct dp),1,fp1))
						{
							if(dp.did==d.did.did)
							{
								pat[i]=dp.pid; //Adding Patient ID In Array
								i++;
							}
						}
						fclose(fp1);
						printf("\nTotal patients under consultation are: %d",i);
						printf("\nAscending Order On basis of ID: ");
						fp1=fopen("Patient.txt","r+");
						while(fread(&p,sizeof(struct patient),1,fp1))
						{
							if(pre(p,pat,i))
							{
								p1[j]=p;
								j++;
							}
						}
						fclose(fp1);
						//Sorting on Basis of ID
						for(k=0;k<j-1;k++)
						{
							flag=0;
							for(l=0;l<j-1-k;l++)
							{
								if(strcmp(p1[l].area,p1[l+1].area)>0)
								{
									temp=p1[l];
									p1[l]=p1[l+1];
									p1[l+1]=temp;
									flag=1;
								}
							}
							if(flag==0) break;
						}
						for(k=0;k<j;k++)
						{
							display(p1[k]);
						}
					}
				}
				fclose(fp);
				break;
			case 6:
				return;
			default:
				printf("Invalid Number!");
				break;
		}
		
	}
}
int pre(struct patient p,int pat[],int i)
{
	int j=0;
	for(j=0;j<i;j++)
	{
		if(p.pid.pid==pat[j]) 
		{
			return 1;
		}
	}
	return 0;
}

int main()
{
	int n;
	printf("1. Add a record in the doctor file\n2. Display list of doctors treating the number of patients\n");
	printf("3. Add record in the patient-doctor file with doctor having\n   least no of patients");
	printf("and on equal number of patient then consider\n   the alphabetic order of doctor’s name\n");
	printf("4. Various summary reports doctor wise\n");
	printf("5. List all the patient records of the file in ascending order\n6. Exit");
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
				discount();
				break;
			case 3:
				least();	
				break;
			case 4:
				summary();
				break;
			case 5:
				ascending();
				break;
			case 6:
				exit(0);
			default:
				printf("Invalid Number!");
				break;
		}	
	}
	return 0;
}
