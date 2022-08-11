/*
	BDAF Lexical Analyzer

	Created by (GROUP 8):
	Arconado, Kristine N.
	Berse, Nikko R.
	Dalay, Jeremy Tristen A.
	Faustino, Kyle C.

	of BSCS 3-2 (AY 2020-2021)
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
//•
void comments(FILE **file, FILE **table, int line, char ch);
void semantic (char array[50][50]);

int main(void){
	char filename[30]="";
	
	printf ("Enter filename (.bdaf) : ");
	scanf(" %s",&filename);
	strcat(filename,".bdaf");
	
	FILE *table = fopen("SymbolTable.txt", "w");
	if (FILE *file = fopen(filename, "r")){
		char ch;
		while (ch!=EOF){ 
			int invalid = 0, line = 0, invalidOpr = 0;
			int negnum=0;
			ch = fgetc(file);
			
			while (ch==' ' || ch=='\n' || ch=='\r' || ch=='\t')	// REMOVE SPACES AND LINEBREAKS
				ch = fgetc(file);

			//-----IDENTIFIER-----
			if (ch >= 'a' && ch <= 'z'){
				while (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||ch>='0'&&ch<='9'||ch=='_'){
					fprintf(table,"%c",ch);
					ch = fgetc(file);
				}
				if (ch=='\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
					fprintf(table,"\t•IDENTIFIER\n");
				else invalid = 1;	
			} // IDENTIFIER
			
			//------KEYWORD, RESERVED WORD, NOISE WORD-----
			else if (ch >= 'A' && ch <= 'Z'){
				
				if (ch == 'S'){ fprintf(table,"%c",ch); ch = fgetc(file); 
					if (ch == 'K'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'R'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == 'R'){ fprintf(table,"%c",ch); ch = fgetc(file);
								if (ch == 'T'){ fprintf(table,"%c",ch); ch = fgetc(file);
									if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
										fprintf(table,"\t•CONTINUE\n");
									else invalid = 1;
								} else invalid = 1;							
							} else invalid = 1;
						} else invalid = 1;
					} else invalid = 1;
				} //SKRRT
				
				else if (ch == 'W'){ fprintf(table,"%c",ch); ch = fgetc(file); 
					if (ch =='A'){ fprintf(table,"%c",ch); ch = fgetc(file); 
						if (ch == 'H'){ fprintf(table,"%c",ch); ch = fgetc(file); 
							if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
								fprintf(table,"\t•BREAK\n");
							else invalid = 1;
						} else invalid = 1;
					} else invalid = 1;
				}//WAH
				
				else if (ch == 'F'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == 'O'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'R'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
								fprintf(table,"\t•LOOP\n");
							else invalid = 1;					
						} else invalid = 1;
					} else invalid = 1;
				}//FOR
					
				else if (ch == 'I'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == 'F'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
							fprintf(table,"\t•IF_STMT\n");
						else invalid = 1;
					}//IF
					else if (ch == 'N'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
							fprintf(table,"\t•INPUT\n");
						else invalid = 1;
					}//IN
					else invalid = 1;
				}//IF-IN
				
				else if (ch == 'E'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == 'L'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'F') { fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
								fprintf(table,"\t•IF_ELSE\n");
							else invalid = 1;	
						}//ELF
						else if (ch == 'S'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == 'E'){ fprintf(table,"%c",ch); ch = fgetc(file);
								if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
									fprintf(table,"\t•IF_NOT\n");
								else invalid = 1;
							} else invalid = 1;
						}//ELSE
						else invalid = 1;
					} else invalid = 1;
				}//ELF-ELSE
				
				else if (ch == 'N'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == 'U'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'M'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == 'B'){ fprintf(table,"%c",ch); ch = fgetc(file);
								if (ch == 'R'){ fprintf(table,"%c",ch); ch = fgetc(file);
									if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
										fprintf(table,"\t•DATATYPE\n");
									else if (ch == 'T'){ fprintf(table,"%c",ch); ch = fgetc(file);
										if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
											fprintf(table,"\t•DATATYPE\n");
										else invalid = 1;
									} else invalid = 1;
								} else invalid = 1;
							} else invalid = 1;
						} else invalid = 1;
					} //NUMBR - NUMBRT
					else if (ch == 'A'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'H'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
								fprintf(table,"\t•TRALSE\n");
							else invalid = 1;
						} else invalid = 1;
					}//NAH
					else invalid = 1;
				} //NUMBR-NUMBRT, NAH
				
				else if (ch == 'C'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == 'H'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'A'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == 'R'){ fprintf(table,"%c",ch); ch = fgetc(file);
								if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
									fprintf(table,"\t•DATATYPE\n");
								else if (ch == 'Z') { fprintf(table,"%c",ch); ch = fgetc(file);
									if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
										fprintf(table,"\t•DATATYPE\n");
									else invalid = 1;
								} else invalid = 1;
							} else invalid = 1;
						} else invalid = 1;
					} //CHAR-CHARZ
					else if (ch == 'M'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'T'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
								fprintf(table,"\t•COMMENT_END\n");
							else invalid = 1;							
						} else invalid = 1;
					}//CMT
					else if (ch == 'O'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'N'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == 'S'){ fprintf(table,"%c",ch); ch = fgetc(file);
								if (ch == 'T'){ fprintf(table,"%c",ch); ch = fgetc(file);
									if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
										fprintf(table,"\t•CONSTANT\n");
									else invalid = 1;
								} else invalid = 1;								
							} else invalid = 1;
						} else invalid = 1;
					} //CONST
					else invalid = 1;
				} //CHAR-CHARZ-CMT-CONST
						
				else if (ch == 'Y'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == 'O'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'W'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
								fprintf(table,"\t•START\n");
							else invalid = 1;
						} else invalid = 1;	
					} else invalid = 1;		
				}//YOW
					
				else if (ch == 'A'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == 'I'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'G'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == 'H'){ fprintf(table,"%c",ch); ch = fgetc(file);
								if (ch == 'T'){ fprintf(table,"%c",ch); ch = fgetc(file);
									if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
										fprintf(table,"\t•END\n");
									else invalid = 1;
								} else invalid = 1;
							} else invalid = 1;
						} else invalid = 1;
					} else invalid = 1;	
				}//AIGHT
				
				else if (ch == 'B'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == 'R'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'U'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == 'H'){ fprintf(table,"%c",ch); ch = fgetc(file);
								if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF){
									fprintf(table,"\t•COMMENT_LINE\n");
									comments(&file, &table, line, ch);
								} else invalid = 1;	
							} else invalid = 1;	
						} else invalid = 1;	
					}//BRUH
					else if (ch == 'T'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'W'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if	(ch == 'B'){ fprintf(table,"%c",ch); ch = fgetc(file);
								if	(ch == 'R'){ fprintf(table,"%c",ch); ch = fgetc(file);
									if	(ch == 'U'){ fprintf(table,"%c",ch); ch = fgetc(file);
										if	(ch == 'H'){ fprintf(table,"%c",ch); ch = fgetc(file);
											if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF){
												fprintf(table,"\t•COMMENT\n");
												ch = fgetc(file);
												line = 1; comments(&file, &table, line, ch);
											} else invalid = 1;	
										} else invalid = 1;	
									} else invalid = 1;	
								} else invalid = 1;	
							} else invalid = 1;	
						} else invalid = 1;	
					}
					else invalid = 1;		
				}//BRUH-BTWBRUH
				
				else if (ch == 'O'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == 'U'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'T'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
								fprintf(table,"\t•OUTPUT\n");
							else invalid = 1;	
						} else invalid = 1;	
					} else invalid = 1;			
				}//OUT
				
				else if (ch == 'G'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == 'O'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'T'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == 'O'){ fprintf(table,"%c",ch); ch = fgetc(file);
								if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
									fprintf(table,"\t•RESERVED\n");
								else invalid = 1;
							} else invalid = 1;
						} else invalid = 1;
					} else invalid = 1;							
				}//GOTO
				
				else if (ch == 'T'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == 'O'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
							fprintf(table,"\t•NOISE\n");
						else invalid = 1;		
					}//TO
					else if (ch == 'R'){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == 'U'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
								fprintf(table,"\t•TRALSE\n");
							else invalid = 1;
					}//TRU
						else if (ch == 'A'){ fprintf(table,"%c",ch); ch = fgetc(file);
							if (ch == 'L'){ fprintf(table,"%c",ch); ch = fgetc(file);
								if (ch == 'S'){ fprintf(table,"%c",ch); ch = fgetc(file);
									if (ch == 'E'){ fprintf(table,"%c",ch); ch = fgetc(file);
										if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
											fprintf(table,"\t•DATATYPE\n");
										else invalid = 1;
									}else invalid = 1;
								}else invalid = 1;
							}else invalid = 1;
						}
						else invalid = 1;
					}
					else invalid = 1;				
				}//TO, TRU, TRALSE
			
			} // KEYWORD, RESERVED WORD, NOISE WORD
			
			//-----DIGITS-----
			else if (ch>='0' && ch<='9' || ch=='.'){
				int fltnum = 0;
				while(ch>='0'&&ch<='9'||ch=='.'){
					fprintf(table,"%c",ch);
					if (ch == '.') fltnum = 1;
					ch = fgetc(file);
				}
				if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF){
					if (fltnum) {
						if (negnum) fprintf(table,"\t•NEG_NUMBRT\n");
						else fprintf(table,"\t•NUMBRT\n");
					} //NUMBRT data type
					else {
						if (negnum) fprintf(table,"\t•NEG_NUMBR\n");
						else fprintf(table,"\t•NUMBR\n");
					} //NUMBR data type
				} else invalid = 1;
				negnum = 0;
			} // DIGITS
			
			//-----CHARACTER-----
			else if (ch == '\''){ fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch!='\n'&&ch!=EOF){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\''){ fprintf(table,"%c",ch); ch = fgetc(file);
						if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
							fprintf(table,"\t•CHAR\n");
						else invalid = 1;
					} else invalid = 1;
				} else invalid = 1;
			} //CHAR data type		
			
			//-----STRING-----
			else if (ch == '"'){ fprintf(table,"%c",ch); ch = fgetc(file);
				while(ch!='\n'&&ch!=EOF&&ch!='"'){
					fprintf(table,"%c",ch); ch = fgetc(file);
				}
				if(ch == '"'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•CHARZ\n");
					else invalid = 1;
				} else invalid = 1;
			} //CHARZ data type 
			
			//-----OPERATORS-----
			else if (ch == '+'){ fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
					fprintf(table,"\t•ARITHMETIC\n");
				else if (ch == '+'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•INCREMENT\n");
				}
				else if (ch == '='){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•ASSIGNMENT\n");
				}
				else if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') invalid = 1;
				else invalidOpr = 1;
			} //+ ++ +=
			
			else if (ch == '-'){ fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
					fprintf(table,"\t•ARITHMETIC\n");
				else if (ch == '-'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•DECREMENT\n");
				}
				else if (ch == '='){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•ASSIGNMENT\n");
				}
				else if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') invalid = 1;
				else if (ch>='0'&&ch<='9'||ch == '.') {
					negnum = 1;
					ungetc(ch, file);
				}
				else invalidOpr = 1;
			} //- -- -=
			
			else if (ch == '*'){ fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
					fprintf(table,"\t•ARITHMETIC\n");
				else if (ch == '*'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•EXPONENT\n");
				}
				else if (ch == '='){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•ASSIGNMENT\n");
				}
				else if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') invalid = 1;
				else invalidOpr = 1;
			} //* ** *=
			
			else if (ch == '/'){ fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
					fprintf(table,"\t•ARITHMETIC\n");
				else if (ch == '='){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•ASSIGNMENT\n");
				}
				else if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') invalid = 1;
				else invalidOpr = 1;
			} // / /=
			
			else if (ch == '\\'){ fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
					fprintf(table,"\t•ARITHMETIC\n");
				else if (ch == '='){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•ASSIGNMENT\n");
				}
				else if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') invalid = 1;
				else invalidOpr = 1;
			} // \ \= integer division
			
			else if (ch == '%'){ fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
					fprintf(table,"\t•ARITHMETIC\n");
				else if (ch == '='){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•ASSIGNMENT\n");
				}
				else if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') invalid = 1;
				else invalidOpr = 1;
			} //% %=
			
			else if (ch == '='){ fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
					fprintf(table,"\t•ASSIGNMENT\n");
				else if (ch == '='){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•EQUALITY\n");
				}
				else if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') invalid = 1;
				else invalidOpr = 1;
			} //= ==
			
			else if (ch == '>'){ fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
					fprintf(table,"\t•RELATIONAL\n");
				else if (ch == '='){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•RELATIONAL\n");
				}
				else if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') invalid = 1;
				else invalidOpr = 1;
			} //> >=
			
			else if (ch == '<'){ fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
					fprintf(table,"\t•RELATIONAL\n");
				else if (ch == '='){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•RELATIONAL\n");
				}
				else if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') invalid = 1;
				else invalidOpr = 1;
			} //< <=
			
			else if (ch == '&'){ fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch == '&'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•LOGICAL\n");
				}
				else if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') invalid = 1;
				else invalidOpr = 1;
			} // &&
			
			else if (ch == '*'){ fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch == '*'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•EXPONENT\n");
				}
				else if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') invalid = 1;
				else invalidOpr = 1;
			} // **
			
			else if (ch == '|'){ fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch == '|'){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•LOGICAL\n");
				}
				else if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') invalid = 1;
				else invalidOpr = 1;
			} // ||
			
			else if (ch == '!'){ fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
					fprintf(table,"\t•LOGICAL\n");
				else if (ch == '='){ fprintf(table,"%c",ch); ch = fgetc(file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						fprintf(table,"\t•EQUALITY\n");
				}
				else if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') invalid = 1;
				else invalidOpr = 1;
			} //! !=
			
			//-----DELIMITER-----
			else if (ch=='('||ch == ')'||ch == '{'||ch == '}'||ch == ';'){
				char temp = ' '; 
				temp = ch;
				fprintf(table,"%c",ch); ch = fgetc(file);
				if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF){
					switch (temp){
						case '(' : 	fprintf(table,"\t•PAREN_OP\n");
									break;
						case ')' : 	fprintf(table,"\t•PAREN_CL\n");
									break;
						case '{' : 	fprintf(table,"\t•BRKT_OP\n");
									break;
						case '}' : 	fprintf(table,"\t•BRKT_CL\n");
									break;
						case ';' :	fprintf(table,"\t•SEPARATOR\n");				
					}
				}					
				else if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') invalid = 1;
				else invalidOpr = 1;
			} // ( ) { } ;
			
			else if(ch!=EOF){
				while (ch!=' '&&ch!='\n'&&ch!='\r'&&ch!='\t'&&ch!=EOF){
					fprintf(table,"%c",ch);
					if (ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||ch>='0'&&ch<='9')
						invalid = 1;
					ch = fgetc(file);
				} if (invalid == 0) invalidOpr = 1;
			}
			
			if (invalid||invalidOpr){
				while (ch!=EOF&&ch!='\n'&&ch!=' '&&ch!='\t'){
					fprintf(table,"%c", ch);
					ch = fgetc(file);
				}	
				if(invalidOpr) fprintf(table,"\t•INVALID_OPERATOR\n");
				else fprintf(table,"\t•INVALID_IDENTIFIER\n");
			}//Invalid
		
		}
		fclose(file);
		fclose(table);
		printf ("DONE");
	}
	else printf("INVALID FILE\n");
}

void comments(FILE **file, FILE **table, int line, char ch){
	if (line == 0){
		while (ch!='\n'&&ch!=EOF){
			fprintf(*table,"%c", ch);
			ch = fgetc(*file);
		}	
		fprintf(*table,"\t•SINGLE_COMMENT\n");
	} else {
		int end = 0;
		char cmt[3];
		LOOP: while(ch!='C'&&ch!=EOF){
				fprintf(*table,"%c", ch);
				ch = fgetc(*file);
			}
		
		if (ch == 'C'){ cmt[0] = ch; ch = fgetc(*file);
			if (ch == 'M'){ cmt[1] = ch; ch = fgetc(*file);
				if (ch == 'T'){ cmt[2] = ch; ch = fgetc(*file);
					if (ch == '\n' || ch==' '|| ch=='\r' || ch=='\t' || ch==EOF)
						end = 1;
					else { fprintf(*table,"%s", cmt); goto LOOP; }							
				} else { fprintf(*table,"M%c", ch); goto LOOP; }
			} else { fprintf(*table,"C"); goto LOOP; }
		} //CMT
		
		fprintf(*table,"\t•MULTILINE\n");
		if (end == 1)
			fprintf(*table,"%s\t•COMMENT_END\n", cmt);
	}
} //COMMENTS
















