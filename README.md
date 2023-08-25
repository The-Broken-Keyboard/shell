# Description

# Assumptions
1. If a command line (which may be consisting of many several commands concatenated in sequence via';' or '&') takes more than 2 seconds in foreground , then I am printing the command names of all commands (exactly one time) and total time taken by that particular command line while getting executed along with prompt.
2. I am assuming that while doing seek if a file name or folder name contains the name which is being searched then they should get printed because user might not be remembering the full name of file or folder.
3. I am assuming there will be space between consecutive - signs (if given with warp). Though i also handled the case if consecutive - signs are given but that is not necessary i guess , so i removed it.
4. In proclore , since our this shell will run in foreground , no other process except of this shell process will contain + sign. 
5. I am not handling the exit command since it was not mentioned in project document and also exit is not executed by execvp.
6. I am storing all commands which got entered in shell as pastevents , even if they were wrong commands.