#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token_list.h"
void readfile();
int bdaf_prog();
void getToken();

/*
BDAF Syntax Analyzer

Created by (GROUP 8):
	Arconado, Kristine N.
	Berse, Nikko R.
	Dalay, Jeremy Tristen A.
	Faustino, Kyle C.

	of BSCS 3-2 (AY 2020-2021)
*/
FILE *fw; 

char token[25]= "";
char lex[25]="";
char lexm[25]="";
char space[2]=" ";
char table [1000][25];
char lexemme [1000][25];
char line[1000]="";
char toFile[1000]="";
char if_for[15]="";
void code_stmt();
void decl_stmt();
void getError();
void asmt_expr();
void cmt();
void in_stmt();
void out_stmt();
void if_block();
void condition_statement();
void loop_block();
void initialization();
void sep_check();
void END();
void update_state();
void in_file();

int a = 0, x = 0,y = 0,len = 0, parenop = 0, opnd = 0, op = 0,error = 0,parencl = 0,iden = 0,apnd =0,warn = 0,update = 0;
int error_total=0,z=0;
int if_set[25];
int brkt_opn=0,brkt_cls=0,looper=0,init=0;
int check = 0;

int main (void)
{
	fw = fopen("Statements.txt","w");

	readfile();
	getToken();
//	printf("%d\t%s\t%s\n",x,lexm,token); 
	bdaf_prog();
}

void readfile()
{
	FILE *f = fopen("SymbolTable.txt", "r");
	int c,len,x = 0;
	
		do
		{ 
			fscanf(f, "%s",token);
			if (token[0] == '•')
			{len = strlen(token);
				for(c = 0; c<len; c++)
				{
					token[c] = token[c+1];
				}
				strcpy(table[x],token);
				strcpy(lexemme[x],line);
				strcpy(line,empty);
				printf("%d\t%s\t%s\n",x,lexemme[x],table[x]);
				x++;
			}
			else
			{	
				strcat(line,token);
				strcat(line,space);
				
			}
			
			if(feof(f))
			{
				break;
			}
		}while(a==0);

	fclose(f);
}

int bdaf_prog()
{
	if(strcmp(start,token)==0)
	{
		printf("\n%s <-- [FOUND] Start of BDAF\n",token);
		fprintf(fw,"%s ~ %s\n",token,lexm);
		getToken();
	//	printf("%d\t%s\t%s\tgoing to code stmt\n",y,lexm,token);
	}
	else getError(1);
	
	code_stmt();
	return 0;
}

void code_stmt()
{update =0;
//printf("%d\t%s\t%s\tinside code_stmt\n",y,lexm,token);
if(z>0)
{
	if((strcmp(brkt_op,token)==0 || strcmp(brkt_cl,token)==0))
	{
		if(strcmp(brkt_op,token)==0)
		{
			brkt_opn++;
			printf("%s\n",lexm);
			fprintf(fw,"%s ~ %s\n",token,lexm);
			getToken();
		}
		else
		{
		brkt_cls++;	
			if(brkt_opn>=brkt_cls)
			{
				printf("%s\n",lexm);
				fprintf(fw,"%s ~ %s\n",token,lexm);
				z--;
				getToken();
			}
			else
			{
				getError(16);
			}
		}
	}
}
	if(strcmp(datatype,token)==0)
	{
		strcpy(line,lexm);
		strcpy(lex,lexm);
		strcpy(toFile,token);
		getToken();
	//	printf("%d\t%s\t%s\tgoing to decl_stmt\n",y,lexm,token);
		decl_stmt();
	}
	else if(strcmp(identifier,token)==0)
	{
		update++;
		strcpy(line,empty);
		strcpy(toFile,empty);
		decl_stmt();
	}
	else if(strcmp(comment,token)==0||strcmp(comment_line,token)==0)
	{
	//	printf("%d\t%s\t%s\tgoing to cmt\n",y,lexm,token);
		cmt();
	}
	else if(strcmp(input,token)==0)
	{
		strcpy(line,lexm);
		strcpy(lex,lexm);
		strcpy(toFile,token);
		getToken();
		in_stmt();
	}
	else if(strcmp(output,token)==0)
	{
		strcpy(line,lexm);
		strcpy(lex,lexm);
		strcpy(toFile,token);
		getToken();
		out_stmt();
	}
	else if(strcmp(if_stmt,token)==0 || strcmp(if_else,token)==0 || strcmp(if_not,token)==0)
	{
	//printf("Inside if check\n");
		strcpy(line,lexm);
		strcpy(lex,lexm);
		strcpy(toFile,token);
		if_block();
	}
	else if(strcmp(loop,token)==0)
	{
		strcpy(line,lexm);
		strcpy(toFile,token);
		getToken();
		loop_block();
	}
	else if(strcmp(end,token)==0)
	{
		strcpy(line,token);
		strcpy(toFile,token);
		END();
	}
	else if(token[0]=='\0')
	{
		getError(25);
		if(z!=0)
		{
			getError(24);
		}
		else
			printf("\n[COMPLETE]: Open and Close Brackets");
			printf("[TOTAL ERROR(s)] FOUND: %d\n[TOTAL WARNING(s)] FOUND: %d",error_total,warn);
			exit(0);
	}
	else
	{
		getToken();
	}
	code_stmt();
}

