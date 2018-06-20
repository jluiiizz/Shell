# shell

## RECENTLY DONE

- Add the **rest** operation.
- Add division operation.
- Add multiplying operation.
- Refactored **math_evaluate**.
- Evaluate simple expressions in MATH mode.

## DOING

- Add support to **fload** and **double** numbers. (VERY HIGH)

## TODO

- Add support to **()**. (VERY HIGH)
- Add support to functions, like **pow, sqrt, integrate, differatiate**. (VERY HIGH)
- Use automated tests. (HIGH)
- Separate input, output and processing from **shell.c**. (HIGH)
- Create a better form to handle arguments in commands. In **ls** for example, "-l" "-la". (HIGH)
- Improve organization and separate source files, include files and lib. files. (NORMAL)
- Improve Makefile linking. (LOW)
- Create an integration with the TWITCH API. (MISC, NORMAL)
- Read information from config file. (HIGH) [THINK ABOUT WHAT THIS FILE WILL CONFIG]
- Configure UpArrow key to show last command. (NORMAL)
- Add support for permissions.
- Add support for links. (LOW)

## BUGS

- MV does not work with linked folders. (NORMAL)

## DONE

- [BUG] **isdigit** just accepting *unsigned chars* in GCC 8. (SOLVED) [Was just a logic problem] (SOLVED)
- [BUG] Not running on GCC 8 on Linux.(SOLVED)
- Create a **Makefile** to make compile process easier.
- Show files and folders size in nibbles on **ls** command.
- Create a command to clear the history (**clrhistory**).
- Create **copy** (cp) command.
- Create **move** (mv) command.
- Create the input system to MATH mode.
- Start code the MATH mode.
- Change the "PS1" variable to make shell more readable.
- Global refactoring.
- Refactor **save_on_history** function and review all code.
- Figure out a better way to generate abosolute paths.
- Create a simple HISTORY file.
- Create a config file.
- Create a **user** command, that shows current user.
- Create a little documentation. In README.
- Generate config and log storage files on first initialization.
- Fix the **shell_process** bug. Stop starting new process after use an unkown command.
- Check **line 289** from **shell.c**, possible rendundance.
- Execute process from programs outsite the shell.
- Create a simple **echo** command.
- Create the **cat** command.
- Implement a **--force** argument to **rmdir** command, to exclude non-empty directories.
- Refactor **shell.c** code.
- Create the **touch** command.
- Create **rm** command.
- Create **rmdir** command.
- Use **stat** system call to verify if a path is a dir or a file.
- Create the **mkdir** command.
- Implement colors.
- Implement the '-l' argument to **ls** command.
- Separate files from directories while using **ls**.
- Review all the code and refactor what is necessary.
- Set virtual machine to start in our shell.
- Create the **cd** command.
- Create the **ls** command.
- Create our initialization setup.
- Create the **help** command.
- Create the **clear** command.
- Create the **pwd** command.
- Create our command system and the **exit** command.
- Read a complete line and print the entire same line.
- Create a continuous loop.
- Create **Utils** file and some basic functions, like uppercase and lowercase strings.
- Create and setup git and github repository.
