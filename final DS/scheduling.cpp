#include <bits/stdc++.h>
#include <time.h>
using namespace std;

int k,t;
int n,i,j,e[100][100],e2[100][100],n0;
void day_allocation(int dayno);
void printdayname(int dayno);
int maxcolors=3;	// max periods per day
int maxsubjects=4;
int totalclass=3;	// MI5 5 4
int maxclasses_perweek=4;
int recoloring=0;

struct vertex
{
char name[30];
char className[15];
char teacherName[15];
int edge,color,count,p;
int count_backup;
int color1;	// if another period is allocated to same period on single day
}v[100],v2[100];

char temp_name[15];

int main()
{
	srand(time(NULL));		// Important statement

	
	printf("Enter no. of Branches: ");
	scanf("%d",&totalclass);  //no. of classes
	printf("Enter maximum subject per class: ");
	scanf("%d",&maxsubjects); 
	n=maxsubjects*totalclass;//nodes
	
	printf("Enter maximum periods of a teacher per week: ");
	scanf("%d",&maxclasses_perweek);
	printf("Enter no. of classes per day: " );
	scanf("%d",&maxcolors);
	printf("Enter classname/teachername:\n");
	for(i=0;i<n;i++){
		  scanf("%s",v[i].name); //scan nodes

		  int index=0;	// index of '/'
		  for(j=0;j<strlen(v[i].name);j++){		  	
			if(v[i].name[j]=='/'){
		  		index=j; break;
		  	}
		  }
		  

		  for(j=0;j<strlen(v[i].name);j++){

		  	if(j<index){
		  		v[i].className[j]=v[i].name[j];
		  	}else if(j>index){
		  		v[i].teacherName[j-index-1]	= v[i].name[j];
		  	}
		}
	}


	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
		//scanf("%d",&e[i][j]);

	       if(i==j){
			e[i][j]=0;
		   }else{
			int flag=1;
			//matching classname
			for(k=0;k<strlen(v[i].className);k++){
				if(v[i].className[k]!=v[j].className[k]){
					flag=0;
					break;
				}
			}

			if(flag==0){flag=1;	//matching teachername
				for(k=0;k<strlen(v[i].teacherName);k++){
				if(v[i].teacherName[k]!=v[j].teacherName[k]){
					flag=0;
					break;
				}
			  }
			}

			if(flag==1){
				e[i][j]=1;
			}else{
				e[i][j]=0;
			}
		}

	//	printf("%d ",e[i][j] );
	  }	
	  //printf("\n");
	}

	    	for(i=0;i<n;i++){	
		v[i].color=0;
		v[i].count=0;
	}

	printf("\nDay 1 schedule ( ");
	printdayname(1);
	printf(" )\n\n");
	day_allocation(1);
	recoloring=0;

	for(i=0;i<n;i++){
		v[i].color=0;
		v[i].count_backup=v[i].count;
	}

	printf("\nDay 2 schedule (");
	printdayname(2);
	printf(")\n\n");
	day_allocation(2);
	recoloring=0;

	for(i=0;i<n;i++){
		v[i].color=0;
		v[i].count_backup=v[i].count;
	}



	printf("\nDay 3 schedule (");
	printdayname(3);
	printf(")\n\n");
	day_allocation(3);
	recoloring=0;

	for(i=0;i<n;i++){
		v[i].color=0;
		v[i].count_backup=v[i].count;
	}



	printf("\nDay 4 schedule (");
	printdayname(4);
	printf(")\n\n");
	day_allocation(4);
	recoloring=0;

	for(i=0;i<n;i++){
		v[i].color=0;
		v[i].count_backup=v[i].count;
	}


	printf("\nDay 5 schedule (");
	printdayname(5);
	printf(")\n\n");
	day_allocation(5);
	recoloring=0;

	for(i=0;i<n;i++){
		v[i].color=0;
		v[i].count_backup=v[i].count;
	}

	printf("\n");

}

