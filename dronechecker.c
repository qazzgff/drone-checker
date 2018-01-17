// 6521617 zy21617 Zijian Chen
#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>
//the following link_list structure and list_append list_get list_length list_free functions were taken form lecture.
struct int_list {
   int value;
   struct int_list *next;
};
typedef struct int_list IntList;

void list_free(IntList **start)
{
   IntList *cur = *start;
   while(cur != NULL)
   {
      IntList *temp = cur->next;
      free(cur);
      cur = temp;
   }
   *start = NULL;
}

//add an element to the end of the list
int list_append(IntList **start, int val)
{
   if(*start == NULL)
   {
      IntList *n = malloc(sizeof(IntList));
      if(n == NULL)
      {
	 printf("Unable to allocate memory.");// error, cannot allocate memory for new list node.
	 exit(5);
      }
      n->value = val;
      n->next = NULL;
      *start = n;
   }
   else
   {
      IntList *cur = *start;
      while(cur->next != NULL)
      {
	 cur = cur->next;
      }
      IntList *n = malloc(sizeof(IntList));
      if(n == NULL)
      {
	 // error, cannot allocate memory for new list node.
	 return 0;
      }
      n->value = val;
      n->next = NULL;
      cur->next = n;
   }
   return 1;
}

//get the nth element of the list
int list_get(IntList *start, int n)
{
   IntList *cur = start;
   if(n < 0)
   {
      return -1;
   }
   while(cur != NULL)
   {
      if(n == 0)
      {
	 return cur->value;
      }
      else
      {
	 n--;
	 cur = cur->next;
      }
   }
   return -1;
}

// get the length of the list
int list_length(IntList *start)
{
   int len = 0;
   IntList *cur = start;
   while(cur != NULL)
   {
      len++;
      cur = cur->next;
   }
   return len;
}

// delete the last value of the list.
int list_delete(IntList **start) 
{
   if(*start == NULL)
   {
	 return 0;
   }
   else
   {
      IntList *prvcur = *start;
      IntList *cur = prvcur->next;
      while(cur->next != NULL)
      {
	 cur = cur->next;
	 prvcur = prvcur->next;
      }
      prvcur->next = NULL;
   }
   return 1;
}

