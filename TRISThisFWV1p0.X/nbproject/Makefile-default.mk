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
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TRISThisFWV1p0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TRISThisFWV1p0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=source/mainv1p0.c source/general_exception_handler.c source/I2C_Bus_Master.c source/tick.c source/delay.c source/LED.c source/PAC1710.c source/MCP4461.c source/commsToRPi.c source/TRISThis.c source/TRISThisDigital.c source/TRISThisAnalog.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/source/mainv1p0.o ${OBJECTDIR}/source/general_exception_handler.o ${OBJECTDIR}/source/I2C_Bus_Master.o ${OBJECTDIR}/source/tick.o ${OBJECTDIR}/source/delay.o ${OBJECTDIR}/source/LED.o ${OBJECTDIR}/source/PAC1710.o ${OBJECTDIR}/source/MCP4461.o ${OBJECTDIR}/source/commsToRPi.o ${OBJECTDIR}/source/TRISThis.o ${OBJECTDIR}/source/TRISThisDigital.o ${OBJECTDIR}/source/TRISThisAnalog.o
POSSIBLE_DEPFILES=${OBJECTDIR}/source/mainv1p0.o.d ${OBJECTDIR}/source/general_exception_handler.o.d ${OBJECTDIR}/source/I2C_Bus_Master.o.d ${OBJECTDIR}/source/tick.o.d ${OBJECTDIR}/source/delay.o.d ${OBJECTDIR}/source/LED.o.d ${OBJECTDIR}/source/PAC1710.o.d ${OBJECTDIR}/source/MCP4461.o.d ${OBJECTDIR}/source/commsToRPi.o.d ${OBJECTDIR}/source/TRISThis.o.d ${OBJECTDIR}/source/TRISThisDigital.o.d ${OBJECTDIR}/source/TRISThisAnalog.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/source/mainv1p0.o ${OBJECTDIR}/source/general_exception_handler.o ${OBJECTDIR}/source/I2C_Bus_Master.o ${OBJECTDIR}/source/tick.o ${OBJECTDIR}/source/delay.o ${OBJECTDIR}/source/LED.o ${OBJECTDIR}/source/PAC1710.o ${OBJECTDIR}/source/MCP4461.o ${OBJECTDIR}/source/commsToRPi.o ${OBJECTDIR}/source/TRISThis.o ${OBJECTDIR}/source/TRISThisDigital.o ${OBJECTDIR}/source/TRISThisAnalog.o

# Source Files
SOURCEFILES=source/mainv1p0.c source/general_exception_handler.c source/I2C_Bus_Master.c source/tick.c source/delay.c source/LED.c source/PAC1710.c source/MCP4461.c source/commsToRPi.c source/TRISThis.c source/TRISThisDigital.c source/TRISThisAnalog.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/TRISThisFWV1p0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/source/mainv1p0.o: source/mainv1p0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/mainv1p0.o.d 
	@${RM} ${OBJECTDIR}/source/mainv1p0.o 
	@${FIXDEPS} "${OBJECTDIR}/source/mainv1p0.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/mainv1p0.o.d" -o ${OBJECTDIR}/source/mainv1p0.o source/mainv1p0.c   
	
${OBJECTDIR}/source/general_exception_handler.o: source/general_exception_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/general_exception_handler.o.d 
	@${RM} ${OBJECTDIR}/source/general_exception_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/source/general_exception_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/general_exception_handler.o.d" -o ${OBJECTDIR}/source/general_exception_handler.o source/general_exception_handler.c   
	
${OBJECTDIR}/source/I2C_Bus_Master.o: source/I2C_Bus_Master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/I2C_Bus_Master.o.d 
	@${RM} ${OBJECTDIR}/source/I2C_Bus_Master.o 
	@${FIXDEPS} "${OBJECTDIR}/source/I2C_Bus_Master.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/I2C_Bus_Master.o.d" -o ${OBJECTDIR}/source/I2C_Bus_Master.o source/I2C_Bus_Master.c   
	
