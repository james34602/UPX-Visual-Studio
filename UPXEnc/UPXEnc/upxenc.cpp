#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	if (argc < 2){
		printf("Usage: UPXEnc.exe <file>\n");
	}
	else{
		FILE *fFile = fopen(argv[1], "rb");
		if (fFile != NULL){
			printf("File (modified): %s\n", argv[1]);

			fseek(fFile, 0, SEEK_END);
			long lSize = ftell(fFile);
			rewind(fFile);

			char *cBuffer = (char *)malloc(lSize*sizeof(char *));
			if (cBuffer != NULL){
				fread(cBuffer, 1, lSize, fFile);
				fclose(fFile);

				BOOL bUPX = FALSE;

				for (int i = 0; i < lSize; i++){
					if ((cBuffer[i] == 0x55) && (cBuffer[i + 1] == 0x50) && (cBuffer[i + 2] == 0x58) && cBuffer[i + 3] == 0x30){
						printf("Found byte pattern at offset: %i\n", i);
						// This is the only value we need to change (UPX0), not (UPX1) or (UPX!)
						cBuffer[i] = 0x41; // Change U (0x55) to A (0x41). 

						bUPX = TRUE;
					}
				}

				if (bUPX == TRUE){
					fFile = fopen(argv[1], "wb");
					if (fFile != NULL){
						fwrite(cBuffer, 1, lSize, fFile);
						free(cBuffer);
						fclose(fFile);

						printf("File %s should be successfully patched!", argv[1]);
					}
					else{
						printf("Unable to open file (write binary).\n");
						return 0;
					}
				}
				else{
					printf("File is not packed by UPX.\n");
					free(cBuffer);

					return 0;
				}
			}
			else{
				printf("Error at: malloc()\n");
				return 0;
			}
		}
		else{
			printf("Unable to open file (read binary).\n");
			return 0;
		}
	}

	getchar();
}