# Debug options (debug or release)
DEBUG_LEVEL = release
# Toolchain prefix
TOOLCHAIN_PREFIX = arm-linux-

# target
EXE = $(OUTPATH)/CamTest
# source
SRCS = \
main.cpp
SYS_SRCS = \
ela_fb.c	\
ela_camera.cpp

# libs
LIBS :=
LIBS_PATH :=
# include path
INCDIR  = -I"../../Libraries/inc"

# build path
ifeq ($(DEBUG_LEVEL), debug)
OUTDIR = Debug
else
OUTDIR = Release
endif

OUTPATH = ./$(OUTDIR)
OBJPATH = $(OUTPATH)/obj
DEPPATH = $(OUTPATH)/dep

# init objects
OBJS = $(addprefix $(OBJPATH)/, $(addsuffix .o, $(basename $(SRCS))))
DEPS = $(addprefix $(DEPPATH)/, $(addsuffix .d, $(basename $(SRCS))))
SYS_OBJS = $(addprefix $(OBJPATH)/, $(addsuffix .o, $(basename $(SYS_SRCS))))
SYS_DEPS = $(addprefix $(DEPPATH)/, $(addsuffix .d, $(basename $(SYS_SRCS))))

# toolchain select
CC  = $(TOOLCHAIN_PREFIX)gcc
CXX = $(TOOLCHAIN_PREFIX)g++
AS  = $(TOOLCHAIN_PREFIX)gcc
AR  = $(TOOLCHAIN_PREFIX)ar
LD  = $(TOOLCHAIN_PREFIX)g++
# compiler optimize
ifeq ($(DEBUG_LEVEL), debug)
OPTIMIZE = -O0 -g3 -gdwarf-2
else
OPTIMIZE = -O2 -g1 -gdwarf-2											# Do NOT use -O3 and -Os
endif										    						# -Os is not align for function
																		# loop and jump.																		
# depends and compiler parameter (cplusplus in kernel MUST NOT use exceptions and rtti)
DEPENDFLAG  = -MM
CXX_EXCEPT  = -fno-exceptions -fno-rtti
COMMONFLAGS = $(OPTIMIZE) -Wall -fmessage-length=0 -fsigned-char -fno-short-enums
CFLAGS      = $(INCDIR) $(COMMONFLAGS) -fPIC -c
CXXFLAGS    = $(INCDIR) $(CXX_EXCEPT) $(COMMONFLAGS) -fPIC -c
ARFLAGS     = -r
# define some useful variable
DEPEND          = $(CC)  $(DEPENDFLAG) $(CFLAGS)
DEPEND.d        = $(subst -g ,,$(DEPEND))
COMPILE.c       = $(CC)  $(CFLAGS)
COMPILE.cxx     = $(CXX) $(CXXFLAGS)

# create depends files
$(DEPPATH)/%.d: %.c
		@echo creating $@
		@if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
		@rm -f $@; \
		echo -n '$@ $(addprefix $(OBJPATH)/, $(dir $<))' > $@; \
		$(DEPEND.d) $< >> $@ || rm -f $@; exit;
$(DEPPATH)/%.d: %.cpp
		@echo creating $@
		@if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
		@rm -f $@; \
		echo -n '$@ $(addprefix $(OBJPATH)/, $(dir $<))' > $@; \
		$(DEPEND.d) $< >> $@ || rm -f $@; exit;
$(DEPPATH)/%.d: ../../Libraries/src/%.c
		@echo creating $@
		@if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
		@rm -f $@; \
		echo -n '$@ $(OBJPATH)/' > $@; \
		$(DEPEND.d) $< >> $@ || rm -f $@; exit;
$(DEPPATH)/%.d: ../../Libraries/src/%.cpp
		@echo creating $@
		@if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
		@rm -f $@; \
		echo -n '$@ $(OBJPATH)/' > $@; \
		$(DEPEND.d) $< >> $@ || rm -f $@; exit;
# compile source files
$(OBJPATH)/%.o: %.c
		@if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
		$(COMPILE.c) $< -o $@
$(OBJPATH)/%.o: %.cpp
		@if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
		$(COMPILE.cxx) $< -o $@		
$(OBJPATH)/%.o: ../../Libraries/src/%.c
		@if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
		$(COMPILE.c) $< -o $@
$(OBJPATH)/%.o: ../../Libraries/src/%.cpp
		@if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
		$(COMPILE.cxx) $< -o $@
	
# Target
all: $(EXE)
	@echo create "$(EXE)" success.

$(EXE): $(OBJS) $(SYS_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	$(LD) -o $(EXE) $(OBJS) $(SYS_OBJS) \
	$(LIBS_PATH) $(LIBS) -lm -lgcc 
	@echo 'Finished building target: $@'
	@echo ' '

# Clean
clean:
	-rm -rf $(EXE)
	-rm -rf $(OBJS)
	-rm -rf $(OBJPATH)
	-rm -rf $(DEPPATH)
clean_project:
	-rm -rf $(OUTPATH)

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(DEPS)),)
sinclude $(DEPS)
endif
ifneq ($(strip $(SYS_DEPS)),)
sinclude $(SYS_DEPS)
endif
endif

.PHONY: all clean dependents clean_project
.SECONDARY:
