private void btnBrowseFile1_Click(object sender, EventArgs e)
{
    OpenFileDialog browser1 = new OpenFileDialog();
    DialogResult locRes = browser1.ShowDialog() ;
    if (locRes == DialogResult.OK)
    {
        txtboxFile1.Text = browser1.FileName;
        filesToOpen[0] = txtboxFile1.Text;
    }
}

private void btnBrowseFile2_Click(object sender, EventArgs e)
{
    OpenFileDialog browser2 = new OpenFileDialog();
    DialogResult locRes = browser2.ShowDialog();
    if (locRes == DialogResult.OK)
    {
        txtboxFile2.Text = browser2.FileName;
        filesToOpen[1] = txtboxFile2.Text;
    }
}
private void btnRun_Click(object sender, EventArgs e)
{
    if (filesToOpen[0] == null && filesToOpen[1] == null)
        MessageBox.Show("No Files selected");

    int i = 0;
    while (i < filesToOpen.Length)
    {
        if (filesToOpen[i] != null && filesToOpen[i] != "")
            System.Diagnostics.Process.Start(filesToOpen[i]);
        i = i + 1;
    }
}
private void btnSave_Click(object sender, EventArgs e)
{
    SaveFileDialog saver = new SaveFileDialog();
    DialogResult LocRes = saver.ShowDialog();
    if (LocRes == DialogResult.OK)
        System.IO.File.WriteAllLines(saver.FileName + ".os", filesToOpen);
        System.IO.File.WriteAllLines(saver.FileName + ".knl", filesToOpen);
        System.IO.File.WriteAllLines(saver.FileName + ".google", filesToOpen);
        private void load(string file)
{
    if (System.IO.Path.GetExtension(file).Equals(".tfo"))
    {
        filesToOpen = System.IO.File.ReadAllLines(file);
        txtboxFile1.Text = filesToOpen[0];
        txtboxFile2.Text = filesToOpen[1];
    }
    else
        MessageBox.Show("Did You Forget to add ".os" at the end?");
}

private void btnLoad_Click(object sender, EventArgs e)
{
    OpenFileDialog loader = new OpenFileDialog();
    DialogResult locRes = loader.ShowDialog();
    if (locRes == DialogResult.OK)
        load(loader.FileName);
}
static void Main(string [] args)
static void Main(string [] args)
{
    Application.EnableVisualStyles();
    Application.SetCompatibleTextRenderingDefault(false);
    
    if (args.Count() == 1)
        Application.Run(new Form1(args[0]));
    else
        Application.Run(new Form1());
}
public Form1(string caller)
{
    InitializeComponent();
    load(caller);
}
}
//
// Reading/writing raw sectors.
//
 
//pBuffer has to be at least 512 bytes wide.
BOOL ReadSector(char chDriveName,char *pBuffer,DWORD nSector)
{
 
    char Buffer[256];
    HANDLE hDevice;
    DWORD dwBytesReaden;

    //Init the drive name (as a Driver name). 
    sprintf(Buffer,"\\\\.\\%c:",chDriveName);

    hDevice = 
      CreateFile(Buffer,                  // drive to open.
                GENERIC_READ,
                FILE_SHARE_READ | // share mode.
                FILE_SHARE_WRITE, 
                NULL,             // default security attributes.
                OPEN_EXISTING,    // disposition.
                0,                // file attributes.
                NULL);            // 

    if(hDrive==INVALID_HANDLE_VALUE)//if Error Openning a drive.
    {
           return FALSE;
    }
 
    //Move the read pointer to the right sector.
    if(SetFilePointer(hDevice,
           nSector*512,
           NULL,
           FILE_BEGIN)==0xFFFFFFFF)
           return FALSE;

    //Read the Sector.
    ReadFile(hDevice,
           pBuffer,
           512,
           &dwBytesReaden,
           0);

    //if Error reading the sector.
    if(dwBytesReaden!=512)
           return FALSE;

    return TRUE;
}
StepRateAndHeadUnloadTime                     db      0DFh
HeadLoadTimeAndDMAModeFlag                    db      2h
DelayForMotorTurnOff                          db      25h
BytesPerSector                                db      2h              
SectorsPerTrack                               db      12h            
IntersectorGapLength                          db      1bh
DataLength                                    db      0FFh
IntersectorGapLengthDuringFormat              db      54h
FormatByteValue                               db      0F6h
HeadSettlingTime                              db      0Fh
DelayUntilMotorAtNormalSpeed                  db      8h
 
DisketteSectorAddress(as LBA)OfTheDataArea    db      0
CylinderNumberToReadFrom                      db      0
SectorNumberToReadFrom                        db      0
DisketteSectorAddress (as LBA) OfTheRootDirectory    db      0
delay(10000);
db 0E9h  ; FAR JMP op code.
db 512   ; 512 bytes
call GiveControlToOS
 
