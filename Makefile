PROJECT_NAME = ScrubbyScramble
GBDK_HOME = ../gbdk
ROMUSAGE_HOME = ../romusage

ASEPRITE_LINUX = aseprite
EMULATOR_LINUX = flatpak run ca._0ldsk00l.Nestopia

ASEPRITE_MAC = /Applications/Aseprite.app/Contents/MacOS/aseprite
EMULATOR_MAC = open -a OpenEmu


# -------  Don't edit under this line  -------

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    ASEPRITE = $(ASEPRITE_LINUX)
    EMULATOR = $(EMULATOR_LINUX)
else ifeq ($(UNAME_S),Darwin)
    ASEPRITE = $(ASEPRITE_MAC)
    EMULATOR = $(EMULATOR_MAC)
endif

LCC = $(GBDK_HOME)/bin/lcc -mmos6502:nes


SRCDIR     = src
LIBDIR     = src/lib
RESDIR     = res
RESSRCDIR  = res/src
OBJDIR     = obj
GBDK_BIN   = $(GBDK_HOME)/bin
BINS	   = $(OBJDIR)/$(PROJECT_NAME).nes
CSOURCES   = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c))) \
             $(foreach dir,$(LIBDIR),$(notdir $(wildcard $(dir)/*.c))) \
             $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/*.c))) \
             $(foreach dir,$(WORLDDIR),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s)))
OBJS       = $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.s=$(OBJDIR)/%.o)

all: prepare $(BINS)


# Compile .c files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	$(LCC) -c -o $@ $<

# Compile .c files in "src/lib/" to .o object files
$(OBJDIR)/%.o:	$(LIBDIR)/%.c
	$(LCC) -c -o $@ $<

# Compile .c files in "res/" to .o object files
$(OBJDIR)/%.o:	$(RESDIR)/%.c
	$(LCC) -c -o $@ $<

# Compile .s assembly files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.s
	$(LCC) -c -o $@ $<

# If needed, compile .c files in "src/" to .s assembly files
# (not required if .c is compiled directly to .o)
$(OBJDIR)/%.s:	$(SRCDIR)/%.c
	$(LCC) -S -o $@ $<

# Link the compiled object files into a .gb ROM file
$(BINS):	$(OBJS)
	$(LCC) -o $(BINS) $(OBJS)

prepare:
	mkdir -p $(OBJDIR)

# Convert Aseprite files to PNGs
aseprite:
	for i in $(RESSRCDIR)/*.8x8.aseprite;  do $(ASEPRITE) --batch $$i --save-as $(RESDIR)/`basename $$i .aseprite`.png; done
	for i in $(RESSRCDIR)/*.8x16.aseprite; do $(ASEPRITE) --batch $$i --save-as $(RESDIR)/`basename $$i .aseprite`.png; done

# Convert PNGs to tile code
tiles:
	for i in $(RESDIR)/*.8x8.png;  do $(GBDK_BIN)/png2asset $$i -spr8x8  -tiles_only -keep_palette_order -keep_duplicate_tiles -sprite_no_optimize -noflip -no_palettes; done
	for i in $(RESDIR)/*.8x16.png; do $(GBDK_BIN)/png2asset $$i -spr8x16 -tiles_only -keep_palette_order -keep_duplicate_tiles -sprite_no_optimize -noflip -no_palettes; done

assets: \
	aseprite \
	tiles

clean:
	rm -f $(OBJDIR)/*.*
	rm -f $(RESDIR)/*.c $(RESDIR)/*.h

run: \
	all \
	emulate

emulate:
	$(EMULATOR) $(BINS)

romusage:
	 $(ROMUSAGE_HOME)/bin/romusage ../$(PROJECT_NAME)/$(OBJDIR)/$(PROJECT_NAME).noi -p:NES1 -smROM -g

run-clean: \
	clean \
	tiles \
	all \
	run
