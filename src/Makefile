#
# OMNeT++/OMNEST Makefile for $(LIB_PREFIX)ndp
#
# This file was generated with the command:
#  opp_makemake --make-so -f --deep -KINET4_PROJ=../../inet4 -DINET_IMPORT -I$$\(INET4_PROJ\)/src -L$$\(INET4_PROJ\)/src -lINET$$\(D\)
#

# Name of target to be created (-o option)
TARGET = $(LIB_PREFIX)ndp$(D)$(SHARED_LIB_SUFFIX)
TARGET_DIR = .

# C++ include paths (with -I)
INCLUDE_PATH = -I$(INET4_PROJ)/src

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = $(LDFLAG_LIBPATH)$(INET4_PROJ)/src  -lINET$(D)

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/application/base/ApplicationBaseNdp.o \
    $O/application/ndpapp/NdpAppBase.o \
    $O/application/ndpapp/NdpBasicClientApp.o \
    $O/application/ndpapp/NdpEchoApp.o \
    $O/application/ndpapp/NdpServerHostApp.o \
    $O/application/ndpapp/NdpSinkApp.o \
    $O/common/MessageDispatcherNdp.o \
    $O/common/ProtocolGroupNdp.o \
    $O/common/ProtocolNdp.o \
    $O/common/ResultFiltersThroughput.o \
    $O/common/TopologyEcmp.o \
    $O/common/queue/NDPQueue.o \
    $O/common/scheduler/CentralSchedulerNdp.o \
    $O/networklayer/configurator/base/NetworkConfiguratorBaseEcmp.o \
    $O/networklayer/configurator/ipv4/Ipv4NetworkConfiguratorEcmp.o \
    $O/networklayer/configurator/ipv4/Ipv4NodeConfiguratorEcmp.o \
    $O/networklayer/ipv4/IcmpNdp.o \
    $O/networklayer/ipv4/Igmpv2Ndp.o \
    $O/networklayer/ipv4/Ipv4FragBufNdp.o \
    $O/networklayer/ipv4/Ipv4HeaderNdp.o \
    $O/networklayer/ipv4/Ipv4NatTableNdp.o \
    $O/networklayer/ipv4/Ipv4Ndp.o \
    $O/networklayer/ipv4/Ipv4NetworkLayerNdp.o \
    $O/networklayer/ipv4/Ipv4RoutingTableEcmp.o \
    $O/networklayer/ipv4/RoutingTableParserEcmp.o \
    $O/transportlayer/Ndp/Ndp.o \
    $O/transportlayer/Ndp/NDPConnectionBase.o \
    $O/transportlayer/Ndp/NDPConnectionEventProc.o \
    $O/transportlayer/Ndp/NDPConnectionRcvSegment.o \
    $O/transportlayer/Ndp/NDPConnectionUtil.o \
    $O/transportlayer/Ndp/NDPReceiveQueue.o \
    $O/transportlayer/Ndp/NDPSendQueue.o \
    $O/transportlayer/Ndp/flavours/DumbNDP.o \
    $O/transportlayer/Ndp/flavours/NDPBaseAlg.o \
    $O/transportlayer/Ndp/flavours/NDPSegmentTransmitInfoList.o \
    $O/transportlayer/Ndp/ndp_common/NdpHeader.o \
    $O/transportlayer/common/L4ToolsNdp.o \
    $O/transportlayer/contract/ndp/NDPSocket.o \
    $O/application/base/ApplicationPacketNdp_m.o \
    $O/application/ndpapp/GenericAppMsgNdp_m.o \
    $O/common/ProtocolNdp_m.o \
    $O/networklayer/ipv4/Ipv4HeaderNdp_m.o \
    $O/networklayer/ipv4/Ipv4OptionsTagNdp_m.o \
    $O/transportlayer/Ndp/NDPConnection_m.o \
    $O/transportlayer/Ndp/ndp_common/NdpHeader_m.o \
    $O/transportlayer/contract/ndp/NDPCommand_m.o

# Message files
MSGFILES = \
    application/base/ApplicationPacketNdp.msg \
    application/ndpapp/GenericAppMsgNdp.msg \
    common/ProtocolNdp.msg \
    networklayer/ipv4/Ipv4HeaderNdp.msg \
    networklayer/ipv4/Ipv4OptionsTagNdp.msg \
    transportlayer/Ndp/NDPConnection.msg \
    transportlayer/Ndp/ndp_common/NdpHeader.msg \
    transportlayer/contract/ndp/NDPCommand.msg

# SM files
SMFILES =

# Other makefile variables (-K)
INET4_PROJ=../../inet4

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIBS = -loppenvir$D $(KERNEL_LIBS) $(SYS_LIBS)
ifneq ($(TOOLCHAIN_NAME),clangc2)
LIBS += -Wl,-rpath,$(abspath $(INET4_PROJ)/src)
endif

COPTS = $(CFLAGS) $(IMPORT_DEFINES) -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# inserted from file 'makefrag':
MSGC:=$(MSGC) --msg6

# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET_DIR)/$(TARGET)

$(TARGET_DIR)/% :: $O/%
	@mkdir -p $(TARGET_DIR)
	$(Q)$(LN) $< $@
ifeq ($(TOOLCHAIN_NAME),clangc2)
	$(Q)-$(LN) $(<:%.dll=%.lib) $(@:%.dll=%.lib)
endif

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile $(CONFIGFILE)
	@$(MKPATH) $O
	@echo Creating shared library: $@
	$(Q)$(SHLIB_LD) -o $O/$(TARGET) $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS) $(LDFLAGS)
	$(Q)$(SHLIB_POSTPROCESS) $O/$(TARGET)

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE) | msgheaders smheaders
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc -MD -MP -MF $O/$(basename $<)_m.h.d $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning $(TARGET)
	$(Q)-rm -rf $O
	$(Q)-rm -f $(TARGET_DIR)/$(TARGET)
	$(Q)-rm -f $(TARGET_DIR)/$(TARGET:%.dll=%.lib)
	$(Q)-rm -f $(call opp_rwildcard, . , *_m.cc *_m.h *_sm.cc *_sm.h)

cleanall:
	$(Q)$(MAKE) -s clean MODE=release
	$(Q)$(MAKE) -s clean MODE=debug
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

# include all dependencies
-include $(OBJS:%=%.d) $(MSGFILES:%.msg=$O/%_m.h.d)
