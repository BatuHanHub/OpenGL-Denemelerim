# - Proje Özellikleri - #
PROJEADI = kanser-oyun
# -- #

# - Derleyiciler - #
CC = g++ # Linux
CCW = x86_64-w64-mingw32-g++ # w*ndows
# -- #

# - Build Dizinleri - #
WINBUILD = ./build/windows
LINUXBUILD = ./build/linux
# -- #

# - Dosya Hiyerarşi - #
SOURCE = ./src
INCLUDE = ./include
LIB = ${WINBUILD}/bin
# -- #

# - Kaynaklar - #
SOURCES = ${SOURCE}/main.cpp ${SOURCE}/glad.c
TUTOSRC = ${SOURCE}/tutorial.cpp ${SOURCE}/glad.c
# -- #

# - Parametreler - #
PARAMS = -Wall -lstdc++ -lGL -lglfw
PARAMSW = -DWIN32 -static -static-libstdc++ -static-libgcc -lmingw32 -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32
# -- #

all: clean lBuild wBuild lRun

# - Linüx :) - #
lBuild: 
	${CC} ${SOURCES} -I${INCLUDE} ${PARAMS} -o ${LINUXBUILD}/bin/${PROJEADI}

lRun: 
	${LINUXBUILD}/bin/${PROJEADI}
# -- #

# - w*ndows - #
wBuild: 
	${CCW} ${SOURCES} -I${INCLUDE} ${PARAMSW} -L${LIB} -o ${WINBUILD}/bin/${PROJEADI}.exe

wRun: 
	start ${WINBUILD}/bin/${PROJEADI}.exe
# -- #

tuto: 
	${CC} ${TUTOSRC} -I${INCLUDE} ${PARAMS} -o ${LINUXBUILD}/bin/${PROJEADI}
	${CCW} ${TUTOSRC} -I${INCLUDE} ${PARAMSW} -L${LIB} -o ${WINBUILD}/bin/${PROJEADI}.exe

clean:
	rm -rf ${LINUXBUILD}/bin/*
	rm -rf ${WINBUILD}/bin/*.exe
	clear
