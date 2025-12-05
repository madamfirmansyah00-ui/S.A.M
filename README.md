# S.A.M
COMP 1028 project
•	How to Compile:
	This program is written in C and was developed using the MinGW GCC compiler. As the project is separated into different files, all source files must be linked during compilation.
	To compile the program, navigate to the project directory in your terminal and run the following command: gcc main.c analysis.c file_io.c report.c sorting.c tokenizer.c toxicity.c ui.c -o      analyzer.exe

•	Required Input Files
	The program requires the following text files to be present in the same directory as the executable (analyzer.exe) for full functionality:
	stopwords.txt
	toxicwords.txt
	test.txt

•	3. Output
	analysis_report.txt: The program will save the final report to this location. Ensure a folder named output exist. 

•	4. Dependencies
	The program relies on the standard C library (stdio.h, stdlib.h, string.h, ctype.h) and some special headers (“analysis.h”, “file_io.h”, “report.h”, “sorting.h”, “tokenizer.h”, “toxicity.h”, “ui.h”) 