${OBJECTDIR}/source/tick.o: source/tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/tick.o.d 
	@${RM} ${OBJECTDIR}/source/tick.o 
	@${FIXDEPS} "${OBJECTDIR}/source/tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/tick.o.d" -o ${OBJECTDIR}/source/tick.o source/tick.c   
	
${OBJECTDIR}/source/delay.o: source/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/delay.o.d 
	@${RM} ${OBJECTDIR}/source/delay.o 
	@${FIXDEPS} "${OBJECTDIR}/source/delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/delay.o.d" -o ${OBJECTDIR}/source/delay.o source/delay.c   
	
${OBJECTDIR}/source/LED.o: source/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/LED.o.d 
	@${RM} ${OBJECTDIR}/source/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/source/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/LED.o.d" -o ${OBJECTDIR}/source/LED.o source/LED.c   
	
${OBJECTDIR}/source/PAC1710.o: source/PAC1710.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/PAC1710.o.d 
	@${RM} ${OBJECTDIR}/source/PAC1710.o 
	@${FIXDEPS} "${OBJECTDIR}/source/PAC1710.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/PAC1710.o.d" -o ${OBJECTDIR}/source/PAC1710.o source/PAC1710.c   
	
${OBJECTDIR}/source/MCP4461.o: source/MCP4461.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/MCP4461.o.d 
	@${RM} ${OBJECTDIR}/source/MCP4461.o 
	@${FIXDEPS} "${OBJECTDIR}/source/MCP4461.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/MCP4461.o.d" -o ${OBJECTDIR}/source/MCP4461.o source/MCP4461.c   
	
${OBJECTDIR}/source/commsToRPi.o: source/commsToRPi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/commsToRPi.o.d 
	@${RM} ${OBJECTDIR}/source/commsToRPi.o 
	@${FIXDEPS} "${OBJECTDIR}/source/commsToRPi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/commsToRPi.o.d" -o ${OBJECTDIR}/source/commsToRPi.o source/commsToRPi.c   
	
${OBJECTDIR}/source/TRISThis.o: source/TRISThis.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/TRISThis.o.d 
	@${RM} ${OBJECTDIR}/source/TRISThis.o 
	@${FIXDEPS} "${OBJECTDIR}/source/TRISThis.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/TRISThis.o.d" -o ${OBJECTDIR}/source/TRISThis.o source/TRISThis.c   
	
${OBJECTDIR}/source/TRISThisDigital.o: source/TRISThisDigital.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/TRISThisDigital.o.d 
	@${RM} ${OBJECTDIR}/source/TRISThisDigital.o 
	@${FIXDEPS} "${OBJECTDIR}/source/TRISThisDigital.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/TRISThisDigital.o.d" -o ${OBJECTDIR}/source/TRISThisDigital.o source/TRISThisDigital.c   
	
${OBJECTDIR}/source/TRISThisAnalog.o: source/TRISThisAnalog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/TRISThisAnalog.o.d 
	@${RM} ${OBJECTDIR}/source/TRISThisAnalog.o 
	@${FIXDEPS} "${OBJECTDIR}/source/TRISThisAnalog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/TRISThisAnalog.o.d" -o ${OBJECTDIR}/source/TRISThisAnalog.o source/TRISThisAnalog.c   
	
else
${OBJECTDIR}/source/mainv1p0.o: source/mainv1p0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/mainv1p0.o.d 
	@${RM} ${OBJECTDIR}/source/mainv1p0.o 
	@${FIXDEPS} "${OBJECTDIR}/source/mainv1p0.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/mainv1p0.o.d" -o ${OBJECTDIR}/source/mainv1p0.o source/mainv1p0.c   
	
${OBJECTDIR}/source/general_exception_handler.o: source/general_exception_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/general_exception_handler.o.d 
	@${RM} ${OBJECTDIR}/source/general_exception_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/source/general_exception_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/general_exception_handler.o.d" -o ${OBJECTDIR}/source/general_exception_handler.o source/general_exception_handler.c   
	