void END()
{
	printf("\n%s <--[FOUND] End of BDAF Program\n",line);
	fprintf(fw,"%s ~ %s\n",token,lexm);
	if(brkt_opn!=brkt_cls)
	{
		getError(24);
	}
	else
	printf("\n[COMPLETE]: Open and Close Brackets\n");
	printf("[TOTAL ERROR(s)] FOUND: %d\n[TOTAL WARNING(s)] FOUND: %d",error_total,warn);
		exit(0);
}

void decl_stmt()
{int a;

	if(strcmp(identifier,token)==0)
	{
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
	//	printf("%d\t%s\t%s\tgoing to assignment\n",y,lexm,token);
	}
	else
	{
		getError(3);
		error++;
	}
	
	if(strcmp(assignment,token)==0) 
	{
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
	//	printf("%d\t%s\t%s\tgoing to asmt_expr\n",y,lexm,token);
	}
	else if(strcmp(numbr,token)==0||strcmp(numbrt,token)==0||strcmp(char_,token)==0||strcmp(charz,token)==0||strcmp(paren_op,token)==0 ||strcmp(paren_cl,token)==0||strcmp(tralse,token)==0)
	{
		if(update!=0)
			getError(13);
		else
			getError(4);
		error++;
	}
	else if(init!=0 || update!=0)
	{
		if(strcmp(increment,token)==0 || strcmp(decrement,token)==0 )
		{
			strcat(line,space);
			strcat(line,lexm);
			strcat(toFile,space);
			strcat(toFile,token);
			in_file();
			printf("%s\t[VALID] Increment/Decrement Statement",line);
			getToken();
			code_stmt();
		}
		else
			getError(13);
		
	}
	else
	{
		printf("\n%s [VALID] %s Declaration\n",line,lex);
		in_file();
		error=0;
		strcpy(line,empty);
		code_stmt();
	}

	if(strcmp(numbr,token)==0||strcmp(numbrt,token)==0||strcmp(identifier,token)==0||strcmp(paren_op,token)==0||strcmp(arithmetic,token)==0||strcmp(char_,token)==0||strcmp(charz,token)==0||strcmp(tralse,token)==0)
	{
	//	printf("going to asmt expr\n");
		asmt_expr();
	}
	else
	{
		getError(5);
		error++;
	}
	parenop = 0;
	opnd = 0;
	op = 0;
	error = 0;
	parencl = 0;
	//printf("%d\t%s\t%s\tgoing to code_stmt\n",y,lexm,token);
}

