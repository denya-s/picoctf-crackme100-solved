#include <stdio.h>
#include <string.h>
#include <stdint.h> 
#include <stdbool.h>

int main()
{
	int passwd_correct;
  	size_t passwd_length;
  	char user_input [51] = {0};
  	
  	char char_a;
  
  	unsigned int encoding_2;
  	unsigned int encoding_1;
  	unsigned int int_15;
  	unsigned int int_51;
  	unsigned int int_85;
  
  	int passwd_length_2;
  	int j = 0;
  	int i = 0; 

    // YOUR PASSWORD STRING HERE.
	char full_password[51] = "qhcpgbpuwbaggepulhstxbwowawfgrkzjstccbnbshekpgllze";	

  	int_85 = 85;
  	int_51 = 51;
  	int_15 = 15;
  	char_a = 'a';

// Bruteforce:
	
	bool cracked = false; // Password has/hasn't been cracked.
    bool char_cracked = false; // Seperate character has/hasn't been cracked.	
       
    int attempt = 0; // Attempt number.
	int changer = 32; // Will grow and change the input character.

    // For changing the user_input character thesame way repeatedly. 
    int enc2_array[50] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,16,17,17,18,17,18,18,19,17,18,18,19,18,19,19,20,16,17,17,18,17,18,18,19,17,18,18,19,18,19,19,20,32,33};

    while(!cracked) // While the password hasn't been cracked:
	{ 
        for (i = 0; i < 50; ++i) 
        {
            char_cracked = false;
            while (!char_cracked)
            {      
                user_input[i] = (char)changer; // Will change the input from 32 to 126 or up to when char_cracked will become true.
    
                // Will encode each character repeatedly until char_cracked will be equal to true:
	            for (j = 0; j < 3; ++j)
                {
		            passwd_correct = (enc2_array[i] >> 4 & int_15) + ((int)user_input[i] - (int)char_a) + (int_15 & enc2_array[i]);
		            user_input[i] = char_a + (char)passwd_correct + (char)(passwd_correct / 0x1a) * -0x1a; // 0x1a = 26.
                }

               // printf("user_input[%d]: %d (%c), full_password[%d]: %d (%c)\n", i, user_input[i], user_input[i], i, full_password[i], full_password[i]);
                
  	          //  passwd_correct = ((char)user_input[i] == (char)full_password[i]) ? 1 : 0; // Check if character is correct (if it is passwd_correct will be 0, if not, it won't).
                passwd_correct = strncmp(&user_input[i], &full_password[i], 1); 
                if (passwd_correct == 0) // Check this condition to determine the correctness of the character:
		        {
    			    printf("\nCHAR %d: SUCCESS! \n", i);
                    printf("Character = %c\n\n", (char)changer); // Display the correct character
                    user_input[i] = (char)changer; // Put the correct character into the correct place in the input.
 			    
                    attempt = 0; // Reset the attempt counter.  
                    changer = 32; // Change to the first diplayable character.
                    char_cracked = true; // Go to the next character in user_input.
                    if (i == 49) 
                    {
                        cracked=true;
                    }
                }
                else  
		        {
                    // Increase the attempt number, 
                    // output the attempt number and character tested, 
                    // increment the character changer to test the next character.
		            attempt++;
			       // printf("\nAttempt number: %d", attempt);
			       // printf("\nChar tested: = %c\n", (char)changer);
                    changer++;	
		        }
  		    }
        }	
	}

    printf("\n\nPassword testing: %s", user_input);	
	
	for (i = 0; i < 3; i = i + 1) {
		for (j = 0; j < 50; j = j + 1) {	
	        encoding_1 = (j % 0xff >> 1 & int_85) + (j % 0xff & int_85); // 0xff = 255.
      	    encoding_2 = ((int)encoding_1 >> 2 & int_51) + (int_51 & encoding_1);
		    passwd_correct = ((int)encoding_2 >> 4 & int_15) + ((int)user_input[j] - (int)char_a) + (int_15 & encoding_2);
	        user_input[j] = char_a + (char)passwd_correct + (char)(passwd_correct / 0x1a) * -0x1a; // 0x1a = 26.
    	}
  	}

	passwd_correct = memcmp(user_input,full_password, 50); // Check this condition:
  	if (passwd_correct == 0) 
	{
        printf("\nSUCCESS! \n");
    }
  	else 
	{
	    printf("\nWRONG! \n"); 
    }
   	
  	return 0;
}