// return true if the line intersect the circle
int intersect(int Ax, int Ay, int Bx, int By, int Cx, int Cy, int r)
{
	double X = Ax*Ax - (2*Ax*Bx) + Bx*Bx + Ay*Ay -(2*Ay*By) + By*By;
	double Y = (2*Cx*Bx)-(2*Cx*Ax)-(2*Cy*Ay)+(2*Cy*By)+(2*Ax*Bx)+(2*Ay*By)-(2*Bx*Bx)-(2*By*By);
	double Z = Cx*Cx-(2*Cx*Bx)+Cy*Cy-(2*Cy*By)-r*r+Bx*Bx+By*By;
	double discrim = Y*Y - (4*X*Z);
	
	if (discrim<0)
	{
		return 0;			
	}
	double t1 = (-Y + sqrt(discrim))/(2*X);
	double t2 = (-Y - sqrt(discrim))/(2*X);
	if(t1>=0.00 && t1<=1.00)
	{
		return 1;
	}
	else if(t2>=0.00 && t2<=1.00)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

// return true if the point is in the zone
int in_zone(int Ax, int Ay, int Cx, int Cy, int r)
{
	double distance;
	double dr;	
	dr = (double)r;
	distance = sqrt( (Ax-Cx)*(Ax-Cx) + (Ay-Cy)*(Ay-Cy) );
	if(distance <= dr)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// checking for space error in the noflyzone file
int space_check_nfz(FILE *stream)
{
	char templine[1024];
	int count;
	while(1)
	{
		while((fgetc(stream)) == 35) //35 stands for the ascii character for '#'
		{
			fscanf(stream,"%*[^\n]%*c"); //jump to the next line
		}
		fseek(stream,-1, SEEK_CUR); //move backwards by 1
				
		int ii;
		fgets(templine, sizeof(templine), stream);
		for(ii=0; ii<strlen(templine); ii++)
		{	
			if(templine[0] == ' ')
			{
				return 0;
			}						
			else if(templine[ii] == ' ')
			{
				count++;
			}
			else if(templine[0]== '\n')
			{
				count = 2;			
			}		
		}
		
		if(count != 2)
		{
			return 0;
		}
		count = 0;
		
		if(fgetc(stream) == EOF)
		{
			return 1;
		}
	}
	return 1;
}

int space_check_2(FILE *stream)
{
	char templine[1024];
	while(!feof(stream))
	{
		fgets(templine, sizeof(templine), stream);
		if(templine[0] == ' ')
		{
			return 0;
		}
	}
	return 1;
}

//check space error for flightplan file
int space_check_fp(FILE *stream)
{
	char templine[1024];
	int count;
	while(1)
	{
		while((fgetc(stream)) == 35) //35 stands for the ascii character for '#'
		{
			fscanf(stream,"%*[^\n]%*c");
		}
		fseek(stream,-1, SEEK_CUR);
				
		int ii;
		fgets(templine, sizeof(templine), stream);
		for(ii=0; ii<strlen(templine); ii++)
		{	
			if(templine[0] == ' ')
			{
				return 0;
			}						
			else if(templine[ii] == ' ')
			{
				count++;
			}
			else if(templine[0]== '\n')
			{
				count = 1;
			}
		}
		if(count != 1)
		{
			return 0;
		}
		count = 0;
		
		if(fgetc(stream) == EOF)
		{
			return 1;
		}
	}
	return 1;
}


//check if the file have two 2 consecutive waypoints
int point_check(int a, int b, int c ,int d)
{
	if(a == c && b==d)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main(int argc, char *argv[])
{
	FILE *nfz = fopen(argv[1], "r");
	FILE *fp = fopen(argv[2], "r");
	if(nfz == NULL || fp == NULL)
	{
		perror("Can not open noflyzone file");
		exit(1);
	}
	
	IntList *nofz = NULL;
	IntList *flp = NULL;

	// file error checking
	if(!space_check_nfz(nfz))
	{
		printf("No-fly zone file invalid.\n");
	 	exit(2);
	}
	rewind(nfz);
	if(!space_check_2(nfz))
	{
		printf("No-fly zone file invalid.\n");
	 	exit(2);
	}
	rewind(nfz);
	
	char check;
	check = fgetc(nfz);
	if(check == EOF)
	{
		printf("Flight plan valid\n");
		exit(0);
	}
	fseek(nfz,-1, SEEK_CUR);
	
	// the following part is aim to store the value in the link list structure
	while(!feof(nfz))
	{
		while((fgetc(nfz)) == 35) //35 stands for the ascii character for '#'
		{
			fscanf(nfz,"%*[^\n]%*c");
			list_delete(&nofz);
		}
		fseek(nfz,-1, SEEK_CUR);	

		int a;
		fscanf(nfz,"%d",&a);
		if(a<0 || a>=10000)
		{
			printf("No-fly zone file invalid.\n");
	 		exit(2);	
		}
		list_append(&nofz, a);
		
		if((fgetc(nfz) == '\n') && list_length(nofz)%3 != 0 )
		{
			printf("No-fly zone file invalid.\n");
			exit(2);
		}
	}
	list_delete(&nofz);
	if((list_length(nofz))%3 != 0)
	{
		printf("No-fly zone file invalid.\n");
		exit(2);
	}
	fclose(nfz);

	//radiu check
	int num_zone0 = list_length(nofz)/3;
	int count_z = 0;
	int i00;
	for(i00=0; i00<num_zone0; i00++)
	{
		if(list_get(nofz, count_z+2) <= 0)
		{
			printf("No-fly zone file invalid.\n");
			exit(2);	
		}
		count_z = count_z + 3;
	} 
	
	//flight paln error checking
	if(!space_check_fp(fp))
	{
		printf("Flight plan file invalid.\n");
	 	exit(3);
	}
	rewind(fp);	

	if(!space_check_2(fp))
	{
		printf("Flight plan file invalid.\n");
	 	exit(3);
	}
	rewind(fp);

	while(!feof(fp))
	{
		while((fgetc(fp)) == 35) //35 stands for the ascii character for '#'
		{
			fscanf(fp,"%*[^\n]%*c");
			list_delete(&flp);
		}
		fseek(fp,-1, SEEK_CUR);

		int b;
		fscanf(fp,"%d",&b);
		if(b<0 || b>=10000)
		{
			printf("Flight plan file invalid.\n");
			exit(3);
		}
		list_append(&flp, b);	
		
		if((fgetc(fp) == '\n') && list_length(flp)%2 != 0 )
		{
			printf("Flight plan file invalid.\n");
			exit(3);
		}
	}
	list_delete(&flp);
	if((list_length(flp))%2 != 0 || list_length(flp)<4 )
	{
		printf("Flight plan file invalid.\n");
		exit(3);
	}
	fclose(fp);
	
	// consecutive waypoints checking
	int num_line0 = (list_length(flp)/2)-1;
	int count_p = 0;
	int i0;
	for(i0=0; i0<num_line0; i0++)
	{
		if(point_check(list_get(flp, count_p), list_get(flp, count_p+1), list_get(flp, count_p+2), list_get(flp, count_p+3)))
		{
			printf("Flight plan file invalid.\n");
			exit(3);
		}
		else
		{
			count_p = count_p + 2;
		}
	}

	// calculation part
	int num_zone = list_length(nofz)/3;
	int num_line = (list_length(flp)/2)-1;
	int count_zone = 0;
	int count_line = 0;
	int i1, i2;
	for (i1=0; i1<num_line; i1++)
	{		
		for(i2=0; i2<num_zone; i2++)
		{
			if(intersect(list_get(flp, count_line), list_get(flp, count_line+1), list_get(flp, count_line+2), list_get(flp, count_line+3), list_get(nofz, count_zone), list_get(nofz, count_zone+1), list_get(nofz, count_zone+2)))
			{	
				printf("Invalid flight plan.\n");
				printf("Enters restricted area around %d, %d.\n", list_get(nofz, count_zone), list_get(nofz, count_zone+1));
				exit(4);
			}
			else
			{
			count_zone = count_zone + 3;
			}
		}
		count_zone = 0;
		count_line = count_line + 2;
	}

	int num_point = (list_length(flp))/2;
	int count_zone2 = 0;
	int count_point = 0;
	int i3, i4;
	for (i3=0; i3<num_point; i3++)
	{
		for(i4=0; i4<num_zone; i4++)
		{
			if(in_zone(list_get(flp, count_line), list_get(flp, count_line+1), list_get(nofz, count_zone), list_get(nofz, count_zone+1), list_get(nofz, count_zone+2)))
			{
				printf("Invalid flight plan.\n");
				printf("Enters restricted area around %d, %d.\n", list_get(nofz, count_zone), list_get(nofz, count_zone+1));
				exit(4);
			}
			count_zone2 = count_zone2 + 3;
		}
		count_zone2 = 0;
		count_point = count_point + 2;
	}
	printf("Flight plan valid\n");
	list_free(&flp);
	list_free(&nofz);
	exit(0);
}