${OBJECTDIR}/source/I2C_Bus_Master.o: source/I2C_Bus_Master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/I2C_Bus_Master.o.d 
	@${RM} ${OBJECTDIR}/source/I2C_Bus_Master.o 
	@${FIXDEPS} "${OBJECTDIR}/source/I2C_Bus_Master.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/I2C_Bus_Master.o.d" -o ${OBJECTDIR}/source/I2C_Bus_Master.o source/I2C_Bus_Master.c   
	
${OBJECTDIR}/source/tick.o: source/tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/tick.o.d 
	@${RM} ${OBJECTDIR}/source/tick.o 
	@${FIXDEPS} "${OBJECTDIR}/source/tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/tick.o.d" -o ${OBJECTDIR}/source/tick.o source/tick.c   
	
${OBJECTDIR}/source/delay.o: source/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/delay.o.d 
	@${RM} ${OBJECTDIR}/source/delay.o 
	@${FIXDEPS} "${OBJECTDIR}/source/delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/delay.o.d" -o ${OBJECTDIR}/source/delay.o source/delay.c   
	
${OBJECTDIR}/source/LED.o: source/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/LED.o.d 
	@${RM} ${OBJECTDIR}/source/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/source/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/LED.o.d" -o ${OBJECTDIR}/source/LED.o source/LED.c   
	
${OBJECTDIR}/source/PAC1710.o: source/PAC1710.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/PAC1710.o.d 
	@${RM} ${OBJECTDIR}/source/PAC1710.o 
	@${FIXDEPS} "${OBJECTDIR}/source/PAC1710.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/PAC1710.o.d" -o ${OBJECTDIR}/source/PAC1710.o source/PAC1710.c   
	
${OBJECTDIR}/source/MCP4461.o: source/MCP4461.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/MCP4461.o.d 
	@${RM} ${OBJECTDIR}/source/MCP4461.o 
	@${FIXDEPS} "${OBJECTDIR}/source/MCP4461.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/MCP4461.o.d" -o ${OBJECTDIR}/source/MCP4461.o source/MCP4461.c   
	
${OBJECTDIR}/source/commsToRPi.o: source/commsToRPi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/commsToRPi.o.d 
	@${RM} ${OBJECTDIR}/source/commsToRPi.o 
	@${FIXDEPS} "${OBJECTDIR}/source/commsToRPi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/commsToRPi.o.d" -o ${OBJECTDIR}/source/commsToRPi.o source/commsToRPi.c   
	
${OBJECTDIR}/source/TRISThis.o: source/TRISThis.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/TRISThis.o.d 
	@${RM} ${OBJECTDIR}/source/TRISThis.o 
	@${FIXDEPS} "${OBJECTDIR}/source/TRISThis.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/TRISThis.o.d" -o ${OBJECTDIR}/source/TRISThis.o source/TRISThis.c   
	
${OBJECTDIR}/source/TRISThisDigital.o: source/TRISThisDigital.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/TRISThisDigital.o.d 
	@${RM} ${OBJECTDIR}/source/TRISThisDigital.o 
	@${FIXDEPS} "${OBJECTDIR}/source/TRISThisDigital.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/TRISThisDigital.o.d" -o ${OBJECTDIR}/source/TRISThisDigital.o source/TRISThisDigital.c   
	
${OBJECTDIR}/source/TRISThisAnalog.o: source/TRISThisAnalog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/TRISThisAnalog.o.d 
	@${RM} ${OBJECTDIR}/source/TRISThisAnalog.o 
	@${FIXDEPS} "${OBJECTDIR}/source/TRISThisAnalog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/source/TRISThisAnalog.o.d" -o ${OBJECTDIR}/source/TRISThisAnalog.o source/TRISThisAnalog.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/TRISThisFWV1p0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TRISThisFWV1p0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/TRISThisFWV1p0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TRISThisFWV1p0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/TRISThisFWV1p0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
