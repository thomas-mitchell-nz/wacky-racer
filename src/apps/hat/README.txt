In order to program the SAM4S

First, plug SAM4S into USB port with ST-LINK Cable.

Next open a Command Prompt window through the Run Menu (Windows Key + R) type cmd and press enter. Into that window enter the following command:
C:\ence461\ence461-path
This will start the toolchain.

Next navigate to the directory bellow:
cd P:\UC2023\Sem 1\ENEL461\wacky-racers

Then enter this command:
openocd -f src/mat91lib/sam4s/scripts/sam4s_stlink.cfg
This will start OCD, which will monitor the response from the SAM4S.

Now open another Command Prompt window. Navigate to the directory with the code you wish to upload.
Also enter the following command:
C:\ence461\ence461-path

Now navigate to desired project directory, this directory must contain a makefile.
Main project directory: 
cd P:\UC2023\Sem 1\ENEL461\wacky-racers\src\apps\hat
Now you may use `make` commands to compile and upload.

Note if makefile does not contain "BOARD = hat" then you must assign this in command prompt
to do this, on windows enter `set BOARD=hat` or on linux/macos `BOARD=hat`.

NOTE:
If you ever erase the memory with the erase pin you MUST rerun the following command before you can program again:
make bootflash

can use 
C:\ence461 
directory to get automated files