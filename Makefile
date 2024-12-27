FILE=
$(FILE)-exe: $(FILE).c
	gcc -g -Wall -Werror -Wextra -o $(FILE)-exe $(FILE).c -finput-charset=UTF-8