GiveControlToOS:
        Pop ax
        Pop ax
        Mov ax,CodeSegement            ;Push the new CS to return.
        Push ax
        mov ax,InstructionPointer      ;Push the new IP to return.
        Push ax
 
        ret                            ;Return to the modified address.
        .MODEL SMALL

.CODE          

ORG 7c00h      ;Because BIOS loades the OS at 
                       ; address 0:7C00h so ORG 7C00h 
                       ; makes that the refrence to date 
                       ; are with the right offset (7c00h).
 
ProgramStart:

                       
   ; CS = 0 / IP = 7C00h // SS = ? / SP = ?
   ; You are now at address 7c00.
jmp start   ;Here we start the, BIOS gave us now the control.



;///////////////////////////////////////////
;//Here goes all the data of the program.
;///////////////////////////////////////////

xCursor db 0
yCursor db 0


nSector db 0
nTrack  db 0
nSide   db 0
nDrive  db 0

nTrays  db 0

'Are You Ready to start Loading the OS...',0
szReady                db
'Error Reading Drive, Press any Key to reboot...',0
szErrorReadingDrive    db
;//Done Reading a track.
szPlaceMarker          db  '~~~~',0
szDone                 db  'Done',0

pOS                    dw   7E00h
;//Points to were to download the Operating System. 

;//Disk Paremeter Table.
StepRateAndHeadUnloadTime                     db      0DFh
HeadLoadTimeAndDMAModeFlag                    db      2h
DelayForMotorTurnOff                          db      25h
;// (1 = 256) //(2 = 512 bytes)
BytesPerSector                                db      2h
;// 18 sectors in a track.
SectorsPerTrack                               db      18
IntersectorGapLength                          db      1Bh
DataLength                                    db      0FFh
IntersectorGapLengthDuringFormat              db      54h
FormatByteValue                               db      0F6h
HeadSettlingTime                              db      0Fh
DelayUntilMotorAtNormalSpeed                  db      8h

DisketteSectorAddress_as_LBA_OfTheDataArea    db      0
CylinderNumberToReadFrom                      db      0
SectorNumberToReadFrom                        db      0
DisketteSectorAddress_as_LBA_OfTheRootDirectory      db      0

;/////////////////////////////////
;//Here the program starts.
;/////////////////////////////////


Start:

CLI     ;Clear Interupt Flag so while setting 
        ;up the stack any intrupt would not be fired.

        mov AX,7B0h    ;lets have the stack start at 7c00h-256 = 7B00h
        mov SS,ax      ;SS:SP = 7B0h:256 = 7B00h:256
        mov SP,256     ;Lets make the stack 256 bytes.

        Mov ax,CS      ;Set the data segment = CS = 0 
        mov DS,ax
        
        XOR AX,AX      ;Makes AX=0.
        MOV ES,AX      ;Make ES=0


STI     ;Set Back the Interupt Flag after 
        ;we finished setting a stack fram.
       
        Call ClearScreen       ;ClearScreen()
        LEA AX,szReady         ;Get Address of szReady.
        CALL PrintMessage      ;Call PrintfMessage()
        CALL GetKey                    ;Call GetKey()
        
        CALL SetNewDisketteParameterTable
        ;SetNewDisketteParameterTable()
        
        CALL DownloadOS
        CALL GetKey                    ;Call GetKey()
        CALL FAR PTR  GiveControlToOS  ;Give Control To OS.

ret

;/////////////////////////////////////
;//Prints a message to the screen.
;/////////////////////////////////////
PrintMessage PROC

        mov DI,AX      ;AX holds the address of the string to Display.
        Mov xCursor,1  ;Column.
        
ContinuPrinting:

        cmp byte ptr [DI],0    ;Did we get to the End of String.
        JE EndPrintingMessage  ;if you gat to the end of the string return.
        
        mov AH,2               ;Move Cursor
        mov DH,yCursor         ;row.
        mov DL,xCursor         ;column.
        mov BH,0               ;page number.
        INT 10h
        INC xCursor
        
        mov AH,0Ah             ;Display Character Function.
        mov AL,[DI]            ;character to display.
        mov BH,0               ;page number.
        mov CX,1               ;number of times to write character
        INT 10h
        
        
               
        INC DI                 ;Go to next character.
        
        JMP ContinuPrinting    ;go to Print Next Character.
               
EndPrintingMessage:
        
        Inc yCursor            ;So Next time the message would
                               ;be printed in the second line.
        
        cmp yCursor,25
        JNE dontMoveCorsurToBegin 
        Mov yCursor,0
        
dontMoveCorsurToBegin:
        ret
        
               
PrintMessage EndP 
;//////////////////////////////////////
;//Watis for the user to press a key.
;//////////////////////////////////////
GetKey PROC

        mov ah,0
        int 16h ;Wait for a key press.
        Ret
        
