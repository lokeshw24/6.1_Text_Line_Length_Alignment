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
#define GAP 10
#define TRUE 1
#define FALSE 0

int main(){
	char filename[]="temp.c";
	FILE *fp=fopen(filename , "r" );
	int t=ALIGNMENT_LENGTH+1;
	char aligned_line[t];
	char broken_word[ALIGNMENT_LENGTH];
	int i=0 , j;

	/* Code to find the no_of_lines ------------
	 *
	int no_of_lines=system("wc -l temp.c | awk '{ print $1 }' ") ;
	no_of_lines=no_of_lines/2;

	if( no_of_lines < 23 ) printf("sldfj ");
	 
	printf("%d \n", no_of_lines );
	return 0;
	*/

	int no_of_characters=1175;
	no_of_characters/=2;
	printf("%d \n", no_of_characters);

	FILE *new_fp=fopen("formatted_output_file.c" ,"w" );

	while(1){
		for( ; i<t && no_of_characters && ( *(aligned_line+i)=(char)fgetc(fp) ) != EOF ; i++ , --no_of_characters ){
			//printf("%c(%d) \n", *(aligned_line+i) , no_of_characters );

		}
			/*if( *(aligned_line+i)=='\n' ) {
				*(aligned_line+i)=(char)fgetc(fp);
			}
			*/
		char *temp=aligned_line+(i-1);
		printf("Stopped at : %c ", *temp );
		/*basically, we are supposed to put '\0' at temp,
		 * but before doing so, lets check if temp has read half word 
		 * or something like that.
		 *
		 */


		/*Changed (temp+1) to (temp) from original code */

		if( *(temp)==EOF || no_of_characters<1 ){
			printf("Temp , i : %c %d \n", *(temp) , i );
			*(temp+1)='\0';
			fprintf( new_fp , "%s\n", aligned_line );
			fclose(new_fp);
			//fprintf( new_fp , "%c", EOF );
			printf("*** \n");
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

		fprintf( new_fp , "%s\n", aligned_line );

		//printf("%s$$\n", aligned_line  );

		/*now fill the aligned_line, by broken_word, but in reverse order */
		int k=0;
		while(i>-1){
			*(aligned_line+k)=*(broken_word+i);
			k++;
			i--;
		}
		i=k;
		//printf("i set to : %d , broken word : %s\n" , i , broken_word);

	}


	/*now half of file is being written as 1st column, so 2nd column will be written using fseek() 
	 */
	printf("%d \n", no_of_characters);
	new_fp=fopen("formatted_output_file.c" ,"w" );
	i=0;

	int sec_col_offset=ALIGNMENT_LENGTH + GAP;

	while(1){
		for( ; i<t && ( *(aligned_line+i)=(char)fgetc(fp) ) != EOF ; i++ );

		char *temp=aligned_line+(i-1);
		/*basically, we are supposed to put '\0' at temp,
		 * * but before doing so, lets check if temp has read half word 
		 * * or something like that.
		 * *
		 * */
		if( *(temp)==EOF ){
			*(temp+1)='\0';
			fseek(new_fp , sec_col_offset , SEEK_CUR );
			fprintf( new_fp , "%s\n", aligned_line );
			fclose(new_fp);
			printf("*** \n");
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

		fseek(new_fp , sec_col_offset , SEEK_CUR );
		fprintf( new_fp , "%s\n", aligned_line );
		//printf("%s$$\n", aligned_line);

		/*now fill the aligned_line, by broken_word, but in reverse order */
		int k=0;
		while(i>-1){
			*(aligned_line+k)=*(broken_word+i);
			k++;
			i--;
		}
		i=k;

	}

	fclose(new_fp);
	fclose(fp);

return 0;

}

