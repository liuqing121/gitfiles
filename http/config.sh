#!/bin/bash



ROOT_PATH=$(pwd)
SRC=$(echo *.c)
OBJ=$(echo ${SRC} | sed 's/\.c/\.o/g')
CC=gcc
OPTION=lpthread
SERVER_NAME=httpd
#main Makefile
cat << EOF >Makefile
.PHONY:all
all:${SERVER_NAME} cgi

${SERVER_NAME}:${OBJ}
	${CC} -o \$@ \$^ -${OPTION} -g
%.o:%.c
	${CC} -c \$<

.PHONY:cgi
cgi:
	cd cgi;make;make output;cd -
.PHONY:clean
clean:
	rm -rf ${SERVER_NAME} ${OBJ} output; cd cgi; make clean;cd -

.PHONY:output
output:all
	mkdir output
	cp ${SERVER_NAME} output/
	cp -rf log output/
	cp -rf conf output/
	cp -rf wwwroot output/
	mkdir -p output/wwwroot/cgi_bin
	cp -f cgi_math output/wwwroot/cgi_bin
	cp -r http_ctl.sh output/
EOF

#cgi Makefile
CGI_PATH=$ROOT_PATH/cgi/
MATH_SRC=$(ls $CGI_PATH | grep 'math' | grep -E '.c$')
MATH_CGI_BIN=cgi_math

cat <<EOF > $CGI_PATH/Makefile
${MATH_CGI_BIN}:$MATH_SRC
	$CC -o \$@ \$^ -g

.PHONY:clean
clean:
	rm -f $MATH_CGI_BIN
.PHONY:output
output:
	cp $MATH_CGI_BIN ..
EOF
