#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SoftTimer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SoftTimer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/TTimer.c src/error.c src/interrupt.c src/main.c src/sysLib.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/TTimer.o ${OBJECTDIR}/src/error.o ${OBJECTDIR}/src/interrupt.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/sysLib.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/TTimer.o.d ${OBJECTDIR}/src/error.o.d ${OBJECTDIR}/src/interrupt.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/sysLib.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/TTimer.o ${OBJECTDIR}/src/error.o ${OBJECTDIR}/src/interrupt.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/sysLib.o

# Source Files
SOURCEFILES=src/TTimer.c src/error.c src/interrupt.c src/main.c src/sysLib.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/SoftTimer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F26J50
MP_PROCESSOR_OPTION_LD=18f26j50
MP_LINKER_DEBUG_OPTION=  -u_DEBUGSTACK
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/TTimer.o: src/TTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/TTimer.o.d 
	@${RM} ${OBJECTDIR}/src/TTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -I"src" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/TTimer.o   src/TTimer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/TTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/src/TTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/error.o: src/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/error.o.d 
	@${RM} ${OBJECTDIR}/src/error.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -I"src" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/error.o   src/error.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/error.o 
	@${FIXDEPS} "${OBJECTDIR}/src/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/interrupt.o: src/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/interrupt.o.d 
	@${RM} ${OBJECTDIR}/src/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -I"src" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/interrupt.o   src/interrupt.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/src/interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -I"src" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/main.o   src/main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/sysLib.o: src/sysLib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/sysLib.o.d 
	@${RM} ${OBJECTDIR}/src/sysLib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -I"src" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/sysLib.o   src/sysLib.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/sysLib.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sysLib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/src/TTimer.o: src/TTimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/TTimer.o.d 
	@${RM} ${OBJECTDIR}/src/TTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"src" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/TTimer.o   src/TTimer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/TTimer.o 
	@${FIXDEPS} "${OBJECTDIR}/src/TTimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/error.o: src/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/error.o.d 
	@${RM} ${OBJECTDIR}/src/error.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"src" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/error.o   src/error.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/error.o 
	@${FIXDEPS} "${OBJECTDIR}/src/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/interrupt.o: src/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/interrupt.o.d 
	@${RM} ${OBJECTDIR}/src/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"src" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/interrupt.o   src/interrupt.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/src/interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"src" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/main.o   src/main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/sysLib.o: src/sysLib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/sysLib.o.d 
	@${RM} ${OBJECTDIR}/src/sysLib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"src" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/sysLib.o   src/sysLib.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/sysLib.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sysLib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/SoftTimer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map" -i  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_SIMULATOR=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/SoftTimer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    -i
else
dist/${CND_CONF}/${IMAGE_TYPE}/SoftTimer.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map" -i  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/SoftTimer.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    -i
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