void day_allocation(int dayno){
	if(dayno!=5){
		// for monday to thursday
		
		for(int class1=1;class1<=totalclass;class1++){
			int random1=random()%maxsubjects;	// between 0 to 3
			//printf("random : %d\n",random1 );
			//printf("for class %d\n",class1 );

				// for any-other class
				int allocat=0;	
				int j=random1+(class1-1)*maxsubjects;
				//printf("for class %d random j is %d\n",class1,j );

				if(dayno>=2){
					int min=9999999,index=0;
					for(i=(class1-1)*maxsubjects;i<(class1)*maxsubjects;i++){
						if(v[i].count<min){
							min=v[i].count;
							index=i;
						}
					}

					j=index;
				}

				while(allocat!=maxcolors){
					// j loops between all subjects of a class
					// allot in sequence c1, c2, c3...
					if(j==maxsubjects*class1){
						j=0+(class1-1)*maxsubjects;
					}

					if(v[j].color==0){
						int flag=0;

						for(int hh=0;hh<n;hh++){	//checking
							if(e[j][hh]==1){
								if(v[hh].color==allocat+1){
									// so 'allocat'th period cannot be assigned to this
									//j++;
									flag=1;
									
									break;
								}

							}
						}

						if(flag==0){
							//printf("for j= %d allocat = %d is assigned\n",j,allocat +1);
							// so 'allocat'th period will be assigned to jth subject
							v[j].color=allocat+1;
							v[j].count++;
							allocat++;
							//j++;
						}
					}
					j++;

					if(allocat<=2){	// to randomize order of allotment of periods
						j=random()%maxsubjects+(class1-1)*maxsubjects;
					}

					recoloring++;

					if(recoloring>=50){
						printf("Coloring failed. ReColoring the graph...\n\n");
					recoloring=0;
						
						for(i=0;i<n;i++){
							v[i].color=0;
							v[i].count=v[i].count_backup;
						}

						day_allocation(dayno);
						return;
					}
				}	
		}
	}else{
		// for day 5 only
		
		for(int class1=1;class1<=totalclass;class1++){
			int random1=random()%maxsubjects;	// between 0 to 3

			int sum_of_classes=0;
			int j=random1+(class1-1)*maxsubjects;

			int allocat=1;

			while(sum_of_classes!=maxclasses_perweek*maxsubjects){		// here 4 is the max number a class can be teached in a week
				if(j==maxsubjects*class1){
						j=0+(class1-1)*maxsubjects;
				}
//				if(allocat==6){allocat=1;}

				int diff=maxclasses_perweek-v[j].count;
				if(diff!=0){
					
					//printf("for j= %d allocat = %d is assigned\n",j,allocat);
					int flag=0;
					for(int hh=0;hh<n;hh++){	//checking
							if(e[j][hh]==1){
								if(v[hh].color==allocat || v[hh].color1==allocat){
									// so 'allocat'th period cannot be assigned to this
									//j++;
									flag=1;
									break;
								}

							}
						}

					if(flag==0){
					   if(v[j].color==0){
						v[j].color=allocat;
							
					}else{
						v[j].color1=allocat;
					}

						allocat++;
						v[j].count++;
					}
					
					
					
				}

				sum_of_classes=0;
				for(i=(class1-1)*maxsubjects;i<(class1)*maxsubjects;i++){
					sum_of_classes+=v[i].count;
				}

				j++;
				recoloring++;

				if(recoloring>=50){
						printf("Coloring failed. ReColoring the graph...\n\n");
					recoloring=0;
						
						for(i=0;i<n;i++){
							v[i].color=0;
							v[i].count=v[i].count_backup;
						}

						day_allocation(dayno);
						return;
					}
			}


		}


	}

	// print schedule 
	for(i=0;i<n;i++)
	{
		if(v[i].color1==0){
			printf("%-15s  Period : %d (total= %d) ",v[i].name,v[i].color,v[i].count);
		}else{
			printf("%-15s  Period : %d,%d (total= %d) ",v[i].name,v[i].color,v[i].color1,v[i].count);
		}

	printf("\n");
	}

}

void printdayname(int dayno){
		string day_name="Unknown";
		
		switch(dayno){
			case 1:printf("Monday");
			break;
			case 2: printf("Tuesday");
			break;
			case 3: printf("Wednesday");
			break;
			case 4: printf("Thursday");
			break;
			case 5: printf("Friday");
			break;
			case 6: printf("Saturday");
			break;	
		}

}