void asmt_expr()
{
	if(strcmp(paren_op,token)==0)
	{
		parenop++;
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
		asmt_expr();
	}
	else if(strcmp(numbr,token)==0||strcmp(numbrt,token)==0||strcmp(identifier,token)==0||strcmp(char_,token)==0||strcmp(charz,token)==0||strcmp(tralse,token)==0)
	{
		opnd++;
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
		asmt_expr();
	}
	else if(strcmp(arithmetic,token)==0)
	{
		if(op>opnd)
		{
			error++;
		}
		op++;
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
		asmt_expr();
	}
	else if(strcmp(paren_cl,token)==0)
	{
		parencl++;
		if(parencl > parenop)
		{
			getError(6);
			error++;
		}
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
		asmt_expr();
	}
	if(parenop != parencl)
	{
		error++;
	//	printf("in paren check\n");
	}
	if(opnd != op+1)
	{
		error++;
	//	printf("in opnd check\t%d\n",error);
	}	
	
		parenop = 0;
		parencl = 0;
		opnd = 0;
		op = 0;
if(looper==0)
{
	if(error == 0&&opnd==0)
	{
		if(update!=0)
		{
			in_file();
			printf("\n%s [VALID]: %s Statement \n",line,lex);
			strcpy(line,empty);
		//printf("%d\t%s\t%s\tgoing to code_stmt\n",y,lexm,token);
			code_stmt();	
			
		}
		else
		{
			in_file();
			printf("\n%s [VALID]: %s Declaration Statement \n",line,lex);
			strcpy(line,empty);	

			//	printf("%d\t%s\t%s\tgoing to code_stmt\n",y,lexm,token);
			code_stmt();
		
		}
	}
	else
	{
		if(update!=0)
		{
			getError(14);
			strcpy(line,empty);
		//	printf("%d\t%s\t%s\tgoing to code_stmt\n",y,lexm,token);
		}
		else
		{
			getError(7);
			strcpy(line,empty);
		//	printf("%d\t%s\t%s\tgoing to code_stmt\n",y,lexm,token);
		}
	}
}
}

