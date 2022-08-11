#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "token_list.h"

int x = 0,y=0,ab=0,c=0,g,a=0,us=0,cd,i=0;
char lexemmes[100][25];
char tokens [100][25];
char lines[100]="";
char check[25]="";
char loc[10]= "BDAF MAIN";
char lex[25]="";
char tok[25]="";
char dtype[25];
char variable[25];
char declared[100][25];
char dec_type[100][25];
char ef[5]="IF";
char elf[5]="ELF";
char ef_f[5]="ELSE";
char space[2] = " ";
char getter[25] = "";
int used[100];
int if_list[100];
void INPUT();
void OUTPUT();
void updt_stmt();
void semantic_check();
void getValue();
void getError();
int declared_check();
void assignment_statement();
void decl_stmt();
void asmt_expr();
int main(void)
{
		FILE *file = fopen("Statements.txt","r");
		
		do
		{ 
			fscanf(file, "%s",getter);
			if (getter[0] == '~')
			{
			
				g = 0;
				while(g<c)
				{fscanf(file, "%s",getter);
					strcpy(lexemmes[g],getter);
					strcat(lines,getter);
					strcat(lines,space);
					g++;
				}
				printf("%s",lines);
				semantic_check();
				printf("\n");
				strcpy(lines,empty);
				c=0;
				x=0;
			}
			else
			{	
				strcpy(tokens[c],getter); 
				
				c++;
			}
			
			if(feof(file))
			{
				break;
			}
		}while(ab==0);

	fclose(file);
	
	for(cd =0; cd<y; cd++)
	{
		if(used[cd]!=1)
		getError(6);

	}
	
}
void semantic_check()
{getValue();
	if(strcmp(input,tok)==0)
	{
		INPUT();	
	}
	else if(strcmp(output,tok)==0)
	{
		OUTPUT();
	}
	else if(strcmp(datatype,tok)==0)
	{
		strcpy(dtype,lex);
		getValue();
		decl_stmt();
	}
	else if(strcmp(identifier,tok)==0)
	{
		updt_stmt();	
	} 
	
}

void condition_statement()
{int j = 0;

	while(j<c)
	{
		getValue();
		if(strcmp(identifier,tok)==0)
		{strcpy(variable,lex);
			int get =0;
			get = declared_check();
			if(j>2)
			{
				if(strcmp(dtype,dec_type[a])!=0)
				{
					getError(4);
				}
			}
			if(get==0&&j<2)
			{
				strcpy(dtype,dec_type[a]);
			}	
		}
		else if(strcmp(numbr,tok)==0||strcmp(numbrt,tok)==0||strcmp(char_,tok)==0)
		{
			if(strcmp(dtype,tok)!=0)
			{
				getError(4);
			}
		}
		else if(strcmp(charz,tok)==0)
			getError(4);
	}
}

void INPUT()
{
	getValue();
	if(declared_check()==0)
	{
		used[a]=1;
		if(strcmp(tok,tralse)==0)
			getError(2);
		else
			printf("\n");
	}
	else
		getError(1);
	
}

void OUTPUT()
{int set = c;
	while(set!=0)
	{
		getValue();
		
		if(strcmp(identifier,tok)==0)
		{
			if(declared_check()==1)	
				getError(1);
			else
			{
				used[a]=1;
			}
		}
		else if(strcmp(arithmetic,tok)==0)
		{
			if(lex[0]!='+')
				printf("[ERROR]: Use only '+' to append CHARZ and IDENTIFIER");
		}
		else if(strcmp(charz,tok)!=0)
			getError(3);
		set--;
	}
	printf("\n");
}

void decl_stmt()
{
strcpy(variable,lex);
int get = declared_check();
	if(get==1)
	{
		strcpy(dec_type[y],dtype);
		strcpy(declared[y],variable);
		y++;
		if(strcmp(assignment,tok)==0)
			asmt_expr();
	}else getError(5);
}

void updt_stmt()
{
strcpy(variable,lex);
int get = declared_check();
	if(get==0)
	{strcpy(dtype,dec_type[a]);
		getValue();
		if(strcmp(assignment,tok)==0)
			asmt_expr();
	}else getError(1);
}

void asmt_expr()
{int a = x;
int b = c;
	while(a<b)
	{
	getValue();
		if(strcmp(identifier,tok)==0)
		{strcpy(variable,lex);
			int get = declared_check();
			if(get==1)
				getError(1);
			else
			{
				if(strcmp(dtype,dec_type[a])!=0)
					getError(4);
				else
				{
					used[a]=1;
				}
			}
		}
		else if(strcmp(dtype,tok)!=0)
		{
			if(strcmp(arithmetic,tok)==0||strcmp(paren_op,tok)==0||strcmp(paren_cl,tok)==0)
			{
				
			}
			else	
			getError(4);
		}
		a++;
	}
}

int declared_check()
{

	a=0;
	while(a<y)
	{
		if(strcmp(variable,declared[a])==0)
			return 0;
	
		a++;
	}
	return 1;
}

void getValue()
{
	strcpy(lex,lexemmes[x]);
	strcpy(tok,tokens[x]);
	x++;
}


void getError(int n)
{
	switch(n)
	{
		case 1: printf("\t[ERROR]: %s Not Declared\t[INSIDE]:%s\n",lex,loc);break;
		case 2: printf("\t[ERROR]: Data Type Mismatch [EXPECTED]: NUMBR|NUMBRT|CHAR|CHARZ [FOUND]: %s\t[INSIDE]:%s\n",tok,loc);break;
		case 3: printf("\t[ERROR]: Data Type Mismatch [EXPECTED]: CHARZ [FOUND]: %s\t[INSIDE]:%s\n",tok,loc);break;
		case 4: printf("\n\t%s\t[ERROR]: Data Type Mismatch [EXPECTED]: %s [FOUND]: %s\t[INSIDE]:%s\n",lex,dtype,dec_type[a],loc);break;
		case 5: printf("\t[ERROR]: Double Declaration [FOUND ] %s was declared as %s\n\t[INSIDE]:%s",lex,dec_type[a],loc);break;
		case 6: printf("\t%s\t%s [WARNING]: Variable Decalared but not used\n\t[INSIDE]:%s",dec_type[cd],declared[cd],loc);break;
	}
}
