#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/cachoeira.o \
	${OBJECTDIR}/jogo_bola.o \
	${OBJECTDIR}/lobo.o \
	${OBJECTDIR}/menu.o \
	${OBJECTDIR}/jogo.o \
	${OBJECTDIR}/gota.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/jogo_coruja.o \
	${OBJECTDIR}/item_madeira.o \
	${OBJECTDIR}/jogo_morcego.o \
	${OBJECTDIR}/rato.o \
	${OBJECTDIR}/animal.o \
	${OBJECTDIR}/atoxado.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/torquere

dist/Release/GNU-Linux-x86/torquere: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/torquere ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/cachoeira.o: nbproject/Makefile-${CND_CONF}.mk cachoeira.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/cachoeira.o cachoeira.cpp

${OBJECTDIR}/jogo_bola.o: nbproject/Makefile-${CND_CONF}.mk jogo_bola.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/jogo_bola.o jogo_bola.cpp

${OBJECTDIR}/lobo.o: nbproject/Makefile-${CND_CONF}.mk lobo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/lobo.o lobo.cpp

${OBJECTDIR}/menu.o: nbproject/Makefile-${CND_CONF}.mk menu.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/menu.o menu.cpp

${OBJECTDIR}/jogo.o: nbproject/Makefile-${CND_CONF}.mk jogo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/jogo.o jogo.cpp

${OBJECTDIR}/gota.o: nbproject/Makefile-${CND_CONF}.mk gota.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/gota.o gota.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/jogo_coruja.o: nbproject/Makefile-${CND_CONF}.mk jogo_coruja.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/jogo_coruja.o jogo_coruja.cpp

${OBJECTDIR}/item_madeira.o: nbproject/Makefile-${CND_CONF}.mk item_madeira.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/item_madeira.o item_madeira.cpp

${OBJECTDIR}/jogo_morcego.o: nbproject/Makefile-${CND_CONF}.mk jogo_morcego.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/jogo_morcego.o jogo_morcego.cpp

${OBJECTDIR}/rato.o: nbproject/Makefile-${CND_CONF}.mk rato.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/rato.o rato.cpp

${OBJECTDIR}/animal.o: nbproject/Makefile-${CND_CONF}.mk animal.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/animal.o animal.cpp

${OBJECTDIR}/atoxado.o: nbproject/Makefile-${CND_CONF}.mk atoxado.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/atoxado.o atoxado.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/torquere

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