void cmt()
{

	if(strcmp(comment_line,token)==0)
	{
		strcpy(line,lexm);
		strcpy(lex,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
		
		if(strcmp(single_comment,token)==0)
		{
			strcat(line,space);
			strcat(line,lexm);
			strcat(toFile,space);
			strcat(toFile,token);
		}
	}
	else if(strcmp(comment,token)==0)
	{
		strcpy(line,lexm);
		strcpy(lex,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
		
		if(strcmp(multiline,token)==0)
		{
			strcat(line,space);
			strcat(line,lexm);
			strcat(toFile,space);
			strcat(toFile,token);
			getToken();
		}
		
		if(strcmp(comment_end,token)==0)
		{
			strcat(line,space);
			strcat(line,lexm);
			strcat(toFile,space);
			strcat(toFile,token);
		}
		else
		{
			warn++;
		}
	}
	
	if(warn == 1)
	{
		printf("\n%s\t[WARNING]:Multiline comment not closed, everything followed by BTWBRUH is considered a Multiline Comment\n\t\t[SYNTAX]: [BTWBRUH],[multiline],[CMT]\n",line);
	}
	else
	{
		in_file();
		printf("\n%s\t[VALID]: Comment Statement\n",line);
		getToken();
	}
}

void in_stmt()
{
	if(strcmp(identifier,token)==0)
	{
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		in_file();
		printf("\n%s\t[VALID]: %s statement\n",line,lex);
		getToken();
	}
	else
	{
		getError(8);
	}
	code_stmt();
}

void out_stmt()
{
char plus = '+';
//printf("inside out_stmt\t%s\t%s\n",lexm,token);
	if(strcmp(identifier,token)==0||strcmp(charz,token)==0)
	{
		iden++;
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
	}
	else if(apnd==iden && plus == lexm[0])
	{
		error++;
		if(apnd>0)
		getError(10);
		else
		getError(9);
	} 
	
	if(strcmp(arithmetic,token)==0)
	{
		apnd++;
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
		out_stmt();
	}
	else if(iden>apnd && strcmp(identifier,token)==0)
	{
		error++;
		if(apnd>0)
		getError(10);
		else
		getError(9);
		
		out_stmt();
	}
	
	if(error == 0)
	{
		in_file();
		printf("\n%s\t[VALID]: OUT statement\n",line);
	}
	else
		getError(11);
	error=0;
	code_stmt();
}

void if_block()
{
if(update==0)
{//printf("%s\t%s\t inside if_block",lexm,token);
	if(strcmp(if_stmt,token)==0)
	{
		if_set[z]=1;
		z++;
	}
	else if(strcmp(if_else,token)==0)
	{
		if(if_set[0]!=1)
		{
			getError(17);
		}
		if_set[z]=2;
		z++;
	}
	else if(strcmp(if_not,token)==0)
	{
		if_set[z]=3;
		z++;
		fprintf(fw,"%s ~ %s\n",token,lexm);
		printf("ELSE [VALID]: ELSE statement");
		getToken();
		code_stmt();
	}
	
	getToken();
	if(strcmp(paren_op,token)==0)
	{
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
	}
	else
	{
		error++;
		getError(6);
	}
	condition_statement();
}
	if(strcmp(paren_cl,token)==0)
	{
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
	}
	else
	{
		error++;
		getError(6);
	}
	
		if(error == 0)
	{
		in_file();
		printf("\n%s\t[VALID]: %s statement\n",line,lex);
		getToken();
	}
	else
		getError(11);
	error=0;
	code_stmt();
}

void condition_statement()
{
	if(strcmp(numbr,token)==0||strcmp(numbrt,token)==0||strcmp(char_,token)==0||strcmp(charz,token)==0||strcmp(identifier,token)==0||strcmp(paren_op,token)==0 ||strcmp(paren_cl,token)==0||strcmp(tralse,token)==0)
	{
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
	}
	else
	{
		error++;
		getError(18);
	}
	
	if(strcmp(relational,token)==0||strcmp(equality,token)==0)
	{
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
	}
	else
	{
		error++;
		getError(19);
	}
	
	if(strcmp(numbr,token)==0||strcmp(numbrt,token)==0||strcmp(char_,token)==0||strcmp(charz,token)==0||strcmp(identifier,token)==0||strcmp(paren_op,token)==0 ||strcmp(paren_cl,token)==0||strcmp(tralse,token)==0)
	{
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
	}
	else
	{
		error++;
		getError(18);
	}
	
	if(strcmp(logical,token)==0)
	{
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
		condition_statement();
	}
	else
	{
		update++;
		if(looper!=0)
			loop_block();
	}
	
}

void loop_block()
{
looper++;
z++;
if(update==0)
{
	if(strcmp(paren_op,token)==0)
	{
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
	}
	else
	{
		error++;
		getError(20);
	}
	initialization();
	sep_check();
	condition_statement();
}
	sep_check();
	update_state();
	if(strcmp(paren_cl,token)==0)
	{
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
	}
	
	if(error==0)
	{
		in_file();
		printf("%s\t[VALID]: FOR Statement\n",line);
	}
	else
	{
		getError(11);
	}
	
	looper=0;
	update=0;
	init=0;
	code_stmt();
}
void initialization()
{
	if(strcmp(datatype,token)==0)
	{
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
		init++;
		decl_stmt();
	}
	else if(strcmp(identifier,token)==0)
	{	update++;
		decl_stmt();
	}
	else
	{
		getError(21);
	}
}
void sep_check()
{
	if(strcmp(seperator,token)==0)
	{
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
	//	printf("going to condition\t%s\t%s\n",lexm,token);
	}
	else
	{
		error++;
		getError(21);
	}
}

void update_state()
{
	if(strcmp(identifier,token)==0)
	{
		strcat(line,space);
		strcat(line,lexm);
		strcat(toFile,space);
		strcat(toFile,token);
		getToken();
		if(strcmp(increment,token)==0||strcmp(decrement,token)==0)
		{
			strcat(line,space);
			strcat(line,lexm);
			strcat(toFile,space);
			strcat(toFile,token);
			getToken();
		}
		else
		{
			error++;
			getError(22);
		}
	}
	else
	{
		error++;
		getError(23);
	}
}
void getToken()
{
	strcpy(token,table[y]); 
	strcpy(lexm,lexemme[y]);	
	y++;
}

void getError(int err)
{//printf("in get error\t%d\n",err);
error_total++;
	switch(err)
	{
		case 1: printf("[ERROR]: The Start of BDAF 'YOW' MISSING\n\t\tSYNTAX: YOW,{<code_stmt>},AIGHT\n\n");break;
		case 2: printf("%s\t[ERROR]: Invalid start of statement\n",line);break;
		case 3: printf("%s^\t[ERROR]: Expected IDENTIFIER after DATATYPE\n\t\tSYNTAX: decl_stmt = <DATATYPE>, <IDENTIFIER>\n\n",line);break;
		case 4: printf("%s^\t[ERROR]: Expected ASSIGNMENT after IDENTIFIER before assignment expression\n\t\tSYNTAX: <DATATYPE>, <IDENTIFIER>, <ASSIGNMENT>, <asmt_expr>]\n\n",line);break;
		case 5: printf("%s^\t[ERROR]: Expected assignmnet expression after ASSIGNMENT\n\t\tSYNTAX: <DATATYPE>, <IDENTIFIER>, <ASSIGNMENT>, <asmt_expr>]\n\n",line);break;
		case 6: printf("%s^\t[ERROR]: Expected Open Parenthesis '(' before Close Parenthesis')'\n",line);break;
		case 7: printf("%s\t[%d ERROR(s)]:[INVALID] %s Declaration Statement\n",line,error,lex);break;
		case 8: printf("%s\t[%d ERROR(s)]:[INVALID] Expected 'IDENTIFIER' after 'IN'\n\t\t[SYNTAX]: 'IN','IDENTIFIER'\n",line,lex);break;
		case 9: printf("%s^\t[ERROR]: Expected 'IDENTIFIER' after 'OUT'\n\t\t[SYNTAX]: 'OUT','IDENTIFIER'\n",line,lex);break;
		case 10: printf("%s^\t[ERROR]: Expected 'IDENTIFIER' after '+'\n\t\t[SYNTAX]: 'OUT','IDENTIFIER', '+', 'IDENTIFIER' \n",line,lex);break;
		case 11: printf("%s\t[%d ERROR(s)]:[INVALID] %s Statement\n",line,error,lex);break;
		case 12: printf("%s^\t[ERROR]: Expected '%s' after 'ASSIGNMENT'\n\t\t[SYNTAX]: 'IDENTIFIER','ASSIGNMENT','%s' \n",line,lex,lex);break;
		case 13: printf("%s^\t[ERROR]: Expected ASSIGNMENT after IDENTIFIER before assignment expression\n\t\tSYNTAX: <IDENTIFIER>, <ASSIGNMENT>, <asmt_expr>]\n\n",line);break;
		case 14: printf("%s^\t[%d ERROR(s)]:[INVALID] %s Statement\n",line,error,lex);break;
		case 15: printf("%s^\t[ERROR]: Bracket is useless here\n",lexemme);break;
		case 16: printf("%s^\t[ERROR]: Expected Open Bracket before Close Bracket\n",lexemme);break;
		case 17: printf("%s^\t[ERROR]: Expected Open Parenthesis\n\t\t[SYNTAX]: 'IF' '(' 'exprn' ')' 'statement'\n",lexemme);break;
		case 18: printf("%s^\t[ERROR]: Expected 'IDENTIFIER' or DECLARED 'DATATYPE' before 'RELATIONAL' or 'EQUALITY'\n",line);break;
		case 19: printf("%s^\t[ERROR]: Expected 'RELATIONAL' or 'EQUALITY' after 'IDENTIFIER' or DECLARED 'DATATYPE'\n",line);break;
		case 20: printf("%s^\t[ERROR]: Expected '(' after 'FOR'\n\t\t[SYNTAX]: 'FOR', '(','INITIALIZATION','SEPERATOR','CONDITION', 'SEPERATOR, 'UPDATE', ')'\n",line);break;
		case 21: printf("%s^\t[ERROR]: Expected 'INITIALIZATION' after'('\n\t\t[SYNTAX]: 'FOR', '(','INITIALIZATION','SEPERATOR','CONDITION', 'SEPERATOR, 'UPDATE', ')'\n",line);break;
		case 22: printf("%s^\t[ERROR]: Expected 'INCREMENT' or 'DECREMENT'\n\t\t[SYNTAX]: 'IDENTIFIER','INCREMENT || DECREMENT'\n",line);break;
		case 23: printf("%s^\t[ERROR]: Expected 'IDENTIFIER'\n\t\t[SYNTAX]: 'IDENTIFIER','INCREMENT || DECREMENT'\n",line);break;
		case 24: printf("\n[ERROR]: [INCOMPLETE]: code blocks, [MISSING]: '{' or '}'\n");break;
		case 25: printf("\n[ERROR]: Expected AIGHT to end the program\n\t\t[SYNTAX]: 'YOW','code_stmt','AIGHT'\n");
	}
}

void in_file()
{
	fprintf(fw,"%s ~ %s\n",toFile,line);
}