GetKey EndP 
;///////////////////////////////////////////
;//Gives Control To Second Part Loader.
;///////////////////////////////////////////
GiveControlToOS PROC

        LEA AX,szDone
        Call PrintMessage
        CALL GetKey
        
        db 0e9h        ;Far JMP op code.
        dw 512         ;JMP 512 bytes ahead.
        
;       POP AX         ;//Another why to make 
                       ;the CPU jump to a new place.
;       POP AX
;       Push 7E0h      ;Push New CS address.
;       Push 0          ;Push New IP address.
               ;The address that comes out is 7E00:0000. 
               ;(512 bytes Higher from were BIOS Put us.)
;       ret
        
        
GiveControlToOS EndP 
;///////////////////////////////////
;//Clear Screen.
;///////////////////////////////////
ClearScreen PROC

        mov ax,0600h   ;//Scroll All Screen UP to Clear Screen.
        mov bh,07
        mov cx,0
        mov dx,184fh   
        int 10h
        
        Mov xCursor,0  ;//Set Corsur Position So next 
                        //write would start in 
                        //the beginning of screen.
        Mov yCursor,0

        Ret
        
ClearScreen EndP
;/////////////////////////////////
;//PrintPlaceMarker.
;/////////////////////////////////
PrintPlaceMarker PROC


        LEA AX,szPlaceMarker
        CALL PrintMessage  ;Call PrintfMessage()
        CALL GetKey        ;Call GetKey()
        ret
        
PrintPlaceMarker EndP
;/////////////////////////////////////////
;//Set New Disk Parameter Table
;/////////////////////////////////////////
SetNewDisketteParameterTable PROC

        LEA DX,StepRateAndHeadUnloadTime
        ;//Get the address of the Disk Parameters Block. 
        
               ;//Int 1E (that is in address 0:78h) 
               ;//holds the address of the disk parametrs 
               ;//block, so now change it to 
               ;//our parametr black.
        ;//DX holds the address of our Parameters block.
        MOV WORD PTR CS:[0078h],DX
        MOV WORD PTR CS:[007Ah],0000
        
        ;Reset Drive To Update the DisketteParameterTable.
        MOV AH,0
        INT 13H
       
        ret
        
SetNewDisketteParameterTable EndP
;///////////////////////////////////
;//DownloadOS
;///////////////////////////////////
DownloadOS PROC

        mov nDrive,0
        mov nSide,0
        mov nTrack,0
        mov nSector,1
        
ContinueDownload:
        
        INC nSector            ;Read Next Sector.
        cmp nSector,19         ;Did we get to end of track.
        JNE StayInTrack
        CALL PrintPlaceMarker  ;Print now '~~~~' so the user would 
                               ;now that we finished reding a track
        INC nTrack             ;If we gat to end of track Move to next track.
        mov nSector,1          ;And Read Next Sector.
        CMP nTrack,5           ;Read 5 Tracks (Modify this value 
                               ;to how much Tracks you want to read).
        JE      EndDownloadingOS
        
StayInTrack:
        
        ;ReadSector();
        Call ReadSector
        
        
        JMP     ContinueDownload
        ;If diden't yet finish Loading OS.
        
EndDownloadingOS:

        ret
        
DownloadOS EndP 
;////////////////////////////////////////
;//Read Sector.
;////////////////////////////////////////
ReadSector PROC

        mov nTrays,0
        
TryAgain:

        mov AH,2               ;//Read Function.
        mov AL,1               ;//1 Sector.
        mov CH,nTrack
        mov CL,nSector         ;//Remember: Sectors start with 1, not 0.
        mov DH,nSide
        mov DL,nDrive
        Mov BX,pOS             ;//ES:BX points to the address 
                               ;to were to store the sector.
        INT 13h
        

        CMP AH,0               ;Int 13 return Code is in AH.
        JE EndReadSector       ;if 'Sucsess' (AH = 0) End function.

        mov AH,0               ;Else Reset Drive . And Try Again...
        INT 13h
        cmp nTrays,3           ;Chack if you tryed reading 
                               ;more then 3 times.
        
        JE DisplayError        ; if tryed 3 Times Display Error.
        
        INC nTrays
        
        jmp TryAgain       ;Try Reading again.
        
DisplayError:
        LEA AX,szErrorReadingDrive
        Call PrintMessage
        Call GetKey
        mov AH,0                       ;Reboot Computer.
        INT 19h
        

EndReadSector:
        ;ADD WORD PTR pOS,512  ;//Move the pointer 
                               ;(ES:BX = ES:pOS = 0:pOS) 512 bytes.
                               ;//Here you set the varible 
                               ;pOS (pOS points to were BIOS 
                               ;//Would load the Next Sector).
        Ret
        
ReadSector EndP 
;////////////////////////////////////
;//
;////////////////////////////////////
END ProgramStart
