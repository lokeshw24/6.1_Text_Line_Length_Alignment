/*WHAT PROG DOES :
 * 	Takes input file, and breaks it into lines of fixed length & outputs those lines.
 * 	The length of each printed line is < the fixed length.If any line ends in the middle of
 * 	some word, then that entire word is printed in next line & the current line is printed
 * 	with less characters.
 *
 */

#include<stdio.h>
#include<string.h>


#define ALIGNMENT_LENGTH 31
#define TRUE 1
#define FALSE 0

int main(){
	char filename[]="temp.c";
	FILE *fp=fopen(filename , "r" );
	int t=ALIGNMENT_LENGTH+1;
	char aligned_line[t];
	char broken_word[ALIGNMENT_LENGTH];
	int i=0 , j;
	 
	FILE *new_fp=fopen("formatted_output_file.c" ,"w" );

	while(1){
		for( ; i<t && ( *(aligned_line+i)=(char)fgetc(fp) ) != EOF ; i++ );

		char *temp=aligned_line+(i-1);
		/*basically, we are supposed to put '\0' at temp,
		 * but before doing so, lets check if temp has read half word 
		 * or something like that.
		 *
		 */
		if( *(temp+1)==EOF ){
			*(temp+1)='\0';
			printf("%s", aligned_line );

			break ;
		}

		else if( *temp==' ' || *temp=='\t' ){
			broken_word[0]=*temp;
			*temp='\0';
			i=0;
		}
		else{
			for(i=0 ; !isspace(*temp) ; i++ ){
				*(broken_word+i)=*temp;
				temp--;
			}
			*(temp+1)='\0' ;
			--i;
		}

		fprintf( new_fp , aligned_line );

		//printf("%s$$\n", aligned_line, i , EOF_flag );

		/*now fill the aligned_line, by broken_word, but in reverse order */
		int k=0;
		while(i>-1){
			*(aligned_line+k)=*(broken_word+i);
			k++;
			i--;
		}
		i=k;

	}

	fclose(fp);
	fclose(new_fp);

return 0;

}